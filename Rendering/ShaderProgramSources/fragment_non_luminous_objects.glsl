#version 330 core

// ===== inputs from vertex shader =====
in vec3 v_FragPos;
in vec3 v_Normal;
in vec4 v_FragPosLightSpace; // from u_lightSpaceMatrix in the VS

// ===== material =====
uniform vec3  u_ambientMaterial;
uniform vec3  u_diffuseMaterial;
uniform vec3  u_specularMaterial;
uniform float u_shininessMaterial;

// ===== camera =====
uniform vec3 u_viewPos;

// ===== directional lights (already in your renderer) =====
const int MAX_DIR_LIGHTS = 8;
uniform int   u_numLights;
uniform vec3  u_directionLight[MAX_DIR_LIGHTS];
uniform vec3  u_ambientLight[MAX_DIR_LIGHTS];
uniform vec3  u_diffuseLight[MAX_DIR_LIGHTS];
uniform vec3  u_specularLight[MAX_DIR_LIGHTS];

// ===== point lights (new) =====
const int MAX_POINT_LIGHTS = 8;
uniform int   u_numPointLights;
uniform vec3  u_pointLightPositions[MAX_POINT_LIGHTS];
uniform vec3  u_pointLightAmbient[MAX_POINT_LIGHTS];
uniform vec3  u_pointLightDiffuse[MAX_POINT_LIGHTS];
uniform vec3  u_pointLightSpecular[MAX_POINT_LIGHTS];
uniform float u_pointLightConstant[MAX_POINT_LIGHTS];
uniform float u_pointLightLinear[MAX_POINT_LIGHTS];
uniform float u_pointLightQuadratic[MAX_POINT_LIGHTS];
uniform float u_pointLightFarPlane[MAX_POINT_LIGHTS]; // per-light far for cube depth normalization

// ===== shadows toggles + samplers (NEW NAMES) =====
uniform int u_hasDirShadow;    // 0/1
uniform int u_hasPointShadow;  // 0/1
uniform sampler2D u_shadowMap2D;   // directional depth map (2D)
uniform samplerCubeShadow u_shadowCube;   // point-light cubemap depth (compare mode ON)

// ===== output =====
out vec4 FragColor;

// --- helpers ---
float DirShadowVisibility(vec4 fragPosLightSpace, vec3 normal, vec3 Ldir)
{
    // project to [0,1]
    vec3 projCoords = fragPosLightSpace.xyz / max(fragPosLightSpace.w, 1e-6);
    projCoords = projCoords * 0.5 + 0.5;

    // outside light frustum -> lit
    if (projCoords.z > 1.0)
        return 1.0;

    float bias = max(0.002 * (1.0 - dot(normalize(normal), normalize(-Ldir))), 0.0005);

    // 3x3 PCF
    float visibility = 0.0;
    vec2 texel = 1.0 / textureSize(u_shadowMap2D, 0);
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float closest = texture(u_shadowMap2D, projCoords.xy + vec2(x, y) * texel).r;
            float current = projCoords.z - bias;
            visibility += (current <= closest) ? 1.0 : 0.0;
        }
    }
    visibility /= 9.0;
    return visibility; // 1 = lit, 0 = shadow
}

float PointShadowVisibility(int i, vec3 fragPos, vec3 normal)
{
    // Only the first point light has a bound shadow cubemap in your C++ right now.
    if (i != 0) return 1.0;

    vec3 L = fragPos - u_pointLightPositions[i];
    float dist = length(L);
    vec3  Ldir = L / max(dist, 1e-6);

    // simple normal-based bias
    float bias = 0.002;

    // samplerCubeShadow expects vec4(dir, refDepth)
    float ref = (dist - bias) / u_pointLightFarPlane[i];
    // visibility: 1 = lit, 0 = shadow
    float visibility = texture(u_shadowCube, vec4(Ldir, ref));
    return visibility;
}

vec3 ApplyPhong(vec3 N, vec3 V, vec3 Ldir, vec3 lightAmbient, vec3 lightDiffuse, vec3 lightSpec, float visibility)
{
    vec3 R = reflect(-Ldir, N);
    float NdotL = max(dot(N, Ldir), 0.0);
    float spec  = pow(max(dot(R, V), 0.0), u_shininessMaterial);

    vec3 ambient = u_ambientMaterial * lightAmbient;
    vec3 diffuse = u_diffuseMaterial * lightDiffuse * NdotL;
    vec3 specula = u_specularMaterial * lightSpec * spec;

    // darken diffuse+spec with shadow; keep ambient
    return ambient + visibility * (diffuse + specula);
}

void main()
{
    vec3 N = normalize(v_Normal);
    vec3 V = normalize(u_viewPos - v_FragPos);

    vec3 color = vec3(0.0);

    // --- directional lights ---
    for (int i = 0; i < min(u_numLights, MAX_DIR_LIGHTS); ++i)
    {
        vec3 Ldir = normalize(-u_directionLight[i]); // light points *toward* the scene
        float vis = (u_hasDirShadow == 1)
            ? DirShadowVisibility(v_FragPosLightSpace, N, Ldir)
            : 1.0;

        color += ApplyPhong(N, V, Ldir, u_ambientLight[i], u_diffuseLight[i], u_specularLight[i], vis);
    }

    // --- point lights ---
    for (int i = 0; i < min(u_numPointLights, MAX_POINT_LIGHTS); ++i)
    {
        vec3 L = u_pointLightPositions[i] - v_FragPos;
        float d = length(L);
        vec3  Ldir = L / max(d, 1e-6);

        float att = 1.0 / (u_pointLightConstant[i] + u_pointLightLinear[i] * d + u_pointLightQuadratic[i] * d * d);

        float vis = (u_hasPointShadow == 1) ? PointShadowVisibility(i, v_FragPos, N) : 1.0;

        vec3 contrib = ApplyPhong(N, V, Ldir,
                                  u_pointLightAmbient[i],
                                  u_pointLightDiffuse[i],
                                  u_pointLightSpecular[i],
                                  vis);

        color += contrib * att;
    }

    FragColor = vec4(color, 1.0);
}

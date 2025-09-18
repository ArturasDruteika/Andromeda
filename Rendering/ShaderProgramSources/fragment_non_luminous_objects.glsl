#version 330 core

in vec3 v_FragPos;
in vec3 v_Normal;
in vec4 v_FragPosLightSpace;

out vec4 outColor;

// ===== material =====
uniform vec3  u_materialAmbient;
uniform vec3  u_materialDiffuse;
uniform vec3  u_materialSpecular;
uniform float u_materialShininess;

// ===== camera =====
uniform vec3 u_cameraPosWS;

// ===== toggles =====
uniform int u_hasDirShadows;
uniform int u_hasPointShadows;

// ===== shadow samplers =====
uniform sampler2D         u_dirShadowMap;     // 2D depth map for directional
uniform samplerCubeShadow u_pointShadowCube;  // cubemap depth for point light

// ===== directional lights =====
uniform int      u_numDirLights;
uniform vec3     u_dirLightDirections[8];
uniform vec3     u_dirLightAmbient[8];
uniform vec3     u_dirLightDiffuse[8];
uniform vec3     u_dirLightSpecular[8];

// ===== point lights =====
uniform int   u_numPointLights;
uniform vec3  u_pointLightPositions[16];
uniform vec3  u_pointLightAmbient[16];
uniform vec3  u_pointLightDiffuse[16];
uniform vec3  u_pointLightSpecular[16];
uniform float u_pointLightConstant[16];
uniform float u_pointLightLinear[16];
uniform float u_pointLightQuadratic[16];
uniform float u_pointLightFarPlanes[16]; // far plane per point light (for visibility compare)

// ===== helpers =====
float dirShadowVisibility(vec4 fragPosLightSpace, vec3 normalWS, vec3 lightDirWS)
{
    // Transform to NDC
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    // Outside the shadow map => lit
    if (projCoords.z > 1.0) return 1.0;

    float bias = max(0.0005, 0.001 * (1.0 - dot(normalWS, -lightDirWS)));

    // 3x3 PCF
    float visibility = 0.0;
    vec2 texelSize = 1.0 / vec2(textureSize(u_dirShadowMap, 0));
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(u_dirShadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            float current  = projCoords.z - bias;
            visibility += current <= pcfDepth ? 1.0 : 0.0;
        }
    }
    visibility /= 9.0;
    return visibility;
}

float pointShadowVisibilitySingle(vec3 fragPosWS, vec3 lightPosWS, float farPlane)
{
    // Vector from light to fragment
    vec3 lightToFrag = fragPosWS - lightPosWS;
    float dist = length(lightToFrag);

    // samplerCubeShadow expects a vec4(dir, compareDepth)
    float shadow = texture(u_pointShadowCube, vec4(normalize(lightToFrag), dist / farPlane));

    return shadow; // 1 = lit, 0 = shadow
}

vec3 applyPhong(vec3 normalWS, vec3 viewDirWS, vec3 lightDirWS,
                vec3 ambient, vec3 diffuse, vec3 specular, float shadowVisibility)
{
    vec3 n = normalize(normalWS);
    vec3 l = normalize(-lightDirWS); // lightDirWS points FROM light TO scene
    vec3 v = normalize(viewDirWS);
    vec3 r = reflect(-l, n);

    float NdotL = max(dot(n, l), 0.0);
    vec3  ambientTerm  = ambient * u_materialAmbient;
    vec3  diffuseTerm  = diffuse * u_materialDiffuse * NdotL;
    float specStrength = pow(max(dot(v, r), 0.0), max(u_materialShininess, 0.0001));
    vec3  specularTerm = specular * u_materialSpecular * specStrength;

    // Apply shadowing to direct lighting terms (not ambient)
    return ambientTerm + shadowVisibility * (diffuseTerm + specularTerm);
}

void main()
{
    vec3 normalWS = normalize(v_Normal);
    vec3 viewDir  = normalize(u_cameraPosWS - v_FragPos);
    vec3 accumColor = vec3(0.0);

    // ----- Directional lights -----
    for (int i = 0; i < u_numDirLights; ++i)
    {
        vec3 lightDirWS = normalize(u_dirLightDirections[i]);
        float visibility = (u_hasDirShadows == 1)
            ? dirShadowVisibility(v_FragPosLightSpace, normalWS, lightDirWS)
            : 1.0;

        vec3 contrib = applyPhong(normalWS, viewDir, lightDirWS,
                                  u_dirLightAmbient[i], u_dirLightDiffuse[i], u_dirLightSpecular[i],
                                  visibility);
        accumColor += contrib;
    }

    // ----- Point lights -----
    for (int i = 0; i < u_numPointLights; ++i)
    {
        vec3  lightPos   = u_pointLightPositions[i];
        vec3  lightDir   = v_FragPos - lightPos;
        float distance   = length(lightDir);
        float attenuation = 1.0 / (u_pointLightConstant[i] +
                                   u_pointLightLinear[i] * distance +
                                   u_pointLightQuadratic[i] * distance * distance);

        float visibility = 1.0;
        if (u_hasPointShadows == 1 && i == 0) // only first light gets a cubemap shadow
        {
            visibility = pointShadowVisibilitySingle(v_FragPos, lightPos, u_pointLightFarPlanes[i]);
        }

        vec3 contrib = applyPhong(normalWS, viewDir, -lightDir,
                                  u_pointLightAmbient[i], u_pointLightDiffuse[i], u_pointLightSpecular[i],
                                  visibility);
        accumColor += contrib * attenuation;
    }

    outColor = vec4(accumColor, 1.0);
}

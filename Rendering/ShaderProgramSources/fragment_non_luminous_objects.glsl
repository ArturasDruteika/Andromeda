#version 330 core

in vec3 v_FragPos;               // world-space fragment position
in vec3 v_Normal;                // world-space interpolated normal (VS: model-only normal matrix)
in vec4 v_FragPosLightSpace;     // lightVP * worldPos

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
uniform sampler2D         u_dirShadowMap;     // manual compare (no compare mode)
uniform samplerCubeShadow u_pointShadowCube;  // hardware compare (compare mode ON)

// ===== directional lights =====
uniform int      u_numDirLights;
uniform vec3     u_dirLightDirections[8];     // EXPECTED: light -> scene (ray dir)
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
uniform float u_pointLightFarPlanes[16];
uniform float u_pointLightIntensity[16];

// ----------------------------------------------------------------------------
// Helpers
// ----------------------------------------------------------------------------
float dirShadowVisibility(vec4 fragPosLightSpace, vec3 normalWS, vec3 lightDirWS)
{
    // Project to [0,1] texture space
    vec3 projCoords = fragPosLightSpace.xyz / max(fragPosLightSpace.w, 1e-6);
    projCoords = projCoords * 0.5 + 0.5;

    // Outside the map => lit (prevents edge PCF poisoning)
    if (projCoords.z > 1.0 ||
        projCoords.x < 0.0 || projCoords.x > 1.0 ||
        projCoords.y < 0.0 || projCoords.y > 1.0)
    {
        return 1.0;
    }

    // Bias from same N·L used for shading
    vec3 n = normalize(normalWS);
    vec3 l = normalize(lightDirWS);          // light -> scene
    float NdotL = max(dot(n, l), 0.0);

    const float constBias   = 0.0005;
    const float slopeFactor = 0.001;
    float bias = max(constBias, slopeFactor * (1.0 - NdotL));

    // 3x3 PCF
    vec2 texelSize = 1.0 / vec2(textureSize(u_dirShadowMap, 0));
    float vis = 0.0;
    for (int dy = -1; dy <= 1; ++dy)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            vec2 o = vec2(dx, dy) * texelSize;
            float mapDepth = texture(u_dirShadowMap, projCoords.xy + o).r;
            float current  = projCoords.z - bias;
            vis += (current <= mapDepth) ? 1.0 : 0.0;
        }
    }
    return vis / 9.0;
}

float pointShadowVisibilitySingle(vec3 fragPosWS, vec3 lightPosWS, float farPlane)
{
    vec3 L = fragPosWS - lightPosWS;           // light -> frag
    float dist = length(L);
    return texture(u_pointShadowCube, vec4(normalize(L), dist / max(farPlane, 1e-6)));
}

// ----------------------------------------------------------------------------
// Blinn–Phong with seam-free specular:
//  - Diffuse uses interpolated normal (smooth if your vertices are smooth).
//  - Specular uses a flat normal computed from derivatives -> no triangle seam.
// ----------------------------------------------------------------------------
vec3 shadeBlinnPhong(
    vec3 normalSmoothWS,     // interpolated normal
    vec3 viewDirWS,          // camera - frag
    vec3 lightDirWS,         // light -> scene (or light->frag for point)
    float intensity,
    vec3 ambientColor,
    vec3 diffuseColor,
    vec3 specularColor,
    float attenuation, 
    float shadowVisibility
)
{
    // Diffuse normal (keeps smoothing if your mesh wants it)
    vec3 n_diffuse = normalize(normalSmoothWS);

    // Flat per-face normal for specular to avoid diagonal seams
    vec3 n_flat = normalize(cross(dFdx(v_FragPos), dFdy(v_FragPos)));
    // Make sure it faces the same hemi-sphere as the interpolated normal
    if (dot(n_flat, n_diffuse) < 0.0) n_flat = -n_flat;

    vec3 v = normalize(viewDirWS);
    vec3 l = normalize(lightDirWS);

    // Ambient (not shadowed)
    vec3 ambientTerm = ambientColor * u_materialAmbient;

    // Diffuse
    float NdotL = max(dot(n_diffuse, l), 0.0);
    vec3  diffuseTerm = diffuseColor * u_materialDiffuse * NdotL;

    // Blinn–Phong specular with flat normal (seam-free)
    float shin = clamp(u_materialShininess, 1.0, 128.0);
    float specStrength = 0.9;
    if (NdotL > 0.0)
    {
        vec3 h = normalize(l + v);
        float NdotH = max(dot(n_flat, h), 0.0);
        specStrength = pow(NdotH, shin);
        // tame grazing spikes
        specStrength *= NdotL;
    }
    vec3 specularTerm = specularColor * u_materialSpecular * specStrength;

    // Apply shadowing to direct terms only
    return ambientTerm + intensity * attenuation * shadowVisibility * (diffuseTerm + specularTerm);
}

void main()
{
    vec3 normalWS = normalize(v_Normal);
    vec3 viewDir  = normalize(u_cameraPosWS - v_FragPos);

    vec3 colorAccum = vec3(0.0);

    // ----- Directional lights -----
    for (int i = 0; i < u_numDirLights; ++i)
    {
        // If your engine stores scene->light, flip here: vec3 lightDirWS = -u_dirLightDirections[i];
        vec3 lightDirWS = normalize(-u_dirLightDirections[i]); // light -> scene

        float visibility = 1.0;
        if (u_hasDirShadows == 1)
            visibility = dirShadowVisibility(v_FragPosLightSpace, normalWS, lightDirWS);

        colorAccum += shadeBlinnPhong(
            normalWS, 
            viewDir, 
            lightDirWS,
            1.0,
            u_dirLightAmbient[i], 
            u_dirLightDiffuse[i], 
            u_dirLightSpecular[i],
            1.0,
            visibility
        );
    }

    // ----- Point lights -----
    for (int i = 0; i < u_numPointLights; ++i)
    {
        vec3 lightPosWS = u_pointLightPositions[i];
        vec3 lightDirWS = lightPosWS - v_FragPos;   // light -> frag
        float dist      = length(lightDirWS);

        float attenuation = 1.0 / (u_pointLightConstant[i] +
                                   u_pointLightLinear[i] * dist +
                                   u_pointLightQuadratic[i] * dist * dist);

        float visibility = 1.0;
        if (u_hasPointShadows == 1 && i == 0)
            visibility = pointShadowVisibilitySingle(v_FragPos, lightPosWS, u_pointLightFarPlanes[i]);

        colorAccum += shadeBlinnPhong(
            normalWS, 
            viewDir, 
            lightDirWS,
            u_pointLightIntensity[i], 
            u_pointLightAmbient[i], 
            u_pointLightDiffuse[i], 
            u_pointLightSpecular[i],
            attenuation,
            visibility
        );
    }

    outColor = vec4(colorAccum, 1.0);
}

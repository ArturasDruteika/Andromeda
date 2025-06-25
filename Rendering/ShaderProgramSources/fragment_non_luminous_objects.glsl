#version 330 core

#define MAX_LIGHTS 8

in vec3 fragPosition;    // world-space position
in vec3 fragNormal;      // world-space normal
in vec4 vertexColor;     // base albedo color

out vec4 FragColor;

// ----------- Material uniforms ------------
uniform float u_ambientStrength;
uniform float u_ambientReflectivity;
uniform float u_diffuseStrength;
uniform float u_specularStrength;
uniform float u_shininess;

// ----------- Light arrays ---------------
uniform int   u_numLights;
uniform vec3  u_lightPos[MAX_LIGHTS];
uniform vec4  u_lightColor[MAX_LIGHTS];

// per-light attenuation
uniform float u_lightConstant[MAX_LIGHTS];
uniform float u_lightLinear[MAX_LIGHTS];
uniform float u_lightQuadratic[MAX_LIGHTS];

// ----------- Shadow map (one light) -------
uniform sampler2D u_shadowMap;         // depth texture
uniform mat4 u_lightSpaceMatrix; // to transform fragPosition into light clip‐space

uniform vec3  u_viewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1]
    projCoords = projCoords * 0.5 + 0.5;

    // If outside the shadow map, consider fully lit
    if(projCoords.z > 1.0) 
        return 0.0;

    // Depth stored in shadow map
    float closestDepth = texture(u_shadowMap, projCoords.xy).r;
    // Current fragment depth from light POV
    float currentDepth = projCoords.z;

    // Bias to prevent self‐shadowing ("shadow acne")
    float bias = max(0.005 * (1.0 - dot(normalize(fragNormal), normalize(u_lightPos[0] - fragPosition))), 
                     0.0005);

    // Simple binary shadow
    return currentDepth - bias > closestDepth ? 1.0 : 0.0;
}

void main()
{
    vec3 norm    = normalize(fragNormal);
    vec3 viewDir = normalize(u_viewPos - fragPosition);

    vec4 ambientAcc  = vec4(0.0);
    vec4 diffuseAcc  = vec4(0.0);
    vec4 specularAcc = vec4(0.0);

    // Precompute the light‐space position for shadow lookup
    vec4 fragPosLightSpace = u_lightSpaceMatrix * vec4(fragPosition, 1.0);
    float shadow = ShadowCalculation(fragPosLightSpace);

    for (int i = 0; i < u_numLights; ++i)
    {
        vec3  L        = u_lightPos[i] - fragPosition;
        float distance = length(L);
        vec3  lightDir = normalize(L);

        // per-light geometric attenuation
        float attenuation = 1.0 / (
            u_lightConstant[i] +
            u_lightLinear  [i] * distance +
            u_lightQuadratic[i] * distance * distance
        );

        // Ambient always applies
        ambientAcc += u_ambientStrength 
                    * u_ambientReflectivity 
                    * u_lightColor[i] 
                    * attenuation;

        // Only add diffuse+specular if NOT in shadow
        if (shadow < 0.5) {
            // Diffuse
            float diff = max(dot(norm, lightDir), 0.0);
            diffuseAcc += diff 
                        * u_lightColor[i] 
                        * u_diffuseStrength 
                        * attenuation;

            // Specular (Blinn–Phong)
            vec3 halfwayDir = normalize(lightDir + viewDir);
            float spec = pow(max(dot(norm, halfwayDir), 0.0), u_shininess);
            specularAcc += u_specularStrength 
                         * spec 
                         * u_lightColor[i] 
                         * attenuation;
        }
    }

    // Combine with base color
    vec4 result = ambientAcc + diffuseAcc + specularAcc;
    FragColor = vec4(result.rgb * vertexColor.rgb, vertexColor.a);
}

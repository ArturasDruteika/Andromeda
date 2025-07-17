#version 330 core

layout(early_fragment_tests) in;

#define MAX_LIGHTS 8

in vec3    fragPosition;       // world‐space position
in vec3    fragNormal;         // world‐space normal
in vec4    vertexColor;        // base albedo color

out vec4 FragColor;

// --------- Material uniforms ---------
uniform vec3  u_ambientMaterial;
uniform vec3  u_diffuseMaterial;
uniform vec3  u_specularMaterial;
uniform float u_shininessMaterial;

// --------- Light uniforms (renamed) ---------
uniform int    u_numLights;
uniform vec3   u_positionLight[MAX_LIGHTS];
uniform vec3   u_ambientLight[MAX_LIGHTS];
uniform vec3   u_diffuseLight[MAX_LIGHTS];
uniform vec3   u_specularLight[MAX_LIGHTS];
uniform float  u_constantLight[MAX_LIGHTS];
uniform float  u_linearLight[MAX_LIGHTS];
uniform float  u_quadraticLight[MAX_LIGHTS];

// Shadow map (for light 0)
uniform sampler2D u_shadowMap;
uniform mat4      u_lightSpaceMatrix;

uniform vec3 u_viewPos;

// --------- Shadow calculation (updated) --------
float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    if (projCoords.z > 1.0) return 0.0;

    float closestDepth = texture(u_shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    float bias = max(0.005 * (1.0 - dot(
                        normalize(fragNormal),
                        normalize(u_positionLight[0] - fragPosition)
                     )),
                     0.0005);
    return currentDepth - bias > closestDepth ? 1.0 : 0.0;
}

void main()
{
    vec3 norm    = normalize(fragNormal);
    vec3 viewDir = normalize(u_viewPos - fragPosition);
    vec4 result  = vec4(0.0);

    // Precompute for shadow
    vec4 fragPosLS = u_lightSpaceMatrix * vec4(fragPosition, 1.0);
    float shadow   = ShadowCalculation(fragPosLS);

    for (int i = 0; i < u_numLights; ++i)
    {
        vec3  lightPos      = u_positionLight[i];
        vec3  lightAmb      = u_ambientLight[i];
        vec3  lightDiff     = u_diffuseLight[i];
        vec3  lightSpec     = u_specularLight[i];
        float constantAtt   = u_constantLight[i];
        float linearAtt     = u_linearLight[i];
        float quadraticAtt  = u_quadraticLight[i];

        vec3 lightDir = normalize(lightPos - fragPosition);
        float distance = length(lightPos - fragPosition);
        float attenuation = 1.0 / (constantAtt
                                 + linearAtt   * distance
                                 + quadraticAtt * distance * distance);

        // Ambient
        vec3 ambient = u_ambientMaterial * lightAmb * attenuation;

        // Diffuse & Specular
        vec3 diffuse  = vec3(0.0);
        vec3 specular = vec3(0.0);
        if (shadow < 0.5)
        {
            float diffFactor = max(dot(norm, lightDir), 0.0);
            diffuse = u_diffuseMaterial
                    * lightDiff
                    * diffFactor
                    * attenuation;

            vec3 halfwayDir = normalize(lightDir + viewDir);
            float specFactor = pow(
                max(dot(norm, halfwayDir), 0.0),
                u_shininessMaterial
            );
            specular = u_specularMaterial
                     * lightSpec
                     * specFactor
                     * attenuation;
        }

        result.rgb += (ambient + diffuse + specular);
    }

    FragColor = vec4(result.rgb, 1.0);
}

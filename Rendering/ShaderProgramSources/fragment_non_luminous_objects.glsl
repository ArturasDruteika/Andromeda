#version 330 core

layout(early_fragment_tests) in;

#define MAX_LIGHTS 8

in vec3 fragPosition;       // world-space position
in vec3 fragNormal;         // world-space normal
in vec4 vertexColor;        // base albedo color

out vec4 FragColor;

// --------- Material uniforms ---------
uniform vec3  u_ambientMaterial;
uniform vec3  u_diffuseMaterial;
uniform vec3  u_specularMaterial;
uniform float u_shininessMaterial;

// --------- Directional Light uniforms ---------
uniform int    u_numLights;
uniform vec3   u_directionLight[MAX_LIGHTS];
uniform vec3   u_ambientLight[MAX_LIGHTS];
uniform vec3   u_diffuseLight[MAX_LIGHTS];
uniform vec3   u_specularLight[MAX_LIGHTS];

// Shadow map (for light 0)
uniform sampler2D u_shadowMap;
uniform mat4      u_lightSpaceMatrix;

uniform vec3 u_viewPos;

// --------- Shadow calculation ---------
float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir, vec3 normal)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    if (projCoords.z > 1.0) return 0.0;

    float closestDepth = texture(u_shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    float bias = clamp(0.005 * (1.0 - dot(normal, lightDir)), 0.0005, 0.01);
    return currentDepth - bias > closestDepth ? 1.0 : 0.0;
}

void main()
{
    vec3 norm    = normalize(fragNormal);
    vec3 viewDir = normalize(u_viewPos - fragPosition);
    vec4 result  = vec4(0.0);

    // Precompute shadow for first light (light 0)
    vec4 fragPosLS = u_lightSpaceMatrix * vec4(fragPosition, 1.0);
    vec3 lightDir0 = normalize(-u_directionLight[0]);
    float shadow = ShadowCalculation(fragPosLS, lightDir0, norm);
    float lightVisibility0 = 1.0 - shadow;

    for (int i = 0; i < u_numLights; ++i)
    {
        vec3 lightDir = normalize(-u_directionLight[i]);  // invert since direction is "to fragment"
        float lightVisibility = (i == 0) ? lightVisibility0 : 1.0;

        // Ambient
        vec3 ambient = u_ambientMaterial * u_ambientLight[i];

        // Diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = u_diffuseMaterial * u_diffuseLight[i] * diff * lightVisibility;

        // Specular
        vec3 halfway = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfway), 0.0), u_shininessMaterial);
        vec3 specular = u_specularMaterial * u_specularLight[i] * spec * lightVisibility;

        result.rgb += ambient + diffuse + specular;
    }

    FragColor = vec4(result.rgb, 1.0);
}

#version 330 core

#define MAX_LIGHTS 8

in vec3 fragPosition;    // world-space position
in vec3 fragNormal;      // world-space normal
in vec4 vertexColor;     // base albedo color

out vec4 FragColor;

// material uniforms
uniform float u_ambientStrength;
uniform float u_diffuseStrength;
uniform float u_specularStrength;
uniform float u_shininess;

// light arrays
uniform int   u_numLights;
uniform vec3  u_lightPos[MAX_LIGHTS];
uniform vec4  u_lightColor[MAX_LIGHTS];

// per-light attenuation
uniform float u_lightConstant[MAX_LIGHTS];
uniform float u_lightLinear[MAX_LIGHTS];
uniform float u_lightQuadratic[MAX_LIGHTS];

uniform vec3  u_viewPos;

void main()
{
    vec3 norm    = normalize(fragNormal);
    vec3 viewDir = normalize(u_viewPos - fragPosition);

    vec4 ambient  = vec4(0.0);
    vec4 diffuse  = vec4(0.0);
    vec4 specular = vec4(0.0);

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

        // Ambient
        ambient += u_ambientStrength * u_lightColor[i] * attenuation;

        // Diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse += diff * u_lightColor[i] * u_diffuseStrength * attenuation;

        // Specular (Blinn–Phong)
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfwayDir), 0.0), u_shininess);
        specular += u_specularStrength * spec * u_lightColor[i] * attenuation;
    }

    // Combine with base color
    vec4 result = ambient + diffuse + specular;
    FragColor = vec4(result.rgb * vertexColor.rgb, vertexColor.a);
}

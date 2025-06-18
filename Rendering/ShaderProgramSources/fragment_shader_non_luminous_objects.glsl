#version 330 core

#define MAX_LIGHTS 8

in vec3 fragPosition;	// world-space position
in vec3 fragNormal;		// world-space normal
in vec4 vertexColor;	// base albedo color

out vec4 FragColor;

uniform float u_ambientStrength;
uniform float u_diffuseStrength;
uniform float u_specularStrength;
uniform float u_shininess;

uniform int   u_numLights;
uniform vec3  u_lightPos[MAX_LIGHTS];
uniform vec4  u_lightColor[MAX_LIGHTS];

uniform vec3  u_viewPos;

uniform float u_attenuationConstant;
uniform float u_attenuationLinear;
uniform float u_attenuationQuadratic;

void main()
{
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(u_viewPos - fragPosition);

    vec4 ambient = vec4(0.0);
    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);

    for (int i = 0; i < u_numLights; ++i)
    {
        vec3  lightDir = normalize(u_lightPos[i] - fragPosition);
        float distance = length(u_lightPos[i] - fragPosition);
        float attenuation = 1.0 / (
            u_attenuationConstant +
            u_attenuationLinear * distance +
            u_attenuationQuadratic * distance * distance
        );

        // Ambient term
        ambient += u_ambientStrength * u_lightColor[i] * attenuation;

        // Diffuse term
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse += diff * u_lightColor[i] * u_diffuseStrength * attenuation;

        // Specular term (Blinn–Phong)
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfwayDir), 0.0), u_shininess);
        specular += u_specularStrength * spec * u_lightColor[i] * attenuation;
    }

    // Combine lighting with the vertex color
    vec4 result = ambient + diffuse + specular;
    FragColor = vec4(result.rgb * vertexColor.rgb, vertexColor.a);
}

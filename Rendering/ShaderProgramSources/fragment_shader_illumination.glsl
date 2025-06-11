#version 330 core

#define MAX_LIGHTS 8

in vec3 fragPosition;
in vec3 fragNormal;
in vec4 vertexColor;

out vec4 FragColor;

uniform float u_ambientStrength;
uniform float u_specularStrength;
uniform float u_shininess;

uniform int u_numLights;
uniform vec3 u_lightPos[MAX_LIGHTS];
uniform vec4 u_lightColor[MAX_LIGHTS];

uniform vec3 u_viewPos;

uniform float u_attenuationConstant;
uniform float u_attenuationLinear;
uniform float u_attenuationQuadratic;

uniform vec4 u_vertexColorOverride;

void main()
{
    vec4 effectiveColor = u_vertexColorOverride.a > 0.0 ? u_vertexColorOverride : vertexColor;

    // Special case: this object is a light source (draw as color override)
    if (u_vertexColorOverride.a > 0.0)
    {
        FragColor = u_vertexColorOverride;
        return;
    }

    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(u_viewPos - fragPosition);

    vec4 ambient = vec4(0.0);
    vec4 diffuse = vec4(0.0);
    vec4 specular = vec4(0.0);

    for (int i = 0; i < u_numLights; ++i)
    {
        vec3 lightDir = normalize(u_lightPos[i] - fragPosition);
        float distance = length(u_lightPos[i] - fragPosition);
        float attenuation = 1.0 / (u_attenuationConstant + u_attenuationLinear * distance + u_attenuationQuadratic * distance * distance);

        // Ambient
        ambient += u_ambientStrength * u_lightColor[i] * attenuation;

        // Diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse += diff * u_lightColor[i] * attenuation;

        // Specular
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);
        specular += u_specularStrength * spec * u_lightColor[i] * attenuation;
    }

    vec4 lighting = (ambient + diffuse + specular) * effectiveColor;
    FragColor = vec4(lighting.rgb, effectiveColor.a);
}

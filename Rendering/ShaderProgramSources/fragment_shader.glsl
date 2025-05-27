#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec4 vertexColor;

out vec4 FragColor;

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;
uniform vec3 u_lightColor;
uniform vec4 u_vertexColorOverride;

void main()
{
    vec4 effectiveColor = u_vertexColorOverride.a > 0.0 ? u_vertexColorOverride : vertexColor;

    // 1. If this fragment belongs to the light-emitting object — draw it as pure white
    if (u_vertexColorOverride.a > 0.0)
    {
        FragColor = u_vertexColorOverride;
        return;
    }

    // 2. Standard Phong lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_lightColor;

    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(u_lightPos - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_viewPos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * u_lightColor;

    vec3 lighting = (ambient + diffuse + specular) * effectiveColor.rgb;
    FragColor = vec4(lighting, effectiveColor.a);
}

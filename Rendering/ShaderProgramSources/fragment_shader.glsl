#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec4 vertexColor;

out vec4 FragColor;

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;
uniform vec3 u_lightColor;

void main()
{
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_lightColor;

    // Diffuse
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(u_lightPos - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(u_viewPos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * u_lightColor;

    // Combine lighting and vertex color
    vec3 lighting = (ambient + diffuse + specular) * vertexColor.rgb;
    FragColor = vec4(lighting, vertexColor.a);
}

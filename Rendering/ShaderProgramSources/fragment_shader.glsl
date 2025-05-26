#version 330 core

in vec4 ourColor;
in vec3 fragNormal;
in vec3 fragPosition;

out vec4 FragColor;

uniform vec3 u_lightDir;   // Direction TO the light (e.g., -normalize(vec3(1,1,1)))
uniform vec3 u_lightColor; // Light color (white = vec3(1.0))
uniform vec3 u_ambientColor; // Ambient fallback (e.g., vec3(0.1))

void main()
{
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(u_lightDir);

    // Lambert diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;

    vec3 ambient = u_ambientColor;

    vec3 finalColor = (ambient + diffuse) * ourColor.rgb;

    FragColor = vec4(finalColor, ourColor.a);
}

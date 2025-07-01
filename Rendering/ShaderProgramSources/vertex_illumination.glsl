#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec3 aNormal;

out vec3 fragPosition;
out vec3 fragNormal;
out vec4 vertexColor;

uniform mat3 u_normalMatrix;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    vec4 worldPosition = u_model * vec4(aPos, 1.0);
    fragPosition = worldPosition.xyz;
    fragNormal = u_normalMatrix * aNormal;
    vertexColor = aColor;

    gl_Position = u_projection * u_view * worldPosition;
}

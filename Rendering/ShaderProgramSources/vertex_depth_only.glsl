#version 330 core
layout(location = 0) in vec3 inPos;

uniform mat4 u_model;
uniform mat4 u_lightSpaceMatrix;

void main()
{
    gl_Position = u_lightSpaceMatrix * u_model * vec4(inPos, 1.0);
}

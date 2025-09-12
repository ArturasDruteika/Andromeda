#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 u_model;

out vec3 fragPosition; // world-space

void main()
{
    fragPosition = vec3(u_model * vec4(aPos, 1.0));
    // gl_Position set in GS
}

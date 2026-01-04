#version 330 core
layout(location = 0) in vec2 aPos;

uniform vec4 u_color;
uniform mat4 u_projection;

out vec4 vertexColor;

void main()
{
    gl_Position = u_projection * vec4(aPos, 0.0, 1.0);
    vertexColor = u_color;
}

#version 330 core

in vec4 vertexColor;	// incoming per-vertex color
out vec4 FragColor;		// output color

void main()
{
    FragColor = vertexColor;
}
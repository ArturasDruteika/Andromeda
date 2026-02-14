#version 330 core
in vec3 gWorldPos;

uniform vec3 u_lightPos;
uniform float u_farPlane;

void main()
{
    float lightDist = length(gWorldPos - u_lightPos);
    gl_FragDepth = lightDist / u_farPlane;  // write to depth
}

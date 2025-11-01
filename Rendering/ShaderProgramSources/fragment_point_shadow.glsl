#version 330 core
in vec3 gWorldPos;

uniform vec3 u_lightPos;
uniform float u_farPlane;

out float fragDepth;

void main()
{
    // compute linear distance from light
    float lightDist = length(gWorldPos - u_lightPos);

    // store normalized distance (0..1)
    lightDist = lightDist / u_farPlane;

    // write as depth value
    fragDepth = lightDist;
}

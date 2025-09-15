#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

in vec3 v_WorldPos[];
out vec3 gWorldPos;

uniform mat4 u_shadowMatrices[6];

void main()
{
    for (int face = 0; face < 6; ++face)
    {
        for (int i = 0; i < 3; ++i)
        {
            gWorldPos   = v_WorldPos[i];
            gl_Position = u_shadowMatrices[face] * vec4(v_WorldPos[i], 1.0);
            EmitVertex();
        }
        EndPrimitive();
    }
}

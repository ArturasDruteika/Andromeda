#version 330 core

// We take triangles in, and emit up to 3 vertices per face * 6 faces = 18.
layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

// 6 face view-projection matrices for the cubemap (built on CPU)
// Face order (recommended):
// 0:+X, 1:-X, 2:+Y, 3:-Y, 4:+Z, 5:-Z
uniform mat4 u_ShadowMatrices[6];

// From the vertex shader: world-space position per vertex
in vec3 fragPosition[];

// To the fragment shader (for distance to light)
out vec3 gWorldPos;

void main()
{
    // Replicate this primitive to all 6 faces
    for (int face = 0; face < 6; ++face)
    {
        // Route emitted vertices to a specific cubemap face
        gl_Layer = face;

        // Emit the triangle for this face
        for (int v = 0; v < 3; ++v)
        {
            gWorldPos   = fragPosition[v];
            gl_Position = u_ShadowMatrices[face] * vec4(fragPosition[v], 1.0);
            EmitVertex();
        }
        EndPrimitive();
    }
}

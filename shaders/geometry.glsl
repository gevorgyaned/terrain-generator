#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 frag_pos[];

out vec3 norm;
out vec3 frag;

void main()
{
    vec3 a = frag_pos[1] - frag_pos[0];
    vec3 b = frag_pos[2] - frag_pos[1];
    norm = normalize(cross(a, b));

    frag = vec3(
        (frag_pos[0].x + frag_pos[1].x + frag_pos[2].x) / 3.0f, 
        (frag_pos[0].y + frag_pos[1].y + frag_pos[2].y) / 3.0f, 
        (frag_pos[0].z + frag_pos[1].z + frag_pos[2].z) / 3.0f
    );

    for (int i = 0; i < 3; ++i) {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }

    EndPrimitive();
}

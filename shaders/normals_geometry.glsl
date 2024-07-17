#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

in vec3 normal;
in vec3 triangle_center;

out vec3 norm;
out vec3 frag;

void main()
{
     
    EndPrimitive();
}

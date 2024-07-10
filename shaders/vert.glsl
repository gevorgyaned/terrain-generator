#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

out vec3 o_normal;
out vec3 frag_pos;

void main()
{
    o_normal = a_normal;
    frag_pos = vec3(model * vec4(a_pos, 1.0));
    gl_Position = proj * view * model * vec4(a_pos, 1.0);
}

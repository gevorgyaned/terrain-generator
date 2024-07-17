#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

uniform mat4 model;
uniform mat4 view;

out vec3 normal;

void main()
{
    mat3 normal_matrix = mat3(transpose(inverse(view * model)));
    normal = vec3(vec4(normal_matrix * a_normal, 0.0));
    gl_Position = view * model * vec4(a_pos, 1.0);
}

#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

out float value;

void main()
{
    gl_Position = proj * view * model * vec4(pos, 1.f);

    value = pos.y;
}


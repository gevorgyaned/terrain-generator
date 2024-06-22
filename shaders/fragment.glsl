#version 330 core

in float value;
out vec4 FragColor;

uniform vec3 col;

void main()
{
    FragColor = vec4(col, 1.f);
}


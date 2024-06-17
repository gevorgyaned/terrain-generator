#version 330 core

in float value;

void main()
{
    vec3 color = vec3(1.f, 0.5f, 0.f);
    gl_FragColor = vec4(color, 1.f);
}


#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

uniform vec3 u_target_color;
uniform vec3 u_camera_location;
uniform vec3 u_light_location;
uniform vec3 u_light_color;

out vec3 color;

void main()
{
    vec3 frag_pos = vec3(model * vec4(a_pos, 1.0));
    vec3 dir = u_light_location - frag_pos;  
    float n = max(dot(dir, a_normal), 0.0f);
    vec3 diffuse = n * u_light_color;

	const float ambient_strength = 0.214f;
    vec3 ambient = ambient_strength * u_light_color;
	
    color = (diffuse + ambient) * u_target_color;

    gl_Position = proj * view * model * vec4(a_pos, 1.0);
}

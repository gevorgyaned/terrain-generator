#version 330 core

out vec4 FragColor;

uniform vec3 u_target_color;
uniform vec3 u_camera_location;
uniform vec3 u_light_location;
uniform vec3 u_light_color;

in vec3 frag_pos;
in vec3 normal;

void main()
{
    vec3 dir = (u_light_location - frag_pos);

    float len = length(dir);

    float brightness = 1.0 / len;

    vec3 norm = normalize(normal);
    float n = max(dot(normalize(dir), norm), 0.0f);
    vec3 diffuse = n * u_light_color * brightness;

	const float ambient_strength = 0.3;
    vec3 ambient = ambient_strength * u_light_color;

    vec3 color = (diffuse + ambient) * u_target_color;
    FragColor = vec4(color, 1.0f);
}

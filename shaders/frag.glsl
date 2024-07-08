#version 330 core

out vec4 FragColor;

uniform vec3 utarget_color;
uniform vec3 ucamera_location;
uniform vec3 ulight_location;
uniform vec3 light_color;

void main()
{

    FragColor = vec4(utarget_color, 1.0f);

	const float ambient_strength = 0.12f;
	


}

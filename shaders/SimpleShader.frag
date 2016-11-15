#version 410 core
in vec3 FragPos;

uniform vec3 gravity_point;
uniform vec3 camera_position;

uniform vec4 border_color;
uniform vec4 center_color;

out vec4 color;

#define BORDER_COLOR	vec4(1.0, 0.0, 0.0, 1.0)
#define CENTER_COLOR	vec4(0.9, 0.65, 0.33, 1.0)

void main()
{
	float	distance = length(gravity_point - FragPos);
	float	ratio = (1.0 / distance) / 4.0;

	color = mix(border_color, center_color, ratio * (-camera_position.z * 0.5));
}

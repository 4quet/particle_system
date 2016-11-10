#version 410
in vec3 FragPos;

uniform vec4 gravity_point;
uniform vec3 camera_position;

out vec4 color;

#define BORDER_COLOR	vec4(1.0, 0.0, 0.0, 1.0)
#define CENTER_COLOR	vec4(0.9, 0.65, 0.33, 1.0)

void main()
{
	float	distance = length(gravity_point.xyz - FragPos);
	float	ratio = (1.0 / distance) / 4.0;

	color = mix(BORDER_COLOR, CENTER_COLOR, ratio * (-camera_position.z * 0.5));
}

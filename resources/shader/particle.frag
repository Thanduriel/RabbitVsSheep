#version 450

layout(location = 0) in vec3 in_position;
layout(location = 0) out vec4 out_color;

void main()
{

	vec3 posAbs = abs(in_position);
	float a = 1 - min(min(posAbs.x, posAbs.y), posAbs.z);
//	float a = 1.442 - length(in_position);
	out_color = vec4(0.33, 0.77, 0.05, a);
}
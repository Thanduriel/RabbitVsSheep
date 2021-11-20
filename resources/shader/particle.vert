#version 450

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_rotation;
layout(location = 2) in float in_size;

layout(location = 0) out vec3 out_position;
layout(location = 1) out vec4 out_rotation;
layout(location = 2) out float out_size;

void main()
{
	out_position = in_position;
	out_rotation = in_rotation;
	out_size = in_size;
}
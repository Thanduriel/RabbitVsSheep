#version 450

layout(location = 0) in vec4 in_normal;
layout(location = 1) in vec2 in_texCoord;
layout(location = 2) in vec3 in_position;

layout(binding = 0) uniform sampler2D tx_diffuse;
layout(location = 3) uniform vec3 c_lightDir;

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 diffuse = texture(tx_diffuse, in_texCoord).rgb;
	float diffuseStrength = clamp( dot( in_normal.xyz, c_lightDir ), 0.3, 1.0 );
	vec3 reflectDir = reflect(-c_lightDir.xyz, in_normal.xyz);
	float specular = max(dot(reflectDir, -normalize(in_position)), 0.f);
	
	out_color = vec4(diffuse * diffuseStrength + 0.5 * pow(specular, 8) * vec3(1,1,1), 1.0);
}
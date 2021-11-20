#version 450

layout(location = 0) in vec3 in_position[1];
layout(location = 1) in vec4 in_rotation[1];
layout(location = 2) in float in_size[1];

layout(location = 0) out vec3 out_position;

layout(location = 0) uniform mat4 c_viewProjection;

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

mat4 quatToMat(vec4 q)
{
		mat4 result;
		float qxx = q.x * q.x;
		float qyy = q.y * q.y;
		float qzz = q.z * q.z;
		float qxz = q.x * q.z;
		float qxy = q.x * q.y;
		float qyz = q.y * q.z;
		float qwx = q.w * q.x;
		float qwy = q.w * q.y;
		float qwz = q.w * q.z;

		result[0] = vec4(1.0 - 2.0 * (qyy +  qzz)
			, 2.0 * (qxy + qwz)
			, 2.0 * (qxz - qwy)
			, 0.0);

		result[1] = vec4(2.0 * (qxy - qwz)
			, 1.0 - 2.0 * (qxx +  qzz)
			, 2.0 * (qyz + qwx)
			, 0.0);

		result[2] = vec4( 2.0 * (qxz + qwy)
			, 2.0 * (qyz - qwx)
			, 1.0 - 2.0 * (qxx +  qyy)
			, 0.0);

		result[3] = vec4(0.0, 0.0, 0.0, 1.0);

		return result;
	}

void drawFace(vec3 positions[4], mat4 transform, float size)
{
	for(int i = 0; i < 4; ++i)
	{
		out_position = positions[i];
		gl_Position = transform * vec4(size * positions[i], 1.0);
		EmitVertex();
	}
	EndPrimitive();
}

void main()
{
	float s = in_size[0];

	mat4 translation;
	translation[0][0] = 1.0;
	translation[1][1] = 1.0;
	translation[2][2] = 1.0;
	translation[3] = vec4(in_position[0], 1.0);

	mat4 transform = c_viewProjection * translation * quatToMat(in_rotation[0]);

	// front
	drawFace(vec3[4](vec3(-1.0,-1.0,1.0), vec3(1.0,-1.0,1.0), vec3(-1.0,1.0,1.0), vec3(1.0,1.0,1.0)), transform,s);
	// back
	drawFace(vec3[4](vec3(-1.0,-1.0,-1.0), vec3(-1.0,1.0,-1.0), vec3(1.0,-1.0,-1.0), vec3(1.0,1.0,-1.0)), transform,s);
	// left
	drawFace(vec3[4](vec3(-1.0,-1.0,-1.0), vec3(-1.0,-1.0,1.0), vec3(-1.0,1.0,-1.0), vec3(-1.0,1.0,1.0)), transform,s);
	//right
	drawFace(vec3[4](vec3(1.0,-1.0,-1.0), vec3(1.0,1.0,-1.0), vec3(1.0,-1.0,1.0), vec3(1.0,1.0,1.0)), transform,s);
	// up
	drawFace(vec3[4](vec3(-1.0,1.0,-1.0), vec3(-1.0,1.0,1.0), vec3(1.0,1.0,-1.0), vec3(1.0,1.0,1.0)), transform,s);
	// down
	drawFace(vec3[4](vec3(-1.0,-1.0,-1.0), vec3(1.0,-1.0,-1.0), vec3(-1.0,-1.0,1.0), vec3(1.0,-1.0,1.0)), transform,s);
	
/*	gl_Position = transform * vec4(-s,-s,s, 1);
	EmitVertex();
	gl_Position = transform * vec4(s,-s,s, 1);
	EmitVertex();
	gl_Position = transform * vec4(-s, s,s, 1);
	EmitVertex();
	gl_Position = transform * vec4(s,s,s, 1);
	EmitVertex();
	EndPrimitive();

	// back
	gl_Position = transform * vec4(-s,-s,-s, 1);
	EmitVertex();
	gl_Position = transform * vec4(-s, s, -s, 1);
	EmitVertex();
	gl_Position = transform * vec4(s,-s,-s, 1);
	EmitVertex();
	gl_Position = transform * vec4(s,s,-s, 1);
	EmitVertex();
	EndPrimitive();

	// left
	gl_Position = transform * vec4(-s,-s,-s, 1);
	EmitVertex();
	gl_Position = transform * vec4(-s,-s,s, 1);
	EmitVertex();
	gl_Position = transform * vec4(-s, s,-s, 1);
	EmitVertex();
	gl_Position = transform * vec4(-s,s,s, 1);
	EmitVertex();
	EndPrimitive();

	// right
	gl_Position = transform * vec4(s,-s,-s, 1);
	EmitVertex();
	gl_Position = transform * vec4(s, s,-s, 1);
	EmitVertex();
	gl_Position = transform * vec4(s,-s,s, 1);
	EmitVertex();
	gl_Position = transform * vec4(s,s,s, 1);
	EmitVertex();
	EndPrimitive();

	// up
	gl_Position = transform * vec4(-s,s,-s, 1);
	EmitVertex();
	gl_Position = transform * vec4(-s,s,s, 1);
	EmitVertex();
	gl_Position = transform * vec4(s, s,-s, 1);
	EmitVertex();
	gl_Position = transform * vec4(s,s,s, 1);
	EmitVertex();
	EndPrimitive();

	// down
	gl_Position = transform * vec4(-s,-s,-s, 1);
	EmitVertex();
	gl_Position = transform * vec4(s, -s,-s, 1);
	EmitVertex();
	gl_Position = transform * vec4(-s,-s,s, 1);
	EmitVertex();
	gl_Position = transform * vec4(s,-s,s, 1);
	EmitVertex();
	EndPrimitive();*/
}
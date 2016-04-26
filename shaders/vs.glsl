#version 450

in vec3 vpos;
in vec3 vnormal;
out vec3 fnormal;

uniform mat4 mvp;

void main()
{	gl_Position = mvp * vec4(vpos, 1.0);
	fnormal = transpose(inverse(mat3(mvp))) * vnormal;
}
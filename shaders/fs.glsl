#version 450

in vec3 fnormal;
out vec3 fcolor;

void main()
{	fcolor = fnormal;
}
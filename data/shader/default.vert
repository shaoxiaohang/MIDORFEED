#version 330
in vec pos;

void main()
{
	gl_Position = vec4(pos,1);
}
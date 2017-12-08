#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 st;
out vec2 texture_st;
void main()
{
	gl_Position = vec4(pos,1);
	texture_st = st;
}
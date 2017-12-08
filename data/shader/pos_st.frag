#version 330
out vec4 color;
in vec2 texture_st;
uniform sampler2D texture0;
void main()
{
	color = texture2D(texture0,texture_st);
}
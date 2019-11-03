#version 330

in vec2 st;

uniform sampler2D fontTex;
uniform vec4 fontColor;

out vec4 color;

void main()
{
	color = vec4(0,0,1,1) * vec4(1,1,1, texture(fontTex, st).r );
}
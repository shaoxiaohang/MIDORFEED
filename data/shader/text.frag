#version 330

in vec2 st;

uniform sampler2D fontTex;
uniform vec4 fontColor;

out vec4 color;

void main()
{
	color = vec4(1,1,1, texture2D(fontTex, st).r) * vec4(1,0,0,1);
	color = texture2D(fontTex, st);
}
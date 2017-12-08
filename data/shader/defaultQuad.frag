#version 330

out vec4 color;
uniform sampler2D scene;
in vec2 TexCoords;
void main()
{
	color = texture2D(scene,TexCoords);
}

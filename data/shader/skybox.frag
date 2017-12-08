#version 330

out vec4 color;
uniform samplerCube skybox;
in vec3 TexCoords;
void main()
{
	color = texture(skybox,TexCoords);
}

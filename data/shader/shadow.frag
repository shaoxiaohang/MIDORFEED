#version 330

out vec4 color;

void main()
{
	color = vec4(gl_FragCoord.z,gl_FragCoord.z,gl_FragCoord.z,1);
}
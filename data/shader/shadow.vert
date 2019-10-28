#version 330

layout (location = 0) in vec3 pos;

uniform mat4 shadow_matrix;
uniform mat4 vrv_model_matrix;

void main()
{
	gl_Position = shadow_matrix * vrv_model_matrix * vec4(pos,1);
	
}
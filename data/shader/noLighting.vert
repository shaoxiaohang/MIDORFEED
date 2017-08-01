#version 330
layout (location = 0) in vec3 pos;

uniform mat4 vrv_view_matrix;
uniform mat4 vrv_model_matrix;
uniform mat4 vrv_proj_matrix;

void main()
{
	gl_Position = vrv_proj_matrix*vrv_view_matrix*vrv_model_matrix*vec4(pos,1);
}
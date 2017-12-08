#version 330
layout (location = 0) in vec3 pos;

uniform mat4 vrv_model_matrix;

layout (std140) uniform CameraUBO
{
	mat4 vrv_proj_matrix;
	mat4 vrv_view_matrix;
	vec3 vrv_view_pos;
};

void main()
{
	gl_Position = vrv_proj_matrix * vrv_view_matrix * vrv_model_matrix * vec4(pos,1);
}
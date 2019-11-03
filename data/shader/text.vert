#version 330

layout (location = 0) in vec4 vertex;

layout (std140) uniform CameraUBO
{
	mat4 vrv_proj_matrix;
	mat4 vrv_view_matrix;
	vec3 vrv_view_pos;
};

uniform mat4 vrv_model_matrix;
out vec2 st;

void main()
{
	gl_Position = vrv_proj_matrix  * vec4(vertex.xy,0,1) ;
	st = vertex.zw;
}
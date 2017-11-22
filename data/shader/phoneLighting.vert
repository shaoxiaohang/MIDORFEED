#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 st;
layout (location = 2) in vec3 normal;

uniform mat4 vrv_model_matrix;


layout (std140) uniform CameraUBO
{
	mat4 vrv_proj_matrix;
	mat4 vrv_view_matrix;
	vec3 vrv_view_pos;
};


out vec2 tex_st;
out vec3 vrv_normal;
out vec3 frag_pos;
void main()
{
	gl_Position = vrv_proj_matrix*vrv_view_matrix*vrv_model_matrix*vec4(pos,1);
	tex_st = st;
	vrv_normal = mat3(transpose(inverse(vrv_model_matrix))) * normalize(normal);
	frag_pos = (vrv_model_matrix*vec4(pos,1)).xyz;
}
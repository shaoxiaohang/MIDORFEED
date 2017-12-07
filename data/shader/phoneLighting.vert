#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 st;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 offset;

uniform mat4 vrv_model_matrix;
uniform bool vrv_instanced;

layout (std140) uniform CameraUBO
{
	mat4 vrv_proj_matrix;
	mat4 vrv_view_matrix;
	vec3 vrv_view_pos;
};

out VS_OUT
{
	vec2 tex_st;
	vec3 vrv_normal;
	vec3 frag_pos;
}vs_out;

out vec2 tex_st;
out vec3 vrv_normal;
out vec3 frag_pos;
void main()
{
	mat4 M;
	if(vrv_instanced)
	{
		M[3] = vec4(offset,1);
	}
	else
	{
		M = vrv_model_matrix;
	}
	
	gl_Position = vrv_proj_matrix*vrv_view_matrix*M*vec4(pos,1);
	tex_st = st;
	vrv_normal = mat3(transpose(inverse(M))) * normalize(normal);
	frag_pos = (M*vec4(pos,1)).xyz;
	vs_out.tex_st = st;
	vs_out.vrv_normal = vrv_normal;
	vs_out.frag_pos = frag_pos;
}
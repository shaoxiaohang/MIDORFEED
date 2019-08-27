#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 st;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 offset;

uniform mat4 vrv_model_matrix;
uniform bool vrv_instanced;
uniform mat4 shadow_matrix;
uniform bool isEllipsoid;

layout (std140) uniform CameraUBO
{
	mat4 vrv_proj_matrix;
	mat4 vrv_view_matrix;
	vec3 vrv_view_pos;
};

out vec2 tex_st;
out vec3 vrv_normal;
out vec3 vrv_tangent;
out vec3 frag_pos;
out vec4 frag_pos_lightSpace;

void main()
{
	mat4 M = mat4(1.0);
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
	vrv_normal = normalize(mat3(transpose(inverse(M))) *normal);
	vrv_tangent = normalize(mat3(transpose(inverse(M))) * tangent);
	mat4 earthMatrix = mat4(1.0);
    if(isEllipsoid)
	{
		
		earthMatrix[0] = vec4(0,0,1,0);
		earthMatrix[1] = vec4(1,0,0,0);
		earthMatrix[2] = vec4(0,1,0,0);
		//frag_pos = earthMatrix*frag_pos;
	}
	frag_pos = (M*vec4(pos,1)).xyz;


	frag_pos_lightSpace =  shadow_matrix* M*vec4(pos,1);
}
#version 330
layout (location = 0) in vec3 pos;

out vec3 TexCoords;

layout (std140) uniform CameraUBO
{
	mat4 vrv_proj_matrix;
	mat4 vrv_view_matrix;
	vec3 vrv_view_pos;
};

void main()
{
	vec4 c1 = vec4(vec3(vrv_view_matrix[0]),0);
	vec4 c2 = vec4(vec3(vrv_view_matrix[1]),0);
	vec4 c3 = vec4(vec3(vrv_view_matrix[2]),0);
	vec4 c4 = vec4(0,0,0,1);
	mat4 view = mat4(c1,c2,c3,c4);
	vec4 final = vrv_proj_matrix*view*vec4(pos,1);
	gl_Position = final.xyzz;
	TexCoords = pos;
}
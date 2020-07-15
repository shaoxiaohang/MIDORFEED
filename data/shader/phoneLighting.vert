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
	
	vec4 view_coor = vrv_view_matrix*vec4(pos,1);
	vec3 projected_view = vec3(view_coor.x / abs(view_coor.z),
	view_coor.y / abs(view_coor.z), 1.0);
	
	float xc = projected_view.x;
    float yc = projected_view.y;
    float rc2 = xc * xc + yc * yc;
	
    float k1 = -0.4619076504532866;
    float k2 = 0.25455138686362;
	
	mat3 intrinsic_ = mat3(
   868.6247, 0, 0, // first column (not row!)
   0, 868.6247, 0, // second column
   512, 288, 1  // third column
	);

    float xc_distortion = xc * (1 + k1 * rc2 + k2 * rc2*rc2);
	//float xc_distortion = xc;
	//float yc_distortion = yc;
    float yc_distortion = yc * (1 + k1 * rc2 + k2 * rc2*rc2);
	
	projected_view.x = xc_distortion;
    projected_view.y = yc_distortion;
	vec3 distortion_vec = intrinsic_ * projected_view;
    float distortion_ndc_x = 2.0f * distortion_vec.x / 1024.0f - 1.0f;;
    float distortion_ndc_y = 2.0f * distortion_vec.y / 576.0f - 1.0f;
	
	gl_Position = vrv_proj_matrix*vrv_view_matrix*vec4(pos,1);
	
	gl_Position.x = distortion_ndc_x * gl_Position.w;
	gl_Position.y = distortion_ndc_y * gl_Position.w;
	
	
	//gl_Position.w = gl_Position.w * 2;
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
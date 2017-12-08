#version 330
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
	vec2 tex_st;
	vec3 vrv_normal;
	vec3 frag_pos;
} gs_in[];

out vec2 tex_st;
out vec3 vrv_normal;
out vec3 frag_pos;

vec3 getNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position)- vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position)- vec3(gl_in[1].gl_Position);
	vec3 c = normalize(cross(a,b));
	return c;
}

vec4 explode(vec4 pos, vec3 normal)
{
	vec4 explode_pos  = pos + vec4(0.2*normal,0);
	return explode_pos;
}

void main()
{

	vec3 normal = getNormal();
    gl_Position =explode( gl_in[0].gl_Position,normal );
	tex_st = gs_in[0].tex_st;
	vrv_normal = gs_in[0].vrv_normal;
	frag_pos = gs_in[0].frag_pos;
    EmitVertex();   
	
    gl_Position = explode( gl_in[1].gl_Position,normal );
	tex_st = gs_in[1].tex_st;
	vrv_normal = gs_in[1].vrv_normal;
	frag_pos = gs_in[1].frag_pos;
    EmitVertex();   
	
    gl_Position = explode( gl_in[2].gl_Position,normal );
	tex_st = gs_in[2].tex_st;
	vrv_normal = gs_in[2].vrv_normal;
	frag_pos = gs_in[2].frag_pos;
    EmitVertex();   

    EndPrimitive();
}
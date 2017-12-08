#version 330
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;


vec3 getNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position)- vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position)- vec3(gl_in[1].gl_Position);
	vec3 c = normalize(cross(a,b));
	return c;
}

void generateLine(vec4 pos, vec3 normal)
{
	gl_Position = pos;
	EmitVertex();
	gl_Position = pos + 0.2 * vec4(normal,0);
	EmitVertex();
}

void main()
{
	vec3 normal = getNormal();
	generateLine(gl_in[0].gl_Position,normal);
	generateLine(gl_in[1].gl_Position,normal);
	generateLine(gl_in[2].gl_Position,normal);
}
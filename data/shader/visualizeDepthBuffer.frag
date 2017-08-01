uniform bool optimizeVisualizeDepth;
out vec4 color;

#define vrv_near_plane 0.1
#define vrv_far_plane 100

float optimizeVisualizeDepthBuffer(float n, float f, bool optimize);

void main()
{
	
	float d = optimizeVisualizeDepthBuffer(vrv_near_plane,vrv_far_plane,optimizeVisualizeDepth);
	color = vec4(d,d,d,1);
}

float optimizeVisualizeDepthBuffer(float n, float f, bool optimize)
{
	if(optimize)
	{
		float zView = n*f/(f + (n-f)*gl_FragCoord.z);
		return clamp((zView-n)/(f-n),0,1);
	}
	else
		return gl_FragCoord.z;
}

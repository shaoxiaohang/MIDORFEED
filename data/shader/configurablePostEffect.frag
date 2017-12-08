#version 330

out vec4 color;
uniform sampler2D scene;
uniform int effectType;
in vec2 TexCoords;

void inverse(inout vec4 color);
void grayScale(inout vec4 color);
void sharpen(inout vec4 color);
void blur(inout vec4 color);
void edgeDetection(inout vec4 color);


void main()
{
	color = texture2D(scene,TexCoords);
	

	switch (effectType)
	{
		case 0:
		break;
		
		case 1:
		inverse(color);
		break;
	
		case 2:
		grayScale(color);
		break;
		
		case 3:
		sharpen(color);
		break;
		
		case 4:
		blur(color);
		break;
		
		case 5:
		edgeDetection(color);
		break;
		
		default:
		break;
		
	};
	
	
}

void inverse(inout vec4 color)
{
	color = vec4(vec3(1.0)-vec3(color),color.a);
}

void grayScale(inout vec4 color)
{
	float average = (color.r + color.g + color.b) / 3.0;
	color = vec4(average,average,average,color.a);
}

vec4 kernel(float[9] matrix)
{
	float offset = 1/300.0;
	
	vec2 offsets[9] = vec2[](vec2(-offset,offset), vec2(0,offset),vec2(offset,offset),
						vec2(-offset,0), vec2(0,0),vec2(offset,0),
						vec2(-offset,-offset),vec2(0,-offset),vec2(offset,-offset));
	vec4 summer =vec4(0);		
	for (int i=0 ;i < 9 ; ++i)
	{
		summer += texture2D(scene,TexCoords + offsets[i])*matrix[i];
	}
	
	return summer;
}


void sharpen(inout vec4 color)
{
	float kernelMatrix[9] = float[](-1,-1,-1,-1,9,-1,-1,-1,-1);
	color = kernel(kernelMatrix);
}

void blur(inout vec4 color)
{
	float kernelMatrix[9] = float[](1.0/16.0,2.0/16.0,1.0/16.0,2.0/16.0,4.0/16.0,2.0/16.0,1.0/16.0,2.0/16.0,1.0/16.0);
	color = kernel(kernelMatrix);
}

void edgeDetection(inout vec4 color)
{
	float kernelMatrix[9] = float[](1,1,1,1,-8,1,1,1,1);
	color = kernel(kernelMatrix);
}



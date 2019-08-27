#version 330
out vec4 FragColor;


struct Material
{
	sampler2D diffuse_tex;
	sampler2D specular_tex;
	sampler2D normal_tex;
	bool hasDiffuse;
	bool hasSpecular;
	bool hasNormal;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

layout (std140) uniform CameraUBO
{
	mat4 vrv_proj_matrix;
	mat4 vrv_view_matrix;
	vec3 vrv_view_pos;
};

uniform Material vrv_material;
uniform samplerCube skybox;
uniform bool vrv_discardAlpha;
uniform float vrv_discardAlphaThreshold;
uniform bool vrv_isTransparent;
uniform sampler2D shadowMap;
uniform bool isLightPoint;
uniform bool isEllipsoid;
uniform vec2 grid_width;
uniform vec2 grid_resolution;

in vec2 tex_st;
in vec3 vrv_normal;
in vec3 vrv_tangent;
in vec3 frag_pos;
in vec4 frag_pos_lightSpace;

struct vrv_light_struct
{
	bool 	used;
	//0 direction light 
	//1 point light
	//2 spot light
	bool castShadow;
	int 	type;
	vec3	position;
	vec3 	direction;
	vec3 	ambient;
	vec3 	diffuse;
	vec3 	specular;
	float 	constant;
	float 	linear;
	float 	quadratic;
	float 	fade;
	float 	cutoff;
};

#define VRV_MAX_NUM_LIGHTS 4
uniform vrv_light_struct vrv_lights[VRV_MAX_NUM_LIGHTS];

//Lighting functions
vec3 phoneLighting(vrv_light_struct light,vec3 diffuse,vec3 specular,float shininess, vec3 N);
vec3 calculateLightColor(vec4 diffuse,vec4 specular,float shininess, vec3 N);
vec3 calculateReflectiveColor();
vec3 calculateRefractiveColor();
float calcualteShadowFactor();
vec3 normalMap();
vec3 calculateNormalForEllispoid(vec3 position);
vec2 calculateTexCoordinateForEllispoid(vec3 normal);
bool intersectEllipsoid(inout float t);

const float earth_radius_a = 6378137;
const float earth_radius_b = 6378137;
const float earth_radius_c = 6356752.314245;

void main()
{	


	vec2 st;
	vec3 N;
	
	//if(isEllipsoid)
	//{
		//vec2 distanceToLine = mod(st,grid_resolution);
		//vec2 dx = abs(dFdx(st));
		//vec2 dy = abs(dFdy(st));
		//vec2 dF = vec2(max(dx.s,dy.s),max(dx.t,dy.t))*grid_width;
		//if(any(lessThan(distanceToLine,dF)))
		//{
			//FragColor = vec4(1,0,0,1);
			//return;
		//}
	//}

	if(isEllipsoid)
	{
		float t=0;
		bool intersect = intersectEllipsoid(t);
				
		if(intersect)
		{
			vec3 direction = normalize(frag_pos-vrv_view_pos);
			vec3 intersectPos = vrv_view_pos + t*direction;
			N = calculateNormalForEllispoid(intersectPos);
			st = calculateTexCoordinateForEllispoid(N);
			FragColor = vrv_material.diffuse * texture2D(vrv_material.diffuse_tex,st);
			//FragColor = vec4(1,0,0,1);
		}
		else
		{
			discard;
		}
	}	
	else
	{
		st = tex_st;
		if(vrv_material.hasNormal)
		{
			N = normalMap();
		}
		else
		{
			N = vrv_normal;
		}

		N = normalize(N);
		
		
		if(isLightPoint)
		{
			FragColor = vec4(vrv_material.diffuse.rgb,1);
		}
		else
		{
			vec4 diffuse;
			vec4 specular;
			if(vrv_material.hasDiffuse)
			{
				diffuse = vrv_material.diffuse * texture2D(vrv_material.diffuse_tex,st);
				if(vrv_discardAlpha)
				{
					if(diffuse.a < vrv_discardAlphaThreshold)
						discard;
				}
			}	
			else
				diffuse = vrv_material.diffuse;
			if(vrv_material.hasSpecular)
				specular = vrv_material.specular * texture2D(vrv_material.specular_tex,st);
			else
				specular = vrv_material.specular;
		
			float alpha = vrv_isTransparent ? diffuse.a : 1;

			FragColor = vec4(calculateLightColor(diffuse,specular,vrv_material.shininess, N),alpha);
		}
	}
	
}

vec3 calculateLightColor(vec4 diffuse,vec4 specular,float shininess, vec3 N)
{
	vec3 finalColor = vec3(0);
	bool hasLight = false;
	for(int i=0; i<VRV_MAX_NUM_LIGHTS; ++i)
	{
		if(vrv_lights[i].used)
		{
			finalColor += phoneLighting(vrv_lights[i],diffuse.xyz,specular.xyz,shininess ,N);
			hasLight = true;
		}
			
	}
	
	if(!hasLight)
	{
		finalColor = diffuse.xyz;
	}
	
	//finalColor += calculateReflectiveColor();
	//finalColor += calculateRefractiveColor();
		
	return finalColor;
}

vec3 phoneLighting(vrv_light_struct light,vec3 diffuse,vec3 specular,float shininess,vec3 N)
{
	vec3 ambient_color = vec3(0,0,0);
	vec3 diffuse_color = vec3(0,0,0);
	vec3 specular_color = vec3(0,0,0);

	if(light.type == 0)
	{
		vec3 L = normalize(-light.direction);
		float theta = max(dot(N,L),0);
		vec3 view_direction = normalize(vrv_view_pos-frag_pos);
		vec3 H = normalize(L + view_direction);
		ambient_color = light.ambient * diffuse;
		diffuse_color = diffuse*theta*light.diffuse;	
		specular_color = pow(max(dot(H,N),0),shininess)* light.specular * specular;
	}
	else if(light.type == 1)
	{
		vec3 lightDirection = light.position - frag_pos;
		float distance = length(lightDirection);
		lightDirection = normalize(lightDirection);
		vec3 view_direction = normalize(vrv_view_pos-frag_pos);
		vec3 H = normalize(lightDirection + view_direction);
		float theta = max(dot(N,lightDirection),0);
		float strength = 1.0/(light.constant + light.linear*distance + light.quadratic*distance*distance);
		ambient_color = light.ambient * diffuse*strength;
		diffuse_color = theta*light.diffuse*diffuse*strength;
		specular_color = pow(max(dot(H,N),0),shininess) * light.specular * specular * strength;
	}
	else
	{
		vec3 lightDirection = light.position - frag_pos;
		float distance = length(lightDirection);
		float strength = 1.0/(light.constant + light.linear*distance + light.quadratic*distance*distance);
		lightDirection = normalize(lightDirection);
		vec3 view_direction = normalize(vrv_view_pos-frag_pos);
		vec3 H = normalize(lightDirection + view_direction);
		float theta = max(dot(N,lightDirection),0);
		float intensity;
		if(theta <= light.cutoff)
			intensity =0;
		else if(theta > light.cutoff && theta < light.fade)
		{
			intensity = clamp((theta-light.cutoff)/(light.fade-light.cutoff),0.0,1.0);
		}
		else 
		{
			intensity = 1.0;
		}
		ambient_color = intensity*light.ambient*diffuse*strength;
		diffuse_color = intensity*max(dot(N,lightDirection),0)*light.diffuse*diffuse*strength;
		specular_color = intensity*pow(max(dot(H,N),0),shininess) * light.specular * specular * strength;	
	}
	
	float shadowFactor = 1.0f;
	
	if(light.castShadow)
		shadowFactor = calcualteShadowFactor();
	
	//return specular_color;
	return ambient_color + (diffuse_color+specular_color) * shadowFactor  ;
	//return vec3(shadowFactor);
	//return frag_pos_lightSpace.xyz;
}

vec3 calculateReflectiveColor()
{
	vec3 I = normalize(vrv_view_pos-frag_pos);
	vec3 N = normalize(vrv_normal);
	vec3 R = reflect(I,N);
	vec3 reflective = texture(skybox,R).xyz;
	return reflective*0.1;
}

vec3 calculateRefractiveColor()
{
	float ratio = 1.0/1.52;
	vec3 I = normalize(vrv_view_pos-frag_pos);
	vec3 N = normalize(vrv_normal);
	vec3 R = refract(I,N,ratio);
	vec3 refractive = texture(skybox,R).xyz;
	return refractive*0.1;
}

float calcualteShadowFactor()
{
	float w = frag_pos_lightSpace.w;
	vec2 NDC = vec2(frag_pos_lightSpace.x/w,frag_pos_lightSpace.y/w);
	vec2 tex = NDC*0.5 + 0.5;
	
	
	float currentDepth = frag_pos_lightSpace.z / w;
	
	if(currentDepth >= 1.0)
		return 1;
	
	
	vec2 texSize = 1.0 / textureSize(shadowMap,0);
	
	float shadow = 0;
	for(int x= -1; x <=1; ++x)
	{
		for(int y= -1; y <=1; ++y)
		{
			float closetDepth = texture2D(shadowMap,tex + vec2(x,y)*texSize).r;
			shadow += closetDepth < currentDepth ? 0 : 1;
		}
	}
	
	shadow = shadow/9.0;
	
	return shadow;
	//return frag_pos.z;
	//return currentDepth;
}

vec3 normalMap()
{
	vec3 N = normalize(vrv_normal);
	vec3 T = normalize(vrv_tangent);
	T = normalize(T - dot(T, N) * N);
	vec3 samplerNormal = texture2D(vrv_material.normal_tex,tex_st).rgb;
	samplerNormal = normalize( 2*samplerNormal -vec3(1) );
	vec3 B = cross(N, T);	
	mat3 TBN = mat3(T, B, N);
	vec3 perturbedN = normalize(TBN * samplerNormal);
	
	return perturbedN;
}

vec3 calculateNormalForEllispoid(vec3 position)
{
	vec3 normal = vec3(position.x/(earth_radius_a*earth_radius_a), position.y/(earth_radius_b*earth_radius_b), position.z/(earth_radius_c*earth_radius_c));
	normal = normalize(normal);
	return normal;
}

vec2 calculateTexCoordinateForEllispoid(vec3 normal)
{
	float PI = 3.14159265359;
	float twoPI = 6.28318530718;
	vec2 st;
	st.x = atan(normal.y,normal.x) / twoPI + 0.5;
	st.y = asin(normal.z) / PI + 0.5;
	return st;
}

bool intersectEllipsoid(inout float t)
{
	vec3 abcsquare = vec3(1.0/(earth_radius_a*earth_radius_a),1.0/(earth_radius_b*earth_radius_b),1.0/(earth_radius_c*earth_radius_c));
	vec3 origin = vrv_view_pos;
	vec3 originsquare = vrv_view_pos*vrv_view_pos;
	vec3 direction = normalize(frag_pos-vrv_view_pos);
	vec3 directionsquare = direction*direction;
	float a = dot(abcsquare,directionsquare);
	float b = 2.0*dot(direction*origin,abcsquare);
	float c = dot(originsquare,abcsquare)-1.0;
	float d = b*b- 4.0*a*c;
		
	if(d < 0)
	{
		return false;
	}
	else
	{
		float sqrtd = sqrt(d);
		float t1 = (-b-sqrtd)/(2*a);
		float t2 = (-b+sqrtd)/(2*a);
		t = min(t1,t2);
		return true;
	}
		
		
}




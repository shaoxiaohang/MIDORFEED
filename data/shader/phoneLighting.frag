struct Material
{
	sampler2D diffuse_tex;
	sampler2D specular_tex;
	bool hasDiffuse;
	bool hasSpecular;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform Material vrv_material;
uniform vec3 vrv_view_pos;
uniform bool vrv_discardAlpha;
uniform float vrv_discardAlphaThreshold;

in vec2 tex_st;
in vec3 vrv_normal;
in vec3 frag_pos;
out vec4 color;

struct vrv_light_struct
{
	bool 	used;
	//0 direction light 
	//1 point light
	//2 spot light
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

#define VRV_MAX_NUM_LIGHTS 2
uniform vrv_light_struct vrv_lights[VRV_MAX_NUM_LIGHTS];

//Lighting functions
vec3 phoneLighting(vrv_light_struct light,vec3 diffuse,vec3 specular,float shininess);
vec3 calculateLightColor(vec4 diffuse,vec4 specular,float shininess);

void main()
{
	vec4 diffuse;
	vec4 specular;
	if(vrv_material.hasDiffuse)
	{
		diffuse = vrv_material.diffuse * texture2D(vrv_material.diffuse_tex,tex_st);
	}
	else
		diffuse = vrv_material.diffuse;
	if(vrv_material.hasSpecular)
		specular = vrv_material.specular * texture2D(vrv_material.specular_tex,tex_st);
	else
		specular = vrv_material.diffuse;
	color = vec4(calculateLightColor(diffuse,specular,vrv_material.shininess),1);
}

vec3 calculateLightColor(vec4 diffuse,vec4 specular,float shininess)
{
	vec3 finalColor = vec3(0);
	for(int i=0; i<VRV_MAX_NUM_LIGHTS; ++i)
	{
		if(vrv_lights[i].used)
			finalColor += phoneLighting(vrv_lights[i],diffuse.xyz,specular.xyz,shininess);
	}
	return finalColor;
}

vec3 phoneLighting(vrv_light_struct light,vec3 diffuse,vec3 specular,float shininess)
{
	vec3 ambient_color = vec3(0,0,0);
	vec3 diffuse_color = vec3(0,0,0);
	vec3 specular_color = vec3(0,0,0);
	vec3 N = normalize(vrv_normal);

	if(light.type == 0)
	{
		float theta = max(dot(N,-light.direction),0);
		vec3 view_direction = normalize(vrv_view_pos-frag_pos);
		ambient_color = light.ambient * diffuse;
		diffuse_color = diffuse*theta*light.diffuse;	
		specular_color = pow(max(dot(reflect(light.direction,N),view_direction),0),shininess)* light.specular * specular;
	}
	else if(light.type == 1)
	{
		vec3 lightDirection = light.position - frag_pos;
		float distance = length(lightDirection);
		lightDirection = normalize(lightDirection);
		vec3 view_direction = normalize(vrv_view_pos-frag_pos);
		float theta = max(dot(N,lightDirection),0);
		float strength = 1.0/(light.constant + light.linear*distance + light.quadratic*distance*distance);
		ambient_color = light.ambient * diffuse*strength;
		diffuse_color = theta*light.diffuse*diffuse*strength;
		specular_color = pow(max(dot(reflect(lightDirection,N),view_direction),0),shininess) * light.specular * specular * strength;
	}
	else
	{
		vec3 lightDirection = light.position - frag_pos;
		float distance = length(lightDirection);
		float strength = 1.0/(light.constant + light.linear*distance + light.quadratic*distance*distance);
		lightDirection = normalize(lightDirection);
		vec3 view_direction = normalize(vrv_view_pos-frag_pos);
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
		specular_color = intensity*pow(max(dot(reflect(lightDirection,N),view_direction),0),shininess) * light.specular * specular * strength;	
	}
	//return specular_color;
	return ambient_color+diffuse_color+specular_color;
}




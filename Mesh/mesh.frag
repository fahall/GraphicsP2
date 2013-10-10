#version 400

in vec3 eyeposition;
in vec3 normal;
flat in vec3 color;

out vec4 FragColor;

const float shininess = 100.0f;
const vec3 lightPosition = vec3(0.0f, 0.0f, 0.0f);

//ambient
const vec3 ambientLightColor = vec3(0.2f, 0.0f, 0.1f);
const vec3 ambientMatColor = vec3(0.9f, 0.0f, 0.3f);

//diffuse
const vec3 diffuseLightColor = vec3(1.0f, 1.0f, 1.0f);
const vec3 diffuseMatColor = vec3(0.4f, 0.2f, 0.6f);

//specular
const vec3 specularLightColor = vec3(1.0f, 1.0f, 1.0f);
const vec3 specularMatColor = vec3(1.0f, 1.0f, 1.0f);

vec3 ads() {

	vec3 L = normalize(lightPosition - eyeposition);
	vec3 N = normalize(normal);
	vec3 E = normalize(-eyeposition);
	vec3 H = normalize(L + E);


	
	
	vec3 ambient = ambientLightColor * ambientMatColor;


	//vec3 diffuse = (L.x*N.x + L.y*N.y + L.z*N.z) * diffuseLightColor.x;
	//diffuse = dot(L, N) *  diffuseLightColor.y;
	//diffuse = dot(L, N) * diffuseLightColor.z;



	//vec3 specular = specularMatColor * pow( dot(N, H), shininess ) * specularLightColor;
	
	
	
	return ambient;
	
}
	

void main() {
	FragColor = vec4(ads(), 1.0f);
	//FragColor = vec4(0.0f, 1.0f, 0.5f, 1.0f);
}
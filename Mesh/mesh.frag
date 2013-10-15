
#version 400

in vec3 position;
in vec3 normal;
flat in vec3 color;
in vec2 UV;


out vec4 FragColor;


uniform sampler2D marsSampler;


const float shininess = 100.0f;
const vec3 lightPosition = vec3(-15.0f, 0.0f, 10.0f);
const vec3 lightIntensity = vec3(1.0f, 1.0f, 1.0f);

//ambient 
const vec3 Ka = vec3(0.3f, 0.0f, 0.2f);

//diffuse
const vec3 Kd = vec3(0.4f, 0.1f, 0.5f);

//specular
const vec3 Ks = vec3(0.9f, 0.9f, 0.0f);


vec3 ads() {
	//check why this has to be -normal and not +normal?? what am I doing wrong
	vec3 n = normalize( vec3(normal) ); //switches or flips what it looks like
	vec3 s = normalize( lightPosition - position );
	vec3 v = normalize( vec3(-position) );
	vec3 r = reflect( -s, n );



	vec3 ambient = lightIntensity * Ka;


	vec3 diffuse = Kd * max( dot(s, n), 0.0f);


	//vec3 specular = Ks * pow( max( dot(r, v), 0.0f), shininess);
	vec3 specular = vec3(0.0f, 0.0f, 0.0f);
	if( dot(v, n) > 0.0f) {
		specular = pow( max( dot(r, v), 0.0f), shininess) * Ks;
	}


	return clamp(ambient + diffuse, 0.0, 1.0);// + specular, 0.0, 1.0);
}

void main() {
	FragColor = vec4(ads(), 1.0f);
	//FragColor = vec4(0.0f, 1.0f, 0.5f, 1.0f);
	//FragColor = texture(marsSampler, UV);
}
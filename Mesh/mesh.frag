#version 400

in vec3 position;
in vec3 normal;
flat in vec3 color;

out vec4 FragColor;

const float shininess = 100.0f;
const vec3 lightPosition = vec3(0.0f, 0.0f, 0.0f);

vec3 ads() {
	vec3 n = normal;

	if(!gl_FrontFacing) {
		n = -n;
	}

	vec3 s = normalize(lightPosition - position);
	vec3 v = normalize(-position);
	vec3 r = reflect(-s, n);
	float s_dot_n = max( dot(s, n), 0.0f);

	return color * s_dot_n + (s_dot_n > 0 ? color * pow( max( dot(r,v), 0.0f), shininess) : vec3(0.0f));
}

void main() {
	//FragColor = vec4(ads(), 1.0f);
	FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
}
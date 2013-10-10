#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 VertexColor;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat3 normalMatrix;

out vec3 eyeposition;
out vec3 normal;
flat out vec3 color;

void main() {
	vec4 pos = projMatrix * viewMatrix * worldMatrix * vec4(VertexPosition, 1.0f);
	gl_Position = pos;

	normal = normalize(normalMatrix * VertexNormal);

	mat4 modelviewMatrix = viewMatrix * worldMatrix;

	eyeposition = vec3(modelviewMatrix * vec4(VertexPosition, 1.0f));

	color = VertexColor;
}
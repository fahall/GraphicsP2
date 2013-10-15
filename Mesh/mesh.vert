
#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 VertexColor;
layout (location = 3) in vec2 VertexUV;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform mat3 normalMatrix;

out vec3 position;
out vec3 normal;
flat out vec3 color;
out vec2 UV;

void main() {
	vec4 pos = projMatrix * viewMatrix * worldMatrix * vec4(VertexPosition, 1.0f);
	gl_Position = pos;

	//why does this not work, I've tried both vertex normals inv(tran) and tran(inv) 
	//normal = normalize(normalMatrix * VertexNormal);
	normal = normalize(VertexNormal);
	

	mat4 modelviewMatrix = viewMatrix * worldMatrix;

	position = vec3(modelviewMatrix * vec4(VertexPosition, 1.0f));

	color = VertexColor;

	UV = VertexUV;
}


#pragma once
#include "Cam.h"

#include <iostream>

float turnRadians = (float)(3.14159 / 16); //how much to turn/rotate by, in radians.

Camera::Camera() {
		camPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		camTarget = glm::vec3(0.0f, 0.0f, -1.0f);
		upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

		forwardDirection = glm::vec3(0.0f, 0.0f, -1.0f);
		rightDirection = glm::vec3(1.0f, 0.0f, 0.0f);
}

Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up) {
	camPosition = pos;
	camTarget = target;
	upDirection = up;
	//add params for these too
	forwardDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	rightDirection = glm::vec3(1.0f, 0.0f, 0.0f);
}

Camera::Camera(float radius, float theta, float phi) {
	Camera::radius = radius;
	Camera::theta = theta;
	Camera::phi = phi;
	
	//find X
	float x = radius * sinf(theta) * cosf(phi);
	//find y
	float y = radius * cosf(theta);
	//find z
	float z = radius * sinf(theta) * sinf(phi);

	camPosition = glm::vec3(x, y, z);
	camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}


Camera::~Camera() {
}

void Camera::MoveIn() {
	radius -= 5.0f; //decrease radius to move closer to origin
	if(radius <= 5.0f) {
		radius = 5.0f;
	}

	//find X
	float x = radius * sinf(theta) * cosf(phi);
	//find y
	float y = radius * cosf(theta);
	//find z
	float z = radius * sinf(theta) * sinf(phi);

	camPosition = glm::vec3(x, y, z);
	camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::MoveOut() {
	radius += 5.0f; //decrease radius to move closer to origin
	if(radius > 500.0f) {
		radius = 500.0f;
	}

	//find X
	float x = radius * sinf(theta) * cosf(phi);
	//find y
	float y = radius * cosf(theta);
	//find z
	float z = radius * sinf(theta) * sinf(phi);

	camPosition = glm::vec3(x, y, z);
	camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}


void Camera::MoveUp() {
	theta -= 0.157f;
	if(theta <= 0.157f) {
		theta = 0.157f;
	}
	//find X
	float x = radius * sinf(theta) * cosf(phi);
	//find y
	float y = radius * cosf(theta);
	//find z
	float z = radius * sinf(theta) * sinf(phi);

	camPosition = glm::vec3(x, y, z);
	camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::MoveDown() {
	theta += 0.157f;
	if(theta > 3.141592f) {
		theta = 3.141592f;
	}
	//find X
	float x = radius * sinf(theta) * cosf(phi);
	//find y
	float y = radius * cosf(theta);
	//find z
	float z = radius * sinf(theta) * sinf(phi);

	camPosition = glm::vec3(x, y, z);
	camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::MoveRight() {
	phi -= 0.157f;
	/*if(phi >= 2.0f * 3.141592f) {
		phi = 0.0f;
	}*/

	//find X
	float x = radius * sinf(theta) * cosf(phi);
	//find y
	float y = radius * cosf(theta);
	//find z
	float z = radius * sinf(theta) * sinf(phi);

	camPosition = glm::vec3(x, y, z);
	camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::MoveLeft() {
	phi += 0.157f;
	/*if(phi >= 2.0f * 3.141592f) {
		phi = 0.0f;
	}*/

	//find X
	float x = radius * sinf(theta) * cosf(phi);
	//find y
	float y = radius * cosf(theta);
	//find z
	float z = radius * sinf(theta) * sinf(phi);

	camPosition = glm::vec3(x, y, z);
	camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
}


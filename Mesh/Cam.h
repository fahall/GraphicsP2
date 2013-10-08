#include <glm.hpp>


class Camera {
public:
	//needed for calculating view matrix
	glm::vec3 camPosition;
	glm::vec3 camTarget;
	glm::vec3 upDirection;

	float radius, theta, phi; //used for spherical coordinates




	//needed to keep track of view direction: forward and right
	glm::vec3 forwardDirection;
	glm::vec3 rightDirection;
	//////////////////////////////////////////////

public:
	Camera();
	Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
	Camera(float radius, float theta, float phi);
	~Camera();


	//I will not be using these since this is not a first person camera.
	/*void MoveForward();
	void MoveBackward();

	void MoveRight();
	void MoveLeft();

	void TurnRight();
	void TurnLeft();

	void mouseTurnX(float radians); //positive radians turn left, negative radians turn right
	void mouseTurnY(float radians); //positive radians look up, negative radians look down
	*/
	////////////////////////////////////////////////////////////////////////////////

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

	void MoveOut();
	void MoveIn();

};
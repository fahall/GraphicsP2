#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GraphicsGL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
using glm::vec3;
using glm::mat4;
#include <vector>
#include "Cam.h"
#include "FileReader.h"

#define PI 3.141592654


using namespace std;

//global texture resolution
int selectedResolution = -1;

float nearZ = 1.0f;
float farZ = 100.0f;
float frustumScale = CalcFrustumScale(45.0f);

mat4 view;
mat4 proj;

Camera cam(50.0f, (float)PI/2, (float)PI/2);

GLuint program;
GLuint vao;
GLuint positionBuffer;
GLuint normalBuffer;
GLuint colorBuffer;
GLuint elementBuffer;

//uniforms
GLuint worldUniform;
GLuint viewUniform;
GLuint projUniform;
GLuint normalMatrixUniform;

//data
vector<vec3> positionData;
vector<vec3> normalData;
vector<vec3> colorData;
vector<GLshort> indexData;

//heightInformation
int heightModifier = 5;
vector<float> heightMap;

void init() {

	//Extract the heightmap from a file.
	if(selectedResolution == 1)
	{
		heightMap = FileReader("Mars.txt");

		int numRows = heightMap[0];
		int numCols = heightMap[1];
	}
	else
	{
		int numRows = 360;
		int numCols = 140;
	}

	//setup tranformation variables theta and phi


	float radius, theta, phi;
	theta = phi = 0.0f;
	radius = 10.0f;
	float thetaStep = (float)( PI / (numRows-1) ); //num rows minus 1 
	float phiStep = (float)((2 * PI) / (numCols-1) );


	//create mesh
	//starts at bottom row of mesh and move up

	for(int i = 0; i < numRows; i++) {
		float y = (float)(i);
		for(int j = 0; j < numCols; j++) {
			float x = (float)(j);
			positionData.push_back(vec3(x, y, 0.0f));
		}
		
	}

	//init indices
	for(int i = 0; i < numRows-1; i++) {
		for(int j = 0; j < numCols-1; j++) {
			int index = i * numCols + j;

			indexData.push_back(index);
			indexData.push_back(index+1);
			indexData.push_back(index+numCols);

			indexData.push_back(index+1);
			indexData.push_back(index+1+numCols);
			indexData.push_back(index+numCols);
			
		}
	}

	//Hold the current "heightMap" index, we start at 2 because [0] & [1] are our texture dimensions
	int currentHeightMapIndex = 2;

	//apply transformations to vertices
	for(int row = 0; row < numRows; row++) {
		//get theta for current row
		theta = (float)( PI - (thetaStep * row) );

		for(int col = 0; col < numCols; col++) {
			//get phi for current col
			phi = ( phiStep * col );
			//get current vertex index
			unsigned int index = (row * numCols) + col;
			
			//Get the heightMapValue at this index
			float currentHeightMapValue = heightMap[currentHeightMapIndex] * heightModifier;

			//Get the exact radius for this point
			float currentRadius = radius + currentHeightMapValue;

			//if we are at first or last row, meaning we are at top or bottom of poles, just make each vertex with that row/col
			//to be (0, 1, 0) or (0, -1, 0)
			if(row == numRows-1) {

				positionData.at(index) = vec3(0.0f, +currentRadius, 0.0f);
			}else if(row == 0) {
				positionData.at(index) = vec3(0.0f, -currentRadius, 0.0f);
			}else {
				float x, y, z;
				x = currentRadius * sinf(theta) * cosf(phi);
				y = currentRadius * cosf(theta);
				z = currentRadius * sinf(theta) * sinf(phi);
				positionData.at(index) = vec3(x, y, z);
				//now that we have our final vertex positions, add normals
				vec3 n = positionData.at(index);
				n = glm::normalize(n);
				normalData.push_back(n);
				//add color attribute
				colorData.push_back(vec3(0.3f, 0.2f, 0.0f));
			}
			//After we've used this heightMap value, we will move to the next heightMap point
			currentHeightMapIndex++;

		} //end inner for()
	} //end outer for()



	//initialize program
	GLuint vertShader, fragShader;

	vertShader = LoadShader(GL_VERTEX_SHADER, "L:/Desktop/Mesh/mesh.vert");
	fragShader = LoadShader(GL_FRAGMENT_SHADER, "L:/Desktop/Mesh/mesh.frag");

	program = CreateProgram(vertShader, fragShader);

	worldUniform = glGetUniformLocation(program, "worldMatrix");
	viewUniform = glGetUniformLocation(program, "viewMatrix");
	projUniform = glGetUniformLocation(program, "projMatrix");
	normalMatrixUniform = glGetUniformLocation(program, "normalMatrix");

	//get view matrix
	view = CalcViewMatrix(cam.camPosition, cam.camTarget, cam.upDirection);
	//set perspective matrix
	proj[0].x = frustumScale;
	proj[1].y = frustumScale;
	proj[2].z = (farZ + nearZ) / (nearZ - farZ);
	proj[2].w = -1.0f;
	proj[3].z = (2 * farZ * nearZ) / (nearZ - farZ);

	//update uniforms
	glUseProgram(program);
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projUniform, 1, GL_FALSE, glm::value_ptr(proj));
	glUseProgram(0);

	//initialzie buffers
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * positionData.size(), (float*)positionData.data(), GL_STATIC_DRAW); //second param: number of floats
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * normalData.size(), (float*)normalData.data(), GL_STATIC_DRAW); //second param: number of floats
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * colorData.size(), (float*)colorData.data(), GL_STATIC_DRAW); //second param: number of floats
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLshort) * indexData.size(), (GLshort*)indexData.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//make connections between the buffer objects and the generic vertex attribute indexes
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

	glBindVertexArray(0);


} //end function

void render() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);
	glBindVertexArray(vao);

	mat4 world(1.0f);
	//world[0].x = world[1].y = 0.5f; //scale down to half size, if I scale, must us normal matrix even though uniform scale
	world[3] = glm::vec4(5.0f, 3.0f, -20.0f, 1.0f); //move away, light at origin
	glUniformMatrix4fv(worldUniform, 1, GL_FALSE, glm::value_ptr(world));

	view = CalcViewMatrix(cam.camPosition, cam.camTarget, cam.upDirection);
	glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));

	mat4 modelview = view * world;

	glm::mat3 normalMatrix(1.0f);
	normalMatrix = glm::mat3(glm::inverse(glm::transpose(modelview)));

	glUniformMatrix4fv(normalMatrixUniform, 1, GL_FALSE, glm::value_ptr(normalMatrix));

	glDrawElements(GL_TRIANGLES, indexData.size(), GL_UNSIGNED_SHORT, 0);


	glBindVertexArray(0);
	glUseProgram(0);

	glutSwapBuffers();
	glutPostRedisplay();

}

void reshape(int w, int h) {
	proj[0].x = frustumScale * (h/(float)w);

	glUseProgram(program);
	glUniformMatrix4fv(projUniform, 1, GL_FALSE, glm::value_ptr(proj));
	glUseProgram(0);

	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 'w': 
			cam.MoveUp();
			break;
		case 's':
			cam.MoveDown();
			break;
		case 'a':
			cam.MoveLeft();
			break;
		case 'd':
			cam.MoveRight();
			break;
		case 27:
		glutLeaveMainLoop();
		return;
	}
}



int main(int argc, char* argv[]) {

	while (selectedResolution != 1 && selectedResolution != 2 && selectedResolution != 3)
	{
		cout << "What resolution would you like?\n 1) low\n 2) medium\n 3) high" << endl;
		cin >> selectedResolution;
	}

	// initialize and run program
	glutInit(&argc, argv);      // GLUT initialization

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);  // Display Mode
	glutInitWindowSize(800, 600);		// set window size
	glutInitWindowPosition(700, 200);
	glutCreateWindow("Shading Language");		// create Window

	glutReshapeFunc(reshape);
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	
	
	//Glew init: get latest functionality
	GLenum err = glewInit();
	if(GLEW_OK != err) {
		fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(err));
	}
	
	init();

	glutMainLoop();

	return 0;
}
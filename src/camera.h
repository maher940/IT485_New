#ifndef CAMERA_H
#define CAMERA_H
#include<glm\mat4x4.hpp>




class Camera
{
public:

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float cameraspeed = 0.05f;

	float lastX = 1024 / 2.0;
	float lastY = 768 / 2.0;


	glm::vec3 camerapos = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 camerafront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f);


	Camera();

	
	void computeMatricesFromInputs();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void cameraMovement(char key);
	void cameraRotation(float x, float y);

};

#endif

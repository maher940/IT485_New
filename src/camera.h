#ifndef CAMERA_H
#define CAMERA_H
#include<glm\mat4x4.hpp>
#include "player.h"

/**
*@breif Class for the camera

*/

class Camera
{
public:

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float cameraspeed = 0.15f;

	float lastX = 1024 / 2.0;
	float lastY = 768 / 2.0;


	glm::vec3 camerapos = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 camerafront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f);


	Camera();

	/**
	*@breif Changes the camera Movement

	*/
	void computeMatricesFromInputs(Player_Struct* player);
	/**
	*@breif returns view matrix

	*/
	glm::mat4 getViewMatrix();
	/**
	*@breif returns projection matrix

	*/
	glm::mat4 getProjectionMatrix();
	/**
	*@breif changes camera's positon

	*/
	void cameraMovement(char key);
	/**
	*@breif rotates camera

	*/
	void cameraRotation(float x, float y, Player_Struct* player);

};

#endif

#include "camera.h"
#include<iostream>

#include "graphics3d.h"
#include <glm/gtc/matrix_transform.hpp>



Camera::Camera()
{

}

glm::mat4 Camera::getProjectionMatrix()
{

	return ViewMatrix;

}


glm::mat4 Camera::getViewMatrix()
{
	return ProjectionMatrix;
}



void Camera::cameraMovement(char key)
{


	if (key == 'W')
	{
		camerapos -= cameraspeed * camerafront;
	}
	if (key == 'S')
	{
		camerapos += cameraspeed * camerafront;
	}
	if (key == 'A')
	{

		camerapos += glm::normalize(glm::cross(camerafront, cameraup)) * cameraspeed;
	}
	if (key == 'D')
	{
		camerapos -= glm::normalize(glm::cross(camerafront, cameraup)) * cameraspeed;
	}
}
bool firstMouse = true;
void Camera::cameraRotation(float x, float y, Player_Struct* player)
{
	
}

void Camera::computeMatricesFromInputs(Player_Struct* player)
{

	ViewMatrix = glm::lookAt(camerapos, camerapos + camerafront, cameraup);

	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}
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
void Camera::cameraRotation(float x, float y)
{



	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y; // Reversed since y-coordinates go from bottom to left
	lastX = x;
	lastY = y;

	float sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;


	/*
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camerafront = glm::normalize(front);
	*/



	glm::vec3 direction(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
		sin(glm::radians(pitch)),
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	);

	camerafront = glm::normalize(direction);
	SDL_Window *window = getwindow();
	

}

void Camera::computeMatricesFromInputs()
{
	
	ViewMatrix = glm::lookAt(camerapos, camerapos + camerafront, cameraup);

	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}
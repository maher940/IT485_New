#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <vector>
#include <stdio.h>
#include<iostream>
#include<GL\glew.h>
#include<glm\vec3.hpp>
#include <glm\vec2.hpp>

/**
*@breif Class for the buttons on the UI

*/
class Button
{

public:

	GLuint vertexbuffer;
	GLuint uvbuffer;

	std::vector<glm::vec3> Button_Verts;
	std::vector<glm::vec3> Button_UVs;
	Button();
	/**
	*@breif Sets up the button size

	*/
	void Button_Setup(glm::vec3 TopRight, glm::vec3 TopLeft, glm::vec3 BotRight, glm::vec3 BotLeft);
	/**
	*@breif Draws the button

	*/
	void Button_Draw();

};









#endif
#ifndef __HUD_H__
#define __HUD_H__

#include <vector>
#include <stdio.h>
#include<iostream>
#include<GL\glew.h>
#include<glm\vec3.hpp>
#include <glm\vec2.hpp>

/**
*@breif Class to create a HUD

*/
class HUD
{

public:

	GLuint vertexbuffer;
	GLuint UVbuffer;
	std::vector<glm::vec3> HUD_Verts;
	std::vector<glm::vec2> HUD_UVs;
	std::vector<unsigned int> HUD_Indices;
	HUD();

/**
*@breif Sets up hud points

*/
void	Set_HUD_Points();

/**
*@breif Draws the hud

*/
void 	Draw_HUD();

/**
*@breif Sets up texture

*/
void	TextureSetUp();

/**
*@breif Loads a texture

*/
void	TextureLoad();

};












#endif



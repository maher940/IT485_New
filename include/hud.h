#ifndef __HUD_H__
#define __HUD_H__

#include <vector>
#include <stdio.h>
#include<iostream>
#include<GL\glew.h>
#include<glm\vec3.hpp>
#include <glm\vec2.hpp>
class HUD
{

public:

	GLuint vertexbuffer;
	GLuint UVbuffer;
	std::vector<glm::vec3> HUD_Verts;
	std::vector<glm::vec2> HUD_UVs;
	std::vector<unsigned int> HUD_Indices;
	HUD();
void	Set_HUD_Points();


void 	Draw_HUD();

void	TextureSetUp();

void	TextureLoad();

};












#endif



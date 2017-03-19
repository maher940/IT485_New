#ifndef __TEST_H__
#define __TEST_H__

#include <glm\vec3.hpp>
#include <glm\vec2.hpp>
#include <GL\glew.h>
#include <stdio.h>
#include <iostream>
#include<vector>
using std::string;


typedef struct  {
	glm::vec3 Position;
}Vertex;


class Test
{
public:
	std::vector<Vertex> vertices;


	Test(std::vector<Vertex> vertices);

	void Draw();


private:
	

	
};






#endif
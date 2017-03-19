#ifndef __TESTMESH_H__
#define __TESTMESH_H__
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "loadobj.h"
using namespace std;

struct Vertex
{
	glm::vec3 Position;
	//glm::vec3 Normals;
	//glm::vec2 Texels;

};



class Mesh
{

public:
	Mesh(Vertex* vertices, unsigned int numverts);

	void Draw();
private:
	Mesh(const Mesh& other);
	void operator=(const Mesh& other);



};








#endif
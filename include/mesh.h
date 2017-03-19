#ifndef __MESH_H__
#define __MESH_H__


#include <stdio.h>
#include <vector>
#include<iostream>
#include<glm\vec3.hpp>
#include<glm\vec2.hpp>
#include<GL\glew.h>

typedef class Iarray_t
{
public:
	unsigned int x;
	unsigned int y;
	unsigned int z;
	bool operator==(const Iarray_t &other);
}Iarray;




typedef struct
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 Texel;

}Vertex;
typedef struct
{
	Vertex x;
	Vertex y;
	Vertex z;

}Face;
typedef struct
{
	GLuint id;
	std::string type;
}Texture;

class Mesh
{


	std::vector<Vertex> vertices;
	std::vector<Vertex> vertices2;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	unsigned int indexsize;
	//std::

public:
	


	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	Mesh();
	~Mesh();

	bool Load_Obj(const char * path);
	void Draw_Mesh();

	void Draw_Quad();

};







#endif
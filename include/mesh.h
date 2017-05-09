#ifndef __MESH_H__
#define __MESH_H__


#include <stdio.h>
#include <vector>
#include<iostream>
#include<glm\vec3.hpp>
#include<glm\vec2.hpp>
#include<GL\glew.h>'



/**
*@breif A class to hold mesh data

*/




/**
*@breif Creates a struct for an Iarray

*/
typedef class Iarray_t
{
public:
	unsigned int x;
	unsigned int y;
	unsigned int z;
	bool operator==(const Iarray_t &other);
}Iarray;


/**
*@breif Creates a struct for Vertex info

*/

typedef struct
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 Texel;

}Vertex;
/**
*@breif Creates a struct for face info

*/
typedef struct
{
	Vertex x;
	Vertex y;
	Vertex z;

}Face;
/**
*@breif Creates a struct for texture

*/
typedef struct
{
	GLuint id;
	std::string type;
}Texture;

class Mesh
{


	

	


	//std::

public:
	
	GLuint VAO;
	GLuint vertexbuffer;
	GLuint normalbuffer;
	GLuint UVbuffer;
	GLuint IndexVBO;
	std::vector<Vertex> vertices;
	std::vector<Vertex> vertices2;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	unsigned int indexsize;


	float maxX;
	float minX;
	float maxY;
	float minY;
	float maxZ;
	float minZ;

	float xdis;
	float ydis;
	float zdis;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
	Mesh();
	~Mesh();
	/**
	*@breif Loads obj information 

	*/
	bool Load_Obj(const char * path);
	/**
	*@breif Draws a mesh based of obj info

	*/
	void Draw_Mesh();
	/**
	*@breif Loads a texture

	*/
	void TextureLoad();
	/**
	*@breif SetUps the buffers for the mesh

	*/
	void SetUp_Buffer();
	/**
	*@breif Draws a quad

	*/
	void Draw_Quad();

};







#endif
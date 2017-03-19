#ifndef __TEST2_H__
#define __TEST2_H__
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>


#include <GL/glew.h> 
#include <glm/glm.hpp>
#include <glm\vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef struct {

	glm::vec3 Pos;
	glm::vec3 Normal;
	glm::vec3 Tangent;
	glm::vec3 Color;
	glm::vec2 Texels;

}Vertex;


typedef struct
{
	GLuint id;
	std::string type;
	
}Texture;


class Mesh
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
public:

	
	Mesh(std::vector<Vertex>* vd, std::vector<GLuint>* id, std::vector<Texture>* td=NULL);
	
	~Mesh();
	void Draw(GLuint programID);

private:
	
	GLuint VAO, VBO, EBO;

};




#endif
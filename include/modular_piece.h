#ifndef __MODULAR_PIECE_H__
#define __MODULAR_PIECE_H__

#include <string>
#include <vector>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL\glew.h>
#include "mesh.h"
#include "physics.h"

/**
*@breif Creates a struct to represent a scene piece

*/

typedef struct
{

	glm::vec3 position;
	Mesh model;
	glm::mat4 ModelMat;
	int inuse;
	std::string type;
	btRigidBody* body;

}Modular_Struct;


/**
*@breif Draws a scene piece
*@param Modular_Struct the piece that will be drawn

*/

void Draw_Piece(Modular_Struct* piece);




#endif

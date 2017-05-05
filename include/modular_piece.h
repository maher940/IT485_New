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


typedef struct
{

	glm::vec3 position;
	Mesh model;
	glm::mat4 ModelMat;
	int inuse;
	std::string type;
	btRigidBody* body;

}Modular_Struct;




void Draw_Piece(Modular_Struct* piece);




#endif

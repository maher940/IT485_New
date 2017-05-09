#ifndef __ENTITY_H__
#define __ENTITY_H__
#include <vector>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL\glew.h>
#include <SDL.h>
#include "mesh.h"
#include <string>
#include <btBulletDynamicsCommon.h>
#include "physics.h"

/**
*@breif The structure that represents entities

*/
typedef struct
{
	
	glm::vec3 position;

	glm::vec3 forward;

	int inuse;

	int entity_num;

	Mesh mesh;

	glm::mat4 Model;

	glm::vec3 color;

	std::string type;

	btRigidBody* body;

	int timer;


}Entity_Struct;

/**
*@breif Thinks for the entity

*/

void Entity_Think(Entity_Struct *ent);

/**
*@breif Draws the entity

*/

void Entity_Draw(Entity_Struct *ent);
/**
*@breif Updates the entity

*/
void Entity_Update(Entity_Struct *ent);
/**
*@breif gets the entity's position

*/

glm::vec3 Entity_getPos(Entity_Struct *ent);
/**
*@breif sets the entity's positon

*/
void Entity_SetPos(Entity_Struct *ent, glm::vec3 postition);











#endif
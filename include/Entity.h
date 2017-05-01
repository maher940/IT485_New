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
typedef struct
{
	
	glm::vec3 position;

	int inuse;

	int entity_num;

	Mesh mesh;

	glm::mat4 Model;

	std::string type;

	btRigidBody* body;


}Entity_Struct;

void Entity_Think(Entity_Struct *ent);

void Entity_Draw(Entity_Struct *ent);

void Entity_Update(Entity_Struct *ent);

glm::vec3 Entity_getPos(Entity_Struct *ent);

void Entity_SetPos(Entity_Struct *ent, glm::vec3 postition);











#endif
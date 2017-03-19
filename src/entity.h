#ifndef __ENTITY_H__
#define __ENTITY_H__
#include <vector>
#include <glm\vec3.hpp>
#include <GL\glew.h>
typedef struct
{
	//Model* m;
	//Sprite* s;
	//std::vector< glm::vec3 > *velocity;
	//int Health;
	//std::vector< glm::vec3 > *position;
	

}Entity;

void Entity_Init(
	GLuint maxentities,
	GLboolean data,
	size_t datasize

);

void Entity_New();

void Entity_close();

void Entity_draw(Entity *ent);

void Entity_Update(Entity *ent);

void Entity_DrawAll();

void Entity_UpdateAll();;






#endif
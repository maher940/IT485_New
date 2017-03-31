#ifndef __ENTITYC_H
#define __ENTITYC_H

#include "glm\vec3.hpp"

#include "GL\glew.h"

#include "mesh.h"



/*
typedef struct
{

	glm::vec3 position;

	glm::vec3 velocity;

	Mesh model;


}Entity_S;

*/





class Entity {



public:


	Entity();

	void Entity_Update();


	void Entity_setposition(glm::vec3 position);

	glm::vec3 Entity_getposition();

	void Entity_setMesh(const char *path);

	void Entity_drawMesh();

	//void Enitiy_free(Entity **entity);

	int inuse;

	int Entity_num;

	glm::vec3 position;

	Mesh mesh;


};












#endif // !__ENTITYC_H



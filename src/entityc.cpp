#include "entityc.h"

#include "physics.h"

#include <glm\mat4x4.hpp>;
Entity::Entity()
{

	//position



	
}


glm::vec3 Entity::Entity_getposition()
{
	return position;
}


void Entity::Entity_setMesh(const char *path)
{

	mesh.Load_Obj(path);
}


void Entity::Entity_drawMesh()
{
	mesh.Draw_Mesh();

}

void Entity::Entity_Update()
{


	
	




}

void Entity::Entity_setposition(glm::vec3 position)
{

	position = this->position;

}

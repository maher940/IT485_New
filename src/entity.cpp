#include "entity.h"

Entity_Struct* entityList;
int numentities;

void Entity_Think(Entity_Struct *ent)
{



}


void Entity_Update(Entity_Struct *ent)
{


}

void Entity_Draw(Entity_Struct *ent)
{

	ent->mesh.Draw_Mesh();
	

}

glm::vec3 Entity_getPos(Entity_Struct *ent)
{

	return ent->position;
}

void Entity_SetPos(Entity_Struct *ent, glm::vec3 pos)
{

	ent->position = pos;


}




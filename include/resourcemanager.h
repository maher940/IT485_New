#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "entity.h"

#define maxentities 10


typedef struct
{

	//Entity_Struct* entityList;

	Entity_Struct entityList[maxentities];
	int numentities;

}Manager;


Manager* getmanager();


void Entity_Close();

void Entity_Free(Entity_Struct *ent);

void Entity_Init();

Entity_Struct* Entity_New(const char * path, glm::vec3 position);

void Entity_UpdateAll();

void Entity_DrawAll();

void Enitity_ThinkAll();






#endif

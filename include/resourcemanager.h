#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__


#include "entity.h"

#define maxentities 20

/**
*@breif Creates a struct to hold/manage all the entities 

*/

typedef struct
{

	

	Entity_Struct entityList[maxentities];
	int numentities;
	std::string type;

	

}Manager;

/**
*@breif returns a manager

*/
Manager* getmanager();

/**
*@breif closes the entity system

*/
void Entity_Close();
/**
*@breif Frees a entity up

*/

void Entity_Free(Entity_Struct *ent);

/**
*@breif Inits the entity system

*/
void Entity_Init();
/**
*@breif Creates a new entity

*/

Entity_Struct* Entity_New(const char * path, glm::vec3 position, Physics* physics, glm::vec3 color, std::string type);
/**
*@breif Updates all entitys

*/
void Entity_UpdateAll(Physics* physics);

/**
*@breif draws all entitys

*/
void Entity_DrawAll();
/**
*@breif thinks for all entities

*/
void Enitity_ThinkAll();






#endif

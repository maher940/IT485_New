#include "resourcemanager.h"
#include "entity.h"
#include "simple_logger.h"


static Manager manager;


Manager* getmanager()
{
	return &manager;
}

void Entity_Init()
{
	

	if (manager.numentities == maxentities)
	{
		slog("No more space for entities");
		return;
	}


	memset(manager.entityList, 0, sizeof(Entity_Struct)*maxentities);

	if (manager.entityList == NULL)
	{
		slog("Entity List is null failed to intialize");

	}

	
	atexit(Entity_Close);
}

void Entity_Free(Entity_Struct *ent)
{

	//manager.entityList[ent->entity_num];
	if (&manager.entityList[ent->entity_num] == NULL)
	{
		slog("Entity does not exist");
	}
	memset(&manager.entityList[ent->entity_num], 0, sizeof(Entity_Struct));
	slog("Entity Freed");
}

void Entity_Close()
{
	if (!manager.entityList)
	{
		return;
	}

	//free(manager.entityList);

	//manager.entityList = NULL;

	memset(manager.entityList, 0, sizeof(Entity_Struct));

	manager.numentities = 0;

}

Entity_Struct* Entity_New(const char * path, glm::vec3 position)
{

	int i;


	if (manager.numentities == maxentities)
	{
		slog("Cannot add more entities");

	}



	for (i = 0; i < maxentities; i++)
	{

		if (manager.entityList[i].inuse)
		{
			continue;
		}

		else {

			memset(&manager.entityList[i], 0, sizeof(Entity_Struct));
			slog("Entity added");

			if (!&manager.entityList[i])
			{
				slog("Entity additin failed");
			}

			manager.numentities++;

			manager.entityList[i].inuse = 1;

			manager.entityList[i].mesh.Load_Obj(path);

			manager.entityList[i].entity_num = i;

			manager.entityList[i].position = position;

			manager.entityList[i].Model = glm::translate(glm::mat4(), position);
		
			break;
		}
	}

	return &manager.entityList[i];

	

}
void Entity_UpdateAll()
{

}

void Entity_DrawAll()
{


	int i;


	for (i = 0; i < maxentities; i++)
	{

		if (!manager.entityList[i].inuse)
		{
			continue;
		}


		Entity_Draw(&manager.entityList[i]);

		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &vp[0][0]);
		
	}
	

}

void Enitity_ThinkAll()
{

}
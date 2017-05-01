#include "resourcemanager.h"

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

Entity_Struct* Entity_New(const char * path, glm::vec3 position, Physics physics)
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

			float width;
			float height;
			float depth;

			width = manager.entityList[i].mesh.xdis;

			height = manager.entityList[i].mesh.ydis;

			depth = manager.entityList[i].mesh.zdis;

			manager.entityList[i].body = physics.CubeRigidBody(glm::vec3(width, height, depth), position, 1);

			//manager.entityList[i].body = physics.CubeRigidBody(manager.entityList[i].mesh.xdis, manager.entityList[i].mesh.ydis, manager.entityList[i].mesh.zdis)



			if (std::strcmp(path, "monkey.obj"))
			{
				manager.entityList[i].type == "monkey";
			}

			else if (std::strcmp(path, "cube.obj"))
			{
				manager.entityList[i].type == "cube";
			}
			else {

				manager.entityList[i].type == "none";
			}
			break;




		}
	}

	return &manager.entityList[i];

	

}
void Entity_UpdateAll()
{

	int i;


	for (i = 0; i < maxentities; i++)
	{

		if (!manager.entityList[i].inuse)
		{
			continue;
		}


		Entity_Update(&manager.entityList[i]);

		//Entity_Draw(&manager.entityList[i]);

		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &vp[0][0]);

	}

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
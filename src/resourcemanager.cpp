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

	//delete(&manager.entityList[ent->entity_num].body);

	memset(&manager.entityList[ent->entity_num], 0, sizeof(Entity_Struct));
	manager.numentities--;

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

Entity_Struct* Entity_New(const char * path, glm::vec3 position, Physics* physics)
{

	int i;

	

	if (manager.numentities == maxentities)
	{
		slog("Cannot add more entities");
		return 0;

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
			manager.entityList[i].forward = position;

			manager.entityList[i].forward.z -= 1;

			manager.entityList[i].Model = glm::translate(glm::mat4(), position);

			float width;
			float height;
			float depth;

			width = manager.entityList[i].mesh.xdis;

			height = manager.entityList[i].mesh.ydis;

			depth = manager.entityList[i].mesh.zdis;

			manager.entityList[i].body = physics->CubeRigidBody(glm::vec3(width, height, depth), position, 1);

			//manager.entityList[i].body = physics->MeshRigidBody(position, 1, manager.entityList[i].mesh);

			physics->bodies[i + 1] = manager.entityList[i].body;

			//manager.entityList[i].body = physics.CubeRigidBody(manager.entityList[i].mesh.xdis, manager.entityList[i].mesh.ydis, manager.entityList[i].mesh.zdis)



			
			if (!std::strcmp(path, "C:\\Users\\Jacob\\IT485\\models\\My_Model\\monkey.obj"))
			{
				//slog("is player \n");
				manager.entityList[i].type = "player";
				
			}

			else if (!std::strcmp(path, "C:\\Users\\Jacob\\IT485\\models\\My_Model\\cube.obj"))
			{
				//slog("is bullet \n");
				manager.entityList[i].type = "bullet";
			}
			else {

				manager.entityList[i].type = "none";
			}
			break;




		}
	}

	return &manager.entityList[i];

	

}
void Entity_UpdateAll(Physics* physics)
{

	int i;


	for (i = 0; i < maxentities; i++)
	{

		if (!manager.entityList[i].inuse)
		{
			continue;
		}

		if (manager.entityList[i].timer > 200)
		{
			
			Entity_Free(&manager.entityList[i]);
			physics->bodies;
			physics->deleteRigidBodyOne(i+1);
			physics->bodies;
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

#include <vector>

#include <glm\vec3.hpp>

#include <iostream>

#include <fstream>
#include "scene.h"
#include "simple_logger.h"
static Scene scene;

Scene* getscene()
{

	return &scene;

}

void SceneInit()
{

	if (scene.numpieces == maxpieces)
	{
		slog("No more space for pieces");
		return;
	}


	memset(scene.ModularList, 0, sizeof(Modular_Struct)*maxpieces);

	if (scene.ModularList == NULL)
	{
		slog("Scene failed to inistalize");
	}

	atexit(SceneClose);
	//memset(manager.entityList, 0, sizeof(Entity_Struct)*maxentities);

	//if (manager.entityList == NULL)
	//{
	//	slog("Entity List is null failed to intialize");

	//}


	//atexit(Entity_Close);




}
void SceneClose()
{

	if (!scene.ModularList)
	{
		return;
	}

	memset(scene.ModularList, 0, sizeof(Modular_Struct));

	scene.numpieces = 0;


}
bool SetupScene(const char * path)
{


	std::ifstream ifs(path);

	std::string str;

	
	// ifs >> str;

	// json j;

	 ifs >> scene.j;

	 

	 if (scene.j == NULL)
	 {
		 return false;
	 }
	 

	 for (int i = 0; i < scene.j["objects"].size(); i++)
	 {


		 std::string str = scene.j["objects"][i]["model"];
		 glm::vec3 temp_pos;
		 temp_pos.x = scene.j["objects"][i]["vector"][0];
		 temp_pos.y = scene.j["objects"][i]["vector"][1];
		 temp_pos.z = scene.j["objects"][i]["vector"][2];

		 if (scene.ModularList[i].inuse)
		 {

			 continue;
		 }

		 else
		 {


			 memset(&scene.ModularList[i], 0, sizeof(Modular_Struct));

			 slog("Scene Piece Added");

			 if (!&scene.ModularList[i])
			 {
				 slog("Scene Piece Failed");
			 }

			 scene.numpieces++;

			 scene.ModularList[i].inuse = 1;

			 scene.ModularList[i].model.Load_Obj(str.c_str());


			 scene.ModularList[i].position = temp_pos;

			 scene.ModularList[i].ModelMat = glm::translate(glm::mat4(), scene.ModularList[i].position);


			 if (str == "C:\\Users\\Jacob\\IT485\\models\\My_Model\\cube.obj")
			 {
				 scene.ModularList[i].type = "cube";
			 }

			 else
			 {
				 scene.ModularList[i].type = "none";
			 }

		 }


	 }
	
return true;

}

void DrawScene()
{

	for (int i = 0; i < maxpieces; i++)
	{

		if (!scene.ModularList[i].inuse)
		{
			continue;
		}


		Draw_Piece(&scene.ModularList[i]);

	}



}


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


			 if (str == "cube.obj")
			 {
				 scene.ModularList[i].type = "cube";
			 }

			 else
			 {
				 scene.ModularList[i].type = "none";
			 }

		 }


	 }

	 








	// std::cout << "This is the file " << str << std::endl;
	 //std::cout << "Second Char " << str[1] << std::endl;

	
	// printf(strc);
	// std::string s = (scene.j["objects"][0]["model"].dump() + "\n");
	//std::string s = (scene.j["objects"][0]["vector"][0].dump() + "\n");
	//slog(s.c_str());

	//ifs >> str;

	

	//scene.j = json::parse(ifs);

	//json j(ifs);

	//scene.j(i);

	//i >> scene.j;




	//scene.j["objects"][0]["model"];

	//slog(scene.j["objects"][0]["model"]);

	/*
	if (scene.j["objects"][0]["model"] == "cube.obj")
	{

		slog("HELLO");


	}
	*/







	/*
	char buf[512];

	std::vector<std::string>temp_models;

	std::vector<glm::vec3>temp_position;

	std::string str = "cube";

	


	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while (fscanf(file, "%[^\n]\n", buf) != EOF)
	{
		glm::vec3 pos;

		if (buf[0] == 'c')
		{
			//glm::vec3 vertex;

			sscanf(buf, "cube %f %f %f", &pos.x, &pos.y, &pos.z);

			temp_models.push_back(str);

			temp_position.push_back(pos);
		}

		//std::string str;

		//sscanf(buf, "%s %f %f %f", &str, &pos.x, &pos.y, &pos.x);

		//temp_models.push_back(str);
		//temp_position.push_back(pos);
		//scene.models.push_back(str);
		//scene.positions.push_back(pos);

	}
	
	/*
	for (int i = 0; i < temp_models.size(); i++)
	{
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


			if (temp_models[i] == "cube")
			{
				scene.ModularList[i].model.Load_Obj("cube3.obj");
			}

			scene.ModularList[i].position = temp_position[i];

			scene.ModularList[i].ModelMat = glm::translate(glm::mat4(), scene.ModularList[i].position);





			//scene.ModularList[i].model.Load_Obj()
			/*
			memset(&manager.entityList[i], 0, sizeof(Entity_Struct));
			slog("Entity added");

			if (!&manager.entityList[i])
			{
				slog("Entity additin failed");
			}
			



		}



	}




	fclose(file);
	return true;
	*/
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

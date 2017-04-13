#ifndef __SCENE_H__
#define __SCENE_H__


#include <vector>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL\glew.h>
#include "modular_piece.h"
#include <vector>
#include <string>

#define maxpieces 100

//std::vector<Vertex> scene_parts;

typedef struct
{
	int numpieces;


	//std::vector<Modular_Struct> scene_parts;

	//std::vector<std::string> models;

	//std::vector<glm::vec3> positions;

	Modular_Struct ModularList[maxpieces];

}Scene;


Scene* getscene();

void SceneInit();

void SceneClose();

bool SetupScene(const char * path);

void DrawScene();




#endif

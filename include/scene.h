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
#include <json.hpp>
#define maxpieces 100


using json = nlohmann::json;
//std::vector<Vertex> scene_parts;

/**
*@breif Creates a struct to represent a scene

*/


typedef struct
{
	int numpieces;

	json j;


	Modular_Struct ModularList[maxpieces];

}Scene;

/**
*@breif returns a scene

*/
Scene* getscene();

/**
*@breif ints a scene

*/
void SceneInit();
/**
*@breif closes a scene

*/

void SceneClose();
/**
*@breif Sets up a scene based on a json file

*/
bool SetupScene(const char * path, Physics* physics);

/**
*@breif Draws a scene

*/
void DrawScene();




#endif

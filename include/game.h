#ifndef __GAME_H__
#define __GAME_H__
#define GLM_ENABLE_EXPERIMENTAL
#include <btBulletDynamicsCommon.h>
#include "simple_logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "vector.h"
#include "mesh.h"
#include "UIPopup.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "SDL.h"
#include <glm\gtx\string_cast.hpp>
#include "hud.h"
#include <GL\glut.h>
#include <GL\freeglut.h>
#include "physics.h"
#include "resourcemanager.h"
#include "player.h"
#include "enemy.h"
#include "button.h"
#include "modular_piece.h"
#include "scene.h"
#include "testload.h"





class Game
{


public:

	char bGameLoopRunning = 1;
	int hudon = 0;

	int debug = 0;

	bool clicked = false;

	bool held = false;

	bool shootheld = false;

	bool meleeheld = false;

	SDL_Event e;

	GLuint MatrixID; 

	Camera cam;

	glm::mat4 Model;

	glm::mat4 vp;

	Manager *manager;

	Scene *scene;

	//Manager *manager = getmanager();

	//Scene *scene = getscene();

	//SceneInit();


	//Physics* physics = new Physics();;

	Physics* physics;

	//SetupScene(path, physics);

	//physics->PlaneBody();
	//Entity_Init();

	Player_Struct* player = new Player_Struct();

	//player->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\monkey.obj", glm::vec3(0, 5, 0), physics, glm::vec3(1, 0, 0), "player");

	//player->ent->body->setAngularFactor(btVector3(0, 0, 0));

	Enemy_Struct* enemy = new Enemy_Struct();

	Enemy_Struct* enemy2 = new Enemy_Struct();

	Enemy_Struct* enemy3 = new Enemy_Struct();

	Enemy_Struct* enemy4 = new Enemy_Struct();

	Enemy_Struct* enemy5 = new Enemy_Struct();

	//enemy->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(0, 5, -15), physics, glm::vec3(0, 1, 0), "enemy");

	//enemy2->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(7, 5, -15), physics, glm::vec3(0, 1, 0), "enemy");

	//enemy3->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(-7, 5, -15), physics, glm::vec3(0, 1, 0), "enemy");

	//enemy4->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(7, 5, 0), physics, glm::vec3(0, 1, 0), "enemy");

	//enemy5->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(-7, 5, 0), physics, glm::vec3(0, 1, 0), "enemy");

	HUD hud;

	//hud.Set_HUD_Points();

	//hud.TextureLoad();

	Button button;

	//button.Button_Setup(glm::vec3(-0.1f, 0.09, 0.0f), glm::vec3(-0.04, 0.09, 0.0f), glm::vec3(-0.1, 0.03, 0.0f), glm::vec3(-0.04, 0.03, 0.0f));

	Button button2;
	//button2.Button_Setup(glm::vec3(-0.1f, 0.22, 0.0f), glm::vec3(-0.04, 0.22, 0.0f), glm::vec3(-0.1, 0.16, 0.0f), glm::vec3(-0.04, 0.16, 0.0f));


	Button button4;

	//button4.Button_Setup(glm::vec3(-0.1f, -0.17, 0.0f), glm::vec3(-0.04, -0.17, 0.0f), glm::vec3(-0.1, -0.23, 0.0f), glm::vec3(-0.04, -0.23, 0.0f));

	Button button5;

	//button5.Button_Setup(glm::vec3(-0.1f, -0.3, 0.0f), glm::vec3(-0.04, -0.3, 0.0f), glm::vec3(-0.1, -0.36, 0.0f), glm::vec3(-0.04, -0.36, 0.0f));

	Button button6;

	//button6.Button_Setup(glm::vec3(-0.1f, -0.43, 0.0f), glm::vec3(-0.04, -0.43, 0.0f), glm::vec3(-0.1, -0.49, 0.0f), glm::vec3(-0.04, -0.49, 0.0f));

	int x;
	int y;

	//int i = 4;
	float time;
	//GLfloat angle = 20;

	//const Uint8 *state = SDL_GetKeyboardState(NULL);
	const Uint8 *state;
	//BulletDebugDrawer_DeprecatedOpenGL mydebugdrawer;
	//physics->space->setDebugDrawer(&mydebugdrawer);


	Game();

	void GameSetup(const char * path);

	void GameRun();











};
#endif

/**
* gametest3d
* @license The MIT License (MIT)
*   @copyright Copyright (c) 2015 EngineerOfLies
*    Permission is hereby granted, free of charge, to any person obtaining a copy
*    of this software and associated documentation files (the "Software"), to deal
*    in the Software without restriction, including without limitation the rights
*    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*    copies of the Software, and to permit persons to whom the Software is
*    furnished to do so, subject to the following conditions:
*    The above copyright notice and this permission notice shall be included in all
*    copies or substantial portions of the Software.
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*    SOFTWARE.
*/
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

GLuint VBO;
GLuint VAO;
GLuint EBO;
GLuint vao;
//GLuint vertexbuffer;
//GLuint IndexVBO;


extern int entityMax;



//GLuint TextureID;

SDL_Surface *image;

//GLuint HUD_Vertex_buf;
//GLuint HUD_UV_buf;
static int health;
static float experience;
static int mana;


GLuint triangleBufferObject;

int* test;

/**
*The bullet debugdrawer class in this file is taken from a tutorial from opengl-tutorial.org
https://github.com/stegu/opengl-tutorial-proofread/blob/master/misc05_picking/misc05_picking_BulletPhysics.cpp
*Linsense say it is fine to use it
http://www.opengl-tutorial.org/uncategorized/2014/02/18/license-changes/
*
*
*
*
*The only other thing that is not mine within this project is the lighting affect although I do understand how it works the code and logic was taken from 
learingopengl.com
https://learnopengl.com/#!Lighting/Basic-Lighting
Lisencne saying it is fine to use it is under public domain
https://creativecommons.org/publicdomain/zero/1.0/
*/
class BulletDebugDrawer_DeprecatedOpenGL : public btIDebugDraw {
public:
	void SetMatrices(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix) {
		glUseProgram(0); // Use Fixed-function pipeline (no shaders)
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(&ViewMatrix[0][0]);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(&ProjectionMatrix[0][0]);
	}
	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) {
		glColor3f(color.x(), color.y(), color.z());
		glBegin(GL_LINES);
		glVertex3f(from.x(), from.y(), from.z());
		glVertex3f(to.x(), to.y(), to.z());
		glEnd();
	}
	virtual void drawContactPoint(const btVector3 &, const btVector3 &, btScalar, int, const btVector3 &) {}
	virtual void reportErrorWarning(const char *) {}
	virtual void draw3dText(const btVector3 &, const char *) {}
	virtual void setDebugMode(int p) {
		m = p;
	}
	int getDebugMode(void) const { return 3; }
	int m;
};




int main(int argc, char *argv[])
{
	//btBroadphaseInterface* broadphase = new btDbvtBroadphase();



	glutInit(&argc, argv);
	int hudon = 0;


	int debug = 0;

	bool clicked = false;

	bool held = false;

	bool shootheld = false;

	bool meleeheld = false;

	health = 100;

	mana = 100;

	experience = 100;
	GLuint vao;

	char bGameLoopRunning = 1;
	SDL_Event e;
	const float triangleVertices[] = {
		0.0f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.366f, 0.0f, 1.0f,
		-0.5f, -0.366f, 0.0f, 1.0f,
		//next part contains vertex colors
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	}; //we love you vertices!


	init_logger("gametest3d.log");
	if (graphics3d_init(1024, 768, 1, "gametest3d", 33) != 0)
	{
		return -1;
	}




	GLuint MatrixID = glGetUniformLocation(graphics3d_get_shader_program(), "VP");
	
	Camera cam;





	glm::mat4 Model = glm::mat4();

	
	glm::mat4 vp;

	Manager *manager = getmanager();

	Scene *scene = getscene();

	SceneInit();

	Physics* physics = new Physics();;

	SetupScene("scene.json", physics);

	physics->PlaneBody();
	Entity_Init();

	Player_Struct* player = new Player_Struct();

	player->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\monkey.obj", glm::vec3(0, 5, 0), physics, glm::vec3(1,0,0), "player");

	player->ent->body->setAngularFactor(btVector3(0, 0, 0));

	Enemy_Struct* enemy = new Enemy_Struct();

	Enemy_Struct* enemy2 = new Enemy_Struct();

	Enemy_Struct* enemy3 = new Enemy_Struct();

	Enemy_Struct* enemy4 = new Enemy_Struct();

	Enemy_Struct* enemy5 = new Enemy_Struct();

	enemy->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(0, 5, -15), physics, glm::vec3(0,1,0), "enemy");

	enemy2->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(7, 5, -15), physics, glm::vec3(0, 1, 0), "enemy");

	enemy3->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(-7, 5, -15), physics, glm::vec3(0, 1, 0), "enemy");

	enemy4->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(15, 5, 0), physics, glm::vec3(0, 1, 0), "enemy");

	enemy5->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(-15, 5, 0), physics, glm::vec3(0, 1, 0), "enemy");

	HUD hud;

	hud.Set_HUD_Points();

	hud.TextureLoad();

	Button button;

	button.Button_Setup(glm::vec3(-0.1f, 0.09, 0.0f), glm::vec3(-0.04, 0.09, 0.0f), glm::vec3(-0.1, 0.03, 0.0f), glm::vec3(-0.04, 0.03, 0.0f));

	Button button2;
	button2.Button_Setup(glm::vec3(-0.1f, 0.22, 0.0f), glm::vec3(-0.04, 0.22, 0.0f), glm::vec3(-0.1, 0.16, 0.0f), glm::vec3(-0.04, 0.16, 0.0f));

	Button button4;

	button4.Button_Setup(glm::vec3(-0.1f, -0.17, 0.0f), glm::vec3(-0.04, -0.17, 0.0f), glm::vec3(-0.1, -0.23, 0.0f), glm::vec3(-0.04, -0.23, 0.0f));

	Button button5;

	button5.Button_Setup(glm::vec3(-0.1f, -0.3, 0.0f), glm::vec3(-0.04, -0.3, 0.0f), glm::vec3(-0.1, -0.36, 0.0f), glm::vec3(-0.04, -0.36, 0.0f));

	Button button6;

	button6.Button_Setup(glm::vec3(-0.1f, -0.43, 0.0f), glm::vec3(-0.04, -0.43, 0.0f), glm::vec3(-0.1, -0.49, 0.0f), glm::vec3(-0.04, -0.49, 0.0f));

	Button button7;

	button7.Button_Setup(glm::vec3(-5.0f, -5.0f, 0.0f), glm::vec3(-5.0f, 5.0f, 0.0f), glm::vec3(5.0f, -5.0f, 0.0f), glm::vec3(5.0f, 5.0f, 0.0f));


	int x;
	int y;

	int i = 4;
	float time;
	GLfloat angle = 20;

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	BulletDebugDrawer_DeprecatedOpenGL mydebugdrawer;
	physics->space->setDebugDrawer(&mydebugdrawer);

	glm::vec3 lightpos(0.0, 0.0, 0.0);
	
	int lasttime = 0;

	while (bGameLoopRunning)
	{
		//SDL_SetRelativeMouseMode(SDL_TRUE);

		if (player->health > 0)
		{
			clicked = false;

			if (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					bGameLoopRunning = 0;
				else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
					bGameLoopRunning = 0;

				else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
				{
					if (shootheld == false)
					{
						if (player->mana >= 10)
						{
							Player_Shoot(player, physics, manager);
						}
					}

					shootheld = true;
				}
				else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_q)
				{
					shootheld = false;
				}

				else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_x)
				{
					if (meleeheld == false)
					{
						Player_Melee(player, physics);
					}

					meleeheld = true;
				}
				else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_x)
				{
					
					meleeheld = false;
					physics->deleteMelee();
				}

				else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_c)
				{

					player->ent->body->activate(true);

					player->ent->body->setAngularVelocity(btVector3(0, 1, 0));

				}
				else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_c)
				{
					player->ent->body->setAngularVelocity(btVector3(0, 0, 0));

				}

				else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_TAB)
					hudon++;
				else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_p)
					debug++;
				else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
				{
					if (held == false)
					{
						clicked = true;
					}

					held = true;
				}

				else if (e.type == SDL_MOUSEBUTTONUP)

					held = false;
			}

			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			SDL_GetMouseState(&x, &y);

			if (state[SDL_SCANCODE_L])
			{
				printf("x %d \n", x);

				printf("y %d \n", y);
			}

			cam.cameraRotation(x, y, player);

			Enemy_AI(enemy, player);
			Enemy_AI(enemy2, player);
			Enemy_AI(enemy3, player);
			Enemy_AI(enemy4, player);
			Enemy_AI(enemy5, player);

			if (state[SDL_SCANCODE_W])
			{

				player->ent->body->activate(true);
				Player_Movement(player, 'W');

			}


			if (state[SDL_SCANCODE_S])
			{
				player->ent->body->activate(true);
				Player_Movement(player, 'S');


			}
			if (state[SDL_SCANCODE_A])
			{
				player->ent->body->activate(true);
				Player_Movement(player, 'A');


			}
			if (state[SDL_SCANCODE_D])
			{
				player->ent->body->activate(true);
				Player_Movement(player, 'D');

			}

			if (state[SDL_SCANCODE_SPACE])
			{
				player->ent->body->activate(true);

				Player_Movement(player, 'U');

			}


			btTransform t;
			player->ent->body->getMotionState()->getWorldTransform(t);
			btVector3 origin = t.getOrigin();
			glm::vec3 newpos;
			newpos.x = origin.getX();
			newpos.y = origin.getY();
			newpos.z = origin.getZ();
			cam.camerapos = newpos;
			cam.camerapos.z += 20;
			cam.camerapos.y += 5;


			if (state[SDL_SCANCODE_U])
			{

				//printf("TEST \n");
				//health = health + 10;
				Player_Health(player, -10);
			}

			if (state[SDL_SCANCODE_I])
			{

				//printf("TEST \n");
				//health = health + 10;
				Player_Mana(player, -10);
			}
			if (state[SDL_SCANCODE_O])
			{

				//printf("TEST \n");
				//health = health + 10;
				Player_Exp(player, 10);

			}

			cam.computeMatricesFromInputs(player);
			glm::mat4 Projection = cam.ProjectionMatrix;
			glm::mat4 View = cam.ViewMatrix;


			vp = Projection * View;

			/* drawing code in here! */

			glUseProgram(graphics3d_get_shader_program());

			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &vp[0][0]);

			GLint objectColorLoc = glGetUniformLocation(graphics3d_get_shader_program(), "objectColor");
			GLint lightColorLoc = glGetUniformLocation(graphics3d_get_shader_program(), "lightColor");
			GLint lightPosLoc = glGetUniformLocation(graphics3d_get_shader_program(), "lightPos");
			glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
			glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
			glUniform3f(lightPosLoc, lightpos.x, lightpos.y, lightpos.z);


			time = SDL_GetTicks() / 1000;

			physics->PhysicsStep(time);

			

			Enemey_Collision(enemy, manager, player, physics);

			Enemey_Collision(enemy2, manager, player, physics);

			Enemey_Collision(enemy3, manager, player, physics);

			Enemey_Collision(enemy4, manager, player, physics);

			Enemey_Collision(enemy5, manager, player, physics);

			Player_Collision(player, manager, physics);
			if (time > lasttime + 1)
			{
				Player_Regen(player);
				lasttime = time;
			}
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			Entity_DrawAll();

			Entity_UpdateAll(physics);


			//Player_Sword(player);

			DrawScene();

			mydebugdrawer.SetMatrices(View, Projection);

			if (debug % 2 != 0)
			{
				physics->space->debugDrawWorld();
			}

			if (hudon % 2 != 0)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				//this should be disabled for UI and HUD stuffs, but enabled for 3D
				glDisable(GL_DEPTH_TEST);
				glUseProgram(graphics3d_get_shader_program2());

				hud.Draw_HUD();

				glUseProgram(graphics3d_get_shader_program3());


				if (player->skillpoints >= 1)
				{
					button.Button_Draw();

					button2.Button_Draw();

					button4.Button_Draw();

					button5.Button_Draw();

					button6.Button_Draw();
					if (x >= 461 && x <= 492)
					{

						if (y >= 299 && y <= 322)
						{
							if (clicked == true)
							{
								//printf("Health \n");
								player->TotalHealth = player->TotalHealth + 10;
								player->skillpoints--;
							}
						}
						if (y >= 348 && y <= 373)
						{
							if (clicked == true)
							{
								//printf("Mana \n");
								player->TotalMana = player->TotalMana + 10;
								player->skillpoints--;
							}
						}

						if (y >= 449 && y <= 472)
						{
							if (clicked == true)
							{
								//printf("Str \n");
								player->strength++;
								player->skillpoints--;
							}
						}

						if (y >= 498 && y <= 520)
						{
							if (clicked == true)
							{
								//printf("Spd \n");
								player->speed++;
								player->skillpoints--;
							}
						}

						if (y >= 549 && y <= 571)
						{
							if (clicked == true)
							{
								//printf("Arc \n");
								player->arcane++;
								player->skillpoints--;
							}
						}
					}
				}
				glDisable(GL_BLEND);


				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LESS);

			}

			time = SDL_GetTicks() / 1000;

			if (player->health != player->TotalHealth)
			{
				int healthregen = time / 60;
			}
			glUseProgram(0);
			/* drawing code above here! */


			//switch to ortho for UI

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glOrtho(0, 1024, 768, 0, -1, 1);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//this should be disabled for UI and HUD stuffs, but enabled for 3D
			glDisable(GL_DEPTH_TEST);
			drawhud(player->health, player->mana, player->experience);

			if (hudon % 2) {

				drawstats(player->TotalHealth, player->experience, player->TotalMana, player->level, player->skillpoints, player->strength, player->speed, player->arcane, player->gold);
			}


			if (player->experience >= 100)
			{
				slog("Player Leveled");
				player->level++;
				player->skillpoints++;
				player->experience = 0;

			}
			glDisable(GL_BLEND);


			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);



			//switch back to Perspective
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
			graphics3d_next_frame();


		}
		else
		{
			if (player->gold < 5)
			{





				glMatrixMode(GL_PROJECTION);
				glPushMatrix();
				glLoadIdentity();
				glOrtho(0, 1024, 768, 0, -1, 1);
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glLoadIdentity();


				drawlose();

				


				//switch back to Perspective
				glMatrixMode(GL_PROJECTION);
				glPopMatrix();
				glMatrixMode(GL_MODELVIEW);
				glPopMatrix();
				graphics3d_next_frame();




			}
			else {



				if (player->gold == 5)
				{
					player->health = -1;


					glMatrixMode(GL_PROJECTION);
					glPushMatrix();
					glLoadIdentity();
					glOrtho(0, 1024, 768, 0, -1, 1);
					glMatrixMode(GL_MODELVIEW);
					glPushMatrix();
					glLoadIdentity();


					drawwin();




					//switch back to Perspective
					glMatrixMode(GL_PROJECTION);
					glPopMatrix();
					glMatrixMode(GL_MODELVIEW);
					glPopMatrix();
					graphics3d_next_frame();

				}
			}
			if (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					bGameLoopRunning = 0;
				else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
					bGameLoopRunning = 0;

				else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
				{
					
					if (player->gold != 5)
					{
						player->gold = 0;
						player->ent->body->getWorldTransform().setOrigin(btVector3(0, 0, 0));
					}
					else 
					{
						player->health = 100;
						player->gold = 0;
						player->mana = 100;
						player->TotalHealth = 100;
						player->level = 1;
						player->skillpoints = 0;
						player->strength = 1;
						player->speed = 1;
						player->arcane = 1;
						player->ent->body->getWorldTransform().setOrigin(btVector3(0, 0, 0));
					}
					if (enemy->alive == false)
					{
						enemy->health = 100;
						enemy->state = 0;
						enemy->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(0, 5, -15), physics, glm::vec3(0, 1, 0), "enemy");
						enemy->alive = true;
					}
					else
					{
						enemy->health = 100;
						enemy->state = 0;

						enemy->ent->body->getWorldTransform().setOrigin(btVector3(0, 5, -15));

					}

					if (enemy2->alive == false)
					{
						enemy2->health = 100;
						enemy2->state = 0;
						enemy2->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(7, 5, -15), physics, glm::vec3(0, 1, 0), "enemy");
						enemy2->alive = true;
					}
					else
					{
						enemy2->health = 100;
						enemy2->state = 0;

						enemy2->ent->body->getWorldTransform().setOrigin(btVector3(7, 5, -15));

					}

					if (enemy3->alive == false)
					{
						enemy3->health = 100;
						enemy3->state = 0;
						enemy3->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(-7, 5, -15), physics, glm::vec3(0, 1, 0), "enemy");
						enemy3->alive = true;
					}
					else
					{
						enemy3->health = 100;
						enemy3->state = 0;

						enemy3->ent->body->getWorldTransform().setOrigin(btVector3(-7, 5, -15));

					}
					if (enemy4->alive == false)
					{
						enemy4->health = 100;
						enemy4->state = 0;
						enemy4->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(15, 5, 0), physics, glm::vec3(0, 1, 0), "enemy");
						enemy4->alive = true;
					}
					else
					{
						enemy4->health = 100;
						enemy4->state = 0;

						enemy4->ent->body->getWorldTransform().setOrigin(btVector3(15, 5, 0));

					}
					if (enemy5->alive == false)
					{
						enemy5->health = 100;
						enemy5->state = 0;
						enemy5->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(-15, 5, 0), physics, glm::vec3(0, 1, 0), "enemy");
						enemy5->alive = true;
					}
					else
					{
						enemy3->health = 100;
						enemy3->state = 0;

						enemy3->ent->body->getWorldTransform().setOrigin(btVector3(-15, 5, 0));

					}
				}
			}

		}

		if (player->gold == 5)
		{
			player->health = -1;
			//slog("coin \n %d", player->gold);

		}
		
	}
	physics->deleteRigidBody();

	physics->deletePhysicsWorld();


	return 0;
}

/*eol@eof*/

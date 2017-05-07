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

Test_Struct* teststr = new Test_Struct();




struct meleecollision : public btCollisionWorld::ContactResultCallback
{


	//testCallback(Test_Struct* context) : ctext(context) {}

	meleecollision(Enemy_Struct* enemy) : ene(enemy) {}


	virtual	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
	{

		Enemy_Health(ene, -10);

		slog("Enemy Health %d \n", ene->health);
		if (ene->health < 0)
		{
			Enemy_Die(ene);
			slog("HEEEEEEE\n");
			//Enemy_Die(ene);
		}
		return 0;

	}

	Enemy_Struct* ene;

};



struct procollision : public btCollisionWorld::ContactResultCallback
{


	//testCallback(Test_Struct* context) : ctext(context) {}

	procollision(Enemy_Struct* enemy) : ene(enemy) {}


	virtual	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
	{


		Enemy_Health(ene, -20);



		slog("Enemy Health %d \n", ene->health);


		return 0;
	}

	Enemy_Struct* ene;

};



class BulletDebugDrawer_DeprecatedOpenGL : public btIDebugDraw {
public:
	void SetMatrices(glm::mat4 pViewMatrix, glm::mat4 pProjectionMatrix) {
		glUseProgram(0); // Use Fixed-function pipeline (no shaders)
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(&pViewMatrix[0][0]);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(&pProjectionMatrix[0][0]);
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


	   //Vertex vertices 

	   //std::vector<Vertex> vertices = Vertex(glm::vec3(0, 0, 0));

	   /*

	   Vertex verts[] = { glm::vec3(-0.5,-0.5,0), glm::vec3(0,0.5,0),glm::vec3(0.5,-0.5,0) };

	   std::vector<Vertex> vertices;

	   vertices.push_back(verts[0]);
	   vertices.push_back(verts[1]);
	   vertices.push_back(verts[2]);

	   Test mesh(vertices);
	   */
	init_logger("gametest3d.log");
	if (graphics3d_init(1024, 768, 1, "gametest3d", 33) != 0)
	{
		return -1;
	}

	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);



	GLuint MatrixID = glGetUniformLocation(graphics3d_get_shader_program(), "VP");
	//glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	//	glm::mat4 View = glm::lookAt(glm::vec3(4, 3, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	Camera cam;




	//Camera cam;

	//View = cam.getViewMatrix();

	//Projection = cam.getProjectionMatrix();


	glm::mat4 Model = glm::mat4();

	//glm::mat4 mvp = Projection * View * Model;
	glm::mat4 vp;





	//glm::mat4 View;




	//glGenBuffers(1, &IndexVBO);
	//glGenBuffers(1, &vertexbuffer);

	//Mesh mesh;

	//Mesh mesh2;

	//mesh.Load_Obj("cube.obj");

	//mesh2.Load_Obj("monkey.obj");


	//Mesh sword;


	//sword.Load_Obj("sword");


	Manager *manager = getmanager();

	Scene *scene = getscene();

	SceneInit();



	//TestScene("test.txt");
	Physics* physics = new Physics();;

	SetupScene("scene.json", physics);

	physics->PlaneBody();

	//physics.

	Entity_Init();

	Player_Struct* player = new Player_Struct();

	player->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\monkey.obj", glm::vec3(0, 5, 0), physics, glm::vec3(1,0,0));

	player->ent->body->setAngularFactor(btVector3(0, 0, 0));

	//player->ent->type = "player";

	Enemy_Struct* enemy = new Enemy_Struct();

	enemy->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(0, 5, -15), physics, glm::vec3(0,1,0));

	//enemy->ent->type = "player";

	//Entity_New("cube.obj", glm::vec3(2, 2, 2));

	//Entity_New("monkey.obj", glm::vec3(0, 0, 0));


	//player.health = health;

	//player.mana = mana;

	//player.experience = experience;


	//Player_Health(&player, 10);

	HUD hud;

	hud.Set_HUD_Points();


	hud.TextureLoad();


	Button button;

	//button.Button_Setup(glm::vec3(0.35f, 0.01f, 0.0f), glm::vec3(0.3f, 0.01f, 0.0f), glm::vec3(0.3f, -0.1f, 0.0f), glm::vec3(0.35f, -0.1f, 0.0f));


	button.Button_Setup(glm::vec3(-0.1f, 0.09, 0.0f), glm::vec3(-0.04, 0.09, 0.0f), glm::vec3(-0.1, 0.03, 0.0f), glm::vec3(-0.04, 0.03, 0.0f));


	Button button2;


	button2.Button_Setup(glm::vec3(-0.1f, 0.22, 0.0f), glm::vec3(-0.04, 0.22, 0.0f), glm::vec3(-0.1, 0.16, 0.0f), glm::vec3(-0.04, 0.16, 0.0f));

	//Button button3;

	//button3.Button_Setup(glm::vec3(-0.1f, -0.04, 0.0f), glm::vec3(-0.04, -0.04, 0.0f), glm::vec3(-0.1, -0.1, 0.0f), glm::vec3(-0.04, -0.1, 0.0f));

	Button button4;

	button4.Button_Setup(glm::vec3(-0.1f, -0.17, 0.0f), glm::vec3(-0.04, -0.17, 0.0f), glm::vec3(-0.1, -0.23, 0.0f), glm::vec3(-0.04, -0.23, 0.0f));

	Button button5;

	button5.Button_Setup(glm::vec3(-0.1f, -0.3, 0.0f), glm::vec3(-0.04, -0.3, 0.0f), glm::vec3(-0.1, -0.36, 0.0f), glm::vec3(-0.04, -0.36, 0.0f));

	Button button6;

	button6.Button_Setup(glm::vec3(-0.1f, -0.43, 0.0f), glm::vec3(-0.04, -0.43, 0.0f), glm::vec3(-0.1, -0.49, 0.0f), glm::vec3(-0.04, -0.49, 0.0f));

	int x;
	int y;


	int i = 4;
	float time;
	GLfloat angle = 20;
	//Camera(glm::vec3 pos, float fov, float aspect, float zNear, float fNear)



	const Uint8 *state = SDL_GetKeyboardState(NULL);


	BulletDebugDrawer_DeprecatedOpenGL mydebugdrawer;
	physics->space->setDebugDrawer(&mydebugdrawer);



	while (bGameLoopRunning)
	{
		//SDL_SetRelativeMouseMode(SDL_TRUE);
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
					Player_Shoot(player, physics, manager);
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
				/*
				if (meleeheld == false)
				{
				Player_Melee(player, physics);
				}

				meleeheld = true;
				*/
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_c)
			{
				player->ent->body->setAngularVelocity(btVector3(0, 0, 0));
				//meleeheld = false;
				//physics->deleteMelee();
			}



			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_y)
			{
				///Player_Sword(&player, physics);
				//Player_Melee(&player, physics);
				Player_Test(player);
			}

			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r)
			{
				slog("Test num %d", player->sword.number);
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_TAB)
				hudon++;
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
		GLfloat radius = 1.0f;
		//GLfloat camX = sin((SDL_GetTicks()/1000) * radius);
		//GLfloat camZ = cos((SDL_GetTicks() / 1000) * radius);

		angle++;

		//View = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		//mvp = Projection * View * Model;



		SDL_GetMouseState(&x, &y);

		if (state[SDL_SCANCODE_L])
		{
			printf("x %d \n", x);

			printf("y %d \n", y);
		}


		cam.cameraRotation(x, y, player);
		/*

		//cam.CameraRot(x, y);
		if (state[SDL_SCANCODE_A])
		{

		//printf("TEST \n");
		cam.cameraMovement('A');
		}

		if (state[SDL_SCANCODE_D])
		{
		cam.cameraMovement('D');
		//printf("TEST \n");
		}
		if (state[SDL_SCANCODE_W])
		{
		cam.cameraMovement('W');
		//printf("TEST \n");
		}
		if (state[SDL_SCANCODE_S])
		{
		cam.cameraMovement('S');
		//printf("TEST \n");
		}
		*/



		Enemy_PlayDis(enemy, player);

		if (enemy->state == 1)
		{
			Enemy_Chase(enemy, player);
		}



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

		//cam.camerafront = newpos;

		cam.camerapos = newpos;

		cam.camerapos.z += 20;
		cam.camerapos.y += 5;

		//cam.camerapos = player.ent->body->getWorldTransform().getOrigin();

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
		//View = cam.getViewMatrix();
		//Projection = cam.getProjectionMatrix();




		cam.computeMatricesFromInputs(player);


		//Player_Pos(&player, cam.camerapos);


		//	glm::mat4 Projection = cam.getProjectionMatrix();
		//glm::mat4 View = cam.getViewMatrix();

		glm::mat4 Projection = cam.ProjectionMatrix;
		glm::mat4 View = cam.ViewMatrix;

		glm::mat4 ProjTest;

		glm::mat4 ViewTest;



		glm::mat4 ProjTest2 = cam.getProjectionMatrix();

		glm::mat4 ViewTest2 = cam.getViewMatrix();



		ProjTest = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

		ViewTest = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));




		vp = Projection * View;

		//mvp2 = ProjTest * ViewTest * Model;

		//mvp3 = ProjTest2 * ViewTest2 * Model;



		/*
		if (state[SDL_SCANCODE_A])
		{


		//printf("TEST \n");
		printf("\n");
		printf("MVP \n");
		std::cout << glm::to_string(mvp) << std::endl;
		printf("\n");
		printf("MVP2 \n");
		std::cout << glm::to_string(mvp2) << std::endl;
		printf("\n");
		printf("MVP3 \n");
		std::cout << glm::to_string(mvp3) << std::endl;
		printf("\n");
		}
		*/





		//printf("x is %d \n", x);
		//printf("y is %d \n", y);
		/* drawing code in here! */

		glUseProgram(graphics3d_get_shader_program());

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &vp[0][0]);


		/*
		for (int i = 0; i < bodies.size(); i++)
		{
		if (bodies[i]->getCollisionShape()->getShapeType() == STATIC_PLANE_PROXYTYPE)
		{
		renderPlane(bodies[i]);
		}
		else if (bodies[i]->getCollisionShape()->getShapeType() == SPHERE_SHAPE_PROXYTYPE)
		renderSphere(bodies[i]);


		}
		*/
		//spSlider6Dof->setAngularLowerLimit(btVector3(0, 1, 0));
		//spSlider6Dof->setAngularUpperLimit(btVector3(0, -1, 0));
		//player->ent->body->setAngularFactor(btVector3(0, 0, 0));
		time = SDL_GetTicks() / 1000;

		if (state[SDL_SCANCODE_J])
		{

			//printf("TEST \n");
			//health = health + 10;
			//Player_Exp(&player, 10);

			player->ent->body->activate(true);
			//player.ent->body->applyCentralImpulse(btVector3(0, 0, 3));
			//player.ent->body->applyForce(btVector3(0., 0., 5.), btVector3(0., 0., 0.));
			player->ent->body->setLinearVelocity(btVector3(0, 0, -3));


			//player.ent->body->applyForce(btVector3(0,20,0),)
			//player.ent->body->applyCentralForce(btVector3(0, 0, 10));
			//slog("number %f \n", physics.callback.hithum);


		}





		if (state[SDL_SCANCODE_C])
		{
			player->ent->body->activate(true);




			//player->ent->body->setAngularVelocity(btVector3(0, 1, 0));
			//player->ent->body->applyTorque(btVector3(0, 2, 0));
			//player.ent->body->getWorldTransform().getBasis().
			//btVector3 p1;
			//p1.rotate(btVector3(3, 0, 0), 10);
			//player.ent->Model = glm::rotate(glm::mat4(), 1.0f, glm::vec3(0,1,0));


		}


		if (state[SDL_SCANCODE_V])
		{


			slog("size of bodies %d", physics->bodies.size());
			//delete(physics.bodies[2]);
			//player.ent->body->activate(true);
			//player.ent->body->applyTorque(btVector3(0, 20, 0));
			//player.ent->body->getWorldTransform().getBasis().getEulerYPR();



			//physics->space->removeCollisionObject(bodies[i]);
			//btMotionState* motionState = bodies[i]->getMotionState();
			//btCollisionShape* shape = bodies[i]->getCollisionShape();
			//delete bodies[i];
			//delete shape;
			//delete motionState;
			/*
			physics.space->removeCollisionObject(physics.bodies[2]);
			btMotionState* motionState = physics.bodies[2]->getMotionState();
			btCollisionShape* shape = physics.bodies[2]->getCollisionShape();

			delete physics.bodies[2];

			delete shape;

			delete motionState;
			*/
			//physics.space->removeRigidBody(physics.bodies[2]);




		}


		testCallback call(teststr);

		meleecollision meleecall(enemy);

		physics->PhysicsStep(time);

		if (physics->Melee.size() > 0)
		{
			//slog("Here the melee is big\n");
			if (enemy->alive == true)
			{
				physics->space->contactPairTest(physics->Melee[0], enemy->ent->body, meleecall);
			}
		}
		//physics->space->contactPairTest(player->ent->body, physics->bodies[0], call);


		if (state[SDL_SCANCODE_B])
		{

			printf("test %d \n", teststr->points);
			//player.ent->body->activate(true);
			//player.ent->body->applyTorque(btVector3(0, 20, 0));

		}


		//slog("test %f \n", test);

		//physics.CollisionTest(player.ent->body);

		//physics.CollisionTest2(player.ent->body, physics.bodies[0]);

		//player.ent->body->







		//physics.space->stepSimulation(time);






		//physics.space->contactTest(player.ent->body, physics.callback);

		//printf("%f \n", physics.callback.hithum);
		/*
		space->stepSimulation(time);
		space->performDiscreteCollisionDetection();
		btDrawingResult renderCallback;


		space->contactTest(bodies[1], renderCallback);

		//mesh.Draw_Mesh();
		//mesh2.Draw_Mesh();
		//hud.Draw_HUD();
		*/
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		Entity_DrawAll();

		Entity_UpdateAll(physics);


		Player_Sword(player);

		DrawScene();

		mydebugdrawer.SetMatrices(View, Projection);
		physics->space->debugDrawWorld();


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
		//printf("Time is %f", time);
		//mesh.Draw();
		/*
		glBindBuffer(GL_ARRAY_BUFFER, triangleBufferObject); //bind the buffer we're applying attributes to
		glEnableVertexAttribArray(0); //0 is our index, refer to "location = 0" in the vertex shader
		glEnableVertexAttribArray(1); //attribute 1 is for vertex color data
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //tell gl (shader!) how to interpret our vertex data
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)48); //color data is 48 bytes in to the array
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		*/


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

			drawstats(player->TotalHealth, player->experience, player->TotalMana, player->level, player->skillpoints, player->strength, player->speed, player->arcane);
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
		//SDL_WarpMouseInWindow(getwindow(), 1024/2,768/2);
		//SDL_PumpEvents();


	}


	physics->deleteRigidBody();

	physics->deletePhysicsWorld();


	return 0;
}

/*eol@eof*/

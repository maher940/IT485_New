#include "game.h"

#include "Debugger.h"



Game::Game()
{

};

void Game::GameSetup(const char * path)
{


	this->MatrixID = glGetUniformLocation(graphics3d_get_shader_program(), "VP");

	

	 this->Model = glm::mat4();

	 this->manager = getmanager();

	 this->scene = getscene();

	 SceneInit();

	 this->physics = new Physics();
	//Physics* physics = new Physics();;

	Physics* physics;

	physics->PlaneBody();

	Entity_Init();
	
	this->player = new Player_Struct();

	player->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\monkey.obj", glm::vec3(0, 5, 0), physics, glm::vec3(1, 0, 0), "player");

	player->ent->body->setAngularFactor(btVector3(0, 0, 0));

	this->enemy = new Enemy_Struct();

	this->enemy2 = new Enemy_Struct();

	this->enemy3 = new Enemy_Struct();

	this->enemy4 = new Enemy_Struct();

	this->enemy5 = new Enemy_Struct();

	this->enemy->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(0, 5, -15), physics, glm::vec3(0, 1, 0), "enemy");

	this->enemy2->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(7, 5, -15), physics, glm::vec3(0, 1, 0), "enemy");

	this->enemy3->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(-7, 5, -15), physics, glm::vec3(0, 1, 0), "enemy");

	this->enemy4->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(7, 5, 0), physics, glm::vec3(0, 1, 0), "enemy");

	this->enemy5->ent = Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\enemy.obj", glm::vec3(-7, 5, 0), physics, glm::vec3(0, 1, 0), "enemy");

	

	this->hud.Set_HUD_Points();

	this->hud.TextureLoad();

	
	this->button.Button_Setup(glm::vec3(-0.1f, 0.09, 0.0f), glm::vec3(-0.04, 0.09, 0.0f), glm::vec3(-0.1, 0.03, 0.0f), glm::vec3(-0.04, 0.03, 0.0f));

	
	this->button2.Button_Setup(glm::vec3(-0.1f, 0.22, 0.0f), glm::vec3(-0.04, 0.22, 0.0f), glm::vec3(-0.1, 0.16, 0.0f), glm::vec3(-0.04, 0.16, 0.0f));


	

	this->button4.Button_Setup(glm::vec3(-0.1f, -0.17, 0.0f), glm::vec3(-0.04, -0.17, 0.0f), glm::vec3(-0.1, -0.23, 0.0f), glm::vec3(-0.04, -0.23, 0.0f));



	this->button5.Button_Setup(glm::vec3(-0.1f, -0.3, 0.0f), glm::vec3(-0.04, -0.3, 0.0f), glm::vec3(-0.1, -0.36, 0.0f), glm::vec3(-0.04, -0.36, 0.0f));


	this->button6.Button_Setup(glm::vec3(-0.1f, -0.43, 0.0f), glm::vec3(-0.04, -0.43, 0.0f), glm::vec3(-0.1, -0.49, 0.0f), glm::vec3(-0.04, -0.49, 0.0f));
	
	this->state = SDL_GetKeyboardState(NULL);
	//const Uint8 *state = SDL_GetKeyboardState(NULL);
	//const Uint8 *state;
	//BulletDebugDrawer_DeprecatedOpenGL mydebugdrawer;
	physics->space->setDebugDrawer(&this->mydebugdrawer);



}

void Game::GameRun()
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
	/*
	if (enemy2->alive == true)
	{
	Enemy_PlayDis(enemy2, player);

	if (enemy2->state == 1)
	{
	Enemy_Chase(enemy2, player);
	}
	}
	if (enemy3->alive == true)
	{
	Enemy_PlayDis(enemy3, player);

	if (enemy3->state == 1)
	{
	Enemy_Chase(enemy3, player);
	}
	}

	if (enemy4->alive == true)
	{
	Enemy_PlayDis(enemy4, player);

	if (enemy4->state == 1)
	{
	Enemy_Chase(enemy4, player);
	}
	}

	if (enemy5->alive == true)
	{
	Enemy_PlayDis(enemy5, player);

	if (enemy5->state == 1)
	{
	Enemy_Chase(enemy5, player);
	}
	}


	*/








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

	time = SDL_GetTicks() / 1000;

	physics->PhysicsStep(time);


	Enemey_Collision(enemy, manager, player, physics);

	Enemey_Collision(enemy2, manager, player, physics);

	Enemey_Collision(enemy3, manager, player, physics);

	Enemey_Collision(enemy4, manager, player, physics);

	Enemey_Collision(enemy5, manager, player, physics);

	Player_Collision(player, manager, physics);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	Entity_DrawAll();

	Entity_UpdateAll(physics);


	Player_Sword(player);

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






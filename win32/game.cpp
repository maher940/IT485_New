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

	//Physics* physics;

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

	physics->space->setDebugDrawer(&mydebugdrawer);
	
	//const Uint8 *state = SDL_GetKeyboardState(NULL);
	//const Uint8 *state;
	//BulletDebugDrawer_DeprecatedOpenGL mydebugdrawer;
	//physics->space->setDebugDrawer(&mydebugdrawer);

}

void Game::GameRun()
{


	clicked = false;

	if (SDL_PollEvent(&this->e))
	{
		if (this->e.type == SDL_QUIT)
			bGameLoopRunning = 0;
		else if (this->e.type == SDL_KEYUP && this->e.key.keysym.sym == SDLK_ESCAPE)
			bGameLoopRunning = 0;

		else if (this->e.type == SDL_KEYDOWN && this->e.key.keysym.sym == SDLK_q)
		{
			if (this->shootheld == false)
			{
				Player_Shoot(this->player, this->physics, this->manager);
			}

			this->shootheld = true;
		}
		else if (this->e.type == SDL_KEYUP && this->e.key.keysym.sym == SDLK_q)
		{
			this->shootheld = false;
		}

		else if (this->e.type == SDL_KEYDOWN && this->e.key.keysym.sym == SDLK_x)
		{
			if (this->meleeheld == false)
			{
				Player_Melee(this->player, this->physics);
			}

			this->meleeheld = true;
		}
		else if (this->e.type == SDL_KEYUP && this->e.key.keysym.sym == SDLK_x)
		{
			this->meleeheld = false;
			this->physics->deleteMelee();
		}

		else if (this->e.type == SDL_KEYDOWN && this->e.key.keysym.sym == SDLK_c)
		{

			this->player->ent->body->activate(true);

			this->player->ent->body->setAngularVelocity(btVector3(0, 1, 0));

		}
		else if (this->e.type == SDL_KEYUP && this->e.key.keysym.sym == SDLK_c)
		{
			this->player->ent->body->setAngularVelocity(btVector3(0, 0, 0));

		}

		else if (this->e.type == SDL_KEYUP && this->e.key.keysym.sym == SDLK_TAB)
			this->hudon++;
		else if (this->e.type == SDL_KEYUP && this->e.key.keysym.sym == SDLK_p)
			this->debug++;
		else if (this->e.type == SDL_MOUSEBUTTONDOWN && this->e.button.button == SDL_BUTTON_LEFT)
		{
			if (this->held == false)
			{
				this->clicked = true;
			}

			this->held = true;
		}

		else if (this->e.type == SDL_MOUSEBUTTONUP)

			this->held = false;
	}

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GetMouseState(&this->x, &this->y);

	if (state[SDL_SCANCODE_L])
	{
		printf("x %d \n", x);

		printf("y %d \n", y);
	}

	this->cam.cameraRotation(x, y, player);

	Enemy_AI(this->enemy, this->player);
	Enemy_AI(this->enemy2, this->player);
	Enemy_AI(this->enemy3, this->player);
	Enemy_AI(this->enemy4, this->player);
	Enemy_AI(this->enemy5, this->player);
	



	if (state[SDL_SCANCODE_W])
	{

		this->player->ent->body->activate(true);
		Player_Movement(this->player, 'W');

	}


	if (state[SDL_SCANCODE_S])
	{
		this->player->ent->body->activate(true);
		Player_Movement(this->player, 'S');


	}
	if (state[SDL_SCANCODE_A])
	{
		this->player->ent->body->activate(true);
		Player_Movement(this->player, 'A');


	}
	if (state[SDL_SCANCODE_D])
	{
		this->player->ent->body->activate(true);
		Player_Movement(this->player, 'D');

	}

	if (state[SDL_SCANCODE_SPACE])
	{
		this->player->ent->body->activate(true);

		Player_Movement(this->player, 'U');

	}


	btTransform t;
	this->player->ent->body->getMotionState()->getWorldTransform(t);
	btVector3 origin = t.getOrigin();
	glm::vec3 newpos;
	newpos.x = origin.getX();
	newpos.y = origin.getY();
	newpos.z = origin.getZ();
	this->cam.camerapos = newpos;
	this->cam.camerapos.z += 20;
	this->cam.camerapos.y += 5;


	if (state[SDL_SCANCODE_U])
	{

		//printf("TEST \n");
		//health = health + 10;
		Player_Health(this->player, -10);
	}

	if (state[SDL_SCANCODE_I])
	{

		//printf("TEST \n");
		//health = health + 10;
		Player_Mana(this->player, -10);
	}
	if (state[SDL_SCANCODE_O])
	{

		//printf("TEST \n");
		//health = health + 10;
		Player_Exp(this->player, 10);

	}

	this->cam.computeMatricesFromInputs(this->player);
	glm::mat4 Projection = this->cam.ProjectionMatrix;
	glm::mat4 View = this->cam.ViewMatrix;


	this->vp = Projection * View;

	/* drawing code in here! */

	glUseProgram(graphics3d_get_shader_program());

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &vp[0][0]);

	this->time = SDL_GetTicks() / 1000;

	this->physics->PhysicsStep(this->time);


	Enemey_Collision(this->enemy, this->manager, this->player, this->physics);

	Enemey_Collision(this->enemy2, this->manager, this->player, this->physics);

	Enemey_Collision(this->enemy3, this->manager, this->player, this->physics);

	Enemey_Collision(this->enemy4, this->manager, this->player, this->physics);

	Enemey_Collision(this->enemy5, this->manager, this->player, this->physics);

	Player_Collision(this->player, this->manager, this->physics);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	Entity_DrawAll();

	Entity_UpdateAll(this->physics);


	Player_Sword(this->player);

	DrawScene();

	//mydebugdrawer.SetMatrices(View, Projection);

	if (debug % 2 != 0)
	{
		this->physics->space->debugDrawWorld();
	}

	if (this->hudon % 2 != 0)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//this should be disabled for UI and HUD stuffs, but enabled for 3D
		glDisable(GL_DEPTH_TEST);
		glUseProgram(graphics3d_get_shader_program2());

		hud.Draw_HUD();

		glUseProgram(graphics3d_get_shader_program3());


		if (this->player->skillpoints >= 1)
		{
			this->button.Button_Draw();

			this->button2.Button_Draw();

			this->button4.Button_Draw();

			this->button5.Button_Draw();

			this->button6.Button_Draw();
			if (this->x >= 461 && this->x <= 492)
			{

				if (this->y >= 299 && this->y <= 322)
				{
					if (this->clicked == true)
					{
						//printf("Health \n");
						this->player->TotalHealth = this->player->TotalHealth + 10;
						this->player->skillpoints--;
					}
				}
				if (y >= 348 && y <= 373)
				{
					if (clicked == true)
					{
						//printf("Mana \n");
						this->player->TotalMana = this->player->TotalMana + 10;
						this->player->skillpoints--;
					}
				}

				if (y >= 449 && y <= 472)
				{
					if (this->clicked == true)
					{
						//printf("Str \n");
						this->player->strength++;
						this->player->skillpoints--;
					}
				}

				if (this->y >= 498 && this->y <= 520)
				{
					if (this->clicked == true)
					{
						//printf("Spd \n");
						this->player->speed++;
						this->player->skillpoints--;
					}
				}

				if (this->y >= 549 && this->y <= 571)
				{
					if (this->clicked == true)
					{
						//printf("Arc \n");
						this->player->arcane++;
						this->player->skillpoints--;
					}
				}
			}
		}
		glDisable(GL_BLEND);


		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

	}

	this->time = SDL_GetTicks() / 1000;

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
	drawhud(this->player->health, this->player->mana, this->player->experience);

	if (hudon % 2) {

		drawstats(this->player->TotalHealth, this->player->experience, this->player->TotalMana, this->player->level, this->player->skillpoints, this->player->strength, this->player->speed, this->player->arcane, this->player->gold);
	}


	if (this->player->experience >= 100)
	{
		slog("Player Leveled");
		this->player->level++;
		this->player->skillpoints++;
		this->player->experience = 0;

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






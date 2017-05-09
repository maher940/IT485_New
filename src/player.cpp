#include "player.h"
#include "simple_logger.h"




struct itemcollision : public btCollisionWorld::ContactResultCallback
{

	//testCallback(Test_Struct* context) : ctext(context) {}
	itemcollision(Player_Struct* player, Physics* physics, Manager* manager, int* num) : play(player), phy(physics), man(manager), numb(num){}


	virtual	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
	{
		play->gold++;

		man->entityList[*numb].timer = 201;

		return 0;
	}

	int* numb;
	Player_Struct* play;
	Physics* phy;
	Manager* man;
};


void Player_Sword(Player_Struct *player)
{
	/*

	glm::vec3 spawnpos;
	btTransform t;
	player->ent->body->getMotionState()->getWorldTransform(t);
	btVector3 forward = t.getBasis().getColumn(2);
	btVector3 right = t.getBasis().getColumn(0);
	btVector3 origin = t.getOrigin();
	spawnpos.x = origin.getX();
	spawnpos.y = origin.getY();
	spawnpos.z = origin.getZ();
	//spawnpos.z -= 5;
	spawnpos.x += -forward.getX();
	spawnpos.y += -forward.getY();
	spawnpos.z += -forward.getZ();
	spawnpos.x += -right.getX() + 3;
	spawnpos.y += -right.getY() + 3;
	spawnpos.z += -right.getZ() + 3;

	player->sword.mesh.Load_Obj("sword3.obj");
	player->sword.position = spawnpos;
	player->sword.Model = glm::translate(glm::mat4(), player->sword.position);
	player->sword.mesh.Draw_Mesh();
	*/

}


void Player_Test(Player_Struct *player)
{

	player->sword.number++;


}

void Player_Health(Player_Struct *player, int health)
{

	player->health += health;

}

void Player_Mana(Player_Struct *player, int mana)
{

	player->mana += mana;
}

void Player_Exp(Player_Struct *player, float exp)
{
	player->experience += exp;

}

void Player_Pos(Player_Struct *player, glm::vec3 camerapos)
{


	camerapos.z += -20;

	player->ent->body->getWorldTransform().setOrigin(btVector3(camerapos.x,

		player->ent->body->getWorldTransform().getOrigin().getY(),

		camerapos.z
	));



}

void Player_Collision(Player_Struct *player, Manager* manager, Physics* physics)
{
	

	for (int i = 0; i < 20; i++)
	{

		if (manager->entityList[i].type == "coin")
		{
			int* j = &manager->entityList[i].entity_num;


			itemcollision itcollid(player, physics, manager, j);
			
			physics->space->contactPairTest(player->ent->body, manager->entityList[i].body, itcollid);

		}

	}


}

void Player_Movement(Player_Struct *player, char key)
{

	//setAngularFactor(btVector3(0, 1, 0))
	float speed = 5 + player->speed;

	if (key == 'W')
	{
		//player->velocity.z = -5;

		player->ent->body->setLinearVelocity(btVector3(player->ent->body->getLinearVelocity().getX(),

			player->ent->body->getLinearVelocity().getY(),

			-speed));

	}
	if (key == 'S')
	{
		//player->velocity.z = 5;
		player->ent->body->setLinearVelocity(btVector3(player->ent->body->getLinearVelocity().getX(),

			player->ent->body->getLinearVelocity().getY(),

			speed));
	}
	if (key == 'A')
	{
		//player->velocity.x = -5;
		player->ent->body->setLinearVelocity(btVector3(-speed,

			player->ent->body->getLinearVelocity().getY(),

			player->ent->body->getLinearVelocity().getZ()));
	}
	if (key == 'D')
	{
		//player->velocity.x = 5;
		player->ent->body->setLinearVelocity(btVector3(speed,

			player->ent->body->getLinearVelocity().getY(),

			player->ent->body->getLinearVelocity().getZ()));


	}

	if (key == 'U')
	{
		//slog("INHERE\n");
		//player->ent->body->applyForce(btVector3(0, 5, 0), btVector3(0, 0, 0));
		//player->velocity.y = 5;

		player->ent->body->setLinearVelocity(btVector3(player->ent->body->getLinearVelocity().getX(),

			speed,

			player->ent->body->getLinearVelocity().getZ()));
	}
	
}
void Player_Shoot(Player_Struct *player, Physics* physics, Manager *manager)
{

	glm::vec3 spawnpos;

	btTransform t;

	player->ent->body->getMotionState()->getWorldTransform(t);



	btVector3 forward = t.getBasis().getColumn(2);

	btVector3 origin = t.getOrigin();

	spawnpos.x = origin.getX();
	spawnpos.y = origin.getY();
	spawnpos.z = origin.getZ(); 

	spawnpos.x += -forward.getX();
	spawnpos.y += -forward.getY();
	spawnpos.z += -forward.getZ();

	for (int i = 0; i < maxentities; i++)
	{


		if (manager->entityList[i].inuse)
		{
			continue;
		}
		else
		{
			player->mana -= 10;
			//slog("Fine added \n");
			Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\cube.obj", spawnpos, physics, glm::vec3(0,1,0), "bullet")->body->setLinearVelocity(-forward * 50);
			slog("Ent Nums %d \n", manager->numentities);
			break;
		}




	}



}

void Player_Regen(Player_Struct *player)
{
	if (player->health < player->TotalHealth)
	{
		player->health++;
	}

	if (player->mana < player->TotalMana)
	{
		player->mana++;
	}



}

void Player_Melee(Player_Struct *player, Physics* physics)
{

	glm::vec3 spawnpos;

	btTransform t;

	player->ent->body->getMotionState()->getWorldTransform(t);

	btVector3 forward = t.getBasis().getColumn(2);
	btVector3 right = t.getBasis().getColumn(0);

	btVector3 origin = t.getOrigin();

	spawnpos.x = origin.getX();
	spawnpos.y = origin.getY();
	spawnpos.z = origin.getZ();

	spawnpos.x += -forward.getX() * 2;
	spawnpos.y += -forward.getY() * 2;
	spawnpos.z += -forward.getZ() * 2;


	physics->CubeRigidBodyTR(glm::vec3(3, 1, 2), spawnpos, 0, &t.getRotation());

}



void Player_ResetMelee(Player_Struct *player, Physics* physics)
{






}
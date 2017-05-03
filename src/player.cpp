#include "player.h"
#include "simple_logger.h"

void Player_Health(Player_Struct *player, int health)
{
	
	player->health += health;
	slog("Health was here \n");
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


void Player_Shoot(Player_Struct *player,Physics* physics, Manager *manager)
{

	glm::vec3 spawnpos;

	btTransform t;

	player->ent->body->getMotionState()->getWorldTransform(t);

	btVector3 forward = t.getBasis().getColumn(2);
	btVector3 origin = t.getOrigin();
	

	spawnpos.x = origin.getX();
	spawnpos.y = origin.getY();
	spawnpos.z = origin.getZ();

	//spawnpos.z -= 5;

	
	spawnpos.x += -forward.getX();
	spawnpos.y += -forward.getY();
	spawnpos.z += -forward.getZ();

	if (manager->numentities != maxentities)
	{
		Entity_New("cube.obj", spawnpos, physics)->body->setLinearVelocity(-forward * 3);
	}
	else
	{
		slog("no more ents");
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

	//spawnpos.z -= 5;


	spawnpos.x += -forward.getX();
	spawnpos.y += -forward.getY();
	spawnpos.z += -forward.getZ();

	spawnpos.x += -right.getX();
	spawnpos.y += -right.getY();
	spawnpos.z += -right.getZ();

	physics->CubeRigidBodyTR(glm::vec3(1, 5, 3), spawnpos, 0);

}
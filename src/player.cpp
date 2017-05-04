#include "player.h"
#include "simple_logger.h"






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

	for (int i = 0; i < maxentities; i++)
	{


		if (manager->entityList[i].inuse)
		{
			continue;
		}
		else
		{
			
			slog("Fine added \n");
			Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\cube.obj", spawnpos, physics)->body->setLinearVelocity(-forward * 20);
			slog("Ent Nums %d \n", manager->numentities);
			break;
		}




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

	//spawnpos.x += -right.getX();
	//spawnpos.y += -right.getY();
	//spawnpos.z += -right.getZ();

	physics->CubeRigidBodyTR(glm::vec3(3, 1, 2), spawnpos, 0, &t.getRotation());

}



void Player_ResetMelee(Player_Struct *player, Physics* physics)
{






}
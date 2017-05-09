#include "enemy.h"


struct procollision : public btCollisionWorld::ContactResultCallback
{

	//testCallback(Test_Struct* context) : ctext(context) {}
	procollision(Enemy_Struct* enemy, Player_Struct* player, Physics* physics, Entity_Struct* bullet) : ene(enemy), play(player), phy(physics), ent(bullet) {}


	virtual	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
	{
		
		Enemy_Health(ene, -40 * play->arcane);
		ent->timer = 201;
		if (ene->health < 0)
		{
			Enemy_Die(ene, phy,play);

		}

		return 0;
	}
	Entity_Struct* ent;
	Enemy_Struct* ene;
	Player_Struct* play;
	Physics* phy;
};

struct meleecollision : public btCollisionWorld::ContactResultCallback
{
	meleecollision(Enemy_Struct* enemy, Player_Struct* player, Physics* physics) : ene(enemy), play(player), phy(physics) {}

	virtual	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
	{
		Enemy_Health(ene, -10 * play->strength);

		if (ene->health < 0)
		{
			Enemy_Die(ene,phy,play);

		}
		return 0;
	}
	Enemy_Struct* ene;
	Player_Struct* play;
	Physics* phy;

};
struct enemycollision : public btCollisionWorld::ContactResultCallback
{

	//testCallback(Test_Struct* context) : ctext(context) {}
	enemycollision(Player_Struct* player) : play(player) {}


	virtual	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
	{


		//Entity_Free(&man->entityList[*numb]);

		play->health--;

		return 0;
	}


	Player_Struct* play;
	
};

void Enemey_Collision(Enemy_Struct* enemy, Manager* manager, Player_Struct* player, Physics* physics)
{
	if (enemy->alive == true)
	{
		if (player->health > 0)
		{

			enemycollision encollid(player);

			physics->space->contactPairTest(player->ent->body, enemy->ent->body, encollid);


		}
		meleecollision melcollid(enemy, player,physics);

		if (physics->Melee.size() > 0)
		{
			if (enemy->alive == true)
			{
				physics->space->contactPairTest(physics->Melee[0], enemy->ent->body, melcollid);
			}
		}

		for (int i = 0; i < 20; i++)
		{
			if (manager->entityList[i].type == "bullet")
			{
				if (enemy->alive == true)
				{
					procollision procollid(enemy, player,physics, &manager->entityList[i]);
					physics->space->contactPairTest(manager->entityList[i].body, enemy->ent->body, procollid);
				}
			}
		}
	}
}

void Enemy_AI(Enemy_Struct* enemy, Player_Struct* player)
{


	if (enemy->alive == true)
	{
		Enemy_PlayDis(enemy, player);

		if (enemy->state == 1)
		{
			Enemy_Chase(enemy, player);
		}
	}


}

void Enemy_Health(Enemy_Struct* enemy, int health)
{

	enemy->health += health;

}


void Enemy_Die(Enemy_Struct* enemy, Physics* physics, Player_Struct* player)
{

	enemy->ent->timer = 201;
	enemy->alive = false;
	enemy->state = 0;
	player->experience += 10;

	Entity_New("C:\\Users\\Jacob\\IT485\\models\\My_Model\\coin.obj", enemy->ent->position, physics, glm::vec3(1, 1, 0), "coin");

}

void Enemy_Patrol(Enemy_Struct* enemy)
{





}

void Enemy_Chase(Enemy_Struct* enemy, Player_Struct* player)
{
	glm::vec3 difference;
	glm::vec3 direction;

	btVector3 moveenemy;
	difference = player->ent->position - enemy->ent->position;

	direction = glm::normalize(difference);

	//if (SDL_SCANCODE_0)
	//{
		//slog("X dir %f \n", direction.x);
		//slog("Y dir %f \n", direction.y);
		//slog("Z dir %f \n", direction.z);
	//}
	moveenemy.setX(direction.x);
	moveenemy.setY(direction.y);
	moveenemy.setZ(direction.z);

	moveenemy *= 5;

	//enemy->ent->body->setLinearFactor(moveenemy);

	enemy->ent->body->setLinearVelocity(moveenemy);

	//enemy->ent->body->getWorldTransform().getOrigin().setY(player->ent->position.y);

}

void Enemy_PlayDis(Enemy_Struct* enemy, Player_Struct* player)
{
	glm::vec3 enemypos;
	glm::vec3 playerpos;

	enemypos = enemy->ent->position;

	playerpos = player->ent->position;

	float dis = glm::distance(enemypos, playerpos);

	if (dis <= 12)
	{

		//slog("Close \n");

		//slog("Dis %f \n", dis);
		enemy->state = 1;
	}
	else
	{
		//slog("Not close \n");
		//enemy->state = 0;
	}
}
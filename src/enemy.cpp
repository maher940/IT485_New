#include "enemy.h"


void Enemy_Health(Enemy_Struct* enemy, int health)
{

	enemy->health += health;

}


void Enemy_Die(Enemy_Struct* enemy)
{

	enemy->ent->timer = 201;
	enemy->alive = false;
	//delete enemy;



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

	if (dis <= 10)
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
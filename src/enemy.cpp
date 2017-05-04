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
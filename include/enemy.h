#ifndef  __ENEMY_H
#define __ENEMY_H


#include "entity.h"
#include "player.h"
#include "resourcemanager.h"


typedef struct
{

	Entity_Struct *ent;

	int health = 100;

	bool alive = true;

	int state;


}Enemy_Struct;


void Enemy_Health(Enemy_Struct* enemy, int health);

void Enemy_Die(Enemy_Struct* enemy);

void Enemy_Patrol(Enemy_Struct* enemy);

void Enemy_Chase(Enemy_Struct* enemy, Player_Struct* player);

void Enemy_PlayDis(Enemy_Struct* enemy, Player_Struct* player);

#endif

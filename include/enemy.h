#ifndef  __ENEMY_H
#define __ENEMY_H


#include "entity.h"
#include "resourcemanager.h"


typedef struct
{

	Entity_Struct *ent;

	int health = 100;

	bool alive = true;


}Enemy_Struct;


void Enemy_Health(Enemy_Struct* enemy, int health);

void Enemy_Die(Enemy_Struct* enemy);




#endif

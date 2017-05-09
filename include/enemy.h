#ifndef  __ENEMY_H
#define __ENEMY_H


#include "entity.h"
#include "player.h"
#include "resourcemanager.h"
/**
*@breif Creates a struct to represent an enemy

*/

typedef struct
{

	Entity_Struct *ent;

	int health = 100;

	bool alive = true;

	int state;


}Enemy_Struct;

/**
*@breif Enemies AI script

*/
void Enemy_AI(Enemy_Struct* enemy, Player_Struct* player);
/**
*@breif Checks for enemies colliding with things

*/
void Enemey_Collision(Enemy_Struct* enemy, Manager* manager, Player_Struct* player, Physics* physics);
/**
*@breif edits the enemies health

*/

void Enemy_Health(Enemy_Struct* enemy, int health);

/**
*@breif Kills the enemy

*/

void Enemy_Die(Enemy_Struct* enemy, Physics* physics, Player_Struct* player);

/**
*@breif Patrol functio for enemy

*/

void Enemy_Patrol(Enemy_Struct* enemy);

/**
*@breif Chase function for enemy

*/
void Enemy_Chase(Enemy_Struct* enemy, Player_Struct* player);

/**
*@breif Calculates the player distance from the enemy

*/

void Enemy_PlayDis(Enemy_Struct* enemy, Player_Struct* player);

#endif

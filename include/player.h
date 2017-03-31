#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "entity.h"


typedef struct
{

	Entity_Struct *ent;

	int health = 100;

	int mana = 100;

	int level = 0;
	
	int skillpoints = 0;

	float experience = 0;


}Player_Struct;


void Player_Health(Player_Struct *player, int health);

void Player_Mana(Player_Struct *player, int mana);

void Player_Exp(Player_Struct *player, float exp);

#endif __PLAYER_H__

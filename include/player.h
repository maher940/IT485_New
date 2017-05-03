#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "entity.h"
#include "resourcemanager.h"

typedef struct
{

	Entity_Struct *ent;

	int health = 100;

	int mana = 100;

	int TotalHealth = 100;

	int TotalMana = 100;

	int level = 1;
	
	int skillpoints = 0;

	float experience = 0;

	int strength = 1;

	int speed = 1;

	int arcane = 1;


}Player_Struct;


void Player_Health(Player_Struct *player, int health);

void Player_Mana(Player_Struct *player, int mana);

void Player_Exp(Player_Struct *player, float exp);

void Player_Pos(Player_Struct *player,glm::vec3 camerapos);

void Player_Shoot(Player_Struct *player, Physics* physics, Manager *manager);


void Player_Melee(Player_Struct *player, Physics* physics);

#endif __PLAYER_H__

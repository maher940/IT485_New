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


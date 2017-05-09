#ifndef  __PICKUP_H
#define __PICKUP_H

#include "entity.h"
#include "player.h"


typedef struct {

	std::string type;
	Entity_Struct* ent;
	bool touched = false;



}Item_Struct;

void Item_Collision(Item_Struct* item, Player_Struct* player);

void Item_PickUp(Item_Struct* item, Player_Struct* player);






#endif
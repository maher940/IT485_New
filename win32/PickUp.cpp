#include "PickUp.h"



struct itemcollision : public btCollisionWorld::ContactResultCallback
{

	//testCallback(Test_Struct* context) : ctext(context) {}
	itemcollision(Item_Struct* item, Player_Struct* player) : it(item), play(player) {}


	virtual	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
	{


		return 0;
	}

	Item_Struct* it;
	Player_Struct* play;

};


void Item_Collision(Item_Struct* item, Player_Struct* player)
{



	//if(item->touched)
}

void Item_PickUp(Item_Struct* item, Player_Struct* player)
{
	if (item->touched == false)
	{



	}


}
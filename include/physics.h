
#ifndef  __PHYSICS_H
#define __PHYSICS_H
#include <btBulletDynamicsCommon.h>
#include <vector>

#include "simple_logger.h"

#include "glm\vec3.hpp"



typedef struct
{


	int points = 0;
}Test_Struct;


struct testCallback : public btCollisionWorld::ContactResultCallback
{

	/*ContactSensorCallback(btRigidBody& tgtBody , YourContext& context /*, ... )
	: btCollisionWorld::ContactResultCallback(), body(tgtBody), ctxt(context) { }

	btRigidBody& body; //!< The body the sensor is monitoring
	YourContext& ctxt; //!< External information for contact processing
	*/



	//testCallback(int& context) : btCollisionWorld::ContactResultCallback(), ctext(context) {}

	//int& ctext;
	testCallback(Test_Struct* context) : ctext(context) {}

	
	

	virtual	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
	{

		//ctext++;
		//slog("Context %f \n", ctext);

		//ctext += 10;
		ctext->points += 10;
		//slog("points %f", ctext->points);
		return 0;
	}

	Test_Struct* ctext;
};




struct CollisionCallback : public btCollisionWorld::ContactResultCallback
{

	virtual	btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
	{
		slog("collision");
		//hithum++;
		//slog("%f \n", hithum);
		return 0;
	}
	
};

class Physics
{



public:


	int heloo;

	btDynamicsWorld* space;

	btDispatcher* dispatcher;

	btCollisionConfiguration* collisionConfig;

	btBroadphaseInterface* broadphase;

	btConstraintSolver* solver;

	std::vector<btRigidBody*>bodies;

	std::vector<glm::vec3>bodiesPos;

	CollisionCallback callback;


	

	Physics();

	void PhysicsStep(float time);

	btRigidBody* SphereRigidBody(float radius, glm::vec3 position, float mass);
	btRigidBody* CubeRigidBody(glm::vec3 size, glm::vec3 position, float mass);
	btRigidBody* PlaneBody();

	void Physics::deleteRigidBody();


	void Physics::deletePhysicsWorld();
	


	void CollisionTest(btRigidBody* body);
	


	void Physics::CollisionTest2(btRigidBody* body1, btRigidBody* body2);
	


};



#endif //  __PHYSICS_H


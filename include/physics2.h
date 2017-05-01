#ifndef  __PHYSICS2_H
#define __PHYSICS2_H






#include <btBulletDynamicsCommon.h>
#include <vector>

#include "simple_logger.h"

#include "glm\vec3.hpp"















class Physics2
{

public:

	//btRigidBody bodies[100];
	btDynamicsWorld* space;

	btDispatcher* dispatcher;

	btCollisionConfiguration* collisionConfig;

	btBroadphaseInterface* broadphase;

	btConstraintSolver* solver;

	std::vector<btRigidBody*>bodies;

	Physics2();

	btRigidBody* SphereRigidBody(float radius, glm::vec3 position, float mass);
	
	btRigidBody* PlaneBody();

	btDynamicsWorld* Physics_Init2();

	void renderPlane2(btRigidBody* plane);
	void renderSphere2(btRigidBody* sphere);


	void deleteRigidBody2();
	void deletePhysicsWorld2();

};
#endif

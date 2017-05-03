#include "physics.h"



Physics::Physics()
{

	collisionConfig = new btDefaultCollisionConfiguration();

	dispatcher = new btCollisionDispatcher(collisionConfig);

	broadphase = new btDbvtBroadphase();

	solver = new btSequentialImpulseConstraintSolver();

	space = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);


	space->setGravity(btVector3(0, -10, 0));
	
};


void Physics::PhysicsStep(float time)
{

	space->stepSimulation(time);

}

btRigidBody* Physics::PlaneBody()
{

	btTransform t;

	t.setIdentity();

	t.setOrigin(btVector3(0, -10, 0));

	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

	btMotionState* motion = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);

	btRigidBody* body = new btRigidBody(info);
	space->addRigidBody(body);

	bodies.push_back(body);

	return body;

}


btRigidBody* Physics::CubeRigidBody(glm::vec3 size, glm::vec3 position, float mass)
{
	slog("We maming a body");
	btTransform t;

	t.setIdentity();

	t.setOrigin(btVector3(position.x, position.y, position.z));

	btBoxShape* cube = new btBoxShape(btVector3(size.x / 2.0, size.y / 2.0, size.z / 2.0));

	btVector3 inertia(0, 0, 0);

	if (mass != 0.0)
	{
		cube->calculateLocalInertia(mass, inertia);
	}

	btMotionState* motion = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cube, inertia);

	btRigidBody* body = new btRigidBody(info);
	space->addRigidBody(body);

	bodies.push_back(body);

	return body;

}

btRigidBody* Physics::CubeRigidBodyTR(glm::vec3 size, glm::vec3 position, float mass)
{

	btTransform t;

	t.setIdentity();

	t.setOrigin(btVector3(position.x, position.y, position.z));

	btBoxShape* cube = new btBoxShape(btVector3(size.x / 2.0, size.y / 2.0, size.z / 2.0));

	btVector3 inertia(0, 0, 0);

	if (mass != 0.0)
	{
		cube->calculateLocalInertia(mass, inertia);
	}

	btMotionState* motion = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cube, inertia);

	btRigidBody* body = new btRigidBody(info);

	body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	space->addRigidBody(body);

	bodies.push_back(body);

	return body;



}
btRigidBody* Physics::SphereRigidBody(float radius, glm::vec3 position, float mass)
{


	btTransform t;

	t.setIdentity();

	t.setOrigin(btVector3(position.x, position.y, position.z));

	btSphereShape* sphere = new btSphereShape(radius);

	btVector3 inertia(0, 0, 0);

	if (mass != 0.0)
	{
		sphere->calculateLocalInertia(mass, inertia);
	}

	btMotionState* motion = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, sphere, inertia);

	btRigidBody* body = new btRigidBody(info);
	space->addRigidBody(body);

	//bodies.push_back(body);

	return body;


}



void Physics::CollisionTest(btRigidBody* body)
{


	space->contactTest(body, callback);

	

}


void Physics::CollisionTest2(btRigidBody* body1, btRigidBody* body2)
{

	space->contactPairTest(body1, body2, callback);

}

void Physics::deleteRigidBody()
{

	for (int i = 0; i < bodies.size(); i++)
	{

		space->removeCollisionObject(bodies[i]);
		btMotionState* motionState = bodies[i]->getMotionState();
		btCollisionShape* shape = bodies[i]->getCollisionShape();
		delete bodies[i];
		delete shape;
		delete motionState;

	}

}


void Physics::deletePhysicsWorld()
{

	delete dispatcher;

	delete collisionConfig;

	delete solver;

	delete broadphase;

	delete space;


}

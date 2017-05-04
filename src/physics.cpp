#include "physics.h"



Physics::Physics()
{

	collisionConfig = new btDefaultCollisionConfiguration();

	dispatcher = new btCollisionDispatcher(collisionConfig);

	broadphase = new btDbvtBroadphase();

	solver = new btSequentialImpulseConstraintSolver();

	space = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);

	space->setGravity(btVector3(0, -10, 0));

	bodies.reserve(maxentities);

	for (int i = 0; i < maxentities; i++)
	{
		
		btTransform t;

		t.setIdentity();

		t.setOrigin(btVector3(0, -8, 0));

		btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

		btMotionState* motion = new btDefaultMotionState(t);

		btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);

		btRigidBody* body = new btRigidBody(info);
		bodies.push_back(body);
	}
	
};


void Physics::PhysicsStep(float time)
{

	space->stepSimulation(time);

}

btRigidBody* Physics::PlaneBody()
{

	btTransform t;

	t.setIdentity();

	t.setOrigin(btVector3(0, -8, 0));

	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

	btMotionState* motion = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);

	btRigidBody* body = new btRigidBody(info);
	space->addRigidBody(body);

	bodies[0] = body;
	//bodies.push_back(body);

	return body;

}


btRigidBody* Physics::CubeRigidBody(glm::vec3 size, glm::vec3 position, float mass)
{
	//slog("We maming a body");
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

	//bodies.push_back(body);

	return body;

}

btRigidBody* Physics::CubeRigidBodyTR(glm::vec3 size, glm::vec3 position, float mass, btQuaternion* quat)
{

	btTransform t;

	t.setIdentity();

	t.setOrigin(btVector3(position.x, position.y, position.z));

	t.setRotation(*quat);

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

	Melee.push_back(body);

	return body;



}







btRigidBody* Physics::MeshRigidBody(glm::vec3 position, float mass, Mesh mesh)
{


	btTransform t;

	t.setIdentity();

	t.setOrigin(btVector3(position.x, position.y, position.z));

	//btBoxShape* cube = new btBoxShape(btVector3(size.x / 2.0, size.y / 2.0, size.z / 2.0));

	btConvexHullShape* cube = new btConvexHullShape();
	//mesh.

	for (int i = 0; i < mesh.indices.size(); i++)
	{
		btVector3 position;

		//mesh.indices[i];
		
		unsigned int j = mesh.indices[i];

		//float w = mesh.vertices2[j].Position.x;

		//position.x = w;
		 // position.x = mesh.vertices2[j].Position.x;
		  //position.y = mesh.vertices2[j].Position.y;
		  //position.z = mesh.vertices2[j].Position.z;

		position.setX(mesh.vertices2[j].Position.x);
		position.setY(mesh.vertices2[j].Position.y);
		position.setZ(mesh.vertices2[j].Position.z);
		  cube->addPoint(position);

	}

	btVector3 inertia(0, 0, 0);

	if (mass != 0.0)
	{
		cube->calculateLocalInertia(mass, inertia);
	}

	btMotionState* motion = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, cube, inertia);

	btRigidBody* body = new btRigidBody(info);
	space->addRigidBody(body);

	//bodies.push_back(body);

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

		
		btMotionState* motionState = bodies[i]->getMotionState();
		btCollisionShape* shape = bodies[i]->getCollisionShape();
		space->removeCollisionObject(bodies[i]);
		delete bodies[i];
		delete shape;
		delete motionState;

	}

}

void Physics::deleteRigidBodyOne(int i)
{


	space->removeCollisionObject(bodies[i]);
	/*
	btMotionState* motionState = bodies[i]->getMotionState();
	btCollisionShape* shape = bodies[i]->getCollisionShape();
	
	delete bodies[i];

	//bodies.erase(bodies.begin() + i);
	delete shape;
	delete motionState;
	*/

	btTransform t;

	t.setIdentity();

	t.setOrigin(btVector3(0, -8, 0));

	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

	btMotionState* motion = new btDefaultMotionState(t);

	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);

	btRigidBody* body = new btRigidBody(info);

	bodies[i] = body;

}
void Physics::deletePhysicsWorld()
{

	delete dispatcher;

	delete collisionConfig;

	delete solver;

	delete broadphase;

	delete space;


}

void Physics::deleteMelee()
{

	space->removeCollisionObject(Melee[0]);
	btMotionState* motionState = Melee[0]->getMotionState();
	btCollisionShape* shape = Melee[0]->getCollisionShape();

	delete Melee[0];

	Melee.erase(Melee.begin() + 0);
	delete shape;
	delete motionState;


}


#ifndef  __PHYSICS_H
#define __PHYSICS_H

#include <btBulletDynamicsCommon.h>
#include <vector>
#define maxentities 21
#include "simple_logger.h"
#include "mesh.h"
#include "glm\vec3.hpp"

/**
*@breif The setup of the physcis world and the rigidbodies

*/

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

	
	std::vector<btRigidBody*>scenerigidbody;

	std::vector<btRigidBody*>Melee;

	std::vector<btRigidBody*>Bullets;

	std::vector<glm::vec3>bodiesPos;




	

	Physics();

	/**
	*@breif Steps throught the physics world

	*/
	void PhysicsStep(float time);

	/**
	*@breif Returns a transfrom created from a glme::vec3

	*/
	btTransform* CreateTransform(glm::vec3 position);

	/**
	*@breif Creates a sphere rigid body

	*/
	btRigidBody* SphereRigidBody(float radius, glm::vec3 position, float mass);

	/**
	*@breif Creates a cube rigid body

	*/
	btRigidBody* CubeRigidBody(glm::vec3 size, btTransform* transform, float mass);
	/**
	*@breif Creates a cube rigid body that is a trigger

	*/

	btRigidBody* CubeRigidBodyTrig(glm::vec3 size, btTransform* transform, float mass);
	/**
	*@breif Creates a cube rigid body that is a trigger and needs a quaterion

	*/

	btRigidBody* CubeRigidBodyTR(glm::vec3 size, glm::vec3 position, float mass, btQuaternion* quat);

	/**
	*@breif Creates a convex hull shape rigid body

	*/
	btRigidBody* MeshRigidBody(glm::vec3 position, float mass, Mesh mesh);

	/**
	*@breif Creates a rigid body based off mesh data

	*/

	btRigidBody* TriRigidBody(glm::vec3 position, float mass, Mesh mesh);

	/**
	*@breif Creates a plane rigid body

	*/

	btRigidBody* PlaneBody();

	/**
	*@breif deletes the rigid bodies

	*/
	void Physics::deleteRigidBody();

	/**
	*@breif deletes the physcis worl

	*/
	void Physics::deletePhysicsWorld();
	/**
	*@breif deletes one rigid body

	*/
	void Physics::deleteRigidBodyOne(int i);
	/**
	*@breif deletes the melee rigid body

	*/
	void Physics::deleteMelee();

	/**
	*@breif runs a collision test

	*/
	void CollisionTest(btRigidBody* body);
	
	/**
	*@breif runs a collision test between two objects

	*/

	void Physics::CollisionTest2(btRigidBody* body1, btRigidBody* body2);
	


};



#endif //  __PHYSICS_H


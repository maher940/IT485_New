#include "physics2.h"
#include"graphics3d.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



Physics2::Physics2()
{

};

btDynamicsWorld* Physics2::Physics_Init2()
{

	collisionConfig = new btDefaultCollisionConfiguration();

	dispatcher = new btCollisionDispatcher(collisionConfig);

	broadphase = new btDbvtBroadphase();

	solver = new btSequentialImpulseConstraintSolver();

	space = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);


	space->setGravity(btVector3(0, -10, 0));

	return space;
}

btRigidBody* Physics2::PlaneBody()
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
btRigidBody* Physics2::SphereRigidBody(float radius, glm::vec3 position, float mass)
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

	bodies.push_back(body);

	return body;



}

void Physics2::renderPlane2(btRigidBody* plane)
{
	if (plane->getCollisionShape()->getShapeType() != STATIC_PLANE_PROXYTYPE)
	{
		return;
	}

	//glColor3f(0.8, 0.8, 0.8);

	//float r = ((btSphereShape*)plane->getCollisionShape())->getRadius();
	btTransform t;

	plane->getMotionState()->getWorldTransform(t);

	GLuint Color = glGetUniformLocation(graphics3d_get_shader_program(), "incolor");

	glm::vec3 colors(0.8, 0.8, 0.8);
	glUniform3fv(Color, 1, glm::value_ptr(colors));

	glBegin(GL_QUADS);
	glVertex3f(-10, -5, 10);
	glVertex3f(-10, -5, -10);
	glVertex3f(10, -5, -10);
	glVertex3f(10, -5, 10);
	glEnd();


}

void Physics2::renderSphere2(btRigidBody* sphere)
{


	GLUquadricObj* quad;

	if (sphere->getCollisionShape()->getShapeType() != SPHERE_SHAPE_PROXYTYPE)
	{
		return;
	}
	GLuint Color = glGetUniformLocation(graphics3d_get_shader_program(), "incolor");
	glm::vec3 colors(0.0, 0.0, 1.0);
	glUniform3fv(Color, 1, glm::value_ptr(colors));

	float r = ((btSphereShape*)sphere->getCollisionShape())->getRadius();
	btTransform t;

	sphere->getMotionState()->getWorldTransform(t);

	btVector3 origin = t.getOrigin();



	quad = gluNewQuadric();

	glm::vec3 position;

	position.x = origin.getX();
	position.y = origin.getY();
	position.z = origin.getZ();

	glm::mat4 Modelmat = glm::translate(glm::mat4(), position);

	GLuint Model = glGetUniformLocation(graphics3d_get_shader_program(), "Model");

	glUniformMatrix4fv(Model, 1, GL_FALSE, &Modelmat[0][0]);

	gluSphere(quad, r, 20, 20);
}




void Physics2::deleteRigidBody2()
{
	for (int i = 0; i<bodies.size(); i++)
	{
		space->removeCollisionObject(bodies[i]);
		btMotionState* motionState = bodies[i]->getMotionState();
		btCollisionShape* shape = bodies[i]->getCollisionShape();
		delete bodies[i];
		delete shape;
		delete motionState;
	}
}
void Physics2::deletePhysicsWorld2()
{
	delete dispatcher;

	delete collisionConfig;

	delete solver;

	delete broadphase;

	delete space;
}
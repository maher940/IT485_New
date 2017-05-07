#include "entity.h"
#include "graphics3d.h"
#include <glm/glm.hpp>
#include "glm\gtc\type_ptr.hpp"
Entity_Struct* entityList;
int numentities;

void Entity_Think(Entity_Struct *ent)
{



}


void Entity_Update(Entity_Struct *ent)
{



	//ent->Model = glm::translate(glm::mat4(), ridgpos);

	btTransform t;

	ent->body->getMotionState()->getWorldTransform(t);

	btVector3 origin = t.getOrigin();

	btVector3 forward = t.getBasis().getColumn(2);
	
	
	glm::vec3 forwardglm;

	forwardglm.x = -forward.getX();
	forwardglm.y = -forward.getY();
	forwardglm.z = -forward.getZ();

	//btQuaternion rotation = t.getRotation();

	ent->forward = forwardglm;

	

	glm::vec3 newpos;

	newpos.x = origin.getX();

	newpos.y = origin.getY();

	newpos.z = origin.getZ();

	ent->position = newpos;

	
	
	ent->Model = glm::translate(glm::mat4(), newpos);

	

	if (ent->type == "bullet")
	{
		ent->timer++;
		//ent->timer++;
		//slog("TImer %d", ent->timer);
	}
	

	//ent->Model = glm::rotate(glm::mat4(), rotation);

	
	

}

void Entity_Draw(Entity_Struct *ent)
{


	GLuint Model = glGetUniformLocation(graphics3d_get_shader_program(), "Model");

	glUniformMatrix4fv(Model, 1, GL_FALSE, &ent->Model[0][0]);


	GLuint Color = glGetUniformLocation(graphics3d_get_shader_program(), "incolor");

	glm::vec3 colors;
	//float colors[] = { 1.0,0.0,0.0};
	/*
	glm::vec3 colors;

	if (ent->type == "bullet")
	{
		 colors = glm::vec3(1.0, 0.0, 0.0);
	}
	if (ent->type == "none")
	{
		colors = glm::vec3(0.0, 0.0, 1.0);
	}
	else
	{
		colors = glm::vec3(0.0, 1.0, 0.0);
	}
	*/
	colors = ent->color;
	glUniform3fv(Color, 1, glm::value_ptr(colors));

	ent->mesh.Draw_Mesh();
	

}

glm::vec3 Entity_getPos(Entity_Struct *ent)
{

	return ent->position;
}

void Entity_SetPos(Entity_Struct *ent, glm::vec3 pos)
{

	ent->position = pos;


}




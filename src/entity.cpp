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
	
	
	
	//btQuaternion rotation = t.getRotation();


	

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


	//float colors[] = { 1.0,0.0,0.0};
	glm::vec3 colors(1.0, 0.0, 0.0);
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




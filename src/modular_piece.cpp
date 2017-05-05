#include "modular_piece.h"

#include "glm\gtc\type_ptr.hpp"

#include "graphics3d.h"




void  Draw_Piece(Modular_Struct *piece)
{

	GLuint Model = glGetUniformLocation(graphics3d_get_shader_program(), "Model");

	//glUniformMatrix4fv(Model, 1, GL_FALSE, &ent->Model[0][0]);



	glUniformMatrix4fv(Model, 1, GL_FALSE, &piece->ModelMat[0][0]);


	GLuint Color = glGetUniformLocation(graphics3d_get_shader_program(), "incolor");


	//float colors[] = { 1.0,0.0,0.0};
	glm::vec3 colors(0.0, 0.0, 1.0);
	glUniform3fv(Color, 1, glm::value_ptr(colors));

	piece->model.Draw_Mesh();



}
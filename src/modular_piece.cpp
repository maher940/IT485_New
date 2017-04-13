#include "modular_piece.h"
#include "graphics3d.h"




void  Draw_Piece(Modular_Struct *piece)
{

	GLuint Model = glGetUniformLocation(graphics3d_get_shader_program(), "Model");

	//glUniformMatrix4fv(Model, 1, GL_FALSE, &ent->Model[0][0]);



	glUniformMatrix4fv(Model, 1, GL_FALSE, &piece->ModelMat[0][0]);

	piece->model.Draw_Mesh();



}
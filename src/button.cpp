#include "button.h"

GLuint Button_Vertex_buf;
GLuint Button_UV_buf;


Button::Button()
{

}

void Button::Button_Setup(glm::vec3 Top, glm::vec3 BotRight, glm::vec3 BotLeft)
{

	Button_Verts.push_back(Top);

	Button_Verts.push_back(BotLeft);

	Button_Verts.push_back(BotRight);

	glGenBuffers(1, &Button_Vertex_buf);


}

void Button::Button_Draw()
{

	glBindBuffer(GL_ARRAY_BUFFER, Button_Vertex_buf);


	glBufferData(GL_ARRAY_BUFFER, Button_Verts.size() * sizeof(glm::vec3), &Button_Verts[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, Button_Vertex_buf);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

}
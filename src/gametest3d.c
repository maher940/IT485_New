/**
* gametest3d
* @license The MIT License (MIT)
*   @copyright Copyright (c) 2015 EngineerOfLies
*    Permission is hereby granted, free of charge, to any person obtaining a copy
*    of this software and associated documentation files (the "Software"), to deal
*    in the Software without restriction, including without limitation the rights
*    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*    copies of the Software, and to permit persons to whom the Software is
*    furnished to do so, subject to the following conditions:
*    The above copyright notice and this permission notice shall be included in all
*    copies or substantial portions of the Software.
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*    SOFTWARE.
*/
#define GLM_ENABLE_EXPERIMENTAL
#include "simple_logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "vector.h"
#include "mesh.h"
#include "UIPopup.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "SDL.h"
#include <glm\gtx\string_cast.hpp>
#include "hud.h"
GLuint VBO;
GLuint VAO;
GLuint EBO;

GLuint vao;
GLuint vertexbuffer;
GLuint IndexVBO;


//GLuint TextureID;

SDL_Surface *image;

//GLuint HUD_Vertex_buf;
//GLuint HUD_UV_buf;
static int health;
static float experience;
static int mana;







GLuint triangleBufferObject;
int main(int argc, char *argv[])
{


	int hudon = 0;
	



	health = 100;

	mana = 100;

	experience = 100;
	GLuint vao;
	
	char bGameLoopRunning = 1;
	SDL_Event e;
	const float triangleVertices[] = {
		0.0f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.366f, 0.0f, 1.0f,
		-0.5f, -0.366f, 0.0f, 1.0f,
		//next part contains vertex colors
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	}; //we love you vertices!


	//Vertex vertices 

	//std::vector<Vertex> vertices = Vertex(glm::vec3(0, 0, 0));
	
	/*

	Vertex verts[] = { glm::vec3(-0.5,-0.5,0), glm::vec3(0,0.5,0),glm::vec3(0.5,-0.5,0) };

	std::vector<Vertex> vertices;

	vertices.push_back(verts[0]);
	vertices.push_back(verts[1]);
	vertices.push_back(verts[2]);

	Test mesh(vertices);
	*/
	init_logger("gametest3d.log");
	if (graphics3d_init(1024, 768, 1, "gametest3d", 33) != 0)
	{
		return -1;
	}
	
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);



	GLuint MatrixID = glGetUniformLocation(graphics3d_get_shader_program(), "MVP");
	//glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
//	glm::mat4 View = glm::lookAt(glm::vec3(4, 3, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	Camera cam;

	


	//Camera cam;
	
	//View = cam.getViewMatrix();

	//Projection = cam.getProjectionMatrix();


	glm::mat4 Model = glm::mat4(1.0f);

	//glm::mat4 mvp = Projection * View * Model;
	glm::mat4 mvp;
	glm::mat4 mvp2;
	glm::mat4 mvp3;
	//glm::mat4 View;




	glGenBuffers(1, &IndexVBO);
	glGenBuffers(1, &vertexbuffer);
	//glGenBuffers(1, &HUD_Vertex_buf);
	//glGenBuffers(1, &HUD_UV_buf);
/*
	
	/*
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao); //make our vertex array object, we need it to restore state we set after binding it. Re-binding reloads the state associated with it.

	glGenBuffers(1, &triangleBufferObject); //create the buffer
	glBindBuffer(GL_ARRAY_BUFFER, triangleBufferObject); //we're "using" this one now
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW); //formatting the data for the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind any buffers
	*/
	//slog("glError: %s", glGetError());
	Mesh mesh;
	mesh.Load_Obj("cube.obj");



	HUD hud;

	hud.Set_HUD_Points();


	hud.TextureLoad();

	//hud.TextrueSetUp();

	

	//TextureID = glGetUniformLocation(graphics3d_get_shader_program2(), "myText");



	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, image);

	//glUniform1i(TextureID, 0);

	//Camera cam(glm::vec3(0,0,1), glm::radians(45.0f), 4/3, 0.1f, 1000.0f);

	
	//Projection = cam.Projection;


	//View = cam.getView();

	//Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	//View = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


	
	//View = cam.getViewMatrix();

	//Projection = cam.getProjectionMatrix();


	int x;
	int y;

	
	int i = 4;
	float time;
	GLfloat angle = 20;
	//Camera(glm::vec3 pos, float fov, float aspect, float zNear, float fNear)

	

	const Uint8 *state = SDL_GetKeyboardState(NULL);


	



	while (bGameLoopRunning)
	{



		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				bGameLoopRunning = 0;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				bGameLoopRunning = 0;

			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_TAB)
				hudon++;
			
		}

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		GLfloat radius = 1.0f;
		//GLfloat camX = sin((SDL_GetTicks()/1000) * radius);
		//GLfloat camZ = cos((SDL_GetTicks() / 1000) * radius);
		
		angle++;
		
		//View = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			 
		//mvp = Projection * View * Model;
		

		
		SDL_GetMouseState(&x, &y);

		cam.cameraRotation(x, y);


		//cam.CameraRot(x, y);
		if (state[SDL_SCANCODE_A])
		{

			//printf("TEST \n");
			cam.cameraMovement('A');
		}
	
		if (state[SDL_SCANCODE_D])
		{
			cam.cameraMovement('D');
			//printf("TEST \n");
		}
		if (state[SDL_SCANCODE_W])
		{
			cam.cameraMovement('W');
			//printf("TEST \n");
		}
		if (state[SDL_SCANCODE_S])
		{
			cam.cameraMovement('S');
			//printf("TEST \n");
		}
		if (state[SDL_SCANCODE_P])
		{
			
			//printf("TEST \n");
		}


		
			
		
		//View = cam.getViewMatrix();
		//Projection = cam.getProjectionMatrix();

		
		
		cam.computeMatricesFromInputs();


	//	glm::mat4 Projection = cam.getProjectionMatrix();
		//glm::mat4 View = cam.getViewMatrix();

		glm::mat4 Projection = cam.ProjectionMatrix;
		glm::mat4 View = cam.ViewMatrix;

		glm::mat4 ProjTest;

		glm::mat4 ViewTest;



		glm::mat4 ProjTest2 = cam.getProjectionMatrix();

		glm::mat4 ViewTest2 = cam.getViewMatrix();



		ProjTest = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

		ViewTest = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));




		mvp = Projection * View * Model;

		mvp2 = ProjTest * ViewTest * Model;

		mvp3 = ProjTest2 * ViewTest2 * Model;



		/*
		if (state[SDL_SCANCODE_A])
		{

			
			//printf("TEST \n");
			printf("\n");
			printf("MVP \n");
			std::cout << glm::to_string(mvp) << std::endl;
			printf("\n");
			printf("MVP2 \n");
			std::cout << glm::to_string(mvp2) << std::endl;
			printf("\n");
			printf("MVP3 \n");
			std::cout << glm::to_string(mvp3) << std::endl;
			printf("\n");
		}
		*/




		
		//printf("x is %d \n", x);
		//printf("y is %d \n", y);
		/* drawing code in here! */

		glUseProgram(graphics3d_get_shader_program());

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
		mesh.Draw_Mesh();

		//hud.Draw_HUD();


		if (hudon % 2 != 0)
		{
			glUseProgram(graphics3d_get_shader_program2());
		
			hud.Draw_HUD();
			
			
		}

		time = SDL_GetTicks() / 1000;
		//printf("Time is %f", time);
		//mesh.Draw();
		/*
		glBindBuffer(GL_ARRAY_BUFFER, triangleBufferObject); //bind the buffer we're applying attributes to
		glEnableVertexAttribArray(0); //0 is our index, refer to "location = 0" in the vertex shader
		glEnableVertexAttribArray(1); //attribute 1 is for vertex color data
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //tell gl (shader!) how to interpret our vertex data
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)48); //color data is 48 bytes in to the array
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		*/

		glUseProgram(0);
		/* drawing code above here! */


		//switch to ortho for UI

		glMatrixMode(GL_PROJECTION);					
		glPushMatrix();							
		glLoadIdentity();						
		glOrtho(0, 1024, 768, 0, -1, 1);				
		glMatrixMode(GL_MODELVIEW);					
		glPushMatrix();							
		glLoadIdentity();


		drawhud(health, mana, experience);
		drawstats(health, experience, mana);


		//switch back to Perspective
		glMatrixMode(GL_PROJECTION);					
		glPopMatrix();							
		glMatrixMode(GL_MODELVIEW);					
		glPopMatrix();



		graphics3d_next_frame();
	}
	return 0;
}

/*eol@eof*/

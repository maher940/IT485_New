#include "UIPopup.h"

#include <iostream>
#include "simple_logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "loadobj.h"
#include "texture.h"
#include "UIPopup.h"
#include <GL\glut.h>
#include "btBulletDynamicsCommon.h"
#include <GLFW\glfw3.h>
#include <GL\freeglut.h>
#include "SDL.h"
#include "SDL_image.h"





void drawstats(int health, float exp, int mana)
{


	/*

	SDL_Surface *image;
	image = IMG_Load("window_blue2.png");

	if (!image) {
		printf("IMG_Load: %s\n", IMG_GetError());
		// handle error
	}
	/*
	if (image)
	{
		printf("Hoorayy Image \n");
	}
	*/
	/*
	glEnable(GL_TEXTURE_2D);


	GLuint textures = 0;
	glGenTextures(1, &textures); //Number of textures stored in array name specified

	glBindTexture(GL_TEXTURE_2D, textures);


	int Mode = GL_RGB;

	if (image->format->BytesPerPixel == 4)
	{
		Mode = GL_RGBA;
	}

	

	// Map the surface to the texture in video memory
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 124, 124, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels); //GL_BITMAP
	glTexImage2D(GL_TEXTURE_2D, 0, Mode, image->w, image->h, 0, Mode, GL_UNSIGNED_BYTE, image->pixels);
	

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	//SDL_FreeSurface(image);


	glBindTexture(GL_TEXTURE_2D, textures);
	
	glBegin(GL_QUADS);
	//glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(510, 135);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(300, 135);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(300, 285);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(510, 285);
	glEnd();

	glDisable(GL_TEXTURE_2D);



	/*
	glTexCoord2f(0.f, 0.f); glVertex2f(x, y); //Bottom left
	glTexCoord2f(1.f, 0.f); glVertex2f(x + iwidth, y); //Bottom right
	glTexCoord2f(1.f, 1.f); glVertex2f(x + iwidth, y + iheight); //Top right
	glTexCoord2f(0.f, 1.f); glVertex2f(x, y + iheight); //Top left
	*/





	/*
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mark_textures[0].id);


	// Draw a textured quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 100, 0);
	glTexCoord2f(1, 1); glVertex3f(100, 100, 0);
	glTexCoord2f(1, 0); glVertex3f(100, 0, 0);
	glEnd();
	*/









	/*
	glColor3f(1, 0, 0);
	std::string healthstring = "Total Health: " + std::to_string(health);



	glWindowPos2i(300, 600);
	//len = (int)strlen(text);
	int len = healthstring.length();


	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, healthstring[i]);
	}

	std::string manastring = "Total Mana: " + std::to_string(mana);

	glWindowPos2i(300, 550);
	int len2 = manastring.length();


	for (int i = 0; i < len2; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, manastring[i]);
	}

	std::string expstring = "Total Exp: " + std::to_string(exp);
	glWindowPos2i(300, 500);
	int len3 = expstring.length();

	for (int i = 0; i < len3; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, expstring[i]);
	}

	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex2f(300, 135);
	glVertex2f(510, 135);
	glVertex2f(510, 185);
	glVertex2f(300, 185);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex2f(300, 185);
	glVertex2f(510, 185);
	glVertex2f(510, 235);
	glVertex2f(300, 235);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex2f(300, 235);
	glVertex2f(510, 235);
	glVertex2f(510, 285);
	glVertex2f(300, 285);
	glEnd();
	*/

}

void deletestats()
{

}


void drawhud(int health, int mana, float exp)
{


	

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);

	//top points of rect
	glVertex2f(health, 680);
	glVertex2f(0, 680);

	//bottom points of rect
	glVertex2f(0, 700);
	glVertex2f(health, 700);
	glEnd();
	

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex2f(mana, 710);
	glVertex2f(0, 710);
	glVertex2f(0, 730);
	glVertex2f(mana, 730);
	glEnd();

	
	glBegin(GL_QUADS);
	glColor3f(1, 1, 0);
	glVertex2f(exp, 740);
	glVertex2f(0, 740);
	glVertex2f(0, 750);
	glVertex2f(exp, 750);
	glEnd();
	

}
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





void drawstats(int health, float exp, int mana, int level, int skillstats)
{



	
	glColor3f(1, 0, 0);
	std::string healthstring = "Total Health: " + std::to_string(health);



	glWindowPos2i(300, 500);
	//len = (int)strlen(text);
	int len = healthstring.length();


	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, healthstring[i]);
	}

	std::string manastring = "Total Mana: " + std::to_string(mana);

	glWindowPos2i(300, 450);
	int len2 = manastring.length();


	for (int i = 0; i < len2; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, manastring[i]);
	}

	std::string expstring = "Total Exp: " + std::to_string(exp);
	glWindowPos2i(300, 400);
	int len3 = expstring.length();

	for (int i = 0; i < len3; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, expstring[i]);
	}


	std::string levelstring = "Level: " + std::to_string(level);
	glWindowPos2i(300, 350);
	int len4 = levelstring.length();

	for (int i = 0; i < len4; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, levelstring[i]);
	}

	std::string skillstring = "Skill points to spend: " + std::to_string(skillstats);
	glWindowPos2i(300, 300);
	int len5 = skillstring.length();

	for (int i = 0; i < len5; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, skillstring[i]);
	}


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
#include <iostream>
#include "Common\glut.h"
#include "Common\GLAux.h"
#include "defines.h"
#include "Particles.h"
#include "Lighting.h"

#pragma comment(lib, "GLAux.lib")


Particles Explosion(0);
Particles Dust(DUST);
Particles RuinsDust(SMALL_DUST);
Lighting Light;


void LoadTextures()
{
	AUX_RGBImageRec *textureWall   = auxDIBImageLoadA("Textures/wall.bmp");
	AUX_RGBImageRec *textureFloor  = auxDIBImageLoadA("Textures/floor.bmp");
	AUX_RGBImageRec *textureGrass  = auxDIBImageLoadA("Textures/grass.bmp");
	AUX_RGBImageRec *textureWindow = auxDIBImageLoadA("Textures/window.bmp");
	AUX_RGBImageRec *textureRuins  = auxDIBImageLoadA("Textures/ruins.bmp");
	AUX_RGBImageRec *textureSteel  = auxDIBImageLoadA("Textures/steel.bmp");
	AUX_RGBImageRec *textureLSteel = auxDIBImageLoadA("Textures/lightsteel.bmp");
	AUX_RGBImageRec *textureDSteel = auxDIBImageLoadA("Textures/darksteel.bmp");
	AUX_RGBImageRec *textureBSteel = auxDIBImageLoadA("Textures/blacksteel.bmp");
	AUX_RGBImageRec *textureSShell = auxDIBImageLoadA("Textures/steelshell.bmp");
	AUX_RGBImageRec *textureGlass  = auxDIBImageLoadA("Textures/glass.bmp");

	glEnable(GL_TEXTURE_2D);
	glGenTextures(TEXTURES_NUMBER, &textures[0]);

	glBindTexture(GL_TEXTURE_2D, textures[TEX_WALL]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureWall->sizeX, textureWall->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureWall->data);

	glBindTexture(GL_TEXTURE_2D, textures[TEX_ROOF]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureFloor->sizeX, textureFloor->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureFloor->data);

	glBindTexture(GL_TEXTURE_2D, textures[TEX_GRASS]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureGrass->sizeX, textureGrass->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureGrass->data);

	glBindTexture(GL_TEXTURE_2D, textures[TEX_WINDOW]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureWindow->sizeX, textureWindow->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureWindow->data);

	glBindTexture(GL_TEXTURE_2D, textures[TEX_RUINS]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureRuins->sizeX, textureRuins->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureRuins->data);

	glBindTexture(GL_TEXTURE_2D, textures[TEX_STEEL]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureSteel->sizeX, textureSteel->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureSteel->data);

	glBindTexture(GL_TEXTURE_2D, textures[TEX_LIGHT_STEEL]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureLSteel->sizeX, textureLSteel->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureLSteel->data);

	glBindTexture(GL_TEXTURE_2D, textures[TEX_DARK_STEEL]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureDSteel->sizeX, textureDSteel->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureDSteel->data);

	glBindTexture(GL_TEXTURE_2D, textures[TEX_BLACK_STEEL]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureBSteel->sizeX, textureBSteel->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureBSteel->data);

	glBindTexture(GL_TEXTURE_2D, textures[TEX_STEEL_SHELL]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureSShell->sizeX, textureSShell->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureSShell->data);

	glBindTexture(GL_TEXTURE_2D, textures[TEX_GLASS]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureGlass->sizeX, textureGlass->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureGlass->data);
}

void ChangeSize(int w, int h) 
{
	if(h == 0)	h = 1;
	float ratio = 1.0 * w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLightfv(GL_LIGHT0, GL_POSITION, Light.lightPos);
}

void DrawTerrain()
{
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[TEX_GRASS]);
	glBegin(GL_QUADS);
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2f(0.0,				0.0);				glVertex3f(-TERRAIN_LENGTH, BUILD_START_Y - 0.01, -TERRAIN_LENGTH);
		glTexCoord2f(GRASS_TEX_REPEAT,	0.0);				glVertex3f( TERRAIN_LENGTH, BUILD_START_Y - 0.01, -TERRAIN_LENGTH);
		glTexCoord2f(GRASS_TEX_REPEAT,	GRASS_TEX_REPEAT);	glVertex3f( TERRAIN_LENGTH, BUILD_START_Y - 0.01,  TERRAIN_LENGTH);
		glTexCoord2f(0.0,				GRASS_TEX_REPEAT);	glVertex3f(-TERRAIN_LENGTH, BUILD_START_Y - 0.01,  TERRAIN_LENGTH);
	glEnd();
}

void DrawPlain()
{
	Light.nShadow == 0 ? glColor3f(1.0, 1.0, 1.0) : glColor3f(0.0, 0.0, 0.0);

#pragma region Corpus
//	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[TEX_STEEL]);
	glBegin(GL_QUAD_STRIP);
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
		glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,   PLAIN_DIAMETER / 4);		
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,   PLAIN_DIAMETER / 4);		
		glNormal3f(0.0, 0.5, 0.5);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 4,   PLAIN_DIAMETER / 2);		
		glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 4,   PLAIN_DIAMETER / 2);		
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 4,   PLAIN_DIAMETER / 2);		
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,   PLAIN_DIAMETER / 2);		
		glNormal3f(0.0, -0.5, 0.5);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,   PLAIN_DIAMETER / 4);		
		glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,   PLAIN_DIAMETER / 4);		
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);	
		glNormal3f(0.0, -0.5, -0.5);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 4,  -PLAIN_DIAMETER / 2);		
		glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,  -PLAIN_DIAMETER / 2);		
		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 4,  -PLAIN_DIAMETER / 2);		
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 4,  -PLAIN_DIAMETER / 2);		
		glNormal3f(0.0, 0.5, -0.5);
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
	glEnd();
#pragma endregion

#pragma region Nose
//	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[TEX_LIGHT_STEEL]);
	glBegin(GL_QUAD_STRIP);
		glNormal3f(0.0, 0.5, 0.5);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);
		glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 4,		PLAIN_DIAMETER / 2);
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,		PLAIN_DIAMETER / 2);
		glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 4,		PLAIN_DIAMETER / 2);
		glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 4,		PLAIN_DIAMETER / 2);	
		glNormal3f(0.0, -0.5, 0.5);
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);	
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);
		glNormal3f(0.0, -1.0, 0.0);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);		
		glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);	
		glNormal3f(0.0, -0.5, -0.5);
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 2);	
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 2);
		glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 2);		
		glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 2);
		glNormal3f(0.0, 0.5, -0.5);
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_PEEK_X + shift,						PLAIN_START_Y,							0);
		glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 4);
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,		PLAIN_DIAMETER / 2);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 4,		PLAIN_DIAMETER / 2);
		glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 2);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 2);
	glEnd();
#pragma endregion

#pragma region Cabine
	GLfloat CABINE_GLASS_Y = PLAIN_START_Y + PLAIN_DIAMETER / 2 + GLASS_HEIGHT;	

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);

//	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[TEX_GLASS]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);	glVertex3f(CABINE_GLASS_START_X + shift,						CABINE_GLASS_Y,					PLAIN_DIAMETER / 8);
		glTexCoord2f(1.0, 0.0);	glVertex3f(CABINE_GLASS_START_X + CABINE_GLASS_WIDTH + shift,	CABINE_GLASS_Y,					PLAIN_DIAMETER / 8);
		glTexCoord2f(0.0, 1.0);	glVertex3f(CABINE_GLASS_START_X + CABINE_GLASS_WIDTH + shift,	CABINE_GLASS_Y,				   -PLAIN_DIAMETER / 8);
		glTexCoord2f(1.0, 1.0);	glVertex3f(CABINE_GLASS_START_X + shift,						CABINE_GLASS_Y,				   -PLAIN_DIAMETER / 8);	
	glEnd();

	glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);
		glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					CABINE_GLASS_Y,						   -PLAIN_DIAMETER / 8);
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	CABINE_GLASS_Y,						   -PLAIN_DIAMETER / 8);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);
		glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	CABINE_GLASS_Y,							PLAIN_DIAMETER / 8);
		glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);
		glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					CABINE_GLASS_Y,						   -PLAIN_DIAMETER / 8);
		glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
#pragma endregion 

#pragma region Wings
//	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[TEX_DARK_STEEL]);
	// Wing (Left)
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.0, 0.0);	glVertex3f(WING_START_X + shift,					PLAIN_START_Y,						-WING_LENGTH);
	glTexCoord2f(1.0, 0.0);	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						-WING_LENGTH);
	glTexCoord2f(0.0, 1.0);	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						 0);
	glTexCoord2f(1.0, 1.0);	glVertex3f(WING_START_X + WING_WIDTH * 0.5 + shift,	PLAIN_START_Y + WING_DEPTH * 0.5,	 0);
	glTexCoord2f(0.0, 0.0);	glVertex3f(WING_START_X + WING_WIDTH * 0.5 + shift,	PLAIN_START_Y - WING_DEPTH * 0.5,	 0);
	glTexCoord2f(1.0, 0.0);	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						 0);
	glTexCoord2f(0.0, 1.0);	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						-WING_LENGTH);
	glEnd();

	// Wing (Right)
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.0, 0.0);	glVertex3f(WING_START_X + shift,					PLAIN_START_Y,						 WING_LENGTH);
	glTexCoord2f(1.0, 0.0);	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						 WING_LENGTH);
	glTexCoord2f(0.0, 1.0);	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						 0);
	glTexCoord2f(1.0, 1.0);	glVertex3f(WING_START_X + WING_WIDTH * 0.5 + shift,	PLAIN_START_Y + WING_DEPTH * 0.5,	 0);
	glTexCoord2f(0.0, 0.0);	glVertex3f(WING_START_X + WING_WIDTH * 0.5 + shift,	PLAIN_START_Y - WING_DEPTH * 0.5,	 0);
	glTexCoord2f(1.0, 0.0);	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						 0);
	glTexCoord2f(0.0, 1.0);	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						 WING_LENGTH);
	glEnd();
#pragma endregion

#pragma region Tail
	// Main part
//	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[TEX_DARK_STEEL]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_START_X - TAIL_LENGTH + shift,		PLAIN_START_Y + PLAIN_DIAMETER / 4,	  0);
	glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);	
	glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,   PLAIN_DIAMETER / 4);		
	glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 4,   PLAIN_DIAMETER / 2);	
	glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 4,   PLAIN_DIAMETER / 2);		
	glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,   PLAIN_DIAMETER / 4);		
	glTexCoord2f(0.0, 1.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
	glTexCoord2f(1.0, 1.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 4,  -PLAIN_DIAMETER / 2);		
	glTexCoord2f(0.0, 0.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 4,  -PLAIN_DIAMETER / 2);	
	glTexCoord2f(1.0, 0.0);	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
	glEnd();

	// Keel
	glBindTexture(GL_TEXTURE_2D, textures[TEX_BLACK_STEEL]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.0, 0.0);	glVertex3f(KEEL_START_X + shift,						KEEL_START_Y,	 0);
	glTexCoord2f(1.0, 0.0);	glVertex3f(KEEL_START_X - KEEL_SIZE_X * 0.5 + shift,	KEEL_START_Y,	 0);
	glTexCoord2f(0.0, 1.0);	glVertex3f(KEEL_START_X - KEEL_SIZE_X * 0.5 + shift,	KEEL_LINE,		 0);
	glTexCoord2f(1.0, 1.0);	glVertex3f(KEEL_START_X + KEEL_SIZE_X * 0.5 + shift,	KEEL_LINE,		-KEEL_SIZE_Z / 2);
	glTexCoord2f(0.0, 0.0);	glVertex3f(KEEL_START_X + KEEL_SIZE_X * 0.5 + shift,	KEEL_LINE,		 KEEL_SIZE_Z / 2);
	glTexCoord2f(1.0, 0.0);	glVertex3f(KEEL_START_X - KEEL_SIZE_X * 0.5 + shift,	KEEL_LINE,		 0);
	glTexCoord2f(0.0, 1.0);	glVertex3f(KEEL_START_X - KEEL_SIZE_X * 0.5 + shift,	KEEL_START_Y,	 0);
	glEnd();

	// Stabilizator (Left)
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.0, 0.0);	glVertex3f(KEEL_START_X + shift,								KEEL_LINE,								-STABILIZATOR_SIZE_Z);
	glTexCoord2f(1.0, 0.0);	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE,								-STABILIZATOR_SIZE_Z);
	glTexCoord2f(0.0, 1.0);	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X + shift,			KEEL_LINE,								 0);
	glTexCoord2f(1.0, 1.0);	glVertex3f(KEEL_START_X + STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE + STABILIZATOR_SIZE_Y * 0.5,	 0);
	glTexCoord2f(0.0, 0.0);	glVertex3f(KEEL_START_X + STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE - STABILIZATOR_SIZE_Y * 0.5,	 0);
	glTexCoord2f(1.0, 0.0);	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X + shift,			KEEL_LINE,								 0);
	glTexCoord2f(0.0, 1.0);	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE,								-STABILIZATOR_SIZE_Z);
	glEnd();
	// Stabilizator (Right)
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.0, 0.0);	glVertex3f(KEEL_START_X + shift,								KEEL_LINE,								 STABILIZATOR_SIZE_Z);
	glTexCoord2f(1.0, 0.0);	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE,								 STABILIZATOR_SIZE_Z);
	glTexCoord2f(0.0, 1.0);	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X + shift,			KEEL_LINE,								 0);
	glTexCoord2f(1.0, 1.0);	glVertex3f(KEEL_START_X + STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE + STABILIZATOR_SIZE_Y * 0.5,	 0);
	glTexCoord2f(0.0, 0.0);	glVertex3f(KEEL_START_X + STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE - STABILIZATOR_SIZE_Y * 0.5,	 0);
	glTexCoord2f(1.0, 0.0);	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X + shift,			KEEL_LINE,								 0);
	glTexCoord2f(0.0, 1.0);	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE,								 STABILIZATOR_SIZE_Z);
	glEnd();
#pragma endregion 

}

void DrawBuilding()
{
	Light.nShadow == 0 ? glColor3f(1.0, 1.0, 1.0) : glColor3f(0.0, 0.0, 0.0);
#pragma region Walls
	glBindTexture(GL_TEXTURE_2D, textures[TEX_WALL]);
	glBegin(GL_QUAD_STRIP);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(BUILD_LEFT_XCOORD,	BUILD_START_Y,					BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glTexCoord2f(1.0, 0.0);	glVertex3f(BUILD_LEFT_XCOORD,	BUILD_HIGH_YCOORD - crashShift,	BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glTexCoord2f(0.0, 1.0);	glVertex3f(BUILD_LEFT_XCOORD,	BUILD_START_Y,					BUILD_START_Z + BUILD_Z_LENGTH / 2);
	glTexCoord2f(1.0, 1.0);	glVertex3f(BUILD_LEFT_XCOORD,	BUILD_HIGH_YCOORD - crashShift,	BUILD_START_Z + BUILD_Z_LENGTH / 2);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 0.0);	glVertex3f(BUILD_RIGHT_XCOORD,	BUILD_START_Y,					BUILD_START_Z + BUILD_Z_LENGTH / 2);
	glTexCoord2f(1.0, 0.0);	glVertex3f(BUILD_RIGHT_XCOORD,	BUILD_HIGH_YCOORD - crashShift,	BUILD_START_Z + BUILD_Z_LENGTH / 2);
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);	glVertex3f(BUILD_RIGHT_XCOORD,	BUILD_START_Y,					BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glTexCoord2f(1.0, 1.0);	glVertex3f(BUILD_RIGHT_XCOORD,	BUILD_HIGH_YCOORD - crashShift,	BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0.0, 0.0);	glVertex3f(BUILD_LEFT_XCOORD,	BUILD_START_Y,					BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glTexCoord2f(1.0, 0.0);	glVertex3f(BUILD_LEFT_XCOORD,	BUILD_HIGH_YCOORD - crashShift,	BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glEnd();
#pragma endregion

#pragma region Roof
	glBindTexture(GL_TEXTURE_2D, textures[TEX_ROOF]);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 0.0);	glVertex3f(BUILD_START_X - BUILD_X_LENGTH / 2,	BUILD_START_Y +  BUILD_Y_LENGTH - crashShift, BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glTexCoord2f(0.0, 1.0);	glVertex3f(BUILD_START_X - BUILD_X_LENGTH / 2,	BUILD_START_Y +  BUILD_Y_LENGTH - crashShift, BUILD_START_Z + BUILD_Z_LENGTH / 2);
	glTexCoord2f(1.0, 1.0);	glVertex3f(BUILD_START_X + BUILD_X_LENGTH / 2,	BUILD_START_Y +  BUILD_Y_LENGTH - crashShift, BUILD_START_Z + BUILD_Z_LENGTH / 2);
	glTexCoord2f(1.0, 0.0);	glVertex3f(BUILD_START_X + BUILD_X_LENGTH / 2,	BUILD_START_Y +  BUILD_Y_LENGTH - crashShift, BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glEnd();
#pragma endregion

#pragma region Windows
	glBindTexture(GL_TEXTURE_2D, textures[TEX_WINDOW]);
	for(GLfloat X = BUILD_START_X - BUILD_X_LENGTH / 2 - WINDOW_LIP; Xsides < 2; X += BUILD_X_LENGTH + WINDOW_LIP * 2)
	{
		for(GLfloat Y = BUILD_START_Y + WINDOW_GAP + crashShift; Y < BUILD_START_Y + BUILD_Y_LENGTH - WINDOW_GAP * 5; Y += BUILD_CELL_SIZE)
			for(GLfloat Z = BUILD_START_Z - BUILD_Z_LENGTH / 2 + WINDOW_GAP; Z < BUILD_START_Z + BUILD_Z_LENGTH / 2 - WINDOW_SIZE; Z += BUILD_CELL_SIZE)
			{
				Xsides == 0 ? glNormal3f(-1.0, 0.0, 0.0) : glNormal3f(1.0, 0.0, 0.0);
				glBegin(GL_QUAD_STRIP);
					glTexCoord2f(0, 0);	glVertex3f(X, Y - crashShift,				Z);
					glTexCoord2f(1, 0);	glVertex3f(X, Y + WINDOW_SIZE - crashShift,	Z);
					glTexCoord2f(0, 1);	glVertex3f(X, Y - crashShift,				Z + WINDOW_SIZE);
					glTexCoord2f(1, 1);	glVertex3f(X, Y + WINDOW_SIZE - crashShift,	Z + WINDOW_SIZE);
										glVertex3f(X, Y - crashShift,				Z + WINDOW_SIZE);
										glVertex3f(X, Y + WINDOW_SIZE - crashShift,	Z + WINDOW_SIZE);
										glVertex3f(X, Y - crashShift,				Z);
										glVertex3f(X, Y + WINDOW_SIZE - crashShift,	Z);
										glVertex3f(X, Y - crashShift,				Z);
										glVertex3f(X, Y + WINDOW_SIZE - crashShift,	Z);
				glEnd();
			}
			Xsides++;
	}

	for(GLfloat Z = BUILD_START_Z - BUILD_Z_LENGTH / 2 - WINDOW_LIP; Zsides < 2; Z += BUILD_Z_LENGTH + WINDOW_LIP * 2)
	{
		for(GLfloat Y = BUILD_START_Y + WINDOW_GAP + crashShift; Y < BUILD_START_Y + BUILD_Y_LENGTH - WINDOW_GAP * 5; Y += BUILD_CELL_SIZE)
			for(GLfloat X = BUILD_START_X - BUILD_X_LENGTH / 2 + WINDOW_GAP; X < BUILD_START_X + BUILD_X_LENGTH / 2 - WINDOW_SIZE; X += BUILD_CELL_SIZE)
			{
				Zsides == 0 ? glNormal3f(0.0, 0.0, -1.0) : glNormal3f(0.0, 0.0, 1.0);
				glBegin(GL_QUAD_STRIP);
					glTexCoord2f(0, 0);	glVertex3f(X,					Y - crashShift,					Z);
					glTexCoord2f(1, 0); glVertex3f(X,					Y + WINDOW_SIZE - crashShift,	Z);
					glTexCoord2f(0, 1);	glVertex3f(X + WINDOW_SIZE,		Y - crashShift,					Z);
					glTexCoord2f(1, 1);	glVertex3f(X + WINDOW_SIZE,		Y + WINDOW_SIZE - crashShift,	Z);
										glVertex3f(X + WINDOW_SIZE,		Y - crashShift,					Z);
										glVertex3f(X + WINDOW_SIZE,		Y + WINDOW_SIZE - crashShift,	Z);
										glVertex3f(X,					Y - crashShift,					Z);
										glVertex3f(X,					Y + WINDOW_SIZE - crashShift,	Z);
										glVertex3f(X,					Y - crashShift,					Z);
										glVertex3f(X,					Y + WINDOW_SIZE - crashShift,	Z);
				glEnd();
			}
			Zsides++;
	}

	Xsides = 0;
	Zsides = 0;
#pragma endregion

}

void DrawDestroyedBuild()
{
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[TEX_RUINS]);
	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.0, 0.0); glVertex3f(BUILD_START_X,							BUILD_START_Y + WINDOW_SIZE, BUILD_START_Z);
		glTexCoord2f(1.0, 0.0); glVertex3f(BUILD_START_X - BUILD_X_LENGTH / 1.5,	BUILD_START_Y,				-BUILD_Z_LENGTH / 1.5);
		glTexCoord2f(0.0, 1.0); glVertex3f(BUILD_START_X + BUILD_X_LENGTH / 2,		BUILD_START_Y,				-BUILD_Z_LENGTH / 2);
		glTexCoord2f(1.0, 1.0); glVertex3f(BUILD_START_X + BUILD_X_LENGTH / 2,		BUILD_START_Y,				 BUILD_Z_LENGTH / 2.5);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.0, 0.0); glVertex3f(BUILD_START_X,							BUILD_START_Y + WINDOW_SIZE, BUILD_START_Z);
		glTexCoord2f(1.0, 0.0); glVertex3f(BUILD_START_X + BUILD_X_LENGTH / 2,		BUILD_START_Y,				 BUILD_Z_LENGTH / 2.5);
		glTexCoord2f(0.0, 1.0); glVertex3f(BUILD_START_X - BUILD_X_LENGTH / 2,		BUILD_START_Y,				 BUILD_Z_LENGTH / 2);
		glTexCoord2f(1.0, 1.0); glVertex3f(BUILD_START_X - BUILD_X_LENGTH / 1.5,	BUILD_START_Y,				-BUILD_Z_LENGTH / 1.5);
	glEnd();
}

void BombState()
{
	bombXCoord = bombStartX + BOMB_CORPUS_LENGTH / 2 + shift;
	bombYCoord = PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY;	

	if (bombXCoord > BUILD_LEFT_XCOORD	&& 
		bombXCoord < BUILD_RIGHT_XCOORD	&&
		bombYCoord < BUILD_HIGH_YCOORD  ||
		bombYCoord < BUILD_START_Z)
	{
		bombYCoord > BUILD_START_Z ? buildExplosion = true : terraExplosion = true;
		bombExplose = true;
		Explosion.GetExpInfo(bombXCoord, bombYCoord, buildExplosion == true ? BUILD : TERRA);
		if (buildExplosion)
		{
			Dust.GetDustInfo(BUILD_START_X, BUILD_START_Y);
			RuinsDust.GetDustInfo(BUILD_START_X, BUILD_START_Y);
		}
		bombRunning = false;
	}
}

void Bomb()
{
	glColor3f(1.0, 1.0, 1.0);
#pragma region Corpus
	glBindTexture(GL_TEXTURE_2D, textures[TEX_STEEL_SHELL]);
	glBegin(GL_QUAD_STRIP);
	glTexCoord2f(0.0, 0.0);	glVertex3f(bombStartX + shift,						PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);		
	glTexCoord2f(1.0, 0.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);		
	glTexCoord2f(0.0, 1.0);	glVertex3f(bombStartX + shift,						PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,   BOMB_DIAMETER / 4);		
	glTexCoord2f(1.0, 1.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,   BOMB_DIAMETER / 4);		
	glTexCoord2f(0.0, 0.0);	glVertex3f(bombStartX + shift,						PLAIN_START_Y - BOMB_DIAMETER / 4 - bombShiftY,   BOMB_DIAMETER / 2);		
	glTexCoord2f(1.0, 0.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 4 - bombShiftY,   BOMB_DIAMETER / 2);		
	glTexCoord2f(0.0, 1.0);	glVertex3f(bombStartX + shift,						PLAIN_START_Y + BOMB_DIAMETER / 4 - bombShiftY,   BOMB_DIAMETER / 2);		
	glTexCoord2f(1.0, 1.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 4 - bombShiftY,   BOMB_DIAMETER / 2);		
	glTexCoord2f(0.0, 0.0);	glVertex3f(bombStartX + shift,						PLAIN_START_Y + BOMB_DIAMETER / 2 - bombShiftY,   BOMB_DIAMETER / 4);		
	glTexCoord2f(1.0, 0.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 2 - bombShiftY,   BOMB_DIAMETER / 4);		
	glTexCoord2f(0.0, 1.0);	glVertex3f(bombStartX + shift,						PLAIN_START_Y + BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);		
	glTexCoord2f(1.0, 1.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);		
	glTexCoord2f(0.0, 0.0);	glVertex3f(bombStartX + shift,						PLAIN_START_Y + BOMB_DIAMETER / 4 - bombShiftY,  -BOMB_DIAMETER / 2);		
	glTexCoord2f(1.0, 0.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 4 - bombShiftY,  -BOMB_DIAMETER / 2);		
	glTexCoord2f(0.0, 1.0);	glVertex3f(bombStartX + shift,						PLAIN_START_Y - BOMB_DIAMETER / 4 - bombShiftY,  -BOMB_DIAMETER / 2);		
	glTexCoord2f(1.0, 1.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 4 - bombShiftY,  -BOMB_DIAMETER / 2);		
	glTexCoord2f(0.0, 0.0);	glVertex3f(bombStartX + shift,						PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);		
	glTexCoord2f(1.0, 0.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);	
	glEnd();
#pragma endregion

#pragma region Nose
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.0, 0.0);	glVertex3f(bombStartX + BOMB_LENGTH + shift,	PLAIN_START_Y - bombShiftY,  0);
	glTexCoord2f(1.0, 0.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);		
	glTexCoord2f(0.0, 1.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,   BOMB_DIAMETER / 4);			
	glTexCoord2f(1.0, 1.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 4 - bombShiftY,   BOMB_DIAMETER / 2);			
	glTexCoord2f(0.0, 0.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 4 - bombShiftY,   BOMB_DIAMETER / 2);			
	glTexCoord2f(1.0, 0.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 2 - bombShiftY,   BOMB_DIAMETER / 4);			
	glTexCoord2f(0.0, 1.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);			
	glTexCoord2f(1.0, 1.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 4 - bombShiftY,  -BOMB_DIAMETER / 2);			
	glTexCoord2f(0.0, 0.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 4 - bombShiftY,  -BOMB_DIAMETER / 2);			
	glTexCoord2f(1.0, 0.0);	glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);	
	glEnd();
#pragma endregion

	BombState();
	bombShiftY += BOMB_FALLING_SPEED;
}

void Destroy()
{
	Explosion.Run();
	if (buildExplosion)
	{
		crashShift += BUILD_Y_LENGTH * CRASH_SPEED;
		Explosion.YCoord -= CRASH_SPEED * 2;
		Dust.Run();
		if (crashShift > BUILD_Y_LENGTH)
		{
			bombExplose = false;
			Explosion.~Particles();
			Dust.~Particles();
			buildDestroyed = true;
		}
	}
}

void Camera()
{
	switch(cameraState)
	{
	case 0:	gluLookAt(-20.0,  20.0, 0.0,		
					   0.0,  0.0,   0.0,
					   0.0,  1.0,   0.0);
			break;
	case 1:	gluLookAt(0.0,  20.0, 20.0,		
					  0.0,  0.0,  0.0,
					  0.0,  1.0,  0.0);
			break;
	case 2:	gluLookAt(0.0,  20.0, -20.0,		
					  0.0,  0.0,  0.0,
					  0.0,  1.0,  0.0);
			break;
	case 3:	gluLookAt(10.0,  30.0, 5.0,		
					  0.0,   0.0,  0.0,
					  0.0,   1.0,  0.0);
			break;
	case 4: gluLookAt(-50.0, 30.0, 0.0,
					   0.0,  0.0,  0.0,
					   0.0,  1.0,  0.0);
			break;
	default: break;
	}
}

void RenderScene(void) 
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Camera();
	DrawTerrain();
	
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, Light.lightPos);
	Light.nShadow = 0;
	DrawPlain();
	if (!buildDestroyed) 
		DrawBuilding();
	glPopMatrix();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glMultMatrixf((GLfloat *)Light.shadowMat);
	shift += PLAIN_SPEED;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	Light.nShadow = 1;
	DrawPlain();
	if (!buildDestroyed) 
		DrawBuilding();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(Light.lightPos[0], Light.lightPos[1], Light.lightPos[2]);
	glColor3f(1.0, 1.0, 0);
	glutSolidSphere(5.0, 10.0, 10.0);
	glPopMatrix();


	if (buildDestroyed)
	{
		DrawDestroyedBuild();
		RuinsDust.Run();
	}
	if (bombRunning)	Bomb();
	if (bombExplose)	Destroy();

    glutSwapBuffers();
}

void Keys(unsigned char key, int x, int y) 
{ 
	if (key == 13)		// Enter
		bombRunning = true;
	if (key == 27)		// Esc
		exit(0);
	if (key == 32)		// Space
	{
		cameraState++;
		if (cameraState == CAMERA_STATES)
			cameraState = 0;
	}	
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Bomber");
	glutFullScreen();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(RenderScene);
	glutKeyboardFunc(Keys);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	LoadTextures();
	Light.Init(BUILD_START_Y);

	glutMainLoop();
	return 0;
}
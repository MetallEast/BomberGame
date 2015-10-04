#include <iostream>
#include "Common\glut.h"
#include "Common\GLAux.h"
#include "defines.h"
#include "Particles.h"

#pragma comment(lib, "GLAux.lib")


Particles Explosion(0);
Particles Dust(DUST);


void LoadTextures()
{
	AUX_RGBImageRec *textureWall   = auxDIBImageLoadA("Textures/wall.bmp");
	AUX_RGBImageRec *textureFloor  = auxDIBImageLoadA("Textures/floor.bmp");
	AUX_RGBImageRec *textureGrass  = auxDIBImageLoadA("Textures/grass.bmp");
	AUX_RGBImageRec *textureWindow = auxDIBImageLoadA("Textures/window.bmp");
	AUX_RGBImageRec *textureRuins  = auxDIBImageLoadA("Textures/ruins.bmp");

	glGenTextures(TEXTURES_NUMBER, &textures[0]);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureWall->sizeX, textureWall->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureWall->data);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureFloor->sizeX, textureFloor->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureFloor->data);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureGrass->sizeX, textureGrass->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureGrass->data);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureWindow->sizeX, textureWindow->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureWindow->data);

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, textureRuins->sizeX, textureRuins->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureRuins->data);
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
}

void DrawTerrain()
{
	glColor3f(0.0, 0.4, 0.0);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,				0.0);				glVertex3f(-TERRAIN_LENGTH, BUILD_START_Y, -TERRAIN_LENGTH);
		glTexCoord2f(GRASS_TEX_REPEAT,	0.0);				glVertex3f( TERRAIN_LENGTH, BUILD_START_Y, -TERRAIN_LENGTH);
		glTexCoord2f(GRASS_TEX_REPEAT,	GRASS_TEX_REPEAT);	glVertex3f( TERRAIN_LENGTH, BUILD_START_Y,  TERRAIN_LENGTH);
		glTexCoord2f(0.0,				GRASS_TEX_REPEAT);	glVertex3f(-TERRAIN_LENGTH, BUILD_START_Y,  TERRAIN_LENGTH);
	glEnd();
}

void DrawPlain()
{
#pragma region Corpus
	glColor3f(0.25, 0.75, 1.0);
	glBegin(GL_QUAD_STRIP);
		glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
		glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
		glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,   PLAIN_DIAMETER / 4);		
		glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,   PLAIN_DIAMETER / 4);		

		glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 4,   PLAIN_DIAMETER / 2);		
		glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 4,   PLAIN_DIAMETER / 2);		

		glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 4,   PLAIN_DIAMETER / 2);		
		glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,   PLAIN_DIAMETER / 2);		

		glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,   PLAIN_DIAMETER / 4);		
		glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,   PLAIN_DIAMETER / 4);		

		glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
		glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		

		glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 4,  -PLAIN_DIAMETER / 2);		
		glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,  -PLAIN_DIAMETER / 2);		

		glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 4,  -PLAIN_DIAMETER / 2);		
		glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 4,  -PLAIN_DIAMETER / 2);		

		glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
		glVertex3f(PLAIN_START_X + CORPUS_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
	glEnd();
#pragma endregion

#pragma region Nose
	glColor3f(0.3, 0.3, 0.35);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);

	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 4,		PLAIN_DIAMETER / 2);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,		PLAIN_DIAMETER / 2);

	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 4,		PLAIN_DIAMETER / 2);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 4,		PLAIN_DIAMETER / 2);	

	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);	
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);

	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);		
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);	

	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 2);	
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 2);

	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 2);		
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 2);

	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(PLAIN_PEEK_X + shift,						PLAIN_START_Y,							0);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 4);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,		PLAIN_DIAMETER / 2);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 4,		PLAIN_DIAMETER / 2);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y - PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 2);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 4,	   -PLAIN_DIAMETER / 2);
	glEnd();
#pragma endregion

#pragma region Cabine
	GLfloat CABINE_GLASS_Y = PLAIN_START_Y + PLAIN_DIAMETER / 2 + GLASS_HEIGHT;	
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex3f(CABINE_GLASS_START_X + shift,						CABINE_GLASS_Y,					PLAIN_DIAMETER / 8);
	glVertex3f(CABINE_GLASS_START_X + CABINE_GLASS_WIDTH + shift,	CABINE_GLASS_Y,					PLAIN_DIAMETER / 8);
	glVertex3f(CABINE_GLASS_START_X + CABINE_GLASS_WIDTH + shift,	CABINE_GLASS_Y,				   -PLAIN_DIAMETER / 8);
	glVertex3f(CABINE_GLASS_START_X + shift,						CABINE_GLASS_Y,				   -PLAIN_DIAMETER / 8);	
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);
	glVertex3f(PLAIN_NOSE_START_X + shift,					CABINE_GLASS_Y,						   -PLAIN_DIAMETER / 8);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	CABINE_GLASS_Y,						   -PLAIN_DIAMETER / 8);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	PLAIN_START_Y + PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);
	glVertex3f(PLAIN_NOSE_START_X + CABINE_LENGTH + shift,	CABINE_GLASS_Y,							PLAIN_DIAMETER / 8);
	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,		PLAIN_DIAMETER / 4);
	glVertex3f(PLAIN_NOSE_START_X + shift,					CABINE_GLASS_Y,						   -PLAIN_DIAMETER / 8);
	glVertex3f(PLAIN_NOSE_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,	   -PLAIN_DIAMETER / 4);
	glEnd();
#pragma endregion 

#pragma region Wings
	glColor3f(0.5, 0.5, 0.5);
	// Wing (Left)
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(WING_START_X + shift,					PLAIN_START_Y,						-WING_LENGTH);
	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						-WING_LENGTH);
	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						 0);
	glVertex3f(WING_START_X + WING_WIDTH * 0.5 + shift,	PLAIN_START_Y + WING_DEPTH * 0.5,	 0);
	glVertex3f(WING_START_X + WING_WIDTH * 0.5 + shift,	PLAIN_START_Y - WING_DEPTH * 0.5,	 0);
	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						 0);
	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						-WING_LENGTH);
	glEnd();

	// Wing (Right)
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(WING_START_X + shift,					PLAIN_START_Y,						 WING_LENGTH);
	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						 WING_LENGTH);
	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						 0);
	glVertex3f(WING_START_X + WING_WIDTH * 0.5 + shift,	PLAIN_START_Y + WING_DEPTH * 0.5,	 0);
	glVertex3f(WING_START_X + WING_WIDTH * 0.5 + shift,	PLAIN_START_Y - WING_DEPTH * 0.5,	 0);
	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						 0);
	glVertex3f(WING_START_X - WING_WIDTH * 0.5 + shift, PLAIN_START_Y,						 WING_LENGTH);
	glEnd();
#pragma endregion

#pragma region Tail
	// Main part
	glColor3f(1, 0.5, 0.5);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(PLAIN_START_X - TAIL_LENGTH + shift,		PLAIN_START_Y + PLAIN_DIAMETER / 4,	  0);
	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);	
	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,   PLAIN_DIAMETER / 4);		
	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 4,   PLAIN_DIAMETER / 2);	
	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 4,   PLAIN_DIAMETER / 2);		
	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,   PLAIN_DIAMETER / 4);		
	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y + PLAIN_DIAMETER / 4,  -PLAIN_DIAMETER / 2);		
	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 4,  -PLAIN_DIAMETER / 2);	
	glVertex3f(PLAIN_START_X + shift,					PLAIN_START_Y - PLAIN_DIAMETER / 2,  -PLAIN_DIAMETER / 4);		
	glEnd();

	// Keel
	glColor3f(1, 0.8, 0.75);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(KEEL_START_X + shift,						KEEL_START_Y,	 0);
	glVertex3f(KEEL_START_X - KEEL_SIZE_X * 0.5 + shift,	KEEL_START_Y,	 0);
	glVertex3f(KEEL_START_X - KEEL_SIZE_X * 0.5 + shift,	KEEL_LINE,		 0);
	glVertex3f(KEEL_START_X + KEEL_SIZE_X * 0.5 + shift,	KEEL_LINE,		-KEEL_SIZE_Z / 2);
	glVertex3f(KEEL_START_X + KEEL_SIZE_X * 0.5 + shift,	KEEL_LINE,		 KEEL_SIZE_Z / 2);
	glVertex3f(KEEL_START_X - KEEL_SIZE_X * 0.5 + shift,	KEEL_LINE,		 0);
	glVertex3f(KEEL_START_X - KEEL_SIZE_X * 0.5 + shift,	KEEL_START_Y,	 0);
	glEnd();

	// Stabilizator (Left)
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(KEEL_START_X + shift,								KEEL_LINE,								-STABILIZATOR_SIZE_Z);
	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE,								-STABILIZATOR_SIZE_Z);
	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X + shift,			KEEL_LINE,								 0);
	glVertex3f(KEEL_START_X + STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE + STABILIZATOR_SIZE_Y * 0.5,	 0);
	glVertex3f(KEEL_START_X + STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE - STABILIZATOR_SIZE_Y * 0.5,	 0);
	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X + shift,			KEEL_LINE,								 0);
	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE,								-STABILIZATOR_SIZE_Z);
	glEnd();
	// Stabilizator (Right)
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(KEEL_START_X + shift,								KEEL_LINE,								 STABILIZATOR_SIZE_Z);
	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE,								 STABILIZATOR_SIZE_Z);
	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X + shift,			KEEL_LINE,								 0);
	glVertex3f(KEEL_START_X + STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE + STABILIZATOR_SIZE_Y * 0.5,	 0);
	glVertex3f(KEEL_START_X + STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE - STABILIZATOR_SIZE_Y * 0.5,	 0);
	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X + shift,			KEEL_LINE,								 0);
	glVertex3f(KEEL_START_X - STABILIZATOR_SIZE_X * 0.5 + shift,	KEEL_LINE,								 STABILIZATOR_SIZE_Z);
	glEnd();
#pragma endregion 

	shift += PLAIN_SPEED;
}

void DrawBuilding()
{

#pragma region Walls
	glColor3f(0.65, 0.65, 1);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUAD_STRIP);
	glTexCoord2f(0.0, 0.0); glVertex3f(BUILD_LEFT_XCOORD,	BUILD_START_Y - crashShift,		BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glTexCoord2f(2.0, 0.0);	glVertex3f(BUILD_LEFT_XCOORD,	BUILD_HIGH_YCOORD - crashShift,	BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glTexCoord2f(0.0, 2.0);	glVertex3f(BUILD_LEFT_XCOORD,	BUILD_START_Y - crashShift,		BUILD_START_Z + BUILD_Z_LENGTH / 2);
	glTexCoord2f(2.0, 2.0);	glVertex3f(BUILD_LEFT_XCOORD,	BUILD_HIGH_YCOORD - crashShift,	BUILD_START_Z + BUILD_Z_LENGTH / 2);
	glTexCoord2f(0.0, 0.0);	glVertex3f(BUILD_RIGHT_XCOORD,	BUILD_START_Y - crashShift,		BUILD_START_Z + BUILD_Z_LENGTH / 2);
	glTexCoord2f(2.0, 0.0);	glVertex3f(BUILD_RIGHT_XCOORD,	BUILD_HIGH_YCOORD - crashShift,	BUILD_START_Z + BUILD_Z_LENGTH / 2);
	glTexCoord2f(0.0, 2.0);	glVertex3f(BUILD_RIGHT_XCOORD,	BUILD_START_Y - crashShift,		BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glTexCoord2f(2.0, 2.0);	glVertex3f(BUILD_RIGHT_XCOORD,	BUILD_HIGH_YCOORD - crashShift,	BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glTexCoord2f(0.0, 0.0);	glVertex3f(BUILD_LEFT_XCOORD,	BUILD_START_Y - crashShift,		BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glTexCoord2f(2.0, 0.0);	glVertex3f(BUILD_LEFT_XCOORD,	BUILD_HIGH_YCOORD - crashShift,	BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glEnd();
#pragma endregion
	
#pragma region Roof
	glColor3f(0.55, 0.65, 0.75);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);	glVertex3f(BUILD_START_X - BUILD_X_LENGTH / 2,	BUILD_START_Y +  BUILD_Y_LENGTH - crashShift, BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glTexCoord2f(0.0, 1.0);	glVertex3f(BUILD_START_X - BUILD_X_LENGTH / 2,	BUILD_START_Y +  BUILD_Y_LENGTH - crashShift, BUILD_START_Z + BUILD_Z_LENGTH / 2);
	glTexCoord2f(1.0, 1.0);	glVertex3f(BUILD_START_X + BUILD_X_LENGTH / 2,	BUILD_START_Y +  BUILD_Y_LENGTH - crashShift, BUILD_START_Z + BUILD_Z_LENGTH / 2);
	glTexCoord2f(1.0, 0.0);	glVertex3f(BUILD_START_X + BUILD_X_LENGTH / 2,	BUILD_START_Y +  BUILD_Y_LENGTH - crashShift, BUILD_START_Z - BUILD_Z_LENGTH / 2);
	glEnd();
#pragma endregion
	
#pragma region Windows
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	for(GLfloat X = BUILD_START_X - BUILD_X_LENGTH / 2 - WINDOW_LIP; Xsides < 2; X += BUILD_X_LENGTH + WINDOW_LIP * 2)
	{
		for(GLfloat Y = BUILD_START_Y + WINDOW_GAP; Y < BUILD_START_Y + BUILD_Y_LENGTH - WINDOW_GAP; Y += BUILD_CELL_SIZE)
			for(GLfloat Z = BUILD_START_Z - BUILD_Z_LENGTH / 2 + WINDOW_GAP; Z < BUILD_START_Z + BUILD_Z_LENGTH / 2 - WINDOW_SIZE; Z += BUILD_CELL_SIZE)
			{
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
		for(GLfloat Y = BUILD_START_Y + WINDOW_GAP; Y < BUILD_START_Y + BUILD_Y_LENGTH - WINDOW_GAP; Y += BUILD_CELL_SIZE)
			for(GLfloat X = BUILD_START_X - BUILD_X_LENGTH / 2 + WINDOW_GAP; X < BUILD_START_X + BUILD_X_LENGTH / 2 - WINDOW_SIZE; X += BUILD_CELL_SIZE)
			{
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
	glBindTexture(GL_TEXTURE_2D, textures[4]);
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
			Dust.GetDustInfo(BUILD_START_X, BUILD_START_Y);
		bombRunning = false;
	}
}

void Bomb()
{
#pragma region Corpus
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUAD_STRIP);
		glVertex3f(bombStartX + shift,						PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);		
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);		
		glVertex3f(bombStartX + shift,						PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,   BOMB_DIAMETER / 4);		
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,   BOMB_DIAMETER / 4);		
		glVertex3f(bombStartX + shift,						PLAIN_START_Y - BOMB_DIAMETER / 4 - bombShiftY,   BOMB_DIAMETER / 2);		
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 4 - bombShiftY,   BOMB_DIAMETER / 2);		
		glVertex3f(bombStartX + shift,						PLAIN_START_Y + BOMB_DIAMETER / 4 - bombShiftY,   BOMB_DIAMETER / 2);		
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 4 - bombShiftY,   BOMB_DIAMETER / 2);		
		glVertex3f(bombStartX + shift,						PLAIN_START_Y + BOMB_DIAMETER / 2 - bombShiftY,   BOMB_DIAMETER / 4);		
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 2 - bombShiftY,   BOMB_DIAMETER / 4);		
		glVertex3f(bombStartX + shift,						PLAIN_START_Y + BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);		
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);		
		glVertex3f(bombStartX + shift,						PLAIN_START_Y + BOMB_DIAMETER / 4 - bombShiftY,  -BOMB_DIAMETER / 2);		
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 4 - bombShiftY,  -BOMB_DIAMETER / 2);		
		glVertex3f(bombStartX + shift,						PLAIN_START_Y - BOMB_DIAMETER / 4 - bombShiftY,  -BOMB_DIAMETER / 2);		
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 4 - bombShiftY,  -BOMB_DIAMETER / 2);		
		glVertex3f(bombStartX + shift,						PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);		
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);	
	glEnd();
#pragma endregion

#pragma region Nose
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(bombStartX + BOMB_LENGTH + shift,	PLAIN_START_Y - bombShiftY,  0);
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);		
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,   BOMB_DIAMETER / 4);			
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 4 - bombShiftY,   BOMB_DIAMETER / 2);			
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 4 - bombShiftY,   BOMB_DIAMETER / 2);			
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 2 - bombShiftY,   BOMB_DIAMETER / 4);			
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);			
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y + BOMB_DIAMETER / 4 - bombShiftY,  -BOMB_DIAMETER / 2);			
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 4 - bombShiftY,  -BOMB_DIAMETER / 2);			
		glVertex3f(bombStartX + BOMB_CORPUS_LENGTH + shift,	PLAIN_START_Y - BOMB_DIAMETER / 2 - bombShiftY,  -BOMB_DIAMETER / 4);	
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
	}
	if (crashShift > BUILD_Y_LENGTH)
	{
		bombExplose = false;
		Explosion.~Particles();
		Dust.~Particles();
		buildDestroyed = true;
	}
}

void Camera()
{
	switch(cameraState)
	{
	case 0:	gluLookAt(20.0, 20.0, 0.0,		
					  0.0,  0.0,  0.0,
					  0.0,  1.0,  0.0);
			break;
	case 1:	gluLookAt(-20.0,  20.0, 0.0,		
					   0.0,  0.0,   0.0,
					   0.0,  1.0,   0.0);
			break;
	case 2:	gluLookAt(0.0,  20.0, 20.0,		
					  0.0,  0.0,  0.0,
					  0.0,  1.0,  0.0);
			break;
	case 3:	gluLookAt(0.0,  20.0, -20.0,		
					  0.0,  0.0,  0.0,
					  0.0,  1.0,  0.0);
			break;
	case 4:	gluLookAt(10.0,  30.0, 5.0,		
					  0.0,   0.0,  0.0,
					  0.0,   1.0,  0.0);
			break;
	case 5:	gluLookAt(50.0,  30.0, 0.0,		
					  0.0,   0.0,  0.0,
					  0.0,   1.0,  0.0);
			break;
	case 6:	gluLookAt(PLAIN_START_X - 5.0,  PLAIN_START_Y + 3.0, 0.0,		
					  0.0,					0.0,				 0.0,
					  0.0,					1.0,				 0.0);
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
	DrawPlain();
	buildDestroyed ? DrawDestroyedBuild() : DrawBuilding();

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Bomber");
	glutFullScreen();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	LoadTextures();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(RenderScene);
	glutKeyboardFunc(Keys);

	glutMainLoop();
	return 0;
}
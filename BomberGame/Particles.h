#include "Common\glut.h"
#include "Common\GLAux.h"

#define PARTICLE_NUMBER		2000

#pragma once

struct Particle
{
	GLfloat life;                    
	GLfloat fade;                    
	GLfloat x, y, z;                    
	GLfloat r, g, b;              
	GLfloat dirX, dirY, dirZ; 
};

class Particles
{
	GLushort type;
	GLuint loop;
	Particle particles[PARTICLE_NUMBER];

	void Initialize();
public:
	void Explosion(GLfloat radius, GLfloat size, GLfloat Xdirection, GLfloat Ydirection, GLfloat Zdirection, GLfloat expXCoord, GLfloat expYCoord);
	Particles(GLushort);
	~Particles(void);
};


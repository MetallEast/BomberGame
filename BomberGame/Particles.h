#pragma once

#include "Common\glut.h"
#include "Common\GLAux.h"


#define PARTICLE_NUMBER		2500
#define TERRA				0
#define BUILD				1
#define DUST				2
#define PARTICLE_SPEED		0.2
#define SIZE				0.3
#define DIRECTION_RANGE		50


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
	GLfloat XCoord;
	GLfloat XReducer, YReducer, ZReducer;
	GLfloat speed;
	GLfloat size;
	GLushort type;
	GLuint loop;
	Particle particles[PARTICLE_NUMBER];

	void Initialize(GLushort type);
public:
	GLfloat YCoord;
	void GetExpInfo(GLfloat bombXCoord, GLfloat bombYCoord, GLushort typeID);
	void GetDustInfo(GLfloat buildStartXCoord, GLfloat buildStartYCoord);
	void Run();
	Particles(GLushort type);
	~Particles(void);
};


#include "Particles.h"


Particles::Particles(GLushort type)
{
	Initialize(type);
}

Particles::~Particles(void)
{
}

void Particles::Initialize(GLushort type)
{
	speed = PARTICLE_SPEED;
	if (type == DUST) size = SIZE * 5.0;
	else if (type == SMALL_DUST) size = SIZE / 2.0;
	else size = SIZE;

	for (loop = 0; loop < PARTICLE_NUMBER; loop++)
	{
		particles[loop].life = 1.0;
		particles[loop].fade = 0.1;  

		particles[loop].x = 0;
		particles[loop].y = 0;
		particles[loop].z = 0;
		
		particles[loop].dirX = 0.0;
		particles[loop].dirY = 0.0;
		particles[loop].dirZ = 0.0;

		if (type < DUST)
		{
			particles[loop].r = 1.0;
			if (loop % 2 == 0) particles[loop].g = 0.65;
				else if (loop % 3 == 0) particles[loop].g = 1.0;
						else particles[loop].g = 0;
			particles[loop].b = 0;
		}
		else 
		{
			if (loop % 2 == 0) 
				particles[loop].r = particles[loop].g = particles[loop].b = 0.21;
			else if (loop % 3 == 0)
				particles[loop].r = particles[loop].g = particles[loop].b = 0.41;
			else 
				particles[loop].r = particles[loop].g = particles[loop].b = 0.6;
		}
	}	
}

void Particles::GetExpInfo(GLfloat X, GLfloat Y, GLushort typeID)
{
	XCoord = X;
	YCoord = Y;
	type = typeID;

	if (type == TERRA)
	{
		XReducer = DIRECTION_RANGE / 2.0;
		YReducer = DIRECTION_RANGE / 5.0;
		ZReducer = DIRECTION_RANGE / 2.0;
	}

	if (type == BUILD)
	{
		XReducer = DIRECTION_RANGE / 2.0;
		YReducer = DIRECTION_RANGE / 2.0;
		ZReducer = DIRECTION_RANGE / 2.0;
	}
}

void Particles::GetDustInfo(GLfloat buildStartXCoord, GLfloat buildStartYCoord)
{
	XCoord = buildStartXCoord;
	YCoord = buildStartYCoord;

	XReducer = DIRECTION_RANGE / 2.0;
	YReducer = DIRECTION_RANGE / 1.5;
	ZReducer = DIRECTION_RANGE / 2.0;
}

void Particles::Run()
{
	GLfloat x, y, z;
	for (loop = 0; loop < PARTICLE_NUMBER; loop++)
	{
		x = particles[loop].x;
		y = particles[loop].y;
		z = particles[loop].z;
 
		glColor4f(particles[loop].r, particles[loop].g, particles[loop].b, particles[loop].life);
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(x, y, z);
			glVertex3f(x + size, y, z);
			glVertex3f(x + size / 2, y + size, z);
			glVertex3f(x + size / 2, y, z - size);
			glVertex3f(x, y, z);
			glVertex3f(x + size, y, z);
		glEnd();
 
		particles[loop].x    += particles[loop].dirX / 1000;
		particles[loop].y    += particles[loop].dirY / 1000;
		particles[loop].z    += particles[loop].dirZ / 1000;
		particles[loop].life -= particles[loop].fade;
 
		if (particles[loop].life < 0.0)
		{
			particles[loop].life = 1.0;
			particles[loop].fade = (float(rand() % 50) / 1000.0) + 0.001;
 
			particles[loop].x = XCoord;
			particles[loop].y = YCoord;
			particles[loop].z = 0;
			
			particles[loop].dirX = float((rand() % DIRECTION_RANGE) - XReducer) * speed;
			if (type != DUST)
				particles[loop].dirY = float((rand() % DIRECTION_RANGE) - YReducer) * speed;
			particles[loop].dirZ = float((rand() % DIRECTION_RANGE) - ZReducer) * speed;
		}
	}	
}
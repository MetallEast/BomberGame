#include "Particles.h"


Particles::Particles(GLushort typeID)
{
	type = typeID;
	Initialize();
}

Particles::~Particles(void)
{
}

void Particles::Initialize()
{
	for (loop = 0; loop < PARTICLE_NUMBER; loop++)
	{
		particles[loop].life = 1.0;
		particles[loop].fade = 0.1;           
		particles[loop].x = 0;
		particles[loop].y = 0;
		particles[loop].z = 0;
		particles[loop].r = 1;
		particles[loop].g = loop % 3 == 0 ? 1   : 0;
		particles[loop].b = 0;
	}	
}

void Particles::Explosion(GLfloat radius, GLfloat size, GLfloat Xdirection, GLfloat Ydirection, GLfloat Zdirection, GLfloat expXCoord, GLfloat expYCoord)
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
			particles[loop].fade = (float(rand() % 50) / 1000.0f) + 0.001;
 
			particles[loop].x = expXCoord;
			particles[loop].y = expYCoord;
			particles[loop].z = 0;
				
			particles[loop].dirX = float((rand() % 50) - Xdirection) * radius;
			particles[loop].dirY = float((rand() % 50) - Ydirection) * radius;
			particles[loop].dirZ = float((rand() % 50) - Zdirection) * radius;
		}
	}	
}
#pragma once

#include <math.h>
#include "Common\glut.h"
#include "Common\GLAux.h"

typedef GLfloat GLTVector3[3];
typedef GLfloat GLTVector4[4];
typedef GLfloat GLTMatrix[16];

class Lighting
{
	GLfloat ambientLight[4];
	GLfloat diffuseLight[4];
	GLfloat specular[4];

	GLfloat gltGetVectorLength(GLTVector3 vNormal);
	void gltScaleVector(GLTVector3 vVector, const GLfloat fScale);
	void gltNormalizeVector(GLTVector3 vNormal);
	void gltSubtractVectors(const GLTVector3 vFirst, const GLTVector3 vSecond, GLTVector3 vResult);
	void gltVectorCrossProduct(const GLTVector3 vU, const GLTVector3 vV, GLTVector3 vResult);
	void gltGetNormalVector(const GLTVector3 vP1, const GLTVector3 vP2, const GLTVector3 vP3, GLTVector3 vNormal);
	void gltGetPlaneEquation(GLTVector3 vPoint1, GLTVector3 vPoint2, GLTVector3 vPoint3, GLTVector3 vPlane);
	void gltMakeShadowMatrix(GLTVector3 vPoints[3], GLTVector4 vLightPos, GLTMatrix destMat);
public:
	GLint nShadow;
	GLTMatrix shadowMat;
	GLfloat	lightPos[4];

	void Init(GLfloat StartY);
	Lighting(void);
	~Lighting(void);
};


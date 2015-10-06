#include "Lighting.h"


Lighting::Lighting()
{
	nShadow = 0;

	ambientLight[0] = 0.3;
	ambientLight[1] = 0.3;
	ambientLight[2] = 0.3;
	ambientLight[3] = 1.0;

	diffuseLight[0] = 0.7;
	diffuseLight[1] = 0.7;
	diffuseLight[2] = 0.7;
	diffuseLight[3] = 1.0;

	specular[0] = 1.0;
	specular[1] = 1.0;
	specular[2] = 1.0;
	specular[3] = 1.0;

	lightPos[0] = 50.0;
	lightPos[1] = 100.0;
	lightPos[2] = -50.0;
	lightPos[3] = 0.0;
}

Lighting::~Lighting(void)
{
}

void Lighting::Init(GLfloat StartY)
{
	GLTVector3 points[3] = {{-1.0,  StartY, -1.0},
							{-1.0,  StartY,  1.0},
							{ 1.0,  StartY,  1.0}};

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.0, 0.0, 1.0, 1.0);
	
	gltMakeShadowMatrix(points, lightPos, shadowMat);	
}

GLfloat Lighting::gltGetVectorLength(GLTVector3 vNormal)
{
	return sqrt(vNormal[1] * vNormal[1] + vNormal[2] * vNormal[2] + vNormal[3] * vNormal[3]);
}

void Lighting::gltScaleVector(GLTVector3 vVector, const GLfloat fScale)
{ 
  vVector[0] *= fScale; vVector[1] *= fScale; vVector[2] *= fScale; 
}

void Lighting::gltNormalizeVector(GLTVector3 vNormal)
{ 
  GLfloat fLength = 1.0f / gltGetVectorLength(vNormal);
  gltScaleVector(vNormal, fLength); 
}

void Lighting::gltSubtractVectors(const GLTVector3 vFirst, const GLTVector3 vSecond, GLTVector3 vResult) 
{
  vResult[0] = vFirst[0] - vSecond[0];
  vResult[1] = vFirst[1] - vSecond[1];
  vResult[2] = vFirst[2] - vSecond[2];
}

void Lighting::gltVectorCrossProduct(const GLTVector3 vU, const GLTVector3 vV, GLTVector3 vResult)
{
  vResult[0] = vU[1]*vV[2] - vV[1]*vU[2];
  vResult[1] = -vU[0]*vV[2] + vV[0]*vU[2];
  vResult[2] = vU[0]*vV[1] - vV[0]*vU[1];
}

void Lighting::gltGetNormalVector(const GLTVector3 vP1, const GLTVector3 vP2, const GLTVector3 vP3, GLTVector3 vNormal)
{
   GLTVector3 vV1, vV2;
  
  gltSubtractVectors(vP2, vP1, vV1);
  gltSubtractVectors(vP3, vP1, vV2);
  
  gltVectorCrossProduct(vV1, vV2, vNormal);
  gltNormalizeVector(vNormal);
}

void Lighting::gltGetPlaneEquation(GLTVector3 vPoint1, GLTVector3 vPoint2, GLTVector3 vPoint3, GLTVector3 vPlane)
{
  gltGetNormalVector(vPoint1, vPoint2, vPoint3, vPlane); 
  vPlane[3] = -(vPlane[0] * vPoint3[0] + vPlane[1] * vPoint3[1] + vPlane[2] * vPoint3[2]);
}

void Lighting::gltMakeShadowMatrix(GLTVector3 vPoints[3], GLTVector4 vLightPos, GLTMatrix destMat)
{
	  GLTVector4 vPlaneEquation;
	  GLfloat dot;
  
	  gltGetPlaneEquation(vPoints[0], vPoints[1], vPoints[2], vPlaneEquation);
  
	  dot =  vPlaneEquation[0]*vLightPos[0] + 
			 vPlaneEquation[1]*vLightPos[1] + 
			 vPlaneEquation[2]*vLightPos[2] + 
			 vPlaneEquation[3]*vLightPos[3];
  
	  destMat[0]  = dot  - vLightPos[0] * vPlaneEquation[0];
	  destMat[4]  = 0.0f - vLightPos[0] * vPlaneEquation[1];
	  destMat[8]  = 0.0f - vLightPos[0] * vPlaneEquation[2];
	  destMat[12] = 0.0f - vLightPos[0] * vPlaneEquation[3];
  
	  destMat[1]  = 0.0f - vLightPos[1] * vPlaneEquation[0];
	  destMat[5]  = dot  - vLightPos[1] * vPlaneEquation[1];
	  destMat[9]  = 0.0f - vLightPos[1] * vPlaneEquation[2];
	  destMat[13] = 0.0f - vLightPos[1] * vPlaneEquation[3];
  
	  destMat[2]  = 0.0f - vLightPos[2] * vPlaneEquation[0];
	  destMat[6]  = 0.0f - vLightPos[2] * vPlaneEquation[1];
	  destMat[10] = dot  - vLightPos[2] * vPlaneEquation[2];
	  destMat[14] = 0.0f - vLightPos[2] * vPlaneEquation[3];
  
	  destMat[3]  = 0.0f - vLightPos[3] * vPlaneEquation[0];
	  destMat[7]  = 0.0f - vLightPos[3] * vPlaneEquation[1];
	  destMat[11] = 0.0f - vLightPos[3] * vPlaneEquation[2];
	  destMat[15] = dot  - vLightPos[3] * vPlaneEquation[3];
}

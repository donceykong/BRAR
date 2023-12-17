#ifndef VIEWS_H
#define VIEWS_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

// Global Variables
extern int viewMode;  // 1 = First Person, 2 = Orbit

// GLfloat perspectiveCamX = 0, perspectiveCamY = 0, perspectiveCamZ = 4;

extern GLfloat OrbitCamZPrev;
extern GLfloat orbitCamX, orbitCamY, orbitCamZ;
extern GLfloat orbitCamAngleY;

extern GLfloat fpCamZoomX, fpCamZoomY, fpCamZoomZ;
extern GLfloat fpCamZoom ;

extern GLfloat overheadCamX, overheadCamY, overheadCamZ;
extern GLfloat overheadCamAngleY;

void perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

void setOrbitView();

void setOverheadView();

void displayView();

#endif // VIEWS_H
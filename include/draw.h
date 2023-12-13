#ifndef DRAW_H
#define DRAW_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include "textureUtils.h"

/*
 ***************************** Misc shapes *****************************
 */

// Draw normal 
void drawNormal(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat length);


/*
 ***************************** Shape edges *****************************
 */

// Draw square prism edges
void drawPrismEdges(float rectangleWidth, float rectangleHeight, float prismBase, float prismHeight); 

// Draw cuboid edges
void drawCuboidEdges(GLfloat width, GLfloat height, GLfloat depth);

void drawRightTriPrismEdges(GLfloat width, GLfloat height, GLfloat depth);

void drawSemiCylinderEdges(GLfloat radius, GLfloat height, int segments, double percentFull);

void drawParallelogramEdges(GLfloat width, GLfloat height, GLfloat depth);


/*
 ***************************** Solid shapes *****************************
*/

void drawPrism(float rectangleWidth, float rectangleHeight, float prismBase, float prismHeight);

void drawCuboid(GLfloat width, GLfloat height, GLfloat depth);

void drawRightTriPrism(GLfloat width, GLfloat height, GLfloat depth);

void drawSemiCylinder(GLfloat radius, GLfloat height, int segments, double percentFull);

void drawParallelogram(GLfloat width, GLfloat height, GLfloat depth);

void drawSphere(double r, int lats, int longs);

#endif // DRAW_H
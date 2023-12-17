#ifndef DRAW_H
#define DRAW_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdbool.h>
#include <time.h>

#include "matrixMath.h"
#include "textureUtils.h"
#include "keys.h"

/*
 ***************************** Misc shapes *****************************
 */

// Draw normal 
void drawNormal(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat length);

void drawFrame(float length);

void drawPoseFrame(float axisLen, float lineThickness);

void drawP2PLine(Vector3 point1, Vector3 point2);

/*
 ****************************Ground Plane & Portal Walls ***************
*/
void drawLorenzAttractor();

void drawPortals();

void drawGroundPlane(Vector3 mapCenter);

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
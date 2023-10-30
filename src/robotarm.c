// Created by: Doncey Albin

#ifdef __APPLE__
#include <GLUT/glut.h>
#define SPEED 1.0
#else
#include <GL/glut.h>
#define SPEED 0.1
#endif

#ifndef RES
#define RES 1
#endif

// External includes
#include <math.h>
#include <stdbool.h>  // Add this include for bool type
#include <stdio.h>

// In-house includes
//#include "plotter.h"
#include "matrixMath.h"
#include "forwardKinematics.h"
#include "miscObjects.h"
#include "textureUtils.h"
#include "robot.h"
#include "views.h"
#include "lighting.h"
#include "keyHandler.h" // Add this import last

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  displayView();            // View with respect to number key pressed
  glPushMatrix();
  glEnable(GL_DEPTH_TEST);  // Enable depth testing

  setupLighting();          // Setup lighting (from lighting.h)

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};  // Adjust this value as needed
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);

  update();
  // Axes
  float axisLen = 0.5;
  drawAxes(axisLen);

  drawRobotArm();

  glDisable(GL_DEPTH_TEST);  // Optionally disable depth testing if not needed later

  glPopMatrix();

  glFlush();
  glutSwapBuffers();
}

int main(int argc, char** argv) {
  // Init GLUT
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH); 

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1500, 1500);
  glutCreateWindow("Robot Arm");

  glutDisplayFunc(display);

  // Arrow key callbacks
  glutSpecialFunc(special);
  glutSpecialUpFunc(specialUp);

  // Keyboard callbacks
  glutKeyboardFunc(handleKeys);
  glutKeyboardUpFunc(handleKeysUp);

  // Mouse callbacks
  //glutMouseFunc(mouseClick);
  //glutMotionFunc(mouseMove);

  // Init texture
  loadTextureFromFile("./assets/cool.bmp");

  //init();
  glutMainLoop();

  return 0;
}

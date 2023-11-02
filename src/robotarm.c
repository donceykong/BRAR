
// Created by: Doncey Albin

#ifdef __APPLE__
#include <GLUT/glut.h>
#define SPEED 1.0
#else
#include <GL/glut.h>
#define SPEED 0.2
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
#include "textureUtils.h"

#include "simulateDrop.h"
#include "simple_objects.h"
#include "miscObjects.h"
#include "groundPlane.h"
#include "robot.h"

#include "matrixMath.h"
#include "forwardKinematics.h"

#include "views.h"
#include "lighting.h"
#include "keyHandler.h" // Add this import last  

#include "CSCIx229.h"

// Global Framerate variables
const double FPS = 260.0;
const double frameDelay = 1000.0 / FPS;
double lastFrameTime = 0.00;

bool ballInHand() {
    if (gripperClosed && fabsf(posX-endEffectorPosition.x)<0.1 &&  fabsf(posY-endEffectorPosition.y)<0.1 && fabsf(posZ-endEffectorPosition.z)<0.1) {
        return true;
        
    }
    else {
        return false;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    update();
    displayView();
    setupLighting();

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    // Set up polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    //GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};  // Adjust this value as needed
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glRotatef((GLfloat)10.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, 0.0);                // Translate floor
    drawGroundPlane();
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    // Set up polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};  // Adjust this value as needed
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    drawAxes(2.0);
    drawRobotArm();
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();

    // Draw sphere simulation
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);  // Enable depth testing

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    bool ballInHandBool = ballInHand();

    if (ballInHandBool) {
        posX = endEffectorPosition.x;
        posY = endEffectorPosition.y;
        posZ = endEffectorPosition.z;
    }
    else {
        getPosition();
    }

    glTranslatef(posX, posY, posZ);
    Sphere(0.2, 100, 100);              // Draw a sphere

    glDisable(GL_DEPTH_TEST);
    glPopMatrix();

    glutPostRedisplay();

    glFlush();
    glutSwapBuffers();
}

void FPSLimitedDisplay () {
    double currentTime = glutGet(GLUT_ELAPSED_TIME);
    double timeSinceLastFrame = currentTime - lastFrameTime;
    
    //printf("timeSinceLastFrame: %f, frameDelay: %f\n", timeSinceLastFrame, frameDelay);

    if (timeSinceLastFrame >= frameDelay) {
        display();
    } else {
        double sleepTime = frameDelay - timeSinceLastFrame;
        //printf("sleepTime: %f\n", sleepTime);
        if (sleepTime > 0.00) {
            usleep((unsigned int)(sleepTime * 1000.00 + 0.5)); // usleep takes sleep time in microseconds
        }
        display();
    }

    lastFrameTime = currentTime;
}

int main(int argc, char** argv) {
  // Init GLUT
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH); 

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1500, 1500);
  glutCreateWindow("Robot Arm");

  glutDisplayFunc(FPSLimitedDisplay);

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
  //loadTextureFromFile("./assets/cool.bmp");

  //init();

  lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
  glutMainLoop();

  return 0;
}
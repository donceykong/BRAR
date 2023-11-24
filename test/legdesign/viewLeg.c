
// Created by: Doncey Albin

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef RES
#define RES 1
#endif

// External includes
#include <math.h>
#include <stdbool.h>  // Add this include for bool type
#include <stdio.h>

#include "textureUtils.h"
#include "robotLeg.h"

// Global variables to store mouse state and position
bool leftButtonPressed = false;
float translateX = 0.0f;
float translateY = 0.0f;
int lastMouseX = 0, lastMouseY = 0;

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            leftButtonPressed = true;
            lastMouseX = x;
            lastMouseY = y;
        } else if (state == GLUT_UP) {
            leftButtonPressed = false;
        }
    }
}

void mouseMove(int x, int y) {
    if (leftButtonPressed) {
        translateX += (x - lastMouseX) * 0.01f; // Adjust the 0.01f factor as needed for speed
        translateY -= (y - lastMouseY) * 0.01f; // Invert y-axis movement
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

void reshape(int width, int height) {
    // Prevent a divide by zero error by making height equal one
    if (height == 0) height = 1;
    float ratio = (float) width / height;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, width, height);

    // Set the correct perspective
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity(); // Reset the model-view matrix

    // Set the camera
    gluLookAt(-translateX, -translateY, 5.0f,  // Camera is at (0,0,10), in World Space
              0.0f, 0.0f, 0.0f,   // and looks at the origin
              0.0f, 1.0f, 0.0f);  // Head is up (set to 0,-1,0 to look upside-down)

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);  // Enable depth testing

    // Set up polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    drawRobotLeg();
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();

    glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // Init GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH); 

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1200, 1200);
    glutCreateWindow("Robot Arm");

    BMPtexture1 = loadTexture("./rusted_metal.bmp");
    BMPtexture2 = loadTexture("./rusted_metal2.bmp");
    BMPtexture3 = loadTexture("./motor_shaft.bmp");
    BMPtexture4 = loadTexture("./sheet_metal3.bmp");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape); // Register the reshape function

    glutMouseFunc(mouseButton); // Register the mouse button callback function
    glutMotionFunc(mouseMove); // Register the mouse motion callback functio

    glutMainLoop();

    return 0;
}

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
#include "CSCIx229.h"

#include "textureUtils.h"
#include "designShapes.h"
#include "matrixMath.h"

#include "robotStateModels.h"
#include "robotController.h"

#include "simulateDrop.h"
#include "miscObjects.h"
#include "groundPlane.h"
#include "robot.h"

#include "mapManager.h"

#include "forwardKinematics.h"

#include "views.h"
#include "lighting.h"
#include "keyHandler.h" // Add this import last  


// Draw frames on robot joints
bool showFrames = true;

// set initial runner speed
double runnerSpeed = 1.0;

// Global Framerate variables
const double FPS = 270.0;
const double frameDelay = 1000.0 / FPS;
double lastFrameTime = 0.00;

// Globals for splash screen
GLuint splashTexture;
bool showSplash = false;

// Global variable for loading progress
float loadingProgress = 0;

void drawSplashScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1500, 0, 1500);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, splashTexture);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex2f(1500.0, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex2f(1500.0, 1500.0);
    glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 1500.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void drawLoadingBar(float progress) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1500, 0, 1500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Disable texture mapping for the loading bar
    glDisable(GL_TEXTURE_2D);

    // Calculate the width of the loading bar based on progress
    float maxBarWidth = 800.0f;
    float barWidth = progress * maxBarWidth; // Assuming the bar is 1400 units wide at full progress
    float barHeight = 10.0f; // Set the height of the bar
    float barX = 100.0f; // X position of the bar
    float barY = 300.0f; // Y position of the bar from the bottom of the window

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(barX, barY+10.0f);
        glVertex2f(barX + maxBarWidth, barY+10.0f);
        glVertex2f(barX + maxBarWidth, barY + barHeight +10.0f);
        glVertex2f(barX, barY + barHeight +10.0f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(barX, barY-10.0f);
        glVertex2f(barX + maxBarWidth, barY-10.0f);
        glVertex2f(barX + maxBarWidth, barY + barHeight -10.0f);
        glVertex2f(barX, barY + barHeight -10.0f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(barX-20.0, barY-10.0f);
        glVertex2f(barX, barY-10.0f);
        glVertex2f(barX-20.0, barY + barHeight +10.0f);
        glVertex2f(barX, barY + barHeight +10.0f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(barX + maxBarWidth + 20.0, barY-10.0f);
        glVertex2f(barX + maxBarWidth, barY-10.0f);
        glVertex2f(barX + maxBarWidth + 20.0, barY + barHeight +10.0f);
        glVertex2f(barX + maxBarWidth, barY + barHeight +10.0f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    // Draw the loading bar as a quad
    glBegin(GL_QUADS);
        glVertex2f(barX, barY);
        glVertex2f(barX + barWidth, barY);
        glVertex2f(barX + barWidth, barY + barHeight);
        glVertex2f(barX, barY + barHeight);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);

    // Restore previous state
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    // Swap buffers to display the loading bar
    //glutPostRedisplay();
    glutSwapBuffers();
    //glFlush();
}

int iter = 0;
int numberPoses = 0;
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    // Set up polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    //GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};  // Adjust this value as needed
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glTranslatef(mapCenterX, 0.00, mapCenterZ);
    drawGroundPlane();
    drawPortals();
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();
    
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
    drawAxes(2.0);
    drawRobot();
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();

    // Draw sphere simulation
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);  // Enable depth testing

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    ballInHandBool = ballInHand();

    if (ballInHandBool) {
        runnerPosX = endEffectorPosition.x;
        runnerPosY = endEffectorPosition.y;
        runnerPosZ = endEffectorPosition.z;
    }
    else {
        getYPosition();
    }

    drawAxes(2.0);
    drawMiniRobot();

    glDisable(GL_DEPTH_TEST);
    glPopMatrix();

    drawText3D();
    // // Show text on screen
    // glMatrixMode(GL_PROJECTION);
    // glPushMatrix();
    // glLoadIdentity();
    // gluOrtho2D(0, 1500, 0, 1500);

    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();

    // // Disable texture mapping for the loading bar
    // glDisable(GL_TEXTURE_2D);
    // Print("runner speed: %f", runnerSpeed);

    /*
     * Add poses to map
    */
    // iter++;
    // //printf("numberPoses: %d, iterDIV10: %d\n", numberPoses, iter/10);
    // if (iter / 10 == 1 & numberPoses < 1000) {
    //     updateRunnerPoseList(numberPoses);
    //     iter = 0;
    //     numberPoses++;
    // }
    // for (int i = 0; i < numberPoses; i++) {
    //     glPushMatrix();
    //     glTranslatef(runnerPoseList[i][0], runnerPoseList[i][1], runnerPoseList[i][2]);
    //     glRotatef((GLfloat)runnerPoseList[i][3], 0.0, 1.0, 0.0);
    //     drawFrame(2.0);
    //     //Sphere(0.5, 4, 4);              
    //     glPopMatrix();
    // }

    updateMapCenter();

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

void endSplash(int value) {
    showSplash = false;
    glutDisplayFunc(showSplash ? drawSplashScreen : FPSLimitedDisplay);
    glutPostRedisplay();
}

void updateLoadingProgress(int value) {
    // Increment loading progress
    loadingProgress += (float)value*0.1; // Increment by a value that makes sense for your application's loading time
    if (loadingProgress >= 200.0f) {
        loadingProgress = 200.0f;
        showSplash = false; // Hide splash screen once loading is complete
    }
    
    // Redisplay to update the loading bar
    drawLoadingBar(loadingProgress);
    glutPostRedisplay();

    // Continue updating until loading is complete
    if (showSplash) {
        glutTimerFunc(300, updateLoadingProgress, 1); // Adjust the timer delay as needed
    }
}

int main(int argc, char** argv) {
    // Init GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH); 

    glutInitWindowPosition(600, 100);
    glutInitWindowSize(1200, 1200);
    glutCreateWindow("Robot Arm");

    //glutDisplayFunc(FPSLimitedDisplay);
    glutDisplayFunc(showSplash ? drawSplashScreen : FPSLimitedDisplay);
    
    // Splash Screen
    glutTimerFunc(0, updateLoadingProgress, 1); // Adjust the timer delay as needed
    glutTimerFunc(3000, endSplash, 0);

    // Arrow key callbacks
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);

    // Keyboard callbacks
    glutKeyboardFunc(handleKeys);
    glutKeyboardUpFunc(handleKeysUp);

    // Mouse callbacks
    //glutMouseFunc(mouseClick);
    //glutMotionFunc(mouseMove);

    //init();

    lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
    
    // load splash texture
    splashTexture = loadTexture("./assets/splashscreen.bmp");

    // load terrain texture
    terrainTexture = loadTexture("./assets/terrain.bmp");

    // load portal texture
    portalTexture = loadTexture("./assets/portal.bmp");

    // load robot textures
    BMPtexture1 = loadTexture("./assets/rusted_metal.bmp");
    BMPtexture2 = loadTexture("./assets/rusted_metal2.bmp");
    BMPtexture3 = loadTexture("./assets/motor_shaft.bmp");
    BMPtexture4 = loadTexture("./assets/sheet_metal3.bmp");
    BMPtexture5 = loadTexture("./assets/robot_body.bmp");

    setRunnerPoseList();

    glutMainLoop();

    return 0;
}
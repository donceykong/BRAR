
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
#include <ft2build.h>   // FreeType (used in main screen buttons)
#include FT_FREETYPE_H

// In-house includes
#include "GameModes.h"      // TOP IMPORT

#include "textureUtils.h"
#include "windowHandler.h"
#include "ftTextHandler.h"
#include "buttonHandler.h"
#include "screenInfo.h"
#include "CSCIx229.h"

#include "designShapes.h"
#include "matrixMath.h"

#include "robotStateModels.h"
#include "robotController.h"

#include "simulateDrop.h"
#include "miscObjects.h"
#include "robot.h"

#include "mapManager.h"
#include "groundPlane.h"

#include "forwardKinematics.h"

#include "views.h"
#include "lighting.h"
#include "keyHandler.h"         // Add this import last  

// Draw frames on robot joints
bool showFrames = true;

// Draw robot pose history on map
bool showPoseHist = false;

// Global Framerate variables
const double FPS = 270.0;
const double frameDelay = 1000.0 / FPS;
double lastFrameTime = 0.00;

// Globals for main screen options
bool showMain = true;

// Mouse callback for game options
int mouseCallbackEnabled = 1; // Global variable to control the callback

int iter = 0;
int numberPoses = 0;
void displayPoseHistory() {
    /*
     * Add poses to map
    */
    if (showPoseHist) {
        iter++;
        //printf("numberPoses: %d, iterDIV10: %d\n", numberPoses, iter/10);
        if (iter / 10 == 1 & numberPoses < 1000) {
            updateRunnerPoseList(numberPoses);
            iter = 0;
            numberPoses++;
        }
        for (int i = 0; i < numberPoses; i++) {
            glPushMatrix();
            glTranslatef(runnerPoseList[i][0], runnerPoseList[i][1], runnerPoseList[i][2]);
            glRotatef((GLfloat)runnerPoseList[i][3], 0.0, 1.0, 0.0);
            drawFrame(2.0);
            //Sphere(0.5, 4, 4);              
            glPopMatrix();
        }
    }
}

void displayTimeCrunch() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    updateTimeCrunch(); // Needs to use nearest map object pose as controller basis for arm
    displayView();
    setupLighting();

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};  // Adjust this value as needed
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    drawGroundPlane();
    drawRobot();                    // Draw chaser (collector)
    computeForwardKinematics();
    glDisable(GL_DEPTH_TEST);

    glDisable(GL_LIGHTING);
    displayPoseHistory();
    setObjAbsorberPos(chaserPosX, chaserPosY, chaserPosZ);
    updateMapTimeCrunch();
    drawNearestLine(nearestMapItem->position.x, nearestMapItem->position.y, nearestMapItem->position.z);

    currentTime = time(NULL);
    elapsedTime = difftime(currentTime, prevTime);
    totalElapsedTime = difftime(currentTime, beginTime);
    if (remainingTime > 0.0) {
        remainingTime -= elapsedTime;
    }
    prevTime = currentTime; 
    sprintf(SIstr1, "Remaining Time: %.5f", remainingTime);
    sprintf(SIstr2, "Total Score: %.5f", totalScore);
    drawSI(SIstr1, SIstr2);

    glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

void displayRunner() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    checkRobotCaptured();
    update();
    displayView();
    setupLighting();

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};  // Adjust this value as needed
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    drawGroundPlane();
    drawRobot();                    // Draw chaser (collector)
    drawMiniRobot();                 // Draw runner
    computeForwardKinematics();
    glDisable(GL_DEPTH_TEST);

    drawText3D();
    displayPoseHistory();
    setObjAbsorberPos(runnerPosX, runnerPosY, runnerPosZ);
    updateMapCenter();

    glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

void display() {
    switch (GAME_MODE) {
        case RUNNER:
            displayRunner();
            break;
        case TIME_CRUNCH:
            displayTimeCrunch();
            chaserYawAdd = 90.0;
            break;
        default:
            break;
    }   

    /*
    * Should I add an escape button? It looks like the following still show even during gameplay
    * Maybe I can add the overhead view in the corner too?
    * Or add robot states?????
    * 
    */
    // drawButtonScreen(); 
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


// GLUT Mouse Button Callback
void mouseButtonCallback(int button, int state, int x, int y) {
    if (!mouseCallbackEnabled) {
        return; // Do nothing if the callback is disabled
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert from window coordinates to OpenGL coordinates
        y = windowYDiff - y;
        
        // Check if the click is within the bounds of Button 1
        if (x > button1XMin && x < button1XMax && y > button1YMin && y < button1YMax) {
            setGameMode(1);
            showMain = false;
            mouseCallbackEnabled = 0;
            beginTime = time(NULL);
            prevTime = beginTime;
        }

        // Check if the click is within the bounds of Button 2
        if (x > button2XMin && x < button2XMax && y > button2YMin && y < button2YMax) {
            setGameMode(0);
            showMain = false;
            mouseCallbackEnabled = 0;
            beginTime = time(NULL);
            prevTime = beginTime;
        }
        glutDisplayFunc(showMain ? drawButtonScreen : FPSLimitedDisplay);
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    // Init GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH); 

    glutInitWindowPosition(windowXPos, windowYPos);
    glutInitWindowSize(windowXDiff, windowYDiff);
    glutCreateWindow("Robot Arm");

    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        fprintf(stderr, "Could not init FreeType Library\n");
        return 1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "./assets/tff/Roboto-Bold.ttf", 0, &face)) {
        fprintf(stderr, "Failed to load font\n");
        return 1;
    }

    setupTextRendering(face); // Call this after FT_New_Face and before the main loop

    // Game play
    // glutDisplayFunc(FPSLimitedDisplay);

    // Main Screen
    glutDisplayFunc(showMain ? drawButtonScreen : FPSLimitedDisplay);

    // Arrow key callbacks
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);

    // Keyboard callbacks
    glutKeyboardFunc(handleKeys);
    glutKeyboardUpFunc(handleKeysUp);

    // Mouse callbacks
    //glutMouseFunc(mouseClick);
    //glutMotionFunc(mouseMove);
    glutMouseFunc(mouseButtonCallback);

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
    addObjectsToMapList();

    glutMainLoop();

    // Cleanup FreeType resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return 0;
}
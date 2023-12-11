
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
// #include <pthread.h>

// In-house includes
// #include "windowHandler.h"   // NO DEPENDS
#include "matrixMath.h"         // NO DEPENDS
// #include "GameModes.h"       // NO DEPENDS
#include "textureUtils.h"       // NO DEPENDS

// #include "ftTextHandler.h"
// #include "buttonHandler.h"   
#include "screenInfo.h"
#include "CSCIx229.h"

#include "designShapes.h"

#include "robotStateModels.h"
#include "miscObjects.h"
#include "robot.h"

#include "mapManager.h"
#include "RRTStar.h"
#include "groundPlane.h"

#include "forwardKinematics.h"

#include "views.h"
#include "lighting.h"
// #include "keyHandler.h"
#include "keyUpdate.h"         
#include "dummy.h"

// Global GAME_MODE enum
enum GameMode GAME_MODE;

GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};  

// Global Framerate variables
int previousTime = 0;
const int desiredFPS = 60;
const int timePerFrame = 1000 / desiredFPS; // milliseconds

// Globals for main screen options
bool showMain = true;

// Mouse callback for game options
int mouseCallbackEnabled = 1; // Global variable to control the callback

Path* rrtStarResult = NULL;
// // Global variables
// pthread_t rrtStarThread;
// bool rrtStarThreadRunning = false;
// pthread_mutex_t mutex;

// void* rrtStarThreadFunc(void* arg) {
//     // Perform RRT* calculations
//     Vector3 startPosition = chaserRobot.position;
//     Vector3 goalPosition = runnerRobot.position;
//     int maxIterations = 1000;
//     Path* newPath = rrtStar(startPosition, goalPosition, maxIterations);

//     pthread_mutex_lock(&mutex);
//     // Update the global result
//     rrtStarResult = newPath;
//     rrtStarThreadRunning = false;
//     pthread_mutex_unlock(&mutex);

//     pthread_exit(NULL);
// }

// void startRrtStarThread() {
//     if (!rrtStarThreadRunning) {
//         rrtStarThreadRunning = true;
//         pthread_create(&rrtStarThread, NULL, rrtStarThreadFunc, NULL);
//     }
// }

void displayViewRobot() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    chaserRobot.speed = 0.0;

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glEnable(GL_COLOR_MATERIAL);
    
    updateViewRobot();
    displayView();
    setupLighting();

    glPushMatrix();
    glTranslatef(0.0, 2.0, 0.0);        // Translate to bring parallelogram top down
    glColor3f(1,1,1);    // Green face color
    drawChaserRobot();                    // Draw chaser (collector)
    glPopMatrix();

    glDisable(GL_DEPTH_TEST);

    glFlush();
    glutSwapBuffers();
}

void displayTimeCrunch() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    updateTimeCrunch(); // Needs to use nearest map object pose as controller basis for arm
    getYPosition(&chaserRobot);
    displayView();
    setupLighting();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glEnable(GL_COLOR_MATERIAL);
    // float white[] = {1,1,1,1};
    // float Emission[]  = {0.0,0.0,0.01*0,1.0};
    // glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 0.3);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

    drawGroundPlane();
    displayPoseHistory(&chaserRobot);
    drawChaserRobot();                    // Draw chaser (collector)
    computeForwardKinematics();

    plotMapBorder();
    plotMapObstacles();
    plotMapItems();
    setObjAbsorberPos(chaserRobot.position.x, chaserRobot.position.y, chaserRobot.position.z);
    updateMapCenter (chaserRobot.position.x, chaserRobot.position.z);
    drawNearestLine(nearestMapItem->position.x, nearestMapItem->position.y, nearestMapItem->position.z, chaserRobot.position, chaserRobot.endEffectorPosition);
    glDisable(GL_DEPTH_TEST);

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

    // glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

void displayRunner() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    checkRobotCaptured();   //
    updateRunner();
    checkRobotCaptured();
    displayView();
    setupLighting();

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glEnable(GL_COLOR_MATERIAL);
    
    drawGroundPlane();
    drawChaserRobot();                    // Draw chaser (collector)
    drawRunnerRobot();                    // Draw runner
    computeForwardKinematics();

    //drawText3D();
    displayPoseHistory(&runnerRobot);

    plotMapBorder();
    plotMapObstacles();
    plotMapItems();
    setObjAbsorberPos(runnerRobot.position.x, runnerRobot.position.y, runnerRobot.position.z);
    updateMapCenter(runnerRobot.position.x, runnerRobot.position.z);

    if (RRTSTAR_ACTIVE) {
        rrtStarResult = rrtStar(chaserRobot.endEffectorPosition, runnerRobot.position, 1000);
        displayRRTStarPath(rrtStarResult);
    }
    
    // // Multi-thread RRT* (Performance is meh)
    // startRrtStarThread(); // Start the RRT* thread if not already running
    // pthread_mutex_lock(&mutex);
    // if (rrtStarResult) {
    //     // Use rrtStarResult for rendering
    //     displayRRTStarPath(rrtStarResult);
    //     // After using the result, free it if necessary and set to NULL
    //     free(rrtStarResult);
    //     rrtStarResult = NULL;
    // }
    // pthread_mutex_unlock(&mutex);


    glDisable(GL_DEPTH_TEST);

    currentTime = time(NULL);
    elapsedTime = difftime(currentTime, prevTime);
    totalElapsedTime = difftime(currentTime, beginTime);
    if (remainingTime > 0.0) {
        remainingTime -= elapsedTime;
    }
    prevTime = currentTime; 

    sprintf(SIstr1, "Time: %.5f", totalElapsedTime);
    sprintf(SIstr2, "Total Score: %.5f", totalScoreRunner);
    drawSI(SIstr1, SIstr2);

    //glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

double colorADJ = 0.0;
void displayEndScreenTimeCrunch() {
    srand(time(NULL));  // set rand generator seed
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);

    // Set up the view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowXDiff, 0.0, windowYDiff);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // drawBackground();
    // Render some text on the screen
    glColor3f(1.0, 0.0, 0.0); // Set text color (green)
    renderText("GAME OVER", windowXDiff/20, windowYDiff/2, 4.0);
    
    glColor3f(0.1 + colorADJ, 0.8+colorADJ, colorADJ); // Set text color (green)
    sprintf(SIstr2, "Total Score: %.5f", totalScore);
    renderText(SIstr2,  windowXDiff/20, windowYDiff/2 - 200, 2.0);

    glColor3f(0.8 + colorADJ, 0.1+colorADJ, 0.1*colorADJ); // Set text color (green)
    sprintf(SITopPlayer, "Top TC player: %s | Score: %f", topPlayerName, topScore);
    renderText(SITopPlayer,  windowXDiff/20, windowYDiff/2 - 300, 1.0);

    colorADJ = (double)rand() / (RAND_MAX);
    
    //glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

void displayEndScreenRunner() {
    srand(time(NULL));  // set rand generator seed
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);

    // Set up the view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowXDiff, 0.0, windowYDiff);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // drawBackground();
    // Render some text on the screen
    glColor3f(1.0, 1.0, 1.0); // Set text color (green)
    renderText("GAME OVER", windowXDiff/20, windowYDiff/2, 4.0);
    
    glColor3f(0.1 + colorADJ, 0.8+colorADJ, colorADJ); // Set text color (green)
    sprintf(SIstr2, "Total Score: %.5f", totalScoreRunner);
    renderText(SIstr2,  windowXDiff/20, windowYDiff/2 - 200, 2.0);

    glColor3f(0.8 + colorADJ, 0.1+colorADJ, 0.1*colorADJ); // Set text color (green)
    sprintf(SITopPlayer, "Top RUN player: %s | Score: %f", topPlayerName, topScore);
    renderText(SITopPlayer,  windowXDiff/20, windowYDiff/2 - 300, 1.0);

    colorADJ = (double)rand() / (RAND_MAX);
    
    //glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

bool GameJustEnded = false;
void display() {
    switch (GAME_MODE) {
        case RUNNER:
            if (!runnerRobot.taken) {
                displayRunner();
            }
            else {
                if (!GameJustEnded) {
                    game.score = totalScoreRunner;
                    saveScore(&game);
                    readScores(&game);
                    GameJustEnded = true;
                }
                displayEndScreenRunner();
            }
            break;
        case TIME_CRUNCH:
            if (remainingTime > 0.0) {
                displayTimeCrunch();
                chaserRobot.yawAdd = 90.0;
            }
            else {
                if (!GameJustEnded) {
                    game.score = totalScore;
                    saveScore(&game);
                    readScores(&game);
                    GameJustEnded = true;
                }
                displayEndScreenTimeCrunch();
            }
            break;
        case VIEW_ROBOT:
                displayViewRobot();
            break;
        default:
            break;
    }   
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
            setGameMode(2);
            showMain = false;
            mouseCallbackEnabled = 0;
            beginTime = time(NULL);
            prevTime = beginTime;

            initChaserRobot();
        }

        // Check if the click is within the bounds of Button 2
        if (x > button2XMin && x < button2XMax && y > button2YMin && y < button2YMax) {
            setGameMode(1);
            showMain = false;
            mouseCallbackEnabled = 0;
            beginTime = time(NULL);
            prevTime = beginTime;

            initChaserRobot();
        }
        // Check if the click is within the bounds of Button 2
        if (x > button3XMin && x < button3XMax && y > button3YMin && y < button3YMax) {
            setGameMode(0);
            showMain = false;
            mouseCallbackEnabled = 0;
            beginTime = time(NULL);
            prevTime = beginTime;

            initChaserRobot();
            initRunnerRobot();
        }
        glutDisplayFunc(showMain ? drawButtonScreen : display);
    }
}

// int fov=55;       //  Field of view (for perspective)
// double asp=1;     //  Aspect ratio
// double dim=30.0;   //  Size of world
// /*
//  *  GLUT calls this routine when the window is resized
//  */
// void reshape(int width,int height)
// {
//    //  Ratio of the width to the height of the window
//    asp = (height>0) ? (double)width/height : 1;
//    //  Set the viewport to the entire window
//    glViewport(0,0, RES*width,RES*height);
//    //  Set projection
//    Project(fov,asp,dim);
// }

// /*
//  *  GLUT calls this routine when the window is resized
//  */
// int zh=0;         //  Azimuth of light
// void idle()
// {
//    //  Elapsed time in seconds
//    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
//    zh = fmod(90*t,360.0);
//    //  Tell GLUT it is necessary to redisplay the scene
//    glutPostRedisplay();
// }

//
void timer(int value) {
    glutPostRedisplay();
}

void idle() {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsedTime = currentTime - previousTime;

    if (elapsedTime < timePerFrame) {
        // Sleep for remaining time
        int sleepTime = timePerFrame - elapsedTime;
        glutTimerFunc(sleepTime, timer, 0);
    } else {
        previousTime = currentTime;
        glutPostRedisplay(); // Request to redraw the scene
    }
}

int main(int argc, char** argv) {
    promptForPlayerName();

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

    // Main Screen
    glutDisplayFunc(showMain ? drawButtonScreen : display);

    // 
    // glutReshapeFunc(reshape);

    // Arrow key callbacks
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);

    // Keyboard callbacks
    glutKeyboardFunc(handleKeys);
    glutKeyboardUpFunc(handleKeysUp);

    // Mouse callbacks
    glutMouseFunc(mouseButtonCallback);
    
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
    BMPtexture6 = loadTexture("./assets/flagstone.bmp");
    BMPtexture7 = loadTexture("./assets/wooden_crate.bmp");

    // setRunnerPoseList();
    addItemsToMapList();
    addObstaclesToMapList();
    
    previousTime = glutGet(GLUT_ELAPSED_TIME);
    glutIdleFunc(idle);

    // // Initialize mutex
    // pthread_mutex_init(&mutex, NULL);

    glutMainLoop();

    // // If the thread is running, join it
    // if (rrtStarThreadRunning) {
    //     pthread_join(rrtStarThread, NULL);
    // }

    // // Destroy mutex before exiting
    // pthread_mutex_destroy(&mutex);

    // Cleanup FreeType resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return 0;
}
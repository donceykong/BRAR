// Doncey Albin
// final executable
// Fall 2023, Computer Graphics, CU Boulder

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
// #include <pthread.h>

// Local includes
// #include "GameModes.h"           // 1. EASY
#include "miscObjects.h"            // 2. EASY - just add to draw.h/draw.c
#include "robot.h"                  // 5. MEDIUM - Make 3 source, keep one header. Add robotArm/legs to draw.h and make drawArm.c, drawLegs.c???
#include "mapManager.h"             // 7. HARD - merge in keyUpdate as a controller? rename to controller?
#include "groundPlane.h"            // 4. EASY - Add to draw.h lib? maybe make a drawGround.c file
#include "views.h"                  // 3. EASY
#include "keyUpdate.h"              // 6. HARD - merge with mapMan? rename to controller?

// fixed headers
// #include "keys.h"
#include "RRTStar.h"
#include "matrixMath.h"
#include "CSCIx229.h"
#include "screenInfo.h"
#include "textureUtils.h"
// #include "draw.h"        // isnt used here...
#include "lighting.h"    

// // OpenMP header
// #include <omp.h>

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

// global lights array
LightArray lights;

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
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPOT_DIRECTION);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glEnable(GL_COLOR_MATERIAL);
    
    updateViewRobot(&lights);
    displayView();
    // setupLighting();

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
    getYPosition(&chaserRobot);
    displayView();

    if (mapCenterUpdated) {
        resetLighting(mapCenter, &lights);
        mapCenterUpdated = false;
    }
    updateLighting(lightsEnabled, spotlightsEnabled, &lights);

    updateTimeCrunch(&lights); 

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glEnable(GL_COLOR_MATERIAL);
    // float white[] = {1,1,1,1};
    // float Emission[]  = {0.0,0.0,0.01*0,1.0};
    // glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, 0.3);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    // glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

    drawGroundPlane(mapCenter);
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

bool doRRT = true;
int waypointInc = 1;
int doRRTInt = 0;
void displayRunner() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    // glEnable(GL_COLOR_MATERIAL);
    
    // set the view
    displayView();

    if (mapCenterUpdated) {
        printf("reseting lighting\n");
        resetLighting(mapCenter, &lights);
        mapCenterUpdated = false;
    }

    checkRobotCaptured();
    updateRunner(&lights);

    // glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    updateLighting(lightsEnabled, spotlightsEnabled, &lights);

    glPolygonMode(GL_FRONT, GL_FILL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    // Diffuse Material
    GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    // Specular Material
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    // Shininess
    GLfloat shininess = 120.0f;
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glEnable(GL_COLOR_MATERIAL);

    // updateLighting(lightsEnabled, spotlightsEnabled, &lights);
    drawGroundPlane(mapCenter);
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

    // RRT*     
    // if (chaserRobot.inCollision) {RRTSTAR_ACTIVE = true;}
    if (RRTSTAR_ACTIVE) {
        if (doRRT) {
            // printf("RRT*\n");
            rrtStarResult = NULL;
            double obstYawAngles[30];
            Vector3 obstPos[30], obstMinPos[30], obstMaxPos[30];
            for (int i=0; i<30; i++) {
                obstPos[i] = mapObstList[i].position;
                obstYawAngles[i] = mapObstList[i].yawAngle; 
                obstMinPos[i] = mapObstList[i].minPos;
                obstMaxPos[i] = mapObstList[i].maxPos;
            }
            setMapStateInfo(runnerRobot.position, chaserRobot.endEffectorPosition, obstPos, obstYawAngles, obstMinPos, obstMaxPos);
            rrtStarResult = rrtStar(1000);
            waypointInc = rrtStarResult->size - 1;
            // printf("rrtStarResult->goalReached: %d\n", rrtStarResult->goalReached);
            doRRT = false;
        }

        if (goalReached) {// && (runnerDist - goalDist) > -1.0) {
            doRRT = false;
            if (waypointInc > -1) {
                WaypointPosX = rrtStarResult->positions[waypointInc].x;
                WaypointPosZ = rrtStarResult->positions[waypointInc].z;
            
                glColor3d(1,0,0.5);
                glPushMatrix();
                glTranslatef(WaypointPosX, 2.0, WaypointPosZ);
                drawSphere(0.4, 3, 3);
                glPopMatrix();
                glColor3d(1,1,1);
                
                double dx = WaypointPosX - chaserRobot.endEffectorPosition.x;
                double dz = WaypointPosZ - chaserRobot.endEffectorPosition.z;
                double dist = sqrt(dx * dx + dz * dz);
                if (dist < 0.01) {
                    waypointInc--;
                }
            }
            else if (waypointInc == -1) {
                doRRT = true;
            }
            doRRTInt++;
        }
        else {
            doRRT = true;
        }

        if (RRTSTAR_TREE_SHOW) {
            displayRRTStarPath(rrtStarResult);
        }
        else {
            displayRRTStarPath(rrtStarResult);
        }
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
            glutPostRedisplay(); // Request to redraw the scene
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

    // initialize map
    initMap();

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
#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <stdlib.h>
#include <time.h>
#include "mapObjects.h"

double mapCenterX = 0.0;
double mapCenterZ = 0.0;
double mapRadius = 100.0;
double map_time =   0.0;

double objAbsorberX;
double objAbsorberY;
double objAbsorberZ;

// Create an array to hold 10 map objects
MapObject objectList[10];

MapObject randMapObj;
MapObject *nearestObj = &randMapObj;

time_t beginTime, currentTime;
double prevTime;
double remainingTime = 60.00;
double elapsedTime = 0.0;
double totalElapsedTime = 0.0;
double totalScore = 0.0;

double rewardDiminish = 1.0;   // No diminishing initially

void setObjAbsorberPos(double x, double y, double z) {
    objAbsorberX = x;
    objAbsorberY = y;
    objAbsorberZ = z;
}

void drawSemiCylinderEdgesMap(GLfloat radius, int segments, double percentFull) {
    glColor3f(1.0, 0.0, 0.0);  // Red color
    glLineWidth(4.0f);         // Set line width to 2.0 pixels
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);        // Center vertex
    for (int i = 0; i <= segments; i += 2) {
        GLfloat angle = -M_PI/2.0 + i * percentFull*2.0*M_PI / segments; 
        GLfloat z = -radius * sin(angle);
        GLfloat x = -radius * cos(angle);

        glNormal3f(x, 0, z);
        glVertex3f(x, 0, z);
    }
    glEnd();
}

void plotMapBorder () {
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    // Set up polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glTranslatef(mapCenterX, 1.0, mapCenterZ);
    drawSemiCylinderEdgesMap(mapRadius, 10000, 100.0);

    glDisable(GL_DEPTH_TEST);
    glPopMatrix();
}

void addObjectsToMapList() {
    srand(time(NULL));  // set rand generator seed
    for (int i = 0; i < 10; i++) {
        //get rand x, y, z within map bounds
        double lowerObjPosX = mapCenterX - mapRadius; // lower X bound
        double upperObjPosX = mapCenterX + mapRadius; // upper X bound
        double lowerObjPosZ = mapCenterZ - mapRadius; // lower Z bound
        double upperObjPosZ = mapCenterZ + mapRadius; // upper Z bound
        
        double randObjPosX = (double)rand() / (RAND_MAX / (upperObjPosX - lowerObjPosX)) + lowerObjPosX;
        double randObjPosZ = (double)rand() / (RAND_MAX / (upperObjPosZ - lowerObjPosZ)) + lowerObjPosZ;

        //get rand yaw
        double lowerObjYaw = 0.0;   // lower bound
        double upperObjYaw = 360.0; // upper bound
        
        double randObjYaw = (double)rand() / (RAND_MAX / (upperObjYaw - lowerObjYaw)) + lowerObjYaw;

        //get rand enum type
        int numEnums = 3; // Number of enumerators in objType, not including EMPTY
        enum objType randObjType = (enum objType)(rand() % numEnums);
        
        //set runner adjust and robot adjust based on type
        double runnerSpeedAdjust;
        double robotSpeedAdjust;
        double timeValue;
        switch (randObjType) {
            case PARALELLOGRAM:
                runnerSpeedAdjust = 1.0;
                robotSpeedAdjust  = 0.0;
                timeValue = 5.0;
                break;
            case SPHERE:
                runnerSpeedAdjust = 1.0;
                robotSpeedAdjust  = 0.0;
                timeValue = 5.0;
                break;
            case CUBE:
                runnerSpeedAdjust = -1.0;
                robotSpeedAdjust  = 0.0;
                break;
            default:
                runnerSpeedAdjust = 0.0;
                robotSpeedAdjust  = 0.0;
                timeValue = 5.0;
                //printf("    - Invalid map obj type.\n");
        }

        // Set ran values to obj struct
        MapObject mapObj;
        mapObj.type = randObjType;
        mapObj.posX = randObjPosX;
        mapObj.posY = (double)rand() / (RAND_MAX / 3.0) + 1.0;            // rand Y init pos between 0 and 3
        mapObj.posZ = randObjPosZ;
        mapObj.yawAngle = randObjYaw;
        mapObj.runnerSpeedAdjust = runnerSpeedAdjust;
        mapObj.robotSpeedAdjust = robotSpeedAdjust;
        mapObj.baseHeight = (double)rand() / (RAND_MAX / 1.0);     // rand Y min between 0 and 1
        mapObj.maxHeight = (double)rand() / (RAND_MAX / 3.0);      // rand Y max between 0 and 10
        mapObj.verticalSpeed = 1.0; //(double)rand() / (RAND_MAX / 4.0);   // rand Y velocity between 0 and 4
        mapObj.timeValue = timeValue;
        mapObj.state = AVAILABLE;
        mapObj.size = 2.0;

        objectList[i] = mapObj;
    }
}

void setNearest(int listIter) {
    double currentEucDistXYZ = getEulerDistanceXYZ(chaserPosX, chaserPosY, chaserPosZ, objectList[listIter].posX, objectList[listIter].posY, objectList[listIter].posZ);
    double nearestEucDistXYZ = getEulerDistanceXYZ(chaserPosX, chaserPosY, chaserPosZ, nearestObj->posX, nearestObj->posY, nearestObj->posZ);
    if (currentEucDistXYZ <= nearestEucDistXYZ) {
        nearestObj = &objectList[listIter];
    }
}

void plotMapObjects() {
    map_time += 0.005;
    //printf("Plotting Map Objects: \n");
    for (int i = 0; i < 10; i++) {
        // If Obj pos = runner pos, set runner adjust and robot adjust based on type
        if (objectList[i].type == EMPTY) {
            objectList[i].posX = -999999999.0;
            objectList[i].posY = -999999999.0;
            objectList[i].posZ = -999999999.0;
            continue;
        }
        else if (abs(objAbsorberX - objectList[i].posX) < 4.0 && abs(objAbsorberY - objectList[i].posY) < 1.0 && abs(objAbsorberZ - objectList[i].posZ) < 4.0) {
            objectList[i].state = COLLECTED;
            runnerSpeed += objectList[i].runnerSpeedAdjust;
            chaserSpeed += objectList[i].robotSpeedAdjust;

            if (remainingTime > 0) {
                if (totalElapsedTime >= 10.0) {
                    rewardDiminish = rewardDiminish*0.99;
                    beginTime = time(NULL);
                }
                remainingTime += objectList[i].timeValue*rewardDiminish;
                totalScore += objectList[i].timeValue*rewardDiminish;
            }

            if (runnerSpeed < 0.0) {
                runnerSpeed = 0.0;
            }
            if (chaserSpeed < 0.0) {
                chaserSpeed = 0.0;
            }
        }

        // Update vertical position based on a sine wave
        objectList[i].posY = objectList[i].baseHeight + objectList[i].maxHeight + objectList[i].maxHeight * sin(objectList[i].verticalSpeed * map_time);

        enum objType currentObjType = objectList[i].type;
        double currentObjPosX = objectList[i].posX;
        double currentObjPosY = objectList[i].posY;
        double currentObjPosZ = objectList[i].posZ;

        setNearest(i);

        if (objectList[i].state == COLLECTED && objectList[i].size < 10.0) {
            objectList[i].size += 1.0;
        }
        else if (objectList[i].state == COLLECTED && objectList[i].size >= 10.0) {
            objectList[i].type = EMPTY;
        }

        objectList[i].yawAngle += 1.0;
        double currentObjYawAngle = objectList[i].yawAngle;
        // Translate then rotate obj
        glPushMatrix();
        glTranslatef(currentObjPosX, currentObjPosY, currentObjPosZ);
        glRotatef((GLfloat)currentObjYawAngle, 0.0, 1.0, 0.0);
        // Draw shape based on rand enum type
        switch (currentObjType) {
            case PARALELLOGRAM:
                if (objectList[i].state == COLLECTED) {
                    glColor3f(0.8, 1.0, 0.8);
                }
                else {
                    glColor3f(0.0, 1.0, 0.0);
                }
                //BMPtexture = BMPtexture5;
                getParallelogram(objectList[i].size, objectList[i].size, objectList[i].size);
                break;
            case SPHERE:
                if (objectList[i].state == COLLECTED) {
                    glColor3f(0.8, 1.0, 0.8);
                }
                else {
                    glColor3f(0.0, 1.0, 1.0);
                }
                //BMPtexture = BMPtexture5;
                Sphere(objectList[i].size/2.0, 4, 4);
                break;
            case CUBE:
                if (objectList[i].state == COLLECTED) {
                    glColor3f(0.8, 1.0, 0.8);
                }
                else {
                    glColor3f(1.0, 0.0, 0.0);
                }
                //BMPtexture = BMPtexture5;
                getCube(objectList[i].size, objectList[i].size, objectList[i].size);
                break;
            case EMPTY:
                //printf("    - Map obj %d is EMPTY.\n", i);
                break;
            default:
            //printf("    - Invalid map obj type.\n");
        }
        glPopMatrix();
    }
}

void updateMapCenter () {
    double dist = getEulerDistanceXZ(mapCenterX, mapCenterZ, runnerPosX, runnerPosZ);
    if (dist > mapRadius) {
        // printf("Map center updated\n");
        mapCenterX = runnerPosX;
        mapCenterZ = runnerPosZ;
        addObjectsToMapList();
    }
    plotMapBorder();
    plotMapObjects();
    // printf("mapCenterX: %f, mapCenterZ: %f\n\n", mapCenterX, mapCenterZ);
}

void updateMapTimeCrunch () {
    double dist = getEulerDistanceXZ(mapCenterX, mapCenterZ, chaserPosX, chaserPosZ);
    if (dist > mapRadius) {
        // printf("Map center updated\n");
        mapCenterX = chaserPosX;
        mapCenterZ = chaserPosZ;
        addObjectsToMapList();
    }
    plotMapBorder();
    plotMapObjects();
    // printf("mapCenterX: %f, mapCenterZ: %f\n\n", mapCenterX, mapCenterZ);
}

#endif // MAP_MANAGER_H
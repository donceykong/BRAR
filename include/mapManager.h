#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <stdlib.h>
#include <time.h>

#include "mapObjects.h"

double mapCenterX = 0.0;
double mapCenterZ = 0.0;
double mapRadius = 100.0;

// Create an array to hold 10 map objects
MapObject objectList[100];

void drawSemiCylinderEdgesMap(GLfloat radius, int segments, double percentFull) {
    glColor3f(1.0, 0.0, 0.0);  // Red color

    glLineWidth(4.0f);          // Set line width to 2.0 pixels
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);  // Center vertex
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
    for (int i = 0; i < 100; i++) {
        //get rand x, y, z within map bounds
        //srand(time(NULL));  // set rand generator seed
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
        switch (randObjType) {
            case PARALELLOGRAM:
                runnerSpeedAdjust = 1.0;
                robotSpeedAdjust  = -1.0;
                break;
            case SPHERE:
                runnerSpeedAdjust = 1.0;
                robotSpeedAdjust  = 0.0;
                break;
            case CUBE:
                runnerSpeedAdjust = -1.0;
                robotSpeedAdjust  = 1.0;
                break;
            default:
                runnerSpeedAdjust = 0.0;
                robotSpeedAdjust  = 0.0;
                //printf("    - Invalid map obj type.\n");
        }

        // Set ran values to obj struct
        MapObject mapObj;
        mapObj.type = randObjType;
        mapObj.posX = randObjPosX;
        mapObj.posY = 0.0;
        mapObj.posZ = randObjPosZ;
        mapObj.yawAngle = randObjYaw;
        mapObj.runnerSpeedAdjust = runnerSpeedAdjust;
        mapObj.robotSpeedAdjust = robotSpeedAdjust;

        objectList[i] = mapObj;
    }
}

void plotMapObjects() {
    //printf("Plotting Map Objects: \n");
    for (int i = 0; i < 100; i++) {
        // If Obj pos = runner pos, set runner adjust and robot adjust based on type
        if (abs(runnerPosX - objectList[i].posX) < 0.1 & abs(runnerPosZ - objectList[i].posZ) < 0.1) {
            objectList[i].type = (enum objType)(4);
            objectList[i].posX = -999999999.0;
            objectList[i].posZ = -999999999.0;
            runnerSpeed += objectList[i].runnerSpeedAdjust;
            monsterRobotSpeed += objectList[i].robotSpeedAdjust;
        }

        enum objType currentObjType = objectList[i].type;
        double currentObjPosX = objectList[i].posX;
        double currentObjPosY = objectList[i].posY;
        double currentObjPosZ = objectList[i].posZ;
        double currentObjYawAngle = objectList[i].yawAngle;

        // Translate then rotate obj
        glPushMatrix();
        glTranslatef(currentObjPosX, currentObjPosY, currentObjPosZ);
        glRotatef((GLfloat)currentObjYawAngle, 0.0, 1.0, 0.0);
        // Draw shape based on rand enum type
        switch (currentObjType) {
            case PARALELLOGRAM:
                //printf("    - Map obj %d is a PARALELLOGRAM.\n", i);
                glColor3f(0.0, 1.0, 0.0);       // face color
                //BMPtexture = BMPtexture5;
                getParallelogram(1.0, 1.0, 1.0);// Draw parallelogram
                break;
            case SPHERE:
                //printf("    - Map obj %d is a SPHERE.\n", i);
                glColor3f(0.0, 1.0, 1.0);       // face color
                //BMPtexture = BMPtexture5;
                Sphere(1.0, 4, 4);              // Draw a sphere
                break;
            case CUBE:
                //printf("    - Map obj %d is a CUBE.\n", i);
                glColor3f(1.0, 0.0, 0.0);        // face color
                //BMPtexture = BMPtexture5;
                getCube(1.0, 1.0, 1.0);
                break;
            case EMPTY:
                //printf("    - Map obj %d is EMPTY.\n", i);
                break;
            default:
                //printf("    - Invalid map obj type.\n");
        }
        glPopMatrix();
    }
    //printf("\n");
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

#endif // MAP_MANAGER_H
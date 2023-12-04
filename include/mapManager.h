#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <stdlib.h>
#include <time.h>
#include "mapObjects.h"
#include "collisionDetection.h"

double mapCenterX = 0.0;
double mapCenterZ = 0.0;
double mapRadius = 100.0;
double map_time =   0.0;

double objAbsorberX;
double objAbsorberY;
double objAbsorberZ;

bool chaserInCollision = false;
bool runnerInCollision = false;

// Array to hold 10 map items
MapItem mapItemList[10];

// Array to hold 5 map obstacles
MapObstacle mapObstList[5];

MapItem randMapItem;
MapItem *nearestMapItem = &randMapItem;

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

void addObstaclesToMapList() {
    srand(time(NULL));  // set rand generator seed
    for (int i = 0; i < 5; i++) {
        //get rand x, y, z within map bounds
        double lowerObstPosX = mapCenterX - mapRadius; // lower X bound
        double lowerObstPosZ = mapCenterZ - mapRadius; // lower Z bound
        
        double randObstPosX = (double)rand() / (RAND_MAX / mapRadius) + lowerObstPosX;
        double randObstPosZ = (double)rand() / (RAND_MAX / mapRadius) + lowerObstPosZ;

        //get rand yaw
        double lowerObstYaw = 0.0;   // lower bound
        double upperObstYaw = 360.0; // upper bound
        
        double randObstYaw = (double)rand() / (RAND_MAX / (upperObstYaw - lowerObstYaw)) + lowerObstYaw;
        
        //get rand enum type
        int numEnums = 1; // Number of enumerators in objType, not including EMPTY
        enum mapObstacleType randObstType = (enum mapObstacleType)(rand() % numEnums);

        // Set ran values to obj struct
        MapObstacle mapObstacle;
        mapObstacle.type = randObstType;
        mapObstacle.position.x = randObstPosX;
        mapObstacle.position.y = 5.0;
        mapObstacle.position.z = randObstPosZ;
        mapObstacle.yawAngle = randObstYaw;
        mapObstacle.width = 10.0;
        mapObstacle.height = 10.0;
        mapObstacle.depth = 0.5;
        setObstacleBounds(&mapObstacle);

        mapObstList[i] = mapObstacle;
    }
}

void plotMapObstacles() {
    glEnable(GL_DEPTH_TEST);
    chaserInCollision = false;
    runnerInCollision = false;
    for (int i = 0; i < 5; i++) {
        bool chaserInCollisionCurr = detect_collision(mapObstList[i], chaserPosX, chaserPosY, chaserPosZ);
        bool runnerInCollisionCurr = detect_collision(mapObstList[i], runnerPosX, runnerPosY, runnerPosZ);
        chaserInCollision += chaserInCollisionCurr; //detect_collision(mapObstList[i], chaserPosX, chaserPosY, chaserPosZ);
        runnerInCollision += runnerInCollisionCurr; //detect_collision(mapObstList[i], runnerPosX, runnerPosY, runnerPosZ);

        enum mapObstacleType currentMapObstType = mapObstList[i].type;
        double currentMapObstPosX = mapObstList[i].position.x;
        double currentMapObstPosY = mapObstList[i].position.y;
        double currentMapObstPosZ = mapObstList[i].position.z;
        //mapObstList[i].yawAngle += 1.0;
        double currentObstYawAngle = mapObstList[i].yawAngle;

        // Translate then rotate obj
        glPushMatrix();
        glTranslatef(currentMapObstPosX, currentMapObstPosY, currentMapObstPosZ);
        //glRotatef((GLfloat)currentObstYawAngle, 0.0, 1.0, 0.0);
        // Draw shape based on rand enum type
        switch (currentMapObstType) {
            case WALL:
                if (chaserInCollisionCurr || runnerInCollisionCurr) {
                    glColor3f(1.0, 0.0, 0.0);
                }
                else {
                    glColor3f(1.0, 1.0, 1.0);
                }
                BMPtexture = BMPtexture5;
                getCuboid(mapObstList[i].width, mapObstList[i].height, mapObstList[i].depth);
                break;
            default:
        }
        glPopMatrix();
    }
    glDisable(GL_DEPTH_TEST);
}

void addItemsToMapList() {
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
        enum mapItemType randObjType = (enum mapItemType)(rand() % numEnums);
        
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
        MapItem mapItem;
        mapItem.type = randObjType;
        mapItem.position.x = randObjPosX;
        mapItem.position.y = (double)rand() / (RAND_MAX / 3.0) + 1.0;            // rand Y init pos between 0 and 3
        mapItem.position.z = randObjPosZ;
        mapItem.yawAngle = randObjYaw;
        mapItem.runnerSpeedAdjust = runnerSpeedAdjust;
        mapItem.robotSpeedAdjust = robotSpeedAdjust;
        mapItem.baseHeight = (double)rand() / (RAND_MAX / 1.0);     // rand Y min between 0 and 1
        mapItem.maxHeight = (double)rand() / (RAND_MAX / 3.0);      // rand Y max between 0 and 10
        mapItem.velocity.y = 1.0; //(double)rand() / (RAND_MAX / 4.0);   // rand Y velocity between 0 and 4
        mapItem.timeValue = timeValue;
        mapItem.state = AVAILABLE;
        mapItem.size = 2.0;

        mapItemList[i] = mapItem;
    }
}

void setNearest(int listIter) {
    double currentEucDistXYZ = getEulerDistanceXYZ(chaserPosX, chaserPosY, chaserPosZ, mapItemList[listIter].position.x, mapItemList[listIter].position.y, mapItemList[listIter].position.z);
    double nearestEucDistXYZ = getEulerDistanceXYZ(chaserPosX, chaserPosY, chaserPosZ, nearestMapItem->position.x, nearestMapItem->position.y, nearestMapItem->position.z);
    if (currentEucDistXYZ <= nearestEucDistXYZ) {
        nearestMapItem = &mapItemList[listIter];
    }
}

void plotMapItems() {
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    map_time += 0.005;
    //printf("Plotting Map Objects: \n");
    for (int i = 0; i < 10; i++) {
        // If Obj pos = runner pos, set runner adjust and robot adjust based on type
        if (mapItemList[i].type == EMPTY) {
            mapItemList[i].position.x = -999999999.0;
            mapItemList[i].position.y = -999999999.0;
            mapItemList[i].position.z = -999999999.0;
            continue;
        }
        else if (abs(objAbsorberX - mapItemList[i].position.x) < 4.0 && abs(objAbsorberY - mapItemList[i].position.y) < 1.0 && abs(objAbsorberZ - mapItemList[i].position.z) < 4.0) {
            mapItemList[i].state = COLLECTED;
            runnerSpeed += mapItemList[i].runnerSpeedAdjust;
            chaserSpeed += mapItemList[i].robotSpeedAdjust;

            if (remainingTime > 0) {
                if (totalElapsedTime >= 10.0) {
                    rewardDiminish = rewardDiminish*0.99;
                    beginTime = time(NULL);
                }
                remainingTime += mapItemList[i].timeValue*rewardDiminish;
                totalScore += mapItemList[i].timeValue*rewardDiminish;
            }

            if (runnerSpeed < 0.0) {
                runnerSpeed = 0.0;
            }
            if (chaserSpeed < 0.0) {
                chaserSpeed = 0.0;
            }
        }

        // Update vertical position based on a sine wave
        mapItemList[i].position.y = mapItemList[i].baseHeight + mapItemList[i].maxHeight + mapItemList[i].maxHeight * sin(mapItemList[i].velocity.y * map_time);

        enum mapItemType currentMapItemType = mapItemList[i].type;
        double currentMapItemPosX = mapItemList[i].position.x;
        double currentMapItemPosY = mapItemList[i].position.y;
        double currentMapItemPosZ = mapItemList[i].position.z;

        setNearest(i);

        if (mapItemList[i].state == COLLECTED && mapItemList[i].size < 10.0) {
            mapItemList[i].size += 1.0;
        }
        else if (mapItemList[i].state == COLLECTED && mapItemList[i].size >= 10.0) {
            mapItemList[i].type = EMPTY;
        }

        mapItemList[i].yawAngle += 1.0;
        double currentObjYawAngle = mapItemList[i].yawAngle;
        // Translate then rotate obj
        glPushMatrix();
        glTranslatef(currentMapItemPosX, currentMapItemPosY, currentMapItemPosZ);
        glRotatef((GLfloat)currentObjYawAngle, 0.0, 1.0, 0.0);
        // Draw shape based on rand enum type
        switch (currentMapItemType) {
            case PARALELLOGRAM:
                if (mapItemList[i].state == COLLECTED) {
                    glColor3f(0.8, 1.0, 0.8);
                }
                else {
                    glColor3f(0.0, 1.0, 0.0);
                }
                //BMPtexture = BMPtexture5;
                getParallelogram(mapItemList[i].size, mapItemList[i].size, mapItemList[i].size);
                break;
            case SPHERE:
                if (mapItemList[i].state == COLLECTED) {
                    glColor3f(0.8, 1.0, 0.8);
                }
                else {
                    glColor3f(0.0, 1.0, 1.0);
                }
                //BMPtexture = BMPtexture5;
                Sphere(mapItemList[i].size/2.0, 4, 4);
                break;
            case CUBE:
                if (mapItemList[i].state == COLLECTED) {
                    glColor3f(0.8, 1.0, 0.8);
                }
                else {
                    glColor3f(1.0, 0.0, 0.0);
                }
                //BMPtexture = BMPtexture5;
                getCuboid(mapItemList[i].size, mapItemList[i].size, mapItemList[i].size);
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

void updateMapCenter (double robotPosX, double robotPosZ) {
    double dist = getEulerDistanceXZ(mapCenterX, mapCenterZ, robotPosX, robotPosZ);
    if (dist > mapRadius) {
        // printf("Map center updated\n");
        mapCenterX = robotPosX;
        mapCenterZ = robotPosZ;
        addItemsToMapList();
        addObstaclesToMapList();
    }
    plotMapBorder();
    plotMapItems();
    plotMapObstacles(); 
    // printf("mapCenterX: %f, mapCenterZ: %f\n\n", mapCenterX, mapCenterZ);
}

#endif // MAP_MANAGER_H
#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <stdlib.h>
#include <time.h>
#include "robot.h"
#include "matrixMath.h"
#include "draw.h"
#include "textureUtils.h"
#include "mapObjects.h"
#include "collision.h"
#include "game.h"

extern bool mapCenterUpdated;
extern Vector3 mapCenter;

extern double mapRadius;
extern double map_time;

extern double objAbsorberX;
extern double objAbsorberY;
extern double objAbsorberZ;

// Array to hold 10 map items
extern MapItem mapItemList[10];

// Array to hold 10 map obstacles
extern int numObstacles;
extern MapObstacle mapObstList[30];

extern MapItem *nearestMapItem;

extern time_t beginTime, currentTime;
extern double prevTime;
extern double remainingTime;
extern double elapsedTime;
extern double totalElapsedTime;
extern double totalScore;                   //Change to: double totalScoreTimeCrunch = 0.0;

extern double totalScoreRunner;
extern double rewardDiminish;   // No diminishing initially

void setObstacleBounds(MapObstacle *obstacle);

void setObjAbsorberPos(double x, double y, double z);

void drawSemiCylinderEdgesMap(GLfloat radius, int segments, double percentFull);

void plotMapBorder ();

bool isFarEnough(double x1, double z1, double x2, double z2, double minDist);

void addObstaclesToMapList();

void checkCollision ();

void plotMapObstacles ();

void addItemsToMapList();

void setNearest(int listIter);

void plotMapItems();

void updateMapCenter (double robotPosX, double robotPosZ);

void initMap ();

#endif // MAP_MANAGER_H
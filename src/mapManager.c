// Doncey Albin
// MapManager lib

#include "mapManager.h"

// Robot structs - Move to better spot?
RobotStruct runnerRobot;
RobotStruct chaserRobot;
double WaypointPosX;
double WaypointPosZ;                //Change to: double totalScoreTimeCrunch = 0.0;

bool mapCenterUpdated;
Vector3 mapCenter;
double mapRadius = 100.0;
double map_time =   0.0;

double objAbsorberX;
double objAbsorberY;
double objAbsorberZ;

// Array to hold 10 map items
MapItem mapItemList[10];

// Array to hold 10 map obstacles
int numObstacles = 30;
MapObstacle mapObstList[30];

MapItem randMapItem;
MapItem *nearestMapItem = &randMapItem;

time_t beginTime, currentTime;
double prevTime;
double remainingTime = 60.00;
double elapsedTime = 0.0;
double totalElapsedTime = 0.0;
double totalScore = 0.0;            //Change to: double totalScoreTimeCrunch = 0.0;

double totalScoreRunner = 0.0;      //
double rewardDiminish = 1.0;        // No diminishing initially

void setObstacleBounds(MapObstacle *obstacle) {
    // Matrix4x4 minPosXObject;
    // Matrix4x4 maxPosXObject;
    // Matrix4x4 minPosZObject;
    // Matrix4x4 maxPosZObject;

    if (obstacle->width == 0.0 || obstacle->height == 0.0 || obstacle->depth == 0.0) {
        printf("OBSTACLE HAS DIMENSION WITH 0 LENGTH! \n");
    }
    else {
        obstacle->minPos.x = (obstacle->position.x - obstacle->width / 2.0);
        obstacle->maxPos.x = (obstacle->position.x + obstacle->width / 2.0);

        obstacle->minPos.y = obstacle->position.y - obstacle->height / 2.0;
        obstacle->maxPos.y = obstacle->position.y + obstacle->height / 2.0;

        obstacle->minPos.z = (obstacle->position.z - obstacle->depth / 2.0);
        obstacle->maxPos.z = (obstacle->position.z + obstacle->depth / 2.0);

        // // // NOW ROTATE ABOUT obstacleYawRad
        // Matrix4x4 transformationMatrix = identityMatrix;
        // transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(obstacle->position.x, obstacle->position.y, obstacle->position.z));
        // transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(obstacle->yawAngle, 0.0, 1.0, 0.0));

        // minPosXObject = multiplyMatrix(transformationMatrix, translationMatrix(-obstacle->width/2, 0.0, 0.0));
        // maxPosXObject = multiplyMatrix(transformationMatrix, translationMatrix (obstacle->width/2, 0.0, 0.0));

        // minPosZObject = multiplyMatrix(transformationMatrix, translationMatrix(0.0, -obstacle->depth/2, 0.0));
        // maxPosZObject = multiplyMatrix(transformationMatrix, translationMatrix(0.0,  obstacle->depth/2, 0.0));
    }

    // glColor3f(1, 0, 0); 
    // // minX
    // glPushMatrix();
    // glTranslatef(extractPosition(minPosXObject).x, extractPosition(minPosXObject).y, extractPosition(minPosXObject).z);
    // Sphere(1.0, 10, 10); 
    // glPopMatrix();

    // // maxX
    // glPushMatrix();
    // glTranslatef(extractPosition(maxPosXObject).x, extractPosition(maxPosXObject).y, extractPosition(maxPosXObject).z);
    // Sphere(1.0, 10, 10); 
    // glPopMatrix();
    // glColor3f(1, 1, 1); 
    // obstacle->showEasy = true;
}

void setObjAbsorberPos(double x, double y, double z) {
    objAbsorberX = x;
    objAbsorberY = y;
    objAbsorberZ = z;
}

void drawSemiCylinderEdgesMap(GLfloat radius, int segments, double percentFull) {
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);        // Center vertex
    for (int i = 0; i <= segments; i += 2) {
        GLfloat angle = PI/2.0 + i * percentFull*2.0*M_PI / segments; 
        GLfloat z = -radius * sin(angle);
        GLfloat x = -radius * cos(angle);

        glNormal3f(x, 0, z);
        glVertex3f(x, 0, z);
    }
    glEnd();
}

void plotMapBorder () {
    glPushMatrix();
    glTranslatef(mapCenter.x, 1.0, mapCenter.z);
    drawSemiCylinderEdgesMap(mapRadius, 10000, 100.0);
    glPopMatrix();
}

bool isFarEnough(double x1, double z1, double x2, double z2, double minDist) {
    double dx = x1 - x2;
    double dz = z1 - z2;
    return (dx * dx + dz * dz) >= minDist * minDist;
}

void addObstaclesToMapList() {
    srand(time(NULL));  // set rand generator seed
    double minDist = sqrt(200);
    for (int i = 0; i < numObstacles; i++) {
        bool positionValid;
        double randObstPosX, randObstPosZ;

        do {
            positionValid = true;

            // Generate random position as before
            double mapDiameter = 2.0 * mapRadius;
            randObstPosX = mapDiameter*((double)rand() / RAND_MAX - 0.5) + mapCenter.x;
            randObstPosZ = mapDiameter*((double)rand() / RAND_MAX - 0.5) + mapCenter.z;

            // Check distance from all previously placed obstacles
            for (int j = 0; j < i; j++) {
                if (!isFarEnough(randObstPosX, randObstPosZ, mapObstList[j].position.x, mapObstList[j].position.z, minDist)) {
                    positionValid = false;
                    break;
                }
            }
            // Check distance from objAbsorberX, objAbsorberZ
            if (!isFarEnough(randObstPosX, randObstPosZ, objAbsorberX, objAbsorberZ, minDist)) {
                positionValid = false;
            }
        } while (!positionValid);

        //get rand yaw
        double lowerObstYaw = 0.0;   // lower bound
        double upperObstYaw = 360.0; // upper bound
        
        double randObstYaw = (double)rand() / (RAND_MAX / (upperObstYaw - lowerObstYaw)) + lowerObstYaw;
        
        //get rand enum type
        int numEnums = 2; // Number of enumerators in objType, not including EMPTY
        enum mapObstacleType randObstType = (enum mapObstacleType)(rand() % numEnums);

        // Set ran values to obj struct
        MapObstacle mapObstacle;
        mapObstacle.showEasy = false;
        mapObstacle.type = randObstType;
        mapObstacle.position.x = randObstPosX;
        mapObstacle.position.y = 5.0;
        mapObstacle.position.z = randObstPosZ;
        mapObstacle.yawAngle = randObstYaw;
        mapObstacle.width = 10.0;
        mapObstacle.height = 10.0;
        if (mapObstacle.type == BOX) {
            mapObstacle.depth = 10.0;
        }
        else {
            mapObstacle.depth = 2.0;
        }
        setObstacleBounds(&mapObstacle);

        mapObstList[i] = mapObstacle;
    }
}

void checkCollision () {
    chaserRobot.inCollision = false;
    runnerRobot.inCollision = false;
    for (int i = 0; i < numObstacles; i++) {
        chaserRobot.inCollision += detect_collision_AABB_TRANS(mapObstList[i], chaserRobot.endEffectorPosition.x, chaserRobot.endEffectorPosition.y, chaserRobot.endEffectorPosition.z);
        runnerRobot.inCollision += detect_collision_AABB_TRANS(mapObstList[i], runnerRobot.position.x, runnerRobot.position.y, runnerRobot.position.z);
    }
}

void plotMapObstacles () {
    chaserRobot.inCollision = false;
    runnerRobot.inCollision = false;
    for (int i = 0; i < numObstacles; i++) {
        bool chaserInCollisionCurr = detect_collision_AABB_TRANS(mapObstList[i], chaserRobot.endEffectorPosition.x, chaserRobot.endEffectorPosition.y, chaserRobot.endEffectorPosition.z);
        bool runnerInCollisionCurr = detect_collision_AABB_TRANS(mapObstList[i], runnerRobot.position.x, runnerRobot.position.y, runnerRobot.position.z);
        chaserRobot.inCollision += chaserInCollisionCurr; //detect_collision(mapObstList[i], chaserRobot.position.x, chaserRobot.position.y, chaserRobot.position.z);
        runnerRobot.inCollision += runnerInCollisionCurr; //detect_collision(mapObstList[i], runnerRobot.position.x, runnerRobot.position.y, runnerRobot.position.z);

        enum mapObstacleType currentMapObstType = mapObstList[i].type;
        double currentMapObstPosX = mapObstList[i].position.x;
        double currentMapObstPosY = mapObstList[i].position.y;
        double currentMapObstPosZ = mapObstList[i].position.z;
        //mapObstList[i].yawAngle += 1.0;
        setObstacleBounds(&mapObstList[i]);
        
        double currentObstYawAngle = mapObstList[i].yawAngle;

        // Translate then rotate obj
        glPushMatrix();
        glTranslatef(currentMapObstPosX, currentMapObstPosY, currentMapObstPosZ);
        glRotatef((GLfloat)currentObstYawAngle, 0.0, 1.0, 0.0);
        // Draw shape based on rand enum type
        switch (currentMapObstType) {
            case BOX:
                if (chaserInCollisionCurr || runnerInCollisionCurr) {
                    glColor3f(1.0, 0.0, 0.0);
                }
                else {
                    glColor3f(1.0, 1.0, 1.0);
                }
                BMPtexture = BMPtexture7;
                drawCuboid(mapObstList[i].width, mapObstList[i].height, mapObstList[i].depth);
                break;
            case WALL:
                if (chaserInCollisionCurr || runnerInCollisionCurr) {
                    glColor3f(1.0, 0.0, 0.0);
                }
                else {
                    glColor3f(1.0, 1.0, 1.0);
                }
                BMPtexture = BMPtexture6;
                drawCuboid(mapObstList[i].width, mapObstList[i].height, mapObstList[i].depth);
                break;
        }
        glPopMatrix();
    }
}

void addItemsToMapList() {
    srand(time(NULL));  // set rand generator seed
    double minDist = sqrt(200);
    for (int i = 0; i < 10; i++) {
        bool positionValid;
        double randObjPosX, randObjPosZ;
        do {
            positionValid = true;

            // Generate random position as before
            double mapDiameter = 2.0 * mapRadius;
            randObjPosX = mapDiameter*((double)rand() / RAND_MAX - 0.5) + mapCenter.x;
            randObjPosZ = mapDiameter*((double)rand() / RAND_MAX - 0.5) + mapCenter.z;

            // Check distance from all previously placed obstacles
            for (int j = 0; j < 30; j++) {
                if (!isFarEnough(randObjPosX, randObjPosZ, mapObstList[j].position.x, mapObstList[j].position.z, minDist)) {
                    positionValid = false;
                    break;
                }
            }
            // Check distance from all previously placed items
            for (int j = 0; j < i; j++) {
                if (!isFarEnough(randObjPosX, randObjPosZ, mapItemList[j].position.x, mapItemList[j].position.z, minDist)) {
                    positionValid = false;
                    break;
                }
            }
            // Check distance from objAbsorberX, objAbsorberZ
            if (!isFarEnough(randObjPosX, randObjPosZ, objAbsorberX, objAbsorberZ, minDist)) {
                positionValid = false;
            }
        } while (!positionValid);

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
                timeValue = 1.0;
                break;
            case SPHERE:
                runnerSpeedAdjust = 1.0;
                robotSpeedAdjust  = 0.0;
                timeValue = 1.0;
                break;
            case CUBE:
                runnerSpeedAdjust = -1.0;
                robotSpeedAdjust  = 0.0;
                timeValue = -1.0;
                break;
            default:
                runnerSpeedAdjust = 0.0;
                robotSpeedAdjust  = 0.0;
                timeValue = 1.0;
                //printf("    - Invalid map obj type.\n");
        }

        // Set ran values to obj struct
        MapItem mapItem;
        mapItem.type = randObjType;
        mapItem.position.x = randObjPosX;
        mapItem.position.y = (double)rand() / (RAND_MAX / 3.0);            // rand Y init pos between 0 and 3
        mapItem.position.z = randObjPosZ;
        mapItem.yawAngle = randObjYaw;
        mapItem.runnerSpeedAdjust = runnerSpeedAdjust;
        mapItem.robotSpeedAdjust = robotSpeedAdjust;
        mapItem.baseHeight = (double)rand() / (RAND_MAX / 1.0) + 0.5;   // rand Y min between 0.5 and 1.5
        mapItem.maxHeight = (double)rand() / (RAND_MAX / 3.0);          // rand Y max between 0 and 3
        mapItem.velocity.y = 1.0; //(double)rand() / (RAND_MAX / 4.0);   // rand Y velocity between 0 and 4
        mapItem.timeValue = timeValue;
        mapItem.state = AVAILABLE;
        mapItem.size = 2.0;

        mapItemList[i] = mapItem;
    }
}

void setNearest(int listIter) {
    double currentEucDistXYZ = getEulerDistanceXYZ(chaserRobot.position.x, chaserRobot.position.y, chaserRobot.position.z, mapItemList[listIter].position.x, mapItemList[listIter].position.y, mapItemList[listIter].position.z);
    double nearestEucDistXYZ = getEulerDistanceXYZ(chaserRobot.position.x, chaserRobot.position.y, chaserRobot.position.z, nearestMapItem->position.x, nearestMapItem->position.y, nearestMapItem->position.z);
    if (currentEucDistXYZ <= nearestEucDistXYZ) {
        nearestMapItem = &mapItemList[listIter];
    }
}

void plotMapItems() {
    map_time += 0.005;
    for (int i = 0; i < 10; i++) {
        // If Obj pos = runner pos, set runner adjust and robot adjust based on type
        if (mapItemList[i].type == EMPTY) {
            mapItemList[i].position.x = -999999999.0;
            mapItemList[i].position.y = -999999999.0;
            mapItemList[i].position.z = -999999999.0;
            continue;
        }
        else if (mapItemList[i].state != COLLECTED && abs(objAbsorberX - mapItemList[i].position.x) < 4.0 && abs(objAbsorberY - mapItemList[i].position.y) < 1.0 && abs(objAbsorberZ - mapItemList[i].position.z) < 4.0) {
            mapItemList[i].state = COLLECTED;

            if (remainingTime >= 0 && GAME_MODE == TIME_CRUNCH) {
                rewardDiminish = rewardDiminish*0.99;
                remainingTime += mapItemList[i].timeValue*rewardDiminish;
                totalScore += mapItemList[i].timeValue*rewardDiminish;
            }
            else if (!runnerRobot.captured && GAME_MODE == RUNNER) {
                //runnerRobot.speedAdjust += mapItemList[i].runnerSpeedAdjust;
                runnerRobot.speedAdjust = runnerRobot.speedAdjust*1.00;             // RUNNER GETS SLOWER
                chaserRobot.speedAdjust = chaserRobot.speedAdjust*1.00;             // RUNNER GETS FASTER AT A LARGER RATE THAN RUNNER GETS SLOW
                totalScoreRunner += mapItemList[i].runnerSpeedAdjust;   // TOTAL RUNNER SCORE
            }

            if (runnerRobot.speedAdjust < 0.0) {
                runnerRobot.speedAdjust = 0.0;
            }
            if (chaserRobot.speedAdjust < 0.0) {
                chaserRobot.speedAdjust = 0.0;
            }
        }

        if (remainingTime <= 0.0) {
            remainingTime = 0.0;
        }

        // Update vertical position based on a sine wave
        mapItemList[i].position.y = mapItemList[i].baseHeight + mapItemList[i].maxHeight + mapItemList[i].maxHeight * sin(mapItemList[i].velocity.y * map_time);
        // printf("mapItem.position.y: %f\n", mapItemList[i].position.y);

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
                BMPtexture = BMPtexture5;
                drawParallelogram(mapItemList[i].size, mapItemList[i].size, mapItemList[i].size);
                break;
            case SPHERE:
                if (mapItemList[i].state == COLLECTED) {
                    glColor3f(0.8, 1.0, 0.8);
                }
                else {
                    glColor3f(0.0, 1.0, 1.0);
                }
                BMPtexture = BMPtexture5;
                drawSphere(mapItemList[i].size/2.0, 4, 4);
                break;
            case CUBE:
                if (mapItemList[i].state == COLLECTED) {
                    glColor3f(0.8, 1.0, 0.8);
                }
                else {
                    glColor3f(1.0, 0.0, 0.0);
                }
                BMPtexture = BMPtexture5;
                drawCuboid(mapItemList[i].size, mapItemList[i].size, mapItemList[i].size);
                break;
            case EMPTY:
                break;
        }
        glPopMatrix();
    }
}

void updateMapCenter (double robotPosX, double robotPosZ) {
    double dist = getEulerDistanceXZ(mapCenter.x, mapCenter.z, robotPosX, robotPosZ);
    if (dist > mapRadius) {
        mapCenter.x = robotPosX;
        mapCenter.z = robotPosZ;
        
        addObstaclesToMapList();
        addItemsToMapList();

        mapCenterUpdated = true;
    }
}

void initMap () {
    mapCenter.x = 0.0;
    mapCenter.y = 1.0;
    mapCenter.z = 0.0;

    addObstaclesToMapList();
    addItemsToMapList();
    
    mapCenterUpdated = true;
}
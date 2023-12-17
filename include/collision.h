/*
 *      COLLISION DETECTION
*/
/************************************************/

// External
#include <stdbool.h>
#include <stdio.h>

// Internal
#include "mapObjects.h"
#include "matrixMath.h"

bool detect_collisionAABB(MapObstacle obstacle, double robotX, double robotY, double robotZ);

bool detect_collision_AABB_TRANS(MapObstacle obstacle, double robotX, double robotY, double robotZ);
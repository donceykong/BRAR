#ifndef MAP_OBJECTS_H
#define MAP_OBJECTS_H

// External 
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Internal
#include "matrixMath.h"

/*
 *      MAP ITEMS
*/
enum mapItemType {
    PARALELLOGRAM,  // 0
    SPHERE,         // 1
    CUBE,           // 2
    EMPTY           // 3
};

enum mapItemState {
    AVAILABLE,      // 0
    COLLECTED       // 1
};

typedef struct {
    enum mapItemType type;
    enum mapItemState state;

    Vector3 position;
    Vector3 velocity;
    GLfloat yawAngle;
    double size;
    double runnerSpeedAdjust;
    double robotSpeedAdjust;
    double timeValue;
    double maxHeight;           // Maximum height for oscillation
    double baseHeight;          // Base height (starting height)
} MapItem;

/*
 *      MAP OBSTACLES
*/
enum mapObstacleType {
    WALL,  // 0
    BOX
};

typedef struct {
    enum mapObstacleType type;
    Vector3 position;
    GLfloat yawAngle;
    float width, height, depth;    // x, y, z dims, respectively.
    Vector3 minPos, maxPos;
    bool showEasy;
} MapObstacle;

#endif // MAP_OBJECTS
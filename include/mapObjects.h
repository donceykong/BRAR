#ifndef MAP_OBJECTS_H
#define MAP_OBJECTS_H

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
    WALL  // 0
};

typedef struct {
    enum mapObstacleType type;
    Vector3 position;
    GLfloat yawAngle;
    double width, height, depth;    // x, y, z dims, respectively.
    Vector3 minPos, maxPos;
} MapObstacle;

void setObstacleBounds(MapObstacle *obstacle) {
    if (obstacle->width == 0.0 || obstacle->height == 0.0 || obstacle->depth == 0.0) {
        printf("OBSTACLE HAS DIMENSION WITH 0 LENGTH! \n");
    }
    else {
        obstacle->minPos.x = obstacle->position.x - obstacle->width / 2.0;
        obstacle->maxPos.x = obstacle->position.x + obstacle->width / 2.0;

        obstacle->minPos.y = obstacle->position.y - obstacle->height / 2.0;
        obstacle->maxPos.y = obstacle->position.y + obstacle->height / 2.0;

        obstacle->minPos.z = obstacle->position.z - obstacle->depth / 2.0;
        obstacle->maxPos.z = obstacle->position.z + obstacle->depth / 2.0;
    }
}

#endif // MAP_OBJECTS_H
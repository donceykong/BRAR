#ifndef MAP_OBJECTS_H
#define MAP_OBJECTS_H

enum mapItemType {
    PARALELLOGRAM,  // 0
    SPHERE,         // 1
    CUBE,           // 2
    EMPTY           // 3
};

enum mapItemState {
    AVAILABLE,      // 0
    COLLECTED           // 1
};

typedef struct
{
    double x;
    double y;
    double z;
} ObjectPosition;

typedef struct {
    enum mapItemType type;
    enum mapItemState state;

    double size;

    double runnerSpeedAdjust;
    double robotSpeedAdjust;
    double timeValue;

    ObjectPosition position;

    GLfloat yawAngle;

    double verticalSpeed; // Speed of vertical movement
    double maxHeight;     // Maximum height for oscillation
    double baseHeight;    // Base height (starting height)
    
} MapItem;

// // Map obstacles
// enum obstacleType {
//     PARALELLOGRAM,  // 0
//     SPHERE,         // 1
//     CUBE,           // 2
//     EMPTY           // 3
// };

// typedef struct {
//     enum obstacleType type;

//     double posX;
//     double posY;
//     double posZ;
//     GLfloat yawAngle;

// } MapObstacle;

#endif // MAP_OBJECTS_H
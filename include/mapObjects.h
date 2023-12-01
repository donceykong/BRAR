#ifndef MAP_OBJECTS_H
#define MAP_OBJECTS_H

enum objType {
    PARALELLOGRAM,  // 0
    SPHERE,         // 1
    CUBE,           // 2
    EMPTY           // 3
};

enum objState {
    AVAILABLE,      // 0
    COLLECTED           // 1
};

typedef struct {
    enum objType type;
    enum objState state;

    double size;

    double runnerSpeedAdjust;
    double robotSpeedAdjust;
    double timeValue;

    double posX;
    double posY;
    double posZ;
    GLfloat yawAngle;

    double verticalSpeed; // Speed of vertical movement
    double maxHeight;     // Maximum height for oscillation
    double baseHeight;    // Base height (starting height)
    
} MapObject;

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
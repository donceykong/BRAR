#ifndef MAP_OBJECTS_H
#define MAP_OBJECTS_H

enum objType {
    PARALELLOGRAM,  // 0
    SPHERE,         // 1
    CUBE,           // 2
    EMPTY           // 3
};

typedef struct {
    enum objType type;

    double runnerSpeedAdjust;
    double robotSpeedAdjust;

    double posX;
    double posY;
    double posZ;
    GLfloat yawAngle;

    double verticalSpeed; // Speed of vertical movement
    double maxHeight;     // Maximum height for oscillation
    double baseHeight;    // Base height (starting height)
    
} MapObject;

#endif // MAP_OBJECTS_H
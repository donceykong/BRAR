#ifndef MAP_OBJECTS_H
#define MAP_OBJECTS_H

#import "designShapes.h"
#import "matrixMath.h"

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

void setObstacleBounds(MapObstacle *obstacle) {
    Matrix4x4 minPosXObject;
    Matrix4x4 maxPosXObject;
    Matrix4x4 minPosZObject;
    Matrix4x4 maxPosZObject;

    if (obstacle->width == 0.0 || obstacle->height == 0.0 || obstacle->depth == 0.0) {
        printf("OBSTACLE HAS DIMENSION WITH 0 LENGTH! \n");
    }
    else {
        double obstacleYawRad = obstacle->yawAngle * PI / 180.0;

        obstacle->minPos.x = (obstacle->position.x - obstacle->width / 2.0);
        obstacle->maxPos.x = (obstacle->position.x + obstacle->width / 2.0);

        obstacle->minPos.y = obstacle->position.y - obstacle->height / 2.0;
        obstacle->maxPos.y = obstacle->position.y + obstacle->height / 2.0;

        obstacle->minPos.z = (obstacle->position.z - obstacle->depth / 2.0);
        obstacle->maxPos.z = (obstacle->position.z + obstacle->depth / 2.0);

        // // NOW ROTATE ABOUT obstacleYawRad
        Matrix4x4 transformationMatrix = identityMatrix;
        transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(obstacle->position.x, obstacle->position.y, obstacle->position.z));
        transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(obstacle->yawAngle, 0.0, 1.0, 0.0));

        minPosXObject = multiplyMatrix(transformationMatrix, translationMatrix(-obstacle->width/2, 0.0, 0.0));
        maxPosXObject = multiplyMatrix(transformationMatrix, translationMatrix (obstacle->width/2, 0.0, 0.0));

        minPosZObject = multiplyMatrix(transformationMatrix, translationMatrix(0.0, -obstacle->depth/2, 0.0));
        maxPosZObject = multiplyMatrix(transformationMatrix, translationMatrix(0.0,  obstacle->depth/2, 0.0));
    }

    if (obstacle->showEasy) {
        glColor3f(0.5, 1, 0.5); 
        // minX
        glPushMatrix();
        glTranslatef(obstacle->position.x, obstacle->position.y, obstacle->position.z);
        glRotatef(obstacle->yawAngle, 0, 1, 0);
        glTranslatef(-obstacle->width/2, 0.0, 0.0);
        Sphere(2.0, 10, 10); 
        glPopMatrix();

        // maxX
        glPushMatrix();
        glTranslatef(obstacle->position.x, obstacle->position.y, obstacle->position.z);
        glRotatef(obstacle->yawAngle, 0, 1, 0);
        glTranslatef(obstacle->width/2, 0.0, 0.0);
        Sphere(2.0, 10, 10); 
        glPopMatrix();
        glColor3f(1, 1, 1); 
        obstacle->showEasy = false;
    }
    else {
        glColor3f(1, 0, 0); 

        // minX
        glPushMatrix();
        glTranslatef(extractPosition(minPosXObject).x, extractPosition(minPosXObject).y, extractPosition(minPosXObject).z);
        Sphere(1.0, 10, 10); 
        glPopMatrix();

        // maxX
        glPushMatrix();
        glTranslatef(extractPosition(maxPosXObject).x, extractPosition(maxPosXObject).y, extractPosition(maxPosXObject).z);
        Sphere(1.0, 10, 10); 
        glPopMatrix();
        glColor3f(1, 1, 1); 
        obstacle->showEasy = true;
    }
}

#endif // MAP_OBJECTS_H
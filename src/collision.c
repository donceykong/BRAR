// Doncey Albin
// Collision lib

#include "collision.h"

bool detect_collisionAABB(MapObstacle obstacle, double robotX, double robotY, double robotZ) {
    if (obstacle.type == WALL || obstacle.type == BOX) {
        return  (obstacle.minPos.x < (robotX + 1.0) && obstacle.maxPos.x > (robotX - 1.0)) &&
                (obstacle.minPos.y < (robotY + 1.0) && obstacle.maxPos.y > (robotY - 1.0)) &&
                (obstacle.minPos.z < (robotZ + 1.0) && obstacle.maxPos.z > (robotZ - 1.0));
    }
    else {
        printf("OBSTACLE DOES NOT HAVE TYPE - NO COLLISION DETECTED.\n");
        return false;
    }
}

bool detect_collision_AABB_TRANS(MapObstacle obstacle, double robotX, double robotY, double robotZ) {
    if (obstacle.type == WALL || obstacle.type == BOX) {
        // Convert robot's position to the rotated frame of the obstacle
        double cosYaw = cos(obstacle.yawAngle * PI / 180);
        double sinYaw = sin(obstacle.yawAngle * PI / 180);

        double transformedRobotX = cosYaw * (robotX - obstacle.position.x) - sinYaw * (robotZ - obstacle.position.z) + obstacle.position.x;
        double transformedRobotZ = sinYaw * (robotX - obstacle.position.x) + cosYaw * (robotZ - obstacle.position.z) + obstacle.position.z;

        // AABB collision check with transformed coordinates
        return  (obstacle.minPos.x <= (transformedRobotX + 2.0) && obstacle.maxPos.x >= (transformedRobotX - 2.0)) &&
                (obstacle.minPos.y <= (robotY + 2.0) && obstacle.maxPos.y >= (robotY - 2.0)) &&
                (obstacle.minPos.z <= (transformedRobotZ + 2.0) && obstacle.maxPos.z >= (transformedRobotZ - 2.0));
    }
    else {
        printf("OBSTACLE DOES NOT HAVE TYPE - NO COLLISION DETECTED.\n");
        return false;
    }
}
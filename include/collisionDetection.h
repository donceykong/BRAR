/*
 *      COLLISION DETECTION
*/
/************************************************/

#include "mapObjects.h"
#include "matrixMath.h"

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
        return  (obstacle.minPos.x < (transformedRobotX + 2.0) && obstacle.maxPos.x > (transformedRobotX - 2.0)) &&
                (obstacle.minPos.y < robotY && obstacle.maxPos.y > robotY) &&
                (obstacle.minPos.z < (transformedRobotZ + 2.0) && obstacle.maxPos.z > (transformedRobotZ - 2.0));
    }
    else {
        printf("OBSTACLE DOES NOT HAVE TYPE - NO COLLISION DETECTED.\n");
        return false;
    }
}

bool detect_collision_RRT(MapObstacle obstacle, double robotX, double robotY, double robotZ) {
    if (obstacle.type == WALL || obstacle.type == BOX) {
        // Convert robot's position to the rotated frame of the obstacle
        double cosYaw = cos(obstacle.yawAngle * PI / 180);
        double sinYaw = sin(obstacle.yawAngle * PI / 180);

        double transformedRobotX = cosYaw * (robotX - obstacle.position.x) - sinYaw * (robotZ - obstacle.position.z) + obstacle.position.x;
        double transformedRobotZ = sinYaw * (robotX - obstacle.position.x) + cosYaw * (robotZ - obstacle.position.z) + obstacle.position.z;

        // AABB collision check with transformed coordinates
        return  (obstacle.minPos.x < (transformedRobotX) && obstacle.maxPos.x > (transformedRobotX)) &&
                (obstacle.minPos.y < robotY && obstacle.maxPos.y > robotY) &&
                (obstacle.minPos.z < (transformedRobotZ) && obstacle.maxPos.z > (transformedRobotZ));
    }
    else {
        printf("OBSTACLE DOES NOT HAVE TYPE - NO COLLISION DETECTED.\n");
        return false;
    }
}

// bool detect_collisionOBB(MapObstacle obstacle, double robotX, double robotY, double robotZ) {
// }

/*
SPHERICAL COLLISION

// Define a struct to represent a circle
typedef struct {
  float x;
  float y;
  float z;
  float radius;
} Sphere;

// Check if two circles collide
int collide(Circle c1, Circle c2) {
  // Calculate the distance between the centers of the circles
  float dx = c1.x - c2.x;
  float dy = c1.y - c2.y;
  float dz = c1.z - c2.z;
  float distance = sqrt(dx * dx + dy * dy + dz * dz);

  // If the distance is less than the sum of the radii, the circles collide
  return distance < c1.radius + c2.radius;
}

int main() {
  // Create two circles
  Sphere c1 = {10, 10, 10, 5};
  Sphere c2 = {20, 20, 10, 5};

  // Check if the circles collide
  if (collide(c1, c2)) {
    printf("The circles collide!\n");
  } else {
    printf("The circles do not collide.\n");
  }

  return 0;
}

*/
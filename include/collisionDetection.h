/*
 *      COLLISION DETECTION
*/
/************************************************/

#include "mapObjects.h"

bool detect_collision(MapObstacle obstacle, double robotX, double robotY, double robotZ) {
    if (obstacle.type == WALL) {
        // return (a.min.x < b.max.x && a.max.x > b.min.x) &&
        //         (a.min.y < b.max.y && a.max.y > b.min.y) &&
        //         (a.min.z < b.max.z && a.max.z > b.min.z);
        return (obstacle.minPos.x < (robotX + 2.0) && obstacle.maxPos.x > (robotX - 2.0)) &&
                (obstacle.minPos.y < (robotY + 2.0) && obstacle.maxPos.y > (robotY - 2.0)) &&
                (obstacle.minPos.z < (robotZ + 2.0) && obstacle.maxPos.z > (robotZ - 2.0));
    }
    else {
        printf("OBSTACLE DOES NOT HAVE TYPE - NO COLLISION DETECTED.\n");
        return false;
    }
}

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
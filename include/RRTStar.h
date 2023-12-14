#ifndef RRTSTAR_H
#define RRTSTAR_H

// Extern
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>  // For rand() and srand()
#include <math.h>    // For cos(), sin(), and M_PI
#include <time.h>    // For time()
#include <stdbool.h>
#include <stdio.h>

#include "matrixMath.h"

extern bool goalReached;
extern bool useMapArea;     // bool for deciding on area for generating random node
extern bool displayRRTSearch;

typedef struct {
    Vector3 searchCenter;
    double searchRad;

    Vector3 position;
} randXYZRadius;

typedef struct {
    Vector3 position;
    double yawAngle;
    Vector3 minPos, maxPos;
} RRTObject; 

typedef struct {
    Vector3 start;
    Vector3 goal;
    Vector3 center;
    RRTObject obst[30];  // Vec3 array of obstacle positions
} mapStateInfo;

typedef struct {
    Vector3* positions;  // Dynamic array to store positions
    int size;            // Number of positions stored
    int capacity;        // Capacity of the array
} Path;

typedef struct ChildNode {
    struct Node* child;     // Current child node.
    struct ChildNode* next; // Next oldest sibling.
} ChildNode;

typedef struct Node {
    Vector3 position;       // XYZ position of node. (Only XZ used)
    double cost;            // Cost of node: sum of euc distances from parents until reaching start pos.
    struct Node* parent;    // Each node can have exactly one parent.
    ChildNode* children;    // Each node can have many children. Children are a linked list, first-in is at top.
} Node;

typedef struct {
    Node* root;             // Pointer to the root node.
    int treeSize;           // Number of nodes in tree.
} nodeTree;

void setMapStateInfo(Vector3 runnerPosition, Vector3 chaserPosition, Vector3 obstaclePositions[30], 
                    double obstacleYawAngles[30], Vector3 obstacleMinPositions[30], Vector3 obstacleMaxPositions[30], Vector3 mapCenter);

// To display path of RRT*
void displayRRTStarPath(Path* path);

// Main RRT* function
Path* rrtStar(int maxIterations);

#endif // RRTSTAR_H
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

typedef struct {
    Vector3 position;
    double yawAngle;
    Vector3 minPos, maxPos;
} RRTObject; 

typedef struct {
    Vector3 start;
    Vector3 goal;
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

double calculateDistance(Node* node1, Node* node2);
double calculateDistanceFromGoal(Node* node1, Vector3 goal);

// Function to initialize the path
Path* createPath(int initialCapacity);
void setMapStateInfo(Vector3 runnerPosition, Vector3 chaserPosition, Vector3 obstaclePositions[30], 
                    double obstacleYawAngles[30], Vector3 obstacleMinPositions[30], Vector3 obstacleMaxPositions[30]);

bool detect_collision_RRT(double nodeX, double nodeY, double nodeZ);

// Function to add a position to the path
void addPositionToPath(Path* path, Vector3 position);

// Function to backtrack from the goal node to the start node
Path* backtrackToStart(Node* goalNode);


// Function to create and initialize the node tree for RRT*.
nodeTree* initializeTree(double startX, double startZ);

// Turn XZ coords into a node and return pointer
Node* createNode(double x, double z);

// Function to retreive random node in map
Node* getRandomNode();

// Child node management
ChildNode* findChildNode(Node* parent, Node* child);

Node* getNextSibling(ChildNode* childNode);

Node* getFirstChild(Node* node);

void addChild(Node* parentNode, Node* childNode);

void freeChildNodes(Node* node);

// Function to check if the path between two nodes is collision-free.
bool nodesInCollision(Node* node1, Node* node2);

// Function to calculate cost of what a node will be, based on assigned parent
double calculateCost(Node* potentialParent, Node* newNode);

void findNearest(Node* currentNode, Node* targetNode, Node** nearestNode, double* minDistance);

// Function to find the nearest node in the tree to a given point.
Node* nearestNeighbor(nodeTree* tree, Node* randomNode);



// REMOVE
void drawNode(Node* node);

void drawEdge(Vector3 start, Vector3 end);



Node* steer(Node* nearest, Node* randomNode, double maxStepSize);

void findPotentialParents(Node* currentNode, Node* newNode, Node** bestParent, double* bestCost, double searchRadius);
void chooseParent(Node* newNode, Node* nearest, nodeTree* tree, double searchRadius);

void addNodeToTree(nodeTree* tree, Node* newNode);

// Function to rewire the tree around the new node if it provides a shorter path for its neighbors.
void rewireNodeIfCostLower(Node* nodeToCheck, Node* newNode, double searchRadius);

void rewireNodes(Node* currentNode, Node* newNode, double searchRadius);

void rewire(nodeTree* tree, Node* newNode, double searchRadius);

bool reachedGoal(Node* newNode, Node* goal, double goalThreshold);

void displayRRTStarPath(Path* path);

void displayRRTTreeRecursive(Node* node);

void displayRRTTree();

// Main RRT* function
Path* rrtStar(int maxIterations);

#endif // RRTSTAR_H
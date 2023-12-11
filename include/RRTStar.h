#ifndef RRTSTAR_H
#define RRTSTAR_H

// Extern
#include <stdlib.h>  // For rand() and srand()
#include <math.h>    // For cos(), sin(), and M_PI
#include <time.h>    // For time()

// Local
#include "matrixMath.h"
#include "mapManager.h"

// enum waypointState {
//     REACHED,        // 0
//     NOT_REACHED     // 1
// };

// typedef struct {
//     enum waypointState state;
//     Vector3 position;
//     struct Waypoint* parent;    // Pointer to the parent waypoint
// } Waypoint;
// waypoints* getWayPointList () {
// waypoint waypoints[100];
// }

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

double calculateDistance(Node* node1, Node* node2) {
    double dx = node1->position.x - node2->position.x;
    double dz = node1->position.z - node2->position.z;
    return sqrt(dx * dx + dz * dz);                     // only interested in x and z
}

// Function to initialize the path
Path* createPath(int initialCapacity) {
    Path* path = (Path*)malloc(sizeof(Path));
    if (path != NULL) {
        path->positions = (Vector3*)malloc(initialCapacity * sizeof(Vector3));
        path->size = 0;
        path->capacity = initialCapacity;
    }
    return path;
}

// Function to add a position to the path
void addPositionToPath(Path* path, Vector3 position) {
    if (path->size >= path->capacity) {
        // Resize the array if needed
        int newCapacity = path->capacity * 2;
        Vector3* newPositions = (Vector3*)realloc(path->positions, newCapacity * sizeof(Vector3));
        if (newPositions != NULL) {
            path->positions = newPositions;
            path->capacity = newCapacity;
        } else {
            // Handle memory allocation failure
            return;
        }
    }
    path->positions[path->size] = position;
    path->size++;
}

// Function to backtrack from the goal node to the start node
Path* backtrackToStart(Node* goalNode) {
    int initialCapacity = 10; // Starting size of the path array
    Path* path = createPath(initialCapacity);
    if (path == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    Node* currentNode = goalNode;
    while (currentNode != NULL) {
        addPositionToPath(path, currentNode->position);
        currentNode = currentNode->parent; // Move to the parent node
    }

    return path;
}


/*
 * Function to create and initialize the node tree for RRT*.
 */
nodeTree* initializeTree(double startX, double startZ) {
    // Allocate memory for nodeTree
    nodeTree* nodes = (nodeTree*)malloc(sizeof(nodeTree));
    if (nodes == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    // Allocate memory for the root node
    nodes->root = (Node*)malloc(sizeof(Node));
    if (nodes->root == NULL) {
        // Handle memory allocation failure
        free(nodes);  // Free the previously allocated tree
        return NULL;
    }

    // Initialize the root node
    nodes->root->position.x = startX;   
    nodes->root->position.y = 2.0;          // Doesnt really matter (unused), but let's set anyways.
    nodes->root->position.z = startZ;
    nodes->root->cost       = 0.0;
    nodes->root->parent     = NULL;         // Root node has no parent
    nodes->root->children   = NULL;         // Root node has no children, yet
    nodes->treeSize         = 1;  // Tree starts with one node

    return nodes;
}

Node* createNode(double x, double z) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node != NULL) {
        node->position.x = x;
        node->position.y = 2.0; // Assuming y is constant or not used
        node->position.z = z;
        node->cost = 0.0;       // Initialize cost, adjust as necessary
        node->parent = NULL;    // No parent as this is a new node
        node->children = NULL;
    }
    // Handle memory allocation failure if needed
    return node;
}

double poseDiff;
Node* getRandomNode() {
    // Initialize random seed - usually done once at the beginning of the program
    //srand(time(NULL));

    // Generate a random angle and radius
    // double angle  = ((double)rand() / (double)RAND_MAX) * 2.0 * M_PI;
    // double radius = ((double)rand() / (double)RAND_MAX) * mapRadius;

    // Calculate x and z using polar coordinates
    // double x = mapCenterX + radius * cos(angle);
    // double z = mapCenterZ + radius * sin(angle);

    // Center gussing about robot positions
    poseDiff = 0.5*sqrt((runnerRobot.position.x-chaserRobot.position.x)*(runnerRobot.position.x-chaserRobot.position.x) + 
                    (runnerRobot.position.z-chaserRobot.position.z)*(runnerRobot.position.z-chaserRobot.position.z));
    // double midlinePoseX = -runnerRobot.position.x + (runnerRobot.position.x-chaserRobot.position.x)/2.0;
    // double midlinePoseZ = -runnerRobot.position.z + (runnerRobot.position.z-chaserRobot.position.z)/2.0;
    
    double angle  = ((double)rand() / (double)RAND_MAX) * 2.0 * M_PI;
    double radius = ((double)rand() / (double)RAND_MAX) * poseDiff;

    // Calculate x and z using polar coordinates
    double x = chaserRobot.position.x + (runnerRobot.position.x-chaserRobot.position.x)/2 + radius + cos(angle);//chaserRobot.position.x + radius * cos(angle);
    double z = chaserRobot.position.z + (runnerRobot.position.z-chaserRobot.position.z)/2 + radius + sin(angle); //chaserRobot.position.z + radius * sin(angle);

    // Create a new node
    Node* randomNode = (Node*)malloc(sizeof(Node));
    if (randomNode != NULL) {
        randomNode->position.x = x;
        randomNode->position.y = 2.0;  // As mentioned, y doesn't matter but set to 2.0
        randomNode->position.z = z;
        randomNode->cost = 0.0;        // Initialize cost, adjust as necessary
        randomNode->parent = NULL;     // No parent as it's a random node
    }

    return randomNode;
}

// Child node management
ChildNode* findChildNode(Node* parent, Node* child) {
    ChildNode* current = parent->children;
    while (current != NULL) {
        if (current->child == child) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // Child node not found
}

Node* getNextSibling(ChildNode* childNode) {
    if (childNode != NULL && childNode->next != NULL) {
        return childNode->next->child;
    }
    return NULL;  // No next sibling
}

Node* getFirstChild(Node* node) {
    if (node != NULL && node->children != NULL) {
        return node->children->child;
    }
    return NULL; // No children
}

void addChild(Node* parentNode, Node* childNode) {
    ChildNode* newChild = (ChildNode*)malloc(sizeof(ChildNode));
    if (newChild != NULL) {
        newChild->child = childNode;
        newChild->next  = parentNode->children;
        parentNode->children = newChild;
    }
    // TODO: Handle memory allocation failure if needed
}

void freeChildNodes(Node* node) {
    ChildNode* current = node->children;
    while (current != NULL) {
        ChildNode* next = current->next;
        free(current);
        current = next;
    }
}

// Function to check if the path between two nodes is collision-free.
bool nodesInCollision(Node* node1, Node* node2) {
    double dx = node2->position.x - node1->position.x;
    double dz = node2->position.z - node1->position.z;
    double distance = calculateDistance(node1, node2);
    double disc = 1.0;

    // Number of discretization steps based on distance and discretization length
    int steps = (int)(distance / disc);
    bool inCollision = false;

    for (int step = 0; step <= steps; step++) {
        // Calculate interpolated point
        double t = (double)step / (double)steps;
        double x = node1->position.x + t * dx;
        double z = node1->position.z + t * dz;

        // Check collision at the interpolated point
        for (int i = 0; i < 30; i++) {
            if (detect_collision_AABB_TRANS(mapObstList[i], x, 2.0, z)) {  // Assuming y = 2.0 as in your structure
                inCollision = true;
                break;
            }
        }

        if (inCollision) {
            break;
        }
    }

    return inCollision;
}

// Function to calculate cost of what a node will be, based on assigned parent
double calculateCost(Node* potentialParent, Node* newNode) {
    double distance = calculateDistance(potentialParent, newNode);
    return potentialParent->cost + distance;  // Total cost is parent's cost plus the distance to the new node
}

void findNearest(Node* currentNode, Node* targetNode, Node** nearestNode, double* minDistance) {
    if (currentNode == NULL) {
        return;
    }

    double distance = calculateDistance(currentNode, targetNode);
    if (distance < *minDistance) {
        *minDistance = distance;
        *nearestNode = currentNode;
    }

    // Traverse to the children of the current node
    Node* child = getFirstChild(currentNode);
    while (child != NULL) {
        findNearest(child, targetNode, nearestNode, minDistance);
        ChildNode* childWrapper = findChildNode(currentNode, child); // Find the ChildNode that corresponds to the 'child'
        if (childWrapper != NULL) {  // Ensure childWrapper is not NULL
            child = getNextSibling(childWrapper);
        } else {
            child = NULL;  // If childWrapper is NULL, there are no more siblings
        }
    }
}

// Function to find the nearest node in the tree to a given point.
Node* nearestNeighbor(nodeTree* tree, Node* randomNode) {
    Node* nearest = NULL;
    double minDistance = INFINITY;

    findNearest(tree->root, randomNode, &nearest, &minDistance);

    return nearest;
}

Node* steer(Node* nearest, Node* randomNode, double maxStepSize) {
    // Calculate the direction from nearest to randomNode
    double dx = nearest->position.x - nearest->position.x;
    double dz = nearest->position.z - nearest->position.z;
    double distance = sqrt(dx * dx + dz * dz);                    

    // If the distance is smaller than the step size, just return the random node
    if (distance < maxStepSize) {
        return createNode(randomNode->position.x, randomNode->position.z);
    }

    // Calculate a scaled direction to step towards the random node
    double scale    = maxStepSize / distance;
    double newX     = nearest->position.x + dx * scale;
    double newZ     = nearest->position.z + dz * scale;

    // Create and return the new node
    return createNode(newX, newZ);
}

void findPotentialParents(Node* currentNode, Node* newNode, Node** bestParent, double* bestCost, double searchRadius) {
    if (currentNode == NULL || newNode == NULL) {
        return;
    }

    double distance = calculateDistance(currentNode, newNode);
    if (distance < searchRadius) {
        if (!nodesInCollision(currentNode, newNode)) {
            double potentialCost = calculateCost(currentNode, newNode);
            if (potentialCost < *bestCost) {
                *bestParent = currentNode;
                *bestCost = potentialCost;
            }
        }
    }

    // Traverse to the children of the current node
    Node* child = getFirstChild(currentNode);
    while (child != NULL) {
        findPotentialParents(child, newNode, bestParent, bestCost, searchRadius);
        ChildNode* childWrapper = findChildNode(currentNode, child); // Find the ChildNode that corresponds to the 'child'
        if (childWrapper != NULL) {  // Ensure childWrapper is not NULL
            child = getNextSibling(childWrapper);
        } else {
            child = NULL;  // If childWrapper is NULL, there are no more siblings
        }
    }
}

void chooseParent(Node* newNode, Node* nearest, nodeTree* tree, double searchRadius) {
    newNode->parent = nearest;
    newNode->cost = calculateCost(nearest, newNode);
    
    Node* bestParent = nearest;  // Start with the nearest node as the current best parent
    double bestCost  = newNode->cost;  // Start with the cost from the nearest node

    findPotentialParents(tree->root, newNode, &bestParent, &bestCost, searchRadius);

    newNode->parent = bestParent; // Update to the best parent found
    newNode->cost = bestCost;     // Update to the best cost found
}

void addNodeToTree(nodeTree* tree, Node* newNode) {
    // TODO: Remove?
    if (tree == NULL || newNode == NULL) {
        return;  // Handle null tree or node
    }

    // Link the new node to its parent
    if (newNode->parent != NULL) {
        addChild(newNode->parent, newNode);
    }

    // Update the tree's metadata
    tree->treeSize++;
}

// Function to rewire the tree around the new node if it provides a shorter path for its neighbors.
void rewireNodeIfCostLower(Node* nodeToCheck, Node* newNode, double searchRadius) {
    if (nodeToCheck == NULL || newNode == NULL) {
        return;
    }

    double distance = calculateDistance(nodeToCheck, newNode);
    if (distance < searchRadius && !nodesInCollision(nodeToCheck, newNode)) {
        double potentialNewCost = newNode->cost + distance;
        if (potentialNewCost < nodeToCheck->cost) {
            nodeToCheck->parent = newNode;
            nodeToCheck->cost = potentialNewCost;
            // You might need to update the children's costs recursively as well
        }
    }
}

void rewireNodes(Node* currentNode, Node* newNode, double searchRadius) {
    if (currentNode == NULL || newNode == NULL) {
        return;
    }

    // Do not rewire the newNode or its direct children
    if (currentNode != newNode && (currentNode->parent == NULL || currentNode->parent != newNode)) {
        rewireNodeIfCostLower(currentNode, newNode, searchRadius);
    }

    // Traverse to the children of the current node
    Node* child = getFirstChild(currentNode);
    while (child != NULL) {
        rewireNodes(child, newNode, searchRadius);
        ChildNode* childWrapper = findChildNode(currentNode, child); // Find the ChildNode that corresponds to the 'child'
        if (childWrapper != NULL) {  // Ensure childWrapper is not NULL
            child = getNextSibling(childWrapper);
        } else {
            child = NULL;  // If childWrapper is NULL, there are no more siblings
        }
    }
}

void rewire(nodeTree* tree, Node* newNode, double searchRadius) {
    if (tree == NULL || newNode == NULL) {
        return;
    }

    // Traverse the tree to find nodes that might benefit from rewiring
    rewireNodes(tree->root, newNode, searchRadius);
}

bool reachedGoal(Node* newNode, Node* goal, double goalThreshold) {
    if (newNode == NULL || goal == NULL) {
        return false;  // Handle null nodes
    }
    double distance = calculateDistance(newNode, goal);
    return distance <= goalThreshold;
}

void displayRRTStarPath(Path* path) {
    if (path != NULL) {
        // Iterate through the path and print positions or use them as needed
        Vector3 pathPosPrev;
        pathPosPrev.x = path->positions[0].x;
        pathPosPrev.y = path->positions[0].y;
        pathPosPrev.z = path->positions[0].z;

        for (int i = 1; i < path->size; i++) {
            glPushMatrix();
            glTranslatef(path->positions[i].x, 2.0, path->positions[i].z);
            Sphere(0.5, 10, 10);
            glPopMatrix();

            drawRRTLine(pathPosPrev, path->positions[i]);
            //printf("Position: X: %f, Z: %f\n", path->positions[i].x, path->positions[i].z);
            
            pathPosPrev.x = path->positions[i].x;
            pathPosPrev.y = path->positions[i].y;
            pathPosPrev.z = path->positions[i].z;
        }
    }
}


Path* rrtStar(Vector3 startPosition, Vector3 goalPosition, int maxIterations) {
    Path* path = NULL;
    nodeTree* tree  = initializeTree(startPosition.x, startPosition.z);
    Node* goal = createNode(goalPosition.x, goalPosition.z); // Using the createNode function
    if (goal == NULL) {
        // Handle allocation error
        return;
    }

    bool goalReached = false;
    double goalThreshold = 0.5;
    double maxStepSize = 0.01;
    double parentSearchRad = 0.5;//*maxStepSize;
    double rewireSearchRad = 1.0;
    Node* newNode;
    Node* randomNode;
    int testGoal = 0;
    for (int i = 0; i < maxIterations; i++) {
        if (testGoal == 2) {
            randomNode = goal;
            testGoal = 0;  
        } else {
            randomNode = getRandomNode();                         // DONE
        }
        testGoal += 1;

        Node* nearest = nearestNeighbor(tree, randomNode);       // DONE
        newNode = steer(nearest, randomNode, maxStepSize*poseDiff); // DONE 

        if (!nodesInCollision(nearest, newNode)) {
            chooseParent(newNode, nearest, tree, parentSearchRad);  // Start with nearest node as best parent initially
            addNodeToTree(tree, newNode);                           // Add new node to the tree list
            rewire(tree, newNode, rewireSearchRad*poseDiff);                 // 
        }

        if (reachedGoal(newNode, goal, goalThreshold) && tree->treeSize > 1) {
            // Goal reached, construct the path and make Waypoint struct
            goalReached = true;
            break;
        }
    }

    if (goalReached) {
        // printf(" *GOAL REACHED!\n\n");
        path = backtrackToStart(newNode); // newNode is the node that reached the goal
        return path;
        // displayRRTStarPath();
        // free(path->positions);
        // free(path);
    }
}

#endif // RRTSTAR_H
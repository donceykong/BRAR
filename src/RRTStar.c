#include "RRTStar.h"

// Global Vars
mapStateInfo map;
int randStartCenter = 1;
double circleRad = 0.25;
Path* path = NULL;
nodeTree* tree;

double calculateDistance(Node* node1, Node* node2) {
    double dx = node1->position.x - node2->position.x;
    double dz = node1->position.z - node2->position.z;
    return sqrt(dx * dx + dz * dz);                     // only interested in x and z
}

double calculateDistanceFromGoal(Node* node1, Vector3 goal) {
    double dx = node1->position.x - goal.x;
    double dz = node1->position.z - goal.z;
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

void setMapStateInfo(Vector3 runnerPosition, Vector3 chaserPosition, Vector3 obstaclePositions[30], double obstacleYawAngles[30], Vector3 obstacleMinPositions[30], Vector3 obstacleMaxPositions[30], Vector3 mapCenter) {
    map.start = chaserPosition;
    map.goal  = runnerPosition;
    map.center = mapCenter;
    for (int i = 0; i < 30; i++) {
        map.obst[i].position = obstaclePositions[i];
        map.obst[i].yawAngle = obstacleYawAngles[i];
        map.obst[i].maxPos = obstacleMaxPositions[i];
        map.obst[i].minPos = obstacleMinPositions[i];
    }
}

bool detect_collision_RRT(double nodeX, double nodeY, double nodeZ) {
    bool inCollision = false;

    for (int i = 0; i < 30; i++) {
        double cosYaw = cos(map.obst[i].yawAngle * PI / 180);
        double sinYaw = sin(map.obst[i].yawAngle * PI / 180);

        double transformedNodeX = cosYaw * (nodeX - map.obst[i].position.x) - sinYaw * (nodeZ - map.obst[i].position.z) + map.obst[i].position.x;
        double transformedNodeZ = sinYaw * (nodeX - map.obst[i].position.x) + cosYaw * (nodeZ - map.obst[i].position.z) + map.obst[i].position.z;

        // AABB collision check with transformed coordinates
        inCollision +=  (map.obst[i].minPos.x < (transformedNodeX + 2.2) && map.obst[i].maxPos.x > (transformedNodeX - 2.2)) &&
                        (map.obst[i].minPos.y < nodeY && map.obst[i].maxPos.y > nodeY) &&
                        (map.obst[i].minPos.z < (transformedNodeZ + 2.2) && map.obst[i].maxPos.z > (transformedNodeZ - 2.2));
    }

    return inCollision;
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
    nodes->root->cost       = calculateDistanceFromGoal(nodes->root, map.goal);
    nodes->root->parent     = NULL;         // Root node has no parent
    nodes->root->children   = NULL;         // Root node has no children, yet
    nodes->treeSize         = 1;            // Tree starts with one node

    return nodes;
}

Node* createNode(double x, double z) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node != NULL) {
        node->position.x = x;
        node->position.y = 2.0; // Assuming y is constant or not used
        node->position.z = z;
        node->cost = 0;         // Initialize cost, adjust as necessary
        node->parent = NULL;    // No parent as this is a new node
        node->children = NULL;
    }
    // Handle memory allocation failure if needed
    return node;
}

randXYZRadius getRandXYZRadius () {
    randXYZRadius rrtRandXYZRadius;

    double angle  = ((double)rand() / (double)RAND_MAX) * 2.0 * M_PI;
    double radius;
    double x;
    double y = 4.0;  // constant
    double z;
    if (useMapArea) {
        // Generate a random angle and radius within map
        float mapRadius = 100.00;
        rrtRandXYZRadius.searchRad = mapRadius;
        radius = ((double)rand() / (double)RAND_MAX) * mapRadius;
        rrtRandXYZRadius.searchCenter.x  = map.center.x;
        rrtRandXYZRadius.searchCenter.y = 2.0;
        rrtRandXYZRadius.searchCenter.z = map.center.z;
        // Calculate x and z using polar coordinates
        x = map.center.x + radius * cos(angle);
        z = map.center.z + radius * sin(angle);
    }
    else {
        // Bound through circles traversing through robot positions
        double dx = map.goal.x-map.start.x;
        double dz = map.goal.z-map.start.z;
        double poseDiff = circleRad*sqrt(dx * dx + dz * dz);
        rrtRandXYZRadius.searchRad = poseDiff;
        radius = ((double)rand() / (double)RAND_MAX) * poseDiff;

        if (circleRad < 1.0) {
            circleRad = circleRad + 0.05;
        }
        // else {
        //     circleRad = 0.25;
        // }
        // Calculate x and z using polar coordinates
        if (randStartCenter == 1) {
            rrtRandXYZRadius.searchCenter.x = map.start.x;
            rrtRandXYZRadius.searchCenter.z = map.start.z;
            randStartCenter += 1;
        }
        else if (randStartCenter == 2) {
            rrtRandXYZRadius.searchCenter.x = map.start.x + dx/2;
            rrtRandXYZRadius.searchCenter.z = map.start.z + dz/2;
            randStartCenter += 1;
        }
        else {
            rrtRandXYZRadius.searchCenter.x = map.goal.x;
            rrtRandXYZRadius.searchCenter.z = map.goal.z;
            randStartCenter = 1;
        }
        rrtRandXYZRadius.searchCenter.y = 2.0;
        
        x = rrtRandXYZRadius.searchCenter.x + radius * cos(angle);
        z = rrtRandXYZRadius.searchCenter.z + radius * sin(angle);
    }
    
    rrtRandXYZRadius.position.x = x;
    rrtRandXYZRadius.position.y = y;
    rrtRandXYZRadius.position.z = z;

    return rrtRandXYZRadius;
}

void displaySearchBoundary (randXYZRadius rrtRandXYZRadius) {
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(rrtRandXYZRadius.searchCenter.x, rrtRandXYZRadius.searchCenter.y, rrtRandXYZRadius.searchCenter.z);
    glLineWidth(6.0f);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    for (int i = 0; i <= 100; i += 2) {
        GLfloat angle = PI/2.0 + i * 2.0*M_PI / 100; 
        GLfloat z = -rrtRandXYZRadius.searchRad * sin(angle);
        GLfloat x = -rrtRandXYZRadius.searchRad * cos(angle);
        glNormal3f(x, 0, z);
        glVertex3f(x, 0, z);
    }

    // Draw where random node is
    glColor3d(0,0,1);
    glPushMatrix();
    glTranslatef(rrtRandXYZRadius.position.x, 2.0, rrtRandXYZRadius.position.z);
    glutSolidSphere(0.1, 3, 3);
    glPopMatrix();
    glColor3d(1,1,1);

    glEnd();
    glPopMatrix();
    glColor3f(1, 1, 1);
}

Node* getRandomNode() {
    // Initialize random seed - usually done once at the beginning of the program
    srand(time(NULL));

    randXYZRadius rrtRandXYZRadius = getRandXYZRadius();

    // if (displayRRTSearch) {
    //     displaySearchBoundary(rrtRandXYZRadius);
    // }

    // Create a new node
    Node* randomNode = (Node*)malloc(sizeof(Node));
    if (randomNode != NULL) {
        randomNode->position.x = rrtRandXYZRadius.position.x;
        randomNode->position.y = rrtRandXYZRadius.position.y;  // y doesn't matter but set to 2.0
        randomNode->position.z = rrtRandXYZRadius.position.z;
        randomNode->cost = 0;
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
    double disc = 0.01;

    // Number of discretization steps based on distance and discretization length
    int steps = (int)(distance / disc);
    bool inCollision = false;

    for (int step = 0; step <= steps; step++) {
        // Calculate interpolated point
        double t = (double)step / (double)steps;
        double x = node1->position.x + t * dx;
        double z = node1->position.z + t * dz;

        inCollision += detect_collision_RRT(x, 2.0, z);

        if (inCollision) {
            break;
        }
    }

    return inCollision;
}

double calculateCost(Node* potentialParent, Node* newNode) {
    double distance = calculateDistance(potentialParent, newNode);
    double distanceFromGoal = calculateDistanceFromGoal(newNode, map.goal);
    return potentialParent->cost + distance + distanceFromGoal;  // Total cost is parent's cost plus the distance to the new node
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

Node* nearestNeighbor(nodeTree* tree, Node* randomNode) {
    Node* nearest = NULL;
    double minDistance = INFINITY;

    findNearest(tree->root, randomNode, &nearest, &minDistance);

    return nearest;
}

void drawNode(Node* node) {
    // Draw the node
    glPushMatrix();
    glTranslatef(node->position.x, node->position.y, node->position.z);
    glColor3f(1, 0, 0); // Set node color (e.g., red)
    glutSolidSphere(1.0, 10, 10); // Draw a small sphere to represent the node
    glPopMatrix();
}

void drawEdge(Vector3 start, Vector3 end) {
    // Draw an edge between two nodes
    glBegin(GL_LINES);
    glColor3f(0, 1, 0); // Set edge color (e.g., green)
    glVertex3f(start.x, start.y, start.z);
    glVertex3f(end.x, end.y, end.z);
    glEnd();
}

Node* steer(Node* nearest, Node* randomNode, double maxStepSize) {
    // Calculate the direction from nearest to randomNode
    double dx = randomNode->position.x - nearest->position.x;
    double dz = randomNode->position.z - nearest->position.z;
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
        if (childWrapper != NULL) {                                  // Ensure childWrapper is not NULL
            child = getNextSibling(childWrapper);
        } else {
            child = NULL;  // If childWrapper is NULL, there are no more siblings
        }
    }
}

void chooseParent(Node* newNode, Node* nearest, nodeTree* tree, double searchRadius) {
    newNode->parent = nearest;
    newNode->cost = calculateCost(nearest, newNode);
    
    Node* bestParent = nearest;         // Start with the nearest node as the current best parent
    double bestCost  = newNode->cost;   // Start with the cost from the nearest node

    findPotentialParents(tree->root, newNode, &bestParent, &bestCost, searchRadius);

    newNode->parent = bestParent;       // Update to the best parent found
    newNode->cost = bestCost;           // Update to the best cost found
}

void addNodeToTree(nodeTree* tree, Node* newNode) {
    if (tree == NULL || newNode == NULL) {
        return;  // Handle null tree or node
    }

    // Link the new node to its parent
    if (newNode->parent != NULL) {
        addChild(newNode->parent, newNode);
    }

    // Update the tree's size
    tree->treeSize++;
}

// Function to rewire the tree around the new node if it provides a shorter path for its neighbors.
void rewireNodeIfCostLower(Node* nodeToCheck, Node* newNode, double searchRadius) {
    if (nodeToCheck == NULL || newNode == NULL) {
        return;
    }

    double distance = calculateDistance(nodeToCheck, newNode);
    double distanceFromGoal = 4*calculateDistanceFromGoal(nodeToCheck, map.goal);
    if (distance < searchRadius && !nodesInCollision(nodeToCheck, newNode)) {
        double potentialNewCost = newNode->cost + distance + distanceFromGoal;
        if (potentialNewCost < nodeToCheck->cost) {
            nodeToCheck->parent = newNode;
            nodeToCheck->cost = potentialNewCost;
            // might need to update the children's costs recursively as well
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
            glColor3d(0,1,0);
            glPushMatrix();
            glTranslatef(path->positions[i].x, 2.0, path->positions[i].z);
            glutSolidSphere(0.1, 3, 3);
            glPopMatrix();
            glColor3d(1,1,1);

            drawEdge(pathPosPrev, path->positions[i]);
            
            pathPosPrev.x = path->positions[i].x;
            pathPosPrev.y = path->positions[i].y;
            pathPosPrev.z = path->positions[i].z;
        }
    }
}

void displayRRTTreeRecursive(Node* node) {
    if (node == NULL) return;

    // Draw the current node
    drawNode(node);

    // Draw an edge to its parent (if it has one)
    if (node->parent) {
        drawEdge(node->position, node->parent->position);
    }

    // Recursively draw children
    ChildNode* childNode = node->children;
    while (childNode != NULL) {
        displayRRTTreeRecursive(childNode->child);
        childNode = childNode->next;
    }
}

void displayRRTTree() {
    if (tree == NULL || tree->root == NULL) return;
    // Start the recursive display from the root
    displayRRTTreeRecursive(tree->root);
    glutPostRedisplay();
    glFlush();
    glutSwapBuffers();
}

// Path* allPaths = NULL;
bool goalReached;
Path* rrtStar(int maxIterations) {
    tree = initializeTree(map.start.x, map.start.z);
    Node* goal = createNode(map.goal.x, map.goal.z);

    goalReached = false;
    double goalThreshold = 1.0;
    double maxStepSize = 8.0;
    double parentSearchRad = 10;
    double rewireSearchRad = 20.0;
    Node* randomNode;
    Node* nearest;
    Node* newNode;
    int testGoal = 0;
    
    for (int i = 0; i < maxIterations; i++) {
        if (testGoal == 0) {
            circleRad = 0.25;
            randomNode = goal;
            testGoal = 20;  
        } else {
            randomNode = getRandomNode();
        }
        testGoal -= 1;

        nearest = nearestNeighbor(tree, randomNode);
        newNode = steer(nearest, randomNode, maxStepSize);
        glutPostRedisplay();
        glFlush();
        glutSwapBuffers();

        if (!nodesInCollision(nearest, newNode)) {
            chooseParent(newNode, nearest, tree, parentSearchRad);  // Start with nearest node as best parent initially
            addNodeToTree(tree, newNode);                           // Add new node to the tree list
            rewire(tree, newNode, rewireSearchRad);                 // 
            if (displayRRTSearch) {
                displayRRTTree();
            }
        }

        if (reachedGoal(newNode, goal, goalThreshold)) {
            // Goal reached, construct the path and make Waypoint struct
            // printf("WHAT");
            goalReached = true;
            break;
        }
    }

    if (goalReached) {
        path = backtrackToStart(newNode); // newNode is the node that reached the goal (may be the goal)
        // free(path->positions);
        // free(path);
    }
    else {
        // printf(" *GOAL NOT REACHED!\n\n");
    }
    return path;
}
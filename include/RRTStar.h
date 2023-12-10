#ifndef RRTSTAR_H
#define RRTSTAR_H

enum waypointState {
    REACHED,        // 0
    NOT_REACHED     // 1
};

typedef struct {
    enum waypointState state;
    Vector3 position;
    GLfloat yawAngle;
} Waypoint;

typedef struct Node {
    Vector3 position;       // Position of the node
    GLfloat yawAngle;       //
    double cost;            //
    struct Node* parent;    // Pointer to the parent node
} Node;

typedef struct {
    Node* root;             // Pointer to the root node
    int treeSize;           //
} nodeTree;

waypoint waypoints[100];

/*
 * Function to create and initialize the node tree for RRT*.
 */
Tree* initializeTree(double startX, double startY) {
    // Allocate memory and initialize the tree with the start node
}

// Function to generate a random node within the workspace.
Node* getRandomNode() {
    // Generate a random node considering the boundaries of the workspace
}

//  Function to find the nearest node in the tree to a given point.
Node* nearestNeighbor(Tree* tree, Node* randomNode) {
    // Find the nearest node in the tree to the randomNode
}

// Function to create a new node in the direction from nearest to random node, within a certain step size.
Node* steer(Node* nearest, Node* randomNode, double stepSize) {
    // Create a new node towards randomNode from nearest
}

// Function to check if the path between two nodes is collision-free.
bool checkCollision(Node* node1, Node* node2) {
    // Implement collision checking logic
}

// Function to choose the best parent for a new node considering the cost.
void chooseParent(Node* newNode, Node* nearest, Tree* tree) {
    // Choose the best parent for newNode
}

// Function to rewire the tree around the new node if it provides a shorter path for its neighbors.
void rewire(Tree* tree, Node* newNode) {
    // Rewire the tree considering the new node
}

void addNodeToTree(Tree* tree, Node* newNode) {
    // Add newNode to the tree
}

void rrtStar(Tree* tree, Node* start, Node* goal, int maxIterations) {
    for (int i = 0; i < maxIterations; i++) {
        Node* randomNode = getRandomNode();
        Node* nearest = nearestNeighbor(tree, randomNode);
        Node* newNode = steer(nearest, randomNode, stepSize);

        if (checkCollision(nearest, newNode)) {
            chooseParent(newNode, nearest, tree);
            addNodeToTree(tree, newNode);
            rewire(tree, newNode);
        }

        if (reachedGoal(newNode, goal)) {
            // Goal reached, construct the path
            break;
        }
    }
}

#endif // RRTSTAR_H
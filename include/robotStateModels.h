#ifndef ROBOT_STATE_MODELS_H
#define ROBOT_STATE_MODELS_H


/*
typedef struct {
    Vector3 endEffectorPosition;
    double joint0Angle, joint1Angle, joint2Angle, joint3Angle;
    double gripperRollAngle, gripperDist;
    bool gripperClosed;

} robotArm;

typedef struct {
    enum mapItemType type;
    enum mapItemState state;
    
    robotArm arm;               // If it has an arm: -> joint0.angle, joint0.angularVel, joint0.pos, joint0.vel
    bool robotCaptured;         // If it is a runner robot, of course

    double mass, e;             // other items of robot ....

    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    // Maybe instead of GLfloat yawAngle, use:
    Vector3 angle;              // where angle.y is yawAngle
    Vector3 angularVel;
    Vector3 angularAccel;

    double poseHist[100][6];    // 100 length pose history [xyz,roll,pitch,yaw]

    // Maybe add forces on the robot?
    Vector3 force;

} robot;
*/

/*
 *
 *  Large robot states (chaser)
 * 
*/

Vector3 endEffectorPosition;

double chaserSpeed = 7.00;

double chaserYawAngle = 0.0;//180.0;
double chaserYawAdd = 0.0;
static double chaserPosX = 0.00, chaserPosY = 2.00, chaserPosZ = 0.00;
static double joint0Angle = 0.0, joint1Angle = 0.0, joint2Angle = 0.0, joint3Angle = 0.0;

static double gripperRollAngle = 0.0;
static double gripperDist = 0.3;
static bool gripperClosed = false;
bool robotCaptured = false;

/*
 *
 *  Mini robot states (runner)
 * 
*/
double runnerSpeed = 4.00;   // Speed of runner robot

double accelSumY        =   0.00;   // Sum total Accel in Y direction
double runnerVelY       =   0.00;   // Initial velocity 0.00 m/s
double runnerVelHeading =   0.00;
double runnerPosX       =   1.00;   // Initial X position is 0.00 meters
double runnerPosY       =   2.00;   // Initial Y position is 100.00 meters
double runnerPosZ       =   0.00;   // Initial Z position is 0.00 meters
double mass             =   0.50;   // mass is 1.50 kg
double forceY           =   0.00;   // Init force in Y direction is 0.00 Newtons
double e                =   0.50;   // Coeff of restitution  

double runnerYawAngle = 180.0;

// list of runner positions
const int numPoses = 1000;
const int poseDim  = 3;

// Create an array to hold 1000 vectors, each with 3 components
double runnerPoseList[1000][4];

void setRunnerPoseList() {
    for (int i = 0; i < poseDim; i++) {
        runnerPoseList[i][0] = runnerPosX;      // runnerXPos
        runnerPoseList[i][1] = runnerPosY;      // runnerYPos
        runnerPoseList[i][2] = runnerPosZ;      // runnerZPos
        runnerPoseList[i][3] = runnerYawAngle;  // runnerYawAngle
    }
}

void updateRunnerPoseList(int i) {
    runnerPoseList[i][0] = runnerPosX;      // runnerXPos
    runnerPoseList[i][1] = runnerPosY;      // runnerYPos
    runnerPoseList[i][2] = runnerPosZ;      // runnerZPos
    runnerPoseList[i][3] = runnerYawAngle;  // runnerYawAngle
}

/*
 * FUNCTIONS
*/

bool isRobotCaptured() {
    if (gripperClosed && fabsf(runnerPosX-endEffectorPosition.x)<0.1 &&  fabsf(runnerPosY-endEffectorPosition.y)<0.1 && fabsf(runnerPosZ-endEffectorPosition.z)<0.1) {
        return true;
    }
    else {
        return false;
    }
}

void checkRobotCaptured() {
    robotCaptured = isRobotCaptured();
    if (robotCaptured) {
        runnerPosX = endEffectorPosition.x;
        runnerPosY = endEffectorPosition.y;
        runnerPosZ = endEffectorPosition.z;
    }
    else {
        getYPosition();
    }
}

#endif // ROBOT_STATE_MODELS_H
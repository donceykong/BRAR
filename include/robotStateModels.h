#ifndef ROBOT_STATE_MODELS_H
#define ROBOT_STATE_MODELS_H

/*
 *
 *  Large robot states (chaser)
 * 
*/

Vector3 endEffectorPosition;

double monsterRobotSpeed = 1.00;

static double joint0Angle = 0.0, joint1Angle = 0.0, joint2Angle = 0.0, joint3Angle = 0.0;
double joint1AngleSign = 1.0, joint2AngleSign = 1.0, joint3AngleSign = 1.0;

static double leftHipAngle = 0.0, rightHipAngle = 0.0;
static double rightHipSign = -1.0, leftHipSign = 1.0;

static double robotXPos = 0.00, robotYPos = 0.00, robotZPos = 0.00;

static double gripperRollAngle = 0.0;
static double gripperDist = 0.3;
static bool   gripperClosed = false;
bool ballInHandBool = false;

/*
 *
 *  Mini robot states (runner)
 * 
*/
extern double runnerSpeed;   // Speed of runner robot

double accelSumY    =   0.00;   // Sum total Accel in Y direction
double runnerVelY   =   0.00;   // Initial velocity 0.00 m/s
double runnerPosX   =   1.00;   // Initial X position is 0.00 meters
double runnerPosY   =   4.00;   // Initial Y position is 100.00 meters
double runnerPosZ   =   0.00;   // Initial Z position is 0.00 meters
double mass         =   0.50;   // mass is 1.50 kg
double forceY       =   0.00;   // Init force in Y direction is 0.00 Newtons
double e            =   0.50;   // Coeff of restitution  

GLfloat runnerYawAngle = 180.0f;

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

bool ballInHand() {
    if (gripperClosed && fabsf(runnerPosX-endEffectorPosition.x)<0.1 &&  fabsf(runnerPosY-endEffectorPosition.y)<0.1 && fabsf(runnerPosZ-endEffectorPosition.z)<0.1) {
        return true;
    }
    else {
        return false;
    }
}

#endif // ROBOT_STATE_MODELS_H
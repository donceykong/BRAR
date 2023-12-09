#ifndef ROBOT_STATE_MODELS_H
#define ROBOT_STATE_MODELS_H

#include <stdlib.h>

// enum robotType {
//     RUNNER_ROBOT,         // 0
//     CHASER_ROBOT,         // 1
//     TIME_CRUNCHER_ROBOT   // 2
// };

typedef struct {
    //enum robotType type;
    double mass, e, speed, viewableSpeed, speedAdjust;  // other items of robot ....

    bool inCollision;

    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    Vector3 prevPos;
    Vector3 prevVel;
    Vector3 prevAccel;

    //Vector3 externalForce;

    double yawAngle;
    double yawAdd;
    // // Maybe instead of GLfloat yawAngle, use:
    // Vector3 angularPos;         // where angle.y is yawAngle
    // Vector3 angularVel;         //
    // Vector3 angularAccel;       //

    // Pose history
    //double poseHist[100][6];    // 100 length pose history [xyz,roll,pitch,yaw]

    // Maybe add forces on the robot?
    Vector3 force;              //



    // If robot has end effector
    double joint1Angle, joint2Angle, joint3Angle;
    Vector3 endEffectorPosition;
    double gripperRollAngle, gripperDist;
    bool gripperClosed;

    bool captured;      // If it is a runner robot, of course
    bool robotTaken;    //
} RobotStruct;

/*
 *
 *  Large robot states (chaser)
 * 
*/
RobotStruct chaserRobot;

void initChaserRobot() {
    chaserRobot.speedAdjust = 1.00;
    chaserRobot.position.y = 2.0;
    chaserRobot.prevPos.y = 2.0;
    chaserRobot.gripperDist = 0.3;
    chaserRobot.gripperClosed = false;
}

/*
 *
 * ROBOT RUNNER STATES
 *
*/
bool robotCaptured = false;
bool robotTaken = false;

// ----------------------------------------
// Vector3 endEffectorPosition;

// double chaserSpeed = 0.00;
// double chaserViewableSpeed =   0.00;
// double chaserSpeedAdjust = 1.00;

// double chaserYawAngle = 0.0;//180.0;
// double chaserYawAdd = 0.0;
// double chaserPosX = 0.00, chaserPosY = 2.00, chaserPosZ = 0.00;
// double prevChaserPosX = 0.00, prevChaserPosY = 2.00, prevChaserPosZ = 0.00;

// double joint1Angle = 0.0, joint2Angle = 0.0, joint3Angle = 0.0;

// double gripperRollAngle = 0.0, gripperDist = 0.3;
// bool gripperClosed = false;


/*
 *
 *  Mini robot states (runner)
 * 
*/
double runnerSpeed = 0.00;              // Speed of runner robot

double accelSumY        =   0.00;       // Sum total Accel in Y direction
double runnerVelY       =   0.00;       // Initial velocity 0.00 m/s
double runnerViewableSpeed =   0.00;    //
double runnerSpeedAdjust = 1.00;        //

double runnerPosX       =   1.00;       // Initial RUNNER X position
double runnerPosY       =   5.00;       // Initial RUNNER Y position
double runnerPosZ       =   0.00;       // Initial RUNNER Z position

double prevRunnerPosX = 0.00;
double prevRunnerPosY = 2.00; 
double prevRunnerPosZ = 0.00;

double mass             =   68.0;       // mass is 68.0 kg (150 lbs)
double forceY           =   0.00;       // Init force in Y direction is 0.00 Newtons
double externalForceY   =   0.00;       // External force on the RUNNER (handled in keyhandler...)
double e                =   0.50;       // Coeff of restitution  

double runnerYawAngle = 180.0;

// list of runner positions
const int numPoses = 100;
const int poseDim  = 3;

// Create an array to hold 100 vectors, each with 3 components
double runnerPoseList[100][4];

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
    if (chaserRobot.gripperClosed && fabsf(runnerPosX-chaserRobot.endEffectorPosition.x)<0.1 &&  fabsf(runnerPosY-chaserRobot.endEffectorPosition.y)<0.1 && fabsf(runnerPosZ-chaserRobot.endEffectorPosition.z)<0.1) {
        return true;
    }
    else {
        return false;
    }
}

void checkRobotCaptured() {
    robotCaptured = isRobotCaptured();
    if (robotCaptured) {
        runnerPosX = chaserRobot.endEffectorPosition.x;
        runnerPosY = chaserRobot.endEffectorPosition.y;
        runnerPosZ = chaserRobot.endEffectorPosition.z;
    }
    else {
        getYPosition();
    }
}

#endif // ROBOT_STATE_MODELS_H
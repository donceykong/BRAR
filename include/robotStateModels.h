#ifndef ROBOT_STATE_MODELS_H
#define ROBOT_STATE_MODELS_H

#include <stdlib.h>
#include "miscObjects.h"

enum robotType {
    RUNNER_ROBOT,         // 0
    CHASER_ROBOT,         // 1
    TIME_CRUNCHER_ROBOT   // 2
};

typedef struct {
    enum robotType type;
    double mass, e, speed;                          //
    double viewableSpeed, speedAdjust;              // other items of robot ....
    bool inCollision;                               //

    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    Vector3 prevPos;
    Vector3 prevVel;
    Vector3 prevAccel;

    double yawAngle;
    double yawAdd;
    // // Maybe instead of GLfloat yawAngle, use:
    // Vector3 angularPos;                          // where angle.y is yawAngle
    // Vector3 angularVel;                          //
    // Vector3 angularAccel;                        //

    // Pose history
    double poseHist[100][4];                        // 100 length pose history [x,y,z,yaw]

    // Net forces on the robot
    Vector3 netForce;                               //
    Vector3 externalForce;                          //

    // If robot has end effector
    double joint1Angle, joint2Angle, joint3Angle;   //
    Vector3 endEffectorPosition;                    //
    double gripperRollAngle, gripperDist;           //
    bool gripperClosed;                             //
    bool captured;                                  // If it is a runner robot, of course
    bool taken;                                     //
} RobotStruct;

RobotStruct runnerRobot;
RobotStruct chaserRobot;


/*
 * FUNCTIONS
 */
void updateRunnerPoseList(RobotStruct *robot, int i) {
    robot->poseHist[i][0] = robot->position.x;    // runnerXPos
    robot->poseHist[i][1] = robot->position.y;    // runnerYPos
    robot->poseHist[i][2] = robot->position.z;    // runnerZPos
    robot->poseHist[i][3] = robot->yawAngle;      // runnerYawAngle
}

bool showPoseHist = false;

void displayPoseHistory(RobotStruct *robot) {
    static int iter = 0;
    static int numberPoses = 100;
    static int poseNumber = 0;

    //printf("numberPoses: %d, iterDIV10: %d\n", numberPoses, iter/10);
    if ((iter / 10 == 1) & (poseNumber < 100)) {
        updateRunnerPoseList(robot, poseNumber);
        iter = 0;
        poseNumber++;
    }
    else if ((iter / 10 == 1) & (poseNumber == 100)) {
        poseNumber = 0;
        iter = 0;
    }
    
    glDisable(GL_LIGHTING);
    for (int i = 0; i < numberPoses; i++) {
        glPushMatrix();
        glTranslatef(robot->poseHist[i][0], robot->poseHist[i][1], robot->poseHist[i][2]);
        glRotatef((GLfloat)robot->poseHist[i][3], 0.0, 1.0, 0.0);
        if (robot->type == RUNNER_ROBOT && showPoseHist) {
            drawPoseFrame(2.0, 3.0);             
        }
        else if (robot->type == CHASER_ROBOT && showPoseHist) {
            drawPoseFrame(2.0, 10.0);
        }
        glPopMatrix();
    }
    glEnable(GL_LIGHTING);
    iter++;
}

double getYawOffset(double joint0Angle, double robotXPos, double robotZPos, double objPosX, double objPosY, double objPosZ) {
    Matrix4x4 transformationMatrix = identityMatrix;
    Vector3 axisOfRotation  = {0.0f, 1.0f, 0.0f};
    Matrix4x4 rMatrix       = rotationMatrix(-joint0Angle, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);
    transformationMatrix    = multiplyMatrix(rMatrix, transformationMatrix);

    // Set Obj pos as a Matrix
    Matrix4x4 objPosMatrix  = translationMatrix(objPosX - robotXPos, objPosY, objPosZ - robotZPos);
    transformationMatrix    = multiplyMatrix(transformationMatrix, objPosMatrix);
    Vector3 relativeObjPos  = extractPosition(transformationMatrix);
    double yawAngle         = atanf(relativeObjPos.z / relativeObjPos.x);
    return yawAngle;
}

/*
 *
 *
 * 
 */
double timestep     =   0.05;   // Simulation timestep
double gY           =  -4.40;   //-9.81;   // Gravitational accel
double forceY       =   0.00;   //

double getNormalForce(RobotStruct *robot) {
    if (robot->position.y > 2) {
        forceY = 0;
    }
    else if (robot->position.y <= 2) {
        forceY = fabs(gY) * robot->mass;
    }
    return forceY;
}

void getYPosition(RobotStruct *robot) {
    double forceY = getNormalForce(robot);  // Calculate force first

    double accelSumY = gY + (forceY + robot->externalForce.y) / robot->mass;

    robot->velocity.y += accelSumY * timestep;
    robot->position.y += robot->velocity.y * timestep;
    
    // If position is below the ground, reverse its velocity and apply restitution
    if (robot->position.y <= 2) {
        robot->position.y = 2;
        robot->velocity.y = -robot->e * robot->velocity.y;
    }
    // If position is below the ground, reverse its velocity and apply restitution
    if (robot->position.y >= 10) {
        robot->position.y = 10.0;
        robot->velocity.y = 0.0;
    }
}   

bool isRobotCaptured() {
    if (chaserRobot.gripperClosed && fabsf(runnerRobot.position.x-chaserRobot.endEffectorPosition.x)<0.1 &&  
        fabsf(runnerRobot.position.y-chaserRobot.endEffectorPosition.y)<0.1 && 
        fabsf(runnerRobot.position.z-chaserRobot.endEffectorPosition.z)<0.1) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void checkRobotCaptured() {
    runnerRobot.captured = isRobotCaptured();
    if (runnerRobot.captured) {
        runnerRobot.position.x = chaserRobot.endEffectorPosition.x;
        runnerRobot.position.y = chaserRobot.endEffectorPosition.y;
        runnerRobot.position.z = chaserRobot.endEffectorPosition.z;
    }
    else {
        getYPosition(&runnerRobot);
    }
}

#endif // ROBOT_STATE_MODELS_H
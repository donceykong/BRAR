// Doncey Albin
// CG, Fall 2023

#include "robot.h"

legStruct chaserRightLeg;
legStruct chaserLeftLeg;

legStruct runnerFrontRightLeg;
legStruct runnerFrontLeftLeg;
legStruct runnerRearRightLeg;
legStruct runnerRearLeftLeg;

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

void computeForwardKinematics() {
    Matrix4x4 transformationMatrix = identityMatrix;

    // Joint0: Base
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(chaserRobot.position.x, chaserRobot.position.y, chaserRobot.position.z));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(chaserRobot.yawAngle + chaserRobot.yawAdd, 0.0, 1.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.0, 0.1, 0.0));

    // Joint1 & Link1
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.0, 0.1, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(chaserRobot.joint1Angle, 0.0, 0.0, 1.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.5, 0.0, 0.0));

    // Joint2 & Link2
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.5, 0.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(chaserRobot.joint2Angle, 0.0, 0.0, 1.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.5, 0.0, 0.0));

    // Joint3 & Link3
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.5, 0.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(chaserRobot.joint3Angle, 0.0, 0.0, 1.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.25, 0.0, 0.0));

    // Joint4 & End Effector
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.25, 0.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(chaserRobot.gripperRollAngle, 1.0, 0.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.1, 0.0, 0.0));

    chaserRobot.endEffectorPosition = extractPosition(transformationMatrix);
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

void updateRunnerPoseList(RobotStruct *robot, int i) {
    robot->poseHist[i][0] = robot->position.x;    // runnerXPos
    robot->poseHist[i][1] = robot->position.y;    // runnerYPos
    robot->poseHist[i][2] = robot->position.z;    // runnerZPos
    robot->poseHist[i][3] = robot->yawAngle;      // runnerYawAngle
}

void initChaserLegs() {
    // Right Leg params
    chaserRightLeg.type             = RIGHT_LEG;
    chaserRightLeg.thighBendAngle   = -60.0; // Init right thigh angle
    chaserRightLeg.thighSign        = 1.0;
    chaserRightLeg.kneeBendAngle    = 90.0;  // Init right knee angle
    chaserRightLeg.kneeSign         = 1.0;
    chaserRightLeg.ankleBendAngle   = 0.0;   // Init right ankle angle
    chaserRightLeg.ankleSign        = 1.0;

    // Left Leg params
    chaserLeftLeg.type              = LEFT_LEG;
    chaserLeftLeg.thighBendAngle    = 45.0; // Init left thigh angle
    chaserLeftLeg.thighSign         = 1.0;
    chaserLeftLeg.kneeBendAngle     = 0.0;  // Init left knee angle
    chaserLeftLeg.kneeSign          = 1.0;
    chaserLeftLeg.ankleBendAngle    = 0.0;  // Init left ankle angle
    chaserLeftLeg.ankleSign         = 1.0;
}

void initRunnerLegs() {
    // Front right leg params
    runnerFrontRightLeg.type            = RIGHT_LEG;
    runnerFrontRightLeg.thighBendAngle  = -60.0;    // Init front right thigh angle
    runnerFrontRightLeg.thighSign       = 1.0;
    runnerFrontRightLeg.kneeBendAngle   = 90.0;     // Init front right knee angle
    runnerFrontRightLeg.kneeSign        = 1.0;
    runnerFrontRightLeg.ankleBendAngle  = 0.0;      // Init front right ankle angle
    runnerFrontRightLeg.ankleSign       = 1.0;

    // Front left leg params
    runnerFrontLeftLeg.type             = LEFT_LEG;
    runnerFrontLeftLeg.thighBendAngle   = 45.0;     // Init front left thigh angle
    runnerFrontLeftLeg.thighSign        = 1.0;
    runnerFrontLeftLeg.kneeBendAngle    = 0.0;      // Init front left knee angle
    runnerFrontLeftLeg.kneeSign         = 1.0;
    runnerFrontLeftLeg.ankleBendAngle   = 0.0;      // Init front left ankle angle
    runnerFrontLeftLeg.ankleSign        = 1.0;

    // Rear right reg params
    runnerRearRightLeg.type             = RIGHT_LEG;
    runnerRearRightLeg.thighBendAngle   = 45.0;     // Init rear right thigh angle
    runnerRearRightLeg.thighSign        = 1.0;
    runnerRearRightLeg.kneeBendAngle    = 0.0;      // Init rear left knee angle
    runnerRearRightLeg.kneeSign         = 1.0;
    runnerRearRightLeg.ankleBendAngle   = 0.0;      // Init rear left ankle angle
    runnerRearRightLeg.ankleSign        = 1.0;

    // Rear left leg params
    runnerRearLeftLeg.type              = LEFT_LEG;
    runnerRearLeftLeg.thighBendAngle    = -60.0;    // Init rear right thigh angle
    runnerRearLeftLeg.thighSign         = 1.0;
    runnerRearLeftLeg.kneeBendAngle     = 90.0;     // Init rear left knee angle
    runnerRearLeftLeg.kneeSign          = 1.0;
    runnerRearLeftLeg.ankleBendAngle    = 0.0;      // Init rear left ankle angle
    runnerRearLeftLeg.ankleSign         = 1.0;
}

void initChaserRobot() {
    initChaserLegs();
    chaserRobot.type            = CHASER_ROBOT; //
    chaserRobot.speedAdjust     = 1.00;         //
    chaserRobot.position.y      = 2.0;          //
    chaserRobot.prevPos.y       = 2.0;          //
    chaserRobot.mass            = 68.0;         // kg (150 lb)
    chaserRobot.e               = 0.20;         // coeff of elasticity 
    chaserRobot.gripperDist     = 0.3;          //
    chaserRobot.gripperClosed   = false;        //
}

void initRunnerRobot() {
    initRunnerLegs();
    runnerRobot.type        = RUNNER_ROBOT; //
    runnerRobot.speedAdjust = 1.00;         //
    runnerRobot.position.x  = 2.0;          //
    runnerRobot.position.y  = 5.0;          //
    runnerRobot.prevPos.y   = 2.0;          //
    runnerRobot.mass        = 68.0;         // kg (150 lb)
    runnerRobot.e           = 0.20;         // coeff of elasticity 
    runnerRobot.yawAngle    = 180.0;        // deg
    runnerRobot.captured    = false;        //
    runnerRobot.taken       = false;        //
}
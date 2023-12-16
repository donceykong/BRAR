#ifndef ROBOT_H
#define ROBOT_H

// Extern
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

// Local
#include "matrixMath.h"
#include "draw.h"
#include "keys.h"

enum legType {
    LEFT_LEG,   // 0
    RIGHT_LEG   // 1
};

typedef struct {
  enum legType type;

  double thighBendAngle;
  double thighSign;

  double kneeBendAngle;  // Init right knee angle
  double kneeSign;

  double ankleBendAngle;   // Init right ankle angle
  double ankleSign;
} legStruct;

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
    double yawAdd;                                  // TODO: fix? (Used for chaser in Time Crunch)
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
    double prevJoint1Angle, prevJoint2Angle, prevJoint3Angle;
    Vector3 endEffectorPosition;                    //
    double gripperRollAngle, gripperDist;           //
    bool gripperClosed;                             //
    bool captured;                                  // If it is a runner robot, of course
    bool taken;                                     //
} RobotStruct;

// Global Vars
extern RobotStruct runnerRobot;
extern RobotStruct chaserRobot;

extern double WaypointPosX;
extern double WaypointPosZ;

extern legStruct chaserRightLeg;
extern legStruct chaserLeftLeg;

extern legStruct runnerFrontRightLeg;
extern legStruct runnerFrontLeftLeg;
extern legStruct runnerRearRightLeg;
extern legStruct runnerRearLeftLeg;

/*
 * FUNCTIONS
 */

void initChaserRobot();
void initRunnerRobot();

// Robot States
void updateRunnerPoseList(RobotStruct *robot, int i);
bool isRobotCaptured();
void checkRobotCaptured();
double getYawOffset(double joint0Angle, double robotXPos, double robotZPos, double objPosX, double objPosY, double objPosZ);
void getYPosition(RobotStruct *robot); // Should be "setter"

// robot Draw Legs
void drawLeg(bool rightLeg, double runSpeed, legStruct *leg, bool onGround);

void drawBody();

// robot Draw Arm
// void robotBase(GLfloat width, GLfloat height, GLfloat depth, double faceC[3]);
// void robotLink(GLfloat width, GLfloat height, GLfloat depth, double faceC[3]);
// void robotEndEffector(GLfloat width, GLfloat height, GLfloat depth, double faceC[3]);
void drawRobotArm();

// robot Draw
void displayPoseHistory(RobotStruct *robot);
void drawRunnerRobot();
void drawChaserRobot();

void computeForwardKinematics();

#endif // ROBOT_H
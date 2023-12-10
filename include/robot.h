#ifndef ROBOT_H
#define ROBOT_H

#include "robotStateModels.h"
#include "robotBody.h"
#include "robotLegs.h"
#include "robotArm.h"

legStruct chaserRightLeg;
legStruct chaserLeftLeg;

legStruct runnerFrontRightLeg;
legStruct runnerFrontLeftLeg;
legStruct runnerRearRightLeg;
legStruct runnerRearLeftLeg;

void initChaserLegs () {
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

void initRunnerLegs () {
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


void drawChaserRobot() {
    glPushMatrix();
    glTranslatef(chaserRobot.position.x, chaserRobot.position.y, chaserRobot.position.z);
    glRotatef((GLfloat)chaserRobot.yawAngle + chaserRobot.yawAdd, 0.0, 1.0, 0.0);

    bool onGround = true;
    if (chaserRobot.position.y > 2.5) {
        onGround = false;
    }

    // robot body
    glPushMatrix();
    drawBody();
    glPopMatrix();

    // robot left leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5);
    drawLeg(true, chaserRobot.viewableSpeed, &chaserRightLeg, onGround);
    glPopMatrix();

    // robot right leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    drawLeg(false, chaserRobot.viewableSpeed, &chaserLeftLeg, onGround);
    glPopMatrix();

    drawRobotArm();
    glPopMatrix();
}

void drawRunnerRobot() {
    glPushMatrix();
    glTranslatef(runnerRobot.position.x, runnerRobot.position.y, runnerRobot.position.z);
    glRotatef((GLfloat)runnerRobot.yawAngle - 90.0, 0.0, 1.0, 0.0);
    
    bool onGround = true;
    if (runnerRobot.position.y > 2.5) {
        onGround = false;
    }
    // printf("runnerRobot.viewableSpeed: %f\n", runnerRobot.viewableSpeed);
    
    /*
     * Back legs 
    */
    // robot body
    glPushMatrix();
    drawBody();
    glPopMatrix();
    
    // robot left leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5);
    drawLeg(true, runnerRobot.viewableSpeed, &runnerRearRightLeg, onGround);
    glPopMatrix();

    // robot right leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    drawLeg(false, runnerRobot.viewableSpeed, &runnerRearLeftLeg, onGround);
    glPopMatrix();

    /*
     * Robot dog mid-section
    */
    glPushMatrix();
    glTranslatef(1.0, 0.0, 0.0);  // Move cube to center between thighs
    glColor3f(1.0, 1.0, 1.0);    // face color
    getCuboid(1.50, 0.4, 0.4);   // Draw cube
    glPopMatrix();

    /*
     * Front legs
    */
    glTranslatef(2.0, 0.0, 0.0);
    // robot body
    glPushMatrix();
    drawBody();
    glPopMatrix();

    // robot left leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5);
    drawLeg(true, runnerRobot.viewableSpeed, &runnerFrontRightLeg, onGround);
    glPopMatrix();

    // robot right leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    drawLeg(false, runnerRobot.viewableSpeed, &runnerFrontLeftLeg, onGround);
    glPopMatrix();

    // robot arm
    //drawRobotArm();

    glPopMatrix();
}

#endif // ROBOT_H
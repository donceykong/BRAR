#ifndef ROBOT_H
#define ROBOT_H

#include "robotBody.h"
#include "robotLegs.h"
#include "robotArm.h"

void drawRobot() {
    glPushMatrix();
    glTranslatef(chaserPosX, chaserPosY, chaserPosZ);
    glRotatef((GLfloat)chaserYawAngle + chaserYawAdd, 0.0, 1.0, 0.0);

    // robot body
    glPushMatrix();
    drawBody();
    glPopMatrix();

    // robot left leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5);
    drawLeg(true, chaserSpeed);
    glPopMatrix();

    // robot right leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    //glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate thigh 180
    drawLeg(false, chaserSpeed);
    glPopMatrix();

    drawRobotArm();
    glPopMatrix();
}

void drawMiniRobot() {
    glPushMatrix();
    glTranslatef(runnerPosX, runnerPosY, runnerPosZ);
    glRotatef((GLfloat)runnerYawAngle - 90.0, 0.0, 1.0, 0.0);

    /*
     * Back legs 
    */
    // robot body
    glPushMatrix();
    drawBody();
    glPopMatrix();

    double viewableRunnerSpeed;
    if (runnerVelHeading == 0.0) {
        viewableRunnerSpeed = 0.0;
    }
    else {
        viewableRunnerSpeed = runnerSpeed;
    }
    
    // robot left leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5);
    drawLeg(true, viewableRunnerSpeed);
    glPopMatrix();

    // robot right leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    //glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate thigh 180
    drawLeg(false, viewableRunnerSpeed);
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
    drawLeg(true, viewableRunnerSpeed);
    glPopMatrix();

    // robot right leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    //glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate thigh 180
    drawLeg(false, viewableRunnerSpeed);
    glPopMatrix();

    // robot arm
    //drawRobotArm();

    glPopMatrix();
}

#endif // ROBOT_H
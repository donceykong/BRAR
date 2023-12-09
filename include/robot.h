#ifndef ROBOT_H
#define ROBOT_H

#include "robotBody.h"
#include "robotLegs.h"
#include "robotArm.h"

void drawRobot() {
    glPushMatrix();
    glTranslatef(chaserRobot.position.x, chaserRobot.position.y, chaserRobot.position.z);
    glRotatef((GLfloat)chaserRobot.yawAngle + chaserRobot.yawAdd, 0.0, 1.0, 0.0);

    // robot body
    glPushMatrix();
    drawBody();
    glPopMatrix();

    // robot left leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5);
    drawLeg(true, chaserRobot.viewableSpeed);
    glPopMatrix();

    // robot right leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    //glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate thigh 180
    drawLeg(false, chaserRobot.viewableSpeed);
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
    
    // robot left leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5);
    drawLeg(true, runnerViewableSpeed);
    glPopMatrix();

    // robot right leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    //glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate thigh 180
    drawLeg(false, runnerViewableSpeed);
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
    drawLeg(true, runnerViewableSpeed);
    glPopMatrix();

    // robot right leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    //glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate thigh 180
    drawLeg(false, runnerViewableSpeed);
    glPopMatrix();

    // robot arm
    //drawRobotArm();

    glPopMatrix();
}

#endif // ROBOT_H
#include "robotBody.h"
#include "robotLegs.h"
#include "robotArm.h"

void drawRobot() {
    glTranslatef(robotXPos, 2.0, robotZPos);
    glRotatef((GLfloat)joint0Angle, 0.0, 1.0, 0.0);

    // robot body
    glPushMatrix();
    drawBody();
    glPopMatrix();

    // robot left leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5);
    drawLeg(true);
    glPopMatrix();

    // robot right leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    //glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate thigh 180
    drawLeg(false);
    glPopMatrix();

    // robot arm
    drawRobotArm();
}

void drawMiniRobot() {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glRotatef((GLfloat)angleYObject - 90.0, 0.0, 1.0, 0.0);

    // robot body
    glPushMatrix();
    drawBody();
    glPopMatrix();

    // robot left leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.5);
    drawLeg(true);
    glPopMatrix();

    // robot right leg
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    //glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate thigh 180
    drawLeg(false);
    glPopMatrix();

    // robot arm
    //drawRobotArm();

    glPopMatrix();
}
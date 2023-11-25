#include "robotBody.h"
#include "robotLegs.h"
#include "robotArm.h"

double rotateRobot = 0.0;

void drawRobot() {
    glRotatef(rotateRobot, 0.0, 1.0, 0.0);  // Rotate robot

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
    //rotateRobot = rotateRobot + 0.1;
}
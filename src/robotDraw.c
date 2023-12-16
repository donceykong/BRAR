// Doncey Albin
// CG, Fall 2023

#include "robot.h"

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
    
    // glDisable(GL_LIGHTING);
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
    // glEnable(GL_LIGHTING);
    iter++;
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
    glTranslatef(runnerRobot.position.x, runnerRobot.position.y, runnerRobot.position.z + 1.75/2);
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
    BMPtexture = BMPtexture5;                         // TODO: Change initial texture
    drawCuboid(1.50, 0.4, 0.4);   // Draw cube
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
// Doncey Albin
// CG, Fall 2023

#include "robot.h"


double timestep     =   0.05;   // Simulation timestep
double gY           =  -9.81;   // Gravitational accel
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
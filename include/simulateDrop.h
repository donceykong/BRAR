#ifndef SIMULATE_DROP_H
#define SIMULATE_DROP_H

/*
    accelSumY   = gY    + forceY/m
    VelY        = velY  + accelSumY * timestep
    PosY        = PosY  + VelY      * timestep      
*/

double timestep     =   0.005;  // Simulation timestep
double gY           =  -9.81;   // Gravitational accel

void getNormalForce() {
    if (runnerPosY > 2) {
        forceY = 0;
    }
    else if (runnerPosY <= 2) {
        forceY = fabs(gY) * mass;
    }
}

void getYPosition() {
    getNormalForce();  // Calculate force first

    accelSumY = gY + forceY / mass;
    runnerVelY = runnerVelY + accelSumY * timestep;
    runnerPosY = runnerPosY + runnerVelY * timestep;
    
    // If ball's position is below the ground, reverse its velocity and apply restitution
    if (runnerPosY <= 2) {
        runnerPosY = 2;
        runnerVelY = -e * runnerVelY;
    }
}   

#endif // SIMULATE_DROP_H
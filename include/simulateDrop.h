#ifndef SIMULATE_DROP_H
#define SIMULATE_DROP_H

/*
    accelSumY   = gY    + forceY/m
    VelY        = velY  + accelSumY * timestep
    PosY        = PosY  + VelY      * timestep      
*/

double timestep     =   0.05;  // Simulation timestep
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

    accelSumY = gY + forceY / mass + externalForceY / mass;

    runnerVelY += accelSumY * timestep;
    runnerPosY += runnerVelY * timestep;
    
    // If position is below the ground, reverse its velocity and apply restitution
    if (runnerPosY <= 2) {
        runnerPosY = 2;
        runnerVelY = -e * runnerVelY;
    }
    // If position is below the ground, reverse its velocity and apply restitution
    if (runnerPosY >= 10) {
        runnerPosY = 10.0;
        runnerVelY = 0.0;
    }

    return runnerPosY;
}   

#endif // SIMULATE_DROP_H
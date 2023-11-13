/*
    accelSumY   = gY    + forceY/m
    VelY        = velY  + accelSumY * timestep
    PosY        = PosY  + VelY      * timestep      
*/

double timestep     =   0.005;  // Simulation timestep
double accelSumY    =   0.00;   // Sum total Accel in Y direction
double velY         =   0.00;   // Initial velocity 0.00 m/s
double posX         =   1.00;   // Initial X position is 0.00 meters
double posY         =   1.00;   // Initial Y position is 100.00 meters
double posZ         =   0.00;   // Initial Z position is 0.00 meters
double gY           =  -9.81;   // Gravitational accel
double mass         =   0.50;   // mass is 1.50 kg
double forceY       =   0.00;   // Init force in Y direction is 0.00 Newtons
double e            =   0.95;   // Coeff of restitution   

void getNormalForce() {
    if (posY > 0) {
        forceY = 0;
    }
    else if (posY <= 0) {
        forceY = fabs(gY) * mass;
    }
}

void getYPosition() {
    getNormalForce();  // Calculate force first

    accelSumY = gY + forceY / mass;
    velY = velY + accelSumY * timestep;
    posY = posY + velY * timestep;
    
    // If ball's position is below the ground, reverse its velocity and apply restitution
    if (posY <= 0) {
        posY = 0;
        velY = -e * velY;
    }
}   
#ifndef GROUND_PLANE_H
#define GROUND_PLANE_H

GLfloat GroundPlaneVertices[] = {
    // Position Indices:            (0 - 2)         
    // Texture Coordinates Indices: (3 - 4)
    100.0f,  0.0f,  100.0f,  1.0f, 1.0f,
   -100.0f,  0.0f,  100.0f,  0.0f, 1.0f,
   -100.0f,  0.0f, -100.0f,  0.0f, 0.0f,

    100.0f,  0.0f,  100.0f,  1.0f, 1.0f,
   -100.0f,  0.0f, -100.0f,  0.0f, 0.0f,
    100.0f,  0.0f, -100.0f,  1.0f, 0.0f
};

void drawLorenzAttractor() {
    srand(time(NULL));  // set rand generator seed
    // Lorenz system parameters
    double sigma = 10 + (double)rand() / (RAND_MAX / 1.0) ;
    double rho = 28.0 + (double)rand() / (RAND_MAX / 3.0) + 1.0;
    double beta = 8.0 / 3.0 + (double)rand() / (RAND_MAX / 3.0);

    // Initial conditions
    double x = 0.01, y = 0, z = 0;

    // Time step for numerical integration
    double dt = 0.01;

    // Start drawing
    glColor3f(1.0, 1.0, 1.0); // Set attractor color
    glPointSize(6.0f);          // Set line width to 2.0 pixels
    glBegin(GL_POINTS);
    glNormal3f(0, 0, 1); 
    
    // Numerical integration and drawing loop
    for (int i = 0; i < 10000; ++i) {
        double color = i/20000.0 + 0.5;
        double bluerand = (double)rand() / (RAND_MAX / 1.0);
        glColor3f(color, 1.0, color + bluerand);

        // Lorenz attractor equations
        double dx = sigma * (y - x) * dt;
        double dy = (x * (rho - z) - y) * dt;
        double dz = (x * y - beta * z) * dt;

        x += dx;
        y += dy;
        z += dz;

        // Adjust the scale and position as necessary
        glVertex2f(x * 5, y * 5);//, z * 5);
        //glVertex3f(x * 5, y * 5, z * 5);
    }

    glEnd();
}

double portalRot = 0.0;
void drawPortals() {
    glColor3f(1.0, 1.0, 1.0);
    
    double zTrans;
    double xTrans;
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        if (i == 0) {
            zTrans = -100.0;
            xTrans = 0.00;
        }
        if (i == 1) {
            zTrans = 100.0;
            xTrans = 0.00;
        }
        if (i == 2) {
            zTrans = 0.0;
            xTrans = -100.00;
        }
        if (i == 3) {
            zTrans = 0.0;
            xTrans = 100.00;
        }
        glTranslatef(xTrans, 50.0, zTrans);
        if (i == 0 || i == 1) {
            glRotatef((GLfloat) 180.0, 1.0, 0.0, 0.0);
        }
        else {
            glRotatef((GLfloat) 90.0, 0.0, 0.0, 1.0);
            glRotatef((GLfloat) 90.0, 1.0, 0.0, 0.0);
        }
        // glRotatef((GLfloat) portalRot, 0.0, 1.0, 0.0);
        // drawAxes(2.0);
        // portalRot += 1.0;

        drawLorenzAttractor();
        glPopMatrix();
    }
}

void drawGroundPlane() {
    glPushMatrix();
    glTranslatef(mapCenterX, 0.00, mapCenterZ);

    glColor3f(1.0, 1.0, 1.0);     // Blue color
    glBegin(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, terrainTexture);
    
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 1.0f, 0.0f);
    for (int i = 0; i < 6 * 5; i += 5) {
        // Optionally set texture coordinates if you're using them.
        glTexCoord2f(GroundPlaneVertices[i + 3], GroundPlaneVertices[i + 4]);
        glVertex3f(GroundPlaneVertices[i], GroundPlaneVertices[i + 1], GroundPlaneVertices[i + 2]);
    }
    
    glEnd();

    drawPortals();
    glPopMatrix();
}

#endif // GROUND_PLANE_H
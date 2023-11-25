// mapModel.h

double mapCenterX = 0.0;
double mapCenterZ = 0.0;
double mapRadius = 20.0;

void drawSemiCylinderEdges(GLfloat radius, int segments, double percentFull) {
    glColor3f(1.0, 0.0, 0.0);  // Red color

    glLineWidth(4.0f);          // Set line width to 2.0 pixels
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);  // Center vertex
    for (int i = 0; i <= segments; i += 2) {
        GLfloat angle = -M_PI/2.0 + i * percentFull*2.0*M_PI / segments; 
        GLfloat z = -radius * sin(angle);
        GLfloat x = -radius * cos(angle);

        glNormal3f(x, 0, z);
        glVertex3f(x, 0, z);
    }
    glEnd();
}

void plotMapBorder () {
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    // Set up polygon mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    // glRotatef(90.0, 0.0, 0.0, 1.0);
    // glColor3f(1.0, 1.0, 1.0);   // White color
    // glLineWidth(4.0f);          // Set line width to 2.0 pixels
    // drawSemiCylinderEdges(2.0, 0.0, 100, 100.0);

    glTranslatef(mapCenterX, 1.0, mapCenterZ);
    drawSemiCylinderEdges(mapRadius, 10000, 100.0);
    // Sphere(mapRadius, 100, 100);              // Draw a sphere

    glDisable(GL_DEPTH_TEST);
    glPopMatrix();
}

void updateMapCenter () {
    double dist = getEulerDistanceXZ(mapCenterX, mapCenterZ, posX, posZ);
    if (dist > mapRadius) {
        printf("Map center updated\n");
        mapCenterX = posX;
        mapCenterZ = posZ;
    }
    plotMapBorder();
    printf("mapCenterX: %f, mapCenterZ: %f\n\n", mapCenterX, mapCenterZ);
}
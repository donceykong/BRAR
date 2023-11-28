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

void drawGroundPlane() {
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
}

double portalRot = 0.0;
void drawPortals() {
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, portalTexture);
    
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
        glTranslatef(xTrans, 0.0, zTrans);
        if (i == 0 || i == 1) {
            glRotatef((GLfloat) 90.0, 1.0, 0.0, 0.0);
        }
        else {
            glRotatef((GLfloat) 90.0, 0.0, 0.0, 1.0);
        }
        glRotatef((GLfloat) portalRot, 0.0, 1.0, 0.0);
        drawAxes(2.0);
        portalRot += 1.0;

        glBegin(GL_TRIANGLES);
        glNormal3f(0.0f, 1.0f, 0.0f);
        for (int i = 0; i < 6 * 5; i += 5) {
            // Optionally set texture coordinates if you're using them.
            glTexCoord2f(GroundPlaneVertices[i + 3], GroundPlaneVertices[i + 4]);
            glVertex3f(GroundPlaneVertices[i], GroundPlaneVertices[i + 1], GroundPlaneVertices[i + 2]);
        }
        glEnd();
        glPopMatrix();
    }
}

#endif // GROUND_PLANE_H
// Created by: Doncey Albin

GLuint BMPtexture1 = 0;
GLuint BMPtexture2 = 0;
GLuint BMPtexture3 = 0;
GLuint BMPtexture4 = 0;
GLuint BMPtexture  = 0;   // Main texture (set to 1:4 as desired)

bool showFrames = false;  // Show joint frames

void drawFrame(float length) {
    glBegin(GL_LINES);
        // X axis in red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(length, 0.0f, 0.0f);

        // Y Axis in Green
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, length, 0.0f);

        // Z Axis in Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, length);
    glEnd();
}

void getCubeEdges(GLfloat width, GLfloat height, GLfloat depth) {
    // Front face
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);

    // Back face
    glVertex3f(-width/2, -height/2, -depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f( width/2, -height/2, -depth/2);

    // Left face
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f(-width/2, -height/2, -depth/2);

    // Right face
    glVertex3f( width/2, -height/2, -depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f( width/2, -height/2,  depth/2);

    // Top face
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);

    // Bottom face
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2, -height/2, -depth/2);
    glVertex3f( width/2, -height/2, -depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
}

void getCube(GLfloat width, GLfloat height, GLfloat depth) {
    // Front face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2, -height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Back face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_QUADS);
    glNormal3f(0, 0,-1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2, -depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Left face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Right face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( width/2, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2,  depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2, -height/2, -depth/2);
    glVertex3f( width/2, -height/2, -depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
    glEnd();

    glColor3f(0.8, 0.8, 1.0);   // Purpleish color
    glLineWidth(4.0f);          // Set line width to 2.0 pixels
    glBegin(GL_LINES);
      getCubeEdges(width, height, depth);
    glEnd();
}

void getRightTriPrismEdges(GLfloat width, GLfloat height, GLfloat depth) {
    // Front face
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);

    // Back face
    glVertex3f(-width/2, -height/2, -depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f( width/2, -height/2, -depth/2);

    // Left face
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f(-width/2, -height/2, -depth/2);

    // Top face
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f( width/2,  -height/2,  depth/2);
    glVertex3f( width/2,  -height/2, -depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);

    // Bottom face
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2, -height/2, -depth/2);
    glVertex3f( width/2, -height/2, -depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
}

void getRightTriPrism(GLfloat width, GLfloat height, GLfloat depth) {
    // Front face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2, -height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glEnd();

    // Back face
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0,-1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2, -depth/2);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  -height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2,  -height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2, -height/2,  depth/2);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    glColor3f(0.8, 0.8, 1.0);   // Purpleish color
    glLineWidth(4.0f);          // Set line width to 2.0 pixels
    glBegin(GL_LINES);
      getRightTriPrismEdges(width, height, depth);
    glEnd();
}

void drawSemiCylinderEdges(GLfloat radius, GLfloat height, int segments, double percentFull) {
    glColor3f(0.8, 0.8, 1.0);   // Purpleish color

    glLineWidth(4.0f);          // Set line width to 2.0 pixels
    glBegin(GL_LINES);
    glVertex3f(0, 0, -height/2);  // Center vertex
    for (int i = 0; i <= segments; i += 2) {
        GLfloat angle = -M_PI/2.0 + i * percentFull*2.0*M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        glNormal3f(x, y, -height/2);
        glVertex3f(x, y, -height/2);
    }
    glEnd();

    glLineWidth(4.0f);            // Set line width to 2.0 pixels
    glBegin(GL_LINES);
    glVertex3f(0, 0, height/2);   // Center vertex
    for (int i = 0; i <= segments; i += 2) {
        GLfloat angle = -M_PI/2.0 + i * percentFull*2.0*M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        glNormal3f(x, y, height/2);
        glVertex3f(x, y, height/2);
    }
    glEnd();
}

void drawSemiCylinder(GLfloat radius, GLfloat height, int segments, double percentFull) {
    /*
     * Draw outer edge
     */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= segments; ++i) {
        GLfloat angle = -M_PI / 2.0 + i * percentFull * 2.0 * M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        // Texture coordinates
        GLfloat s = (float)i / segments; // Assuming horizontal wrap of texture
        GLfloat t_lower = 0.0f; // Texture coordinate for lower ring
        GLfloat t_upper = 1.0f; // Texture coordinate for upper ring

        glNormal3f(x, y, 0.0f);
        glTexCoord2f(s, t_lower); glVertex3f(x, y, -height / 2);  // Lower ring
        glTexCoord2f(s, t_upper); glVertex3f(x, y, height / 2);   // Upper ring
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    /*
     * Draw front face
     */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_TRIANGLE_FAN);

    // Center vertex and its texture coordinate
    glTexCoord2f(0.5f, 0.5f);   // Texture coordinate for the center
    glVertex3f(0, 0, height/2); // Center vertex
    glNormal3f(0.0f, 0.0f, height/2);
    for (int i = 0; i <= segments; ++i) {
        GLfloat angle = -M_PI / 2.0 + i * percentFull * 2.0 * M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        // Calculate texture coordinates for the perimeter vertices
        GLfloat s = 0.5 + 0.5 * cos(angle); // Map the angle to [0, 1] range
        GLfloat t = 0.5 + 0.5 * sin(angle);

        glTexCoord2f(s, t); // Texture coordinate for each perimeter vertex
        glNormal3f(x, y, height/2);
        glVertex3f(x, y, height/2); // Perimeter vertex
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);


    /*
     * Draw back face
     */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_TRIANGLE_FAN);

    glTexCoord2f(0.5f, 0.5f);     // Texture coordinate for the center
    glVertex3f(0, 0, -height/2);  // Center vertex
    glNormal3f(0.0f, 0.0f, -height/2);
    for (int i = 0; i <= segments; ++i) {
        GLfloat angle = -M_PI/2.0 + i * percentFull*2.0*M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        // Calculate texture coordinates for the perimeter vertices
        GLfloat s = 0.5 + 0.5 * cos(angle); // Map the angle to [0, 1] range
        GLfloat t = 0.5 + 0.5 * sin(angle);

        glTexCoord2f(s, t); // Texture coordinate for each perimeter vertex
        glNormal3f(x, y, -height/2);
        glVertex3f(x, y, -height/2);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    drawSemiCylinderEdges(radius, height, segments, percentFull);
}

void getParallelogramEdges(GLfloat width, GLfloat height, GLfloat depth) {
    // Front face
    glBegin(GL_LINES);
    glVertex3f(-width/4, -height/2,  depth/2); // bottom
    glVertex3f( width/4, -height/2,  depth/2);

    glVertex3f(-width/4, -height/2, depth/2); // left
    glVertex3f(-width/2,  height/2, depth/2);

    glVertex3f( width/2,  height/2, depth/2); // right
    glVertex3f( width/4, -height/2, depth/2);
    glEnd();

    // Back face
    glBegin(GL_LINES);
    glVertex3f(-width/4, -height/2,  -depth/2); // bottom
    glVertex3f( width/4, -height/2,  -depth/2);

    glVertex3f(-width/4, -height/2, -depth/2); // left
    glVertex3f(-width/2,  height/2, -depth/2);

    glVertex3f( width/2,  height/2, -depth/2); // right
    glVertex3f( width/4, -height/2, -depth/2);
    glEnd();

    // Left face bottom
    glBegin(GL_LINES);
    glVertex3f(-width/4, -height/2,  depth/2);
    glVertex3f(-width/4, -height/2, -depth/2);
    glEnd();

    // Right face
    glBegin(GL_LINES);
    glVertex3f( width/4, -height/2, -depth/2);
    glVertex3f( width/4, -height/2,  depth/2);
    glEnd();
}

void getParallelogram(GLfloat width, GLfloat height, GLfloat depth) {
    // Front face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/4, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/4, -height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glNormal3f(0, 0,-1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/4, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/4, -height/2, -depth/2);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/4, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/4, -height/2, -depth/2);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( width/4, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/4, -height/2,  depth/2);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/4, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/4, -height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/4, -height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/4, -height/2,  depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0, 1.0, 1.0);   // White color
    glLineWidth(4.0f);          // Set line width to 2.0 pixels
    getParallelogramEdges(width, height, depth);
}

// Joint to Joint length is 0.66
void robotThigh(double percentFull, double thickness, double faceC[3], bool topLayer) {
    glPushMatrix();

    GLuint BMPtexturePrev = BMPtexture;
    BMPtexture = BMPtexture3;
    // Draw motor shaft
    if (!topLayer) {
      glTranslatef(0.0, 0.0, -(0.5*thickness+0.75*thickness));      // Move out 0.5 len thigh and shaft thickness
      glColor3f(1.0, 1.0, 1.0);                                     // face color
      drawSemiCylinder(0.1, 1.5*thickness, 1000, 1.0);              // Draw motor cylindrical shaft
      glTranslatef(0.0, 0.0, (0.5*thickness+0.75*thickness));       // Move back to thigh
    }
    BMPtexture = BMPtexturePrev;

    // face colors
    glColor3f(faceC[0], faceC[1], faceC[2]);                        // face color
    drawSemiCylinder(0.2*percentFull, thickness, 1000, 0.5);        // Draw top semi cylinder

    glTranslatef(0.0, -0.05, 0.0);                                  // Move cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);                        // face color
    getCube(0.4*percentFull, 0.1, thickness);                       // Draw cube

    glTranslatef(0.0, -0.1, 0.0);                                   // Translate to bring parallelogram top down
    glColor3f(faceC[0], faceC[1], faceC[2]);                        // face color
    getParallelogram(0.4*percentFull, 0.1, thickness);              // Draw parallelogram

    glTranslatef(0.0, -0.25, 0.0);                                  // Move cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);                        // face color
    getCube(0.2*percentFull, 0.4, thickness);                       // Draw cube
    glTranslatef(0.0, -0.2, 0.0);                                   // To get to end of cube

    if (!topLayer) {
        glTranslatef(0.0, -0.06, thickness/4);      // To get to end cylinder center
        glColor3f(faceC[0], faceC[1], faceC[2]);    // face color
        drawSemiCylinder(0.12*percentFull, thickness/2, 1000, 1.0);      // Draw semi-cylinder
        glTranslatef(0.0, 0.0, -thickness/4);      // To get to end cylinder center
    }
    else {
        glTranslatef(0.0, -0.06, 0.0);      // To get to end cylinder center
        glColor3f(faceC[0], faceC[1], faceC[2]);    // face color
        drawSemiCylinder(0.12*percentFull, thickness, 1000, 1.0);      // Draw semi-cylinder      
    }

    glPopMatrix();
}

// Joint to Joint length is 1.00
void robotShin(double percentFull, double thickness, double faceC[3], bool topLayer) {
    glPushMatrix();

    glTranslatef(0.0, 0.0, -thickness/4);             // To shift to 3/4 of thickness
    if (!topLayer) {
        glColor3f(faceC[0], faceC[1], faceC[2]);                        // Green face color
        drawSemiCylinder(0.12*percentFull, thickness/2, 1000, 1.0);     // Draw Semi-cylinder
        // end of cylinder
    }

    glTranslatef(0.0, -0.1, 0.0);               // Translate to bring cube top down
    if (!topLayer) {
        //drawFrame(1.0);
        glColor3f(faceC[0], faceC[1], faceC[2]);    // Green face color
        getCube(0.2*percentFull, 0.15, thickness/2);   // Draw Cube
    }
    glTranslatef(0.0, -0.15/2, 0.0);               // To get to end of cube
    glTranslatef(0.0, 0.0, thickness/4);              // To shift back from 3/4 of thickness
    
    glTranslatef(0.0, -0.15, 0.0);               // Translate to bring cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);    // Green face color
    getCube(0.2*percentFull, 0.3, thickness);   // Draw Cube
    glTranslatef(0.0, -0.15, 0.0);               // To get to end of cube
    
    glTranslatef(0.0, -0.05, 0.0);              // Translate to bring parallelogram top down
    glColor3f(faceC[0], faceC[1], faceC[2]);    // Green face color
    getParallelogram(0.2*percentFull, 0.1, thickness);            // Draw parallelogram
    glTranslatef(0.0, -0.05, 0.0);              // To get to end of parallelogram
    
    glTranslatef(0.0, -0.2, 0.0);               // Translate to bring cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);    // Green face color
    getCube(0.1*percentFull, 0.4, thickness);                     // Draw Cube
    glTranslatef(0.0, -0.2, 0.0);               // To get to end of cube

    //0.1 + 0.075 + 0.3 + 0.1 + 0.4  = 0.975 -> length so far
    glTranslatef(0.0, -(1.0-0.975), 0.0);               // Translate to bring cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);            // Green face color
    drawSemiCylinder(0.075*percentFull, thickness/2, 1000, 1.0);     // Draw Semi-cylinder
    glTranslatef(0.0, -0.0, 0.0);               // To get to end of cube

    glPopMatrix();
}

// Joint to Joint length is 
void robotFoot() {
    BMPtexture = BMPtexture2;
    glPushMatrix();
    
    int faceC[3] = {1.0, 1.0, 1.0};                 // face color

    // Ankle of foot
    glColor3f(faceC[0], faceC[1], faceC[2]);            // Green face color
    drawSemiCylinder(0.075, 0.05, 1000, 1.0);     // Draw Semi-cylinder

    // Front of foot
    glRotatef(-20.0, 0.0, 0.0, 1.0);                //
    glTranslatef(0.15, 0.0, 0.0);                   // Translate to bring cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getRightTriPrism(0.3, 0.15, 0.05);
    glTranslatef(0.0, -0.075, 0.0); 

    glTranslatef(0.0, -0.025, 0.125);               // Translate to bring cube top down
    glRotatef(90.0, 1.0, 0.0, 0.0);                 //
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getRightTriPrism(0.3, 0.15, 0.05);
    glRotatef(-90.0, 1.0, 0.0, 0.0);                //
    glTranslatef(0.0, 0.025,  -0.125); 

    glTranslatef(0.0, -0.025, -0.125);              // Translate to bring cube top down
    glRotatef(-90.0, 1.0, 0.0, 0.0);                //
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getRightTriPrism(0.3, 0.15, 0.05);              // 
    glRotatef(90.0, 1.0, 0.0, 0.0);                 //
    glTranslatef(0.0, 0.025,  0.125); 

    glTranslatef(0.15 - 0.1/2.0, -0.025, 0.0);      // Translate prism center to bottom of foot
    glRotatef(20.0, 0.0, 0.0, 1.0);                
    glRotatef(180.0, 0.0, 0.0, 1.0);                // 
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getParallelogram(0.2, 0.05, 0.2);               // Draw parallelogram
    glRotatef(180.0, 0.0, 0.0, 1.0); 
    glRotatef(-20.0, 0.0, 0.0, 1.0); 
    glTranslatef(-(0.15 - 0.1/2.0), 0.025, 0.0);    // Translate back

    // Translate back to ankle
    glTranslatef(-0.15, 0.075, 0.0); 
    glRotatef(20.0, 0.0, 0.0, 1.0);                 // 
    
    // Heel of foot
    glRotatef(180.0, 0.0, 1.0, 0.0);                //

    glRotatef(-6.66, 0.0, 0.0, 1.0);                //
    glTranslatef(0.225, 0.0, 0.0);                   // Translate to bring cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getRightTriPrism(0.45, 0.05, 0.05);
    glTranslatef(0.0, -0.05, 0.0); 

    glTranslatef(0.45/2.0 - 0.1/2.0, -0.0, 0.0);      // Translate prism center to bottom of foot
    glRotatef(20.0, 0.0, 0.0, 1.0);                
    glRotatef(180.0, 0.0, 0.0, 1.0);                // 
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getParallelogram(0.2, 0.05, 0.1);               // Draw parallelogram
    glRotatef(180.0, 0.0, 0.0, 1.0); 
    glRotatef(-20.0, 0.0, 0.0, 1.0); 
    glTranslatef(-(0.45/2.0 - 0.1/2.0), 0.0, 0.0);    // Translate back
    
    glPopMatrix();
}

double thighBendAngle = -45.0;             // Init thigh angle
double thighSign = 1.0;

double kneeBendAngle = 0.0;               // Knee angle
double sign = 1.0;

double ankleBendAngle = 0.0;              // Knee angle
double ankleSign = 1.0;

void drawRightLeg() {
  // Joint0: robotLeftLeg
  double totalThickness = 0.0;
  double prevThickness = 0.0;
  
  /*
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * Begin Thigh
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  
  BMPtexture = BMPtexture1;

  thighBendAngle = thighBendAngle + thighSign*0.2;
  if (thighBendAngle > 0) {
    thighSign = -1.0;
  }
  else if (thighBendAngle < -45.0) {
    thighSign = 1.0;
  }
  if (showFrames) {
    drawFrame(1.0);
  }
  glRotatef(thighBendAngle, 0.0, 0.0, 1.0);                  // Rotate thigh about hip
  //double faceC[3] = {1.0, 165.0/255.0, 0.0};      // Orange face color
  double faceC[3] = {1.0, 1.0, 1.0};                // White face color
  double thickness = 0.2;                           //
  totalThickness = totalThickness + thickness/2;    //
  prevThickness = thickness;                        //
  robotThigh(1.0, thickness, faceC, false);         // Draw thigh

  BMPtexture = BMPtexture4;

  faceC[1] = 0.5;                                   // face color
  thickness = prevThickness*0.2;                    //
  totalThickness = totalThickness + thickness;      //
  glTranslatef(0.0, 0.0, (thickness+prevThickness)/2.0);    // Translate to face of thigh
  robotThigh(0.75, thickness, faceC, true);         // Draw thigh top layer
  prevThickness = thickness;

  faceC[0] = 0.5;                                   // face color
  thickness = prevThickness*0.2;                    //
  totalThickness = totalThickness + thickness/2;    //
  glTranslatef(0.0, 0.0,(thickness+prevThickness)/2.0);    // Translate to face of thigh
  robotThigh(0.4, thickness, faceC, true);          // Draw thigh top layer
  prevThickness = thickness;

  glTranslatef(0.0, 0.0, -totalThickness);          // Translate back to center of bottom thigh layer
  glTranslatef(0.0, -0.66, 0.0);                    // Translate to end of thigh

  //glTranslatef(0.0, -0.5, 0.0);                   // Further translate to better view shin
  /*
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * Begin shin
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  BMPtexture = BMPtexture1;

  totalThickness = 0.0;                             // reset total thickness
  kneeBendAngle = kneeBendAngle + sign*0.2;         // Knee angle
  if (kneeBendAngle > 90) {
    sign = -1.0;
  }
  else if (kneeBendAngle < 0) {
    sign = 1.0;
  }
  glRotatef(kneeBendAngle, 0.0, 0.0, 1.0);          // Rotate shin
  if (showFrames) {
    drawFrame(1.0);  
  }                  
  //double faceCShin[3] = {0.5, 0.0, 1.0};            // Shin face color
  double faceCShin[3] = {1.0, 1.0, 1.0};                // White face color
  thickness = 0.2;                                  //
  totalThickness = totalThickness + thickness/2;    //
  prevThickness = thickness;                        //
  robotShin(1.0, thickness, faceCShin, false);      // Draw shin

  BMPtexture = BMPtexture4;

  faceCShin[1] = 0.5;                               // Shin face color
  thickness = prevThickness*0.2;                    //
  totalThickness = totalThickness + thickness;      //
  glTranslatef(0.0, 0.0, (thickness+prevThickness)/2.0);    // Translate to face of thigh
  robotShin(0.75, thickness, faceCShin, true);      // Draw shin
  prevThickness = thickness;                        //

  faceCShin[0] = 0.5;                               // Shin face color
  thickness = prevThickness*0.2;                    //
  totalThickness = totalThickness + thickness/2;    //
  glTranslatef(0.0, 0.0, (thickness+prevThickness)/2.0);    // Translate to face of thigh
  robotShin(0.4, thickness, faceCShin, true);       // Draw shin
  prevThickness = thickness;                        //
  
  glTranslatef(0.0, -1.0, 0.0);                     // Translate to end of shin
  glTranslatef(0.0, 0.0, -totalThickness);          // Translate back to center of bottom thigh layer

  /*
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * Begin foot
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  //glTranslatef(0.8, 0.0, 0.0);          // Translate foot for improved viewi
  BMPtexture = BMPtexture1;

  ankleBendAngle = ankleBendAngle + ankleSign*0.2;  // Knee angle
  if (ankleBendAngle > 0) {
    ankleSign = -1.0;
  }
  else if (ankleBendAngle < -90) {
    ankleSign = 1.0;
  }
  //ankleBendAngle = 0;
  glRotatef(ankleBendAngle, 0.0, 0.0, 1.0);         // Rotate foot
  if (showFrames) {
    drawFrame(1.0);  
  } 
  robotFoot();                                      // Draw foot
}

double leftThighBendAngle = 45.0;             // Init thigh angle
double leftThighSign = 1.0;

double leftKneeBendAngle = 0.0;               // Knee angle
double leftKneeSign = 1.0;

double leftAnkleBendAngle = 0.0;              // Knee angle
double leftAnkleSign = 1.0;

void drawLeftLeg() {
  // Joint0: robotLeftLeg
  double totalThickness = 0.0;
  double prevThickness = 0.0;
  // glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate leg 180

  /*
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * Begin Thigh
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate thigh 180
  BMPtexture = BMPtexture1;

  leftThighBendAngle = leftThighBendAngle + leftThighSign*0.2;         // Knee angle
  if (leftThighBendAngle > 45.0) {
    leftThighSign = -1.0;
  }
  else if (leftThighBendAngle < 0.0) {
    leftThighSign = 1.0;
  }

  if (showFrames) {
    drawFrame(1.0);  
  } 
  glRotatef(leftThighBendAngle, 0.0, 0.0, 1.0);                  // Rotate thigh about hip
  //double faceC[3] = {1.0, 165.0/255.0, 0.0};      // Orange face color
  double faceC[3] = {1.0, 1.0, 1.0};                // White face color
  double thickness = 0.2;                           //
  totalThickness = totalThickness + thickness/2;    //
  prevThickness = thickness;                        //
  robotThigh(1.0, thickness, faceC, false);         // Draw thigh

  BMPtexture = BMPtexture4;

  faceC[1] = 0.5;                                   // face color
  thickness = prevThickness*0.2;                    //
  totalThickness = totalThickness + thickness;      //
  glTranslatef(0.0, 0.0, (thickness+prevThickness)/2.0);    // Translate to face of thigh
  robotThigh(0.75, thickness, faceC, true);         // Draw thigh top layer
  prevThickness = thickness;

  faceC[0] = 0.5;                                   // face color
  thickness = prevThickness*0.2;                    //
  totalThickness = totalThickness + thickness/2;    //
  glTranslatef(0.0, 0.0,(thickness+prevThickness)/2.0);    // Translate to face of thigh
  robotThigh(0.4, thickness, faceC, true);          // Draw thigh top layer
  prevThickness = thickness;

  glTranslatef(0.0, 0.0, -totalThickness);          // Translate back to center of bottom thigh layer
  glTranslatef(0.0, -0.66, 0.0);                    // Translate to end of thigh
  glRotatef(-180.0f, 0.0, 1.0, 0.0);  // Rotate back 180

  //glTranslatef(0.0, -0.5, 0.0);                   // Further translate to better view shin
  /*
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * Begin shin
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate shin 180
  BMPtexture = BMPtexture1;
  
  totalThickness = 0.0;                                       // reset total thickness
  leftKneeBendAngle = leftKneeBendAngle + leftKneeSign*0.2;         // Knee angle
  if (leftKneeBendAngle > 90) {
    leftKneeSign = -1.0;
  }
  else if (leftKneeBendAngle < 0) {
    leftKneeSign = 1.0;
  }
  glRotatef(-leftKneeBendAngle, 0.0, 0.0, 1.0);          // Rotate shin
  if (showFrames) {
    drawFrame(1.0);  
  } 
  //double faceCShin[3] = {0.5, 0.0, 1.0};              // Shin face color
  double faceCShin[3] = {1.0, 1.0, 1.0};                // White face color
  thickness = 0.2;                                  //
  totalThickness = totalThickness + thickness/2;    //
  prevThickness = thickness;                        //
  robotShin(1.0, thickness, faceCShin, false);      // Draw shin
  
  BMPtexture = BMPtexture4;
  
  faceCShin[1] = 0.5;                               // Shin face color
  thickness = prevThickness*0.2;                    //
  totalThickness = totalThickness + thickness;      //
  glTranslatef(0.0, 0.0, (thickness+prevThickness)/2.0);    // Translate to face of thigh
  robotShin(0.75, thickness, faceCShin, true);      // Draw shin
  prevThickness = thickness;                        //

  faceCShin[0] = 0.5;                               // Shin face color
  thickness = prevThickness*0.2;                    //
  totalThickness = totalThickness + thickness/2;    //
  glTranslatef(0.0, 0.0, (thickness+prevThickness)/2.0);    // Translate to face of thigh
  robotShin(0.4, thickness, faceCShin, true);       // Draw shin
  prevThickness = thickness;                        //
  
  glTranslatef(0.0, -1.0, 0.0);                     // Translate to end of shin
  glTranslatef(0.0, 0.0, -totalThickness);          // Translate back to center of shin thigh layer
  glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate back 180

  /*
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * Begin foot
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  //glTranslatef(0.8, 0.0, 0.0);          // Translate foot for improved viewing
  BMPtexture = BMPtexture1;

  ankleBendAngle = ankleBendAngle + ankleSign*0.2;  // Knee angle
  if (ankleBendAngle > 0) {
    ankleSign = -1.0;
  }
  else if (ankleBendAngle < -90) {
    ankleSign = 1.0;
  }
  //ankleBendAngle = 0;
  glRotatef(ankleBendAngle, 0.0, 0.0, 1.0);         // Rotate foot
  if (showFrames) {
    drawFrame(1.0);  
  } 
  robotFoot();                                      // Draw foot
  
  
  //glRotatef(0.0, 0.0, 0.0, -1.0);
}

void drawRobotLeg() {
    glPushMatrix();
    drawRightLeg();
    glPopMatrix();
    //glTranslatef(0.0, 1.66, 0.0);    // Translate to face of thigh

    glTranslatef(0.0, 0.0, -1.0);    // Translate to face of thigh

    glPushMatrix();
    drawLeftLeg();
    glPopMatrix();
}
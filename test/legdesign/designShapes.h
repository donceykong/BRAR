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

    // Back face;
    glBegin(GL_QUADS);
    glNormal3f(0, 0,-1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
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

    // Right face
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( width/2, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2,  depth/2);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2, -height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2,  depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

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
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glNormal3f(0, 0,-1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/4, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/4, -height/2, -depth/2);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/4, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/4, -height/2, -depth/2);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( width/4, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/4, -height/2,  depth/2);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/4, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/4, -height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/4, -height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/4, -height/2,  depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0, 1.0, 1.0);   // White color
    glLineWidth(4.0f);          // Set line width to 2.0 pixels
    getParallelogramEdges(width, height, depth);
}
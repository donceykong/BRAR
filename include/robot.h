// Created by: Doncey Albin

static double joint0Angle = 0.0, joint1Angle = 0.0, joint2Angle = 0.0, joint3Angle = 0.0;

static double leftHipAngle = 0.0, rightHipAngle = 0.0;
static double rightHipSign = -1.0, leftHipSign = 1.0;

static double gripperRollAngle = 0.0;
static double gripperDist = 0.3;
static bool   gripperClosed = false;

void drawNormalArrow(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat scale) {
    glBegin(GL_LINES);
    glVertex3f(x, y, z);  // start point of the line (original vertex)
    glVertex3f(x + nx * scale, y + ny * scale, z + nz * scale);  // end point of the line
    glEnd();
}

void getFrontFaceVertices(GLfloat width, GLfloat height, GLfloat depth) {
    double textureScale = 0.8;
    double normalScale = 0.5;
    
    GLfloat nx = 0.0f, ny = 0.0f, nz = 1.0f; // Normal for the front face

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtextureID);
    
    glBegin(GL_QUADS);
    glNormal3f(nx, ny, nz);

    // Front face top quad vertices
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, height/2,  depth/2); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2 + (width/2)*textureScale, height/2 - (height/2)*textureScale,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2, height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2 - (width/2)*textureScale, height/2 - (height/2)*textureScale,  depth/2);
    glEnd();

    // Draw normals for the top quad
    drawNormalArrow(-width/2, height/2, depth/2, nx, ny, nz, normalScale);
    drawNormalArrow(-width/2 + (width/2)*textureScale, height/2 - (height/2)*textureScale, depth/2, nx, ny, nz, normalScale);
    drawNormalArrow( width/2, height/2, depth/2, nx, ny, nz, normalScale);
    drawNormalArrow( width/2 - (width/2)*textureScale, height/2 - (height/2)*textureScale, depth/2, nx, ny, nz, normalScale);

    glBegin(GL_QUADS);
    // Front face bottom quad vertices
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2, depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2 + (width/2)*textureScale, -height/2 + (height/2)*textureScale,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2, -height/2, depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2 - (width/2)*textureScale, -height/2 + (height/2)*textureScale,  depth/2);
    glEnd();

    // Draw normals for the bottom quad
    drawNormalArrow(-width/2, -height/2, depth/2, nx, ny, nz, normalScale);
    drawNormalArrow(-width/2 + (width/2)*textureScale, -height/2 + (height/2)*textureScale, depth/2, nx, ny, nz, normalScale);
    drawNormalArrow( width/2, -height/2, depth/2, nx, ny, nz, normalScale);
    drawNormalArrow( width/2 - (width/2)*textureScale, -height/2 + (height/2)*textureScale, depth/2, nx, ny, nz, normalScale);

    glBegin(GL_QUADS);
    // Front face left quad vertices
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2 + (width/2)*textureScale, height/2 - (height/2)*textureScale,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2 + (width/2)*textureScale, -height/2 + (height/2)*textureScale,  depth/2);
    glEnd();

    // Draw normals for the left quad
    drawNormalArrow(-width/2, height/2, depth/2, nx, ny, nz, normalScale);
    drawNormalArrow(-width/2 + (width/2)*textureScale, height/2 - (height/2)*textureScale, depth/2, nx, ny, nz, normalScale);
    drawNormalArrow(-width/2, -height/2, depth/2, nx, ny, nz, normalScale);
    drawNormalArrow(-width/2 + (width/2)*textureScale, -height/2 + (height/2)*textureScale, depth/2, nx, ny, nz, normalScale);

    glBegin(GL_QUADS);
    // Front face right quad vertices
    glTexCoord2f(0.0f, 0.0f); glVertex3f(width/2, height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(width/2 - (width/2)*textureScale, height/2 - (height/2)*textureScale,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(width/2, -height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(width/2 - (width/2)*textureScale, -height/2 + (height/2)*textureScale,  depth/2);
    glEnd();

    // Draw normals for the right quad
    drawNormalArrow(width/2, height/2, depth/2, nx, ny, nz, normalScale);
    drawNormalArrow(width/2 - (width/2)*textureScale, height/2 - (height/2)*textureScale, depth/2, nx, ny, nz, normalScale);
    drawNormalArrow(width/2, -height/2, depth/2, nx, ny, nz, normalScale);
    drawNormalArrow(width/2 - (width/2)*textureScale, -height/2 + (height/2)*textureScale, depth/2, nx, ny, nz, normalScale);

    glDisable(GL_TEXTURE_2D);
}

void getFrontFaceVertices_noTexture(GLfloat width, GLfloat height, GLfloat depth) {
    // Front face top quad
    glVertex3f(-width/2, height/2,  depth/2);
    glVertex3f(-width/2 + (width/2)*0.25, height/2 - (height/2)*0.25,  depth/2);
    glVertex3f( width/2, height/2,  depth/2);
    glVertex3f( width/2 - (width/2)*0.25, height/2 - (height/2)*0.25,  depth/2);

    // Front face bottom quad
    glVertex3f(-width/2, -height/2, depth/2);
    glVertex3f(-width/2 + (width/2)*0.25, -height/2 + (height/2)*0.25,  depth/2);
    glVertex3f( width/2, -height/2, depth/2);
    glVertex3f( width/2 - (width/2)*0.25, -height/2 + (height/2)*0.25,  depth/2);

    // Front face left quad
    glVertex3f(-width/2, height/2,  depth/2);
    glVertex3f(-width/2 + (width/2)*0.25, height/2 - (height/2)*0.25,  depth/2);
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2 + (width/2)*0.25, -height/2 + (height/2)*0.25,  depth/2);

    // Front face right quad
    glVertex3f(width/2, height/2,  depth/2);
    glVertex3f(width/2 - (width/2)*0.25, height/2 - (height/2)*0.25,  depth/2);
    glVertex3f(width/2, -height/2,  depth/2);
    glVertex3f(width/2 - (width/2)*0.25, -height/2 + (height/2)*0.25,  depth/2);
}

void getCubeVertices(GLfloat width, GLfloat height, GLfloat depth) {
    // Front face
    glColor3f(1.0, 1.0, 1.0);  // White color
    getFrontFaceVertices(width, height, depth);

    // Back face
    getFrontFaceVertices(width, height, -depth);

    // Left face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Right face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( width/2, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2,  depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Top face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Bottom face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2, -height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2,  depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void getCubeVerticesNoTexture(GLfloat width, GLfloat height, GLfloat depth) {
    // Front face
    glColor3f(1.0, 1.0, 1.0);  // White color
    getFrontFaceVertices_noTexture(width, height, depth);

    // Back face
    getFrontFaceVertices_noTexture(width, height, -depth);

    // Left face
    glBegin(GL_QUADS);
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f(-width/2, -height/2, -depth/2);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glVertex3f( width/2, -height/2, -depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2, -height/2, -depth/2);
    glVertex3f( width/2, -height/2, -depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
    glEnd();
}

void getCubeVerts(GLfloat width, GLfloat height, GLfloat depth) {
    glColor3f(1.0, 1.0, 1.0);  // White color, so the texture isn't modulated

    // Front face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2, -height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Back face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2, -depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Left face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Right face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( width/2, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2,  depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Top face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Bottom face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtextureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2, -height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2,  depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
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

void drawSemiCylinder(GLfloat radius, GLfloat height, int segments) {
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= segments; ++i) {
        GLfloat angle = i * M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        glNormal3f(x, y, 0.0f);
        glVertex3f(x, y, -height/2);  // Lower ring
        glVertex3f(x, y, height/2);  // Upper ring
    }
    glEnd();

    glLineWidth(2.0f);          // Set line width to 2.0 pixels
    glBegin(GL_LINES);
    for (int i = 0; i <= segments; i += 60) {
      GLfloat angle = i * M_PI / segments; 
      GLfloat x = radius * sin(angle);
      GLfloat y = radius * cos(angle);

      glVertex3f(x, y, -height/2);  // Lower ring
      glVertex3f(x, y, height/2);   // Upper ring
    }
    glEnd();

    // Draw bottom face
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, -height); // Center vertex
    glNormal3f(0.0f, 0.0f, -1.0f);
    for (int i = -segments; i <= segments; ++i) {
        GLfloat angle = i * M_PI / segments;
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        glVertex3f(x, y, -height/2);
    }
    glEnd();

    glLineWidth(2.0f);          // Set line width to 2.0 pixels
    glBegin(GL_LINES);
    glVertex3f(0, 0, -height);  // Center vertex
    for (int i = -segments; i <= segments; i += 2) {
        GLfloat angle = i * M_PI / segments;
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        glVertex3f(x, y, -height/2);
    }
    glEnd();

    // Draw top face
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, height);   // Center vertex
    glNormal3f(0.0f, 0.0f, 1.0f);
    for (int i = -segments; i <= segments; ++i) {
        GLfloat angle = i * M_PI / segments;
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        glVertex3f(x, y, height/2);
    }
    glEnd();

    glLineWidth(2.0f);          // Set line width to 2.0 pixels
    glBegin(GL_LINES);
    glVertex3f(0, 0, height);   // Center vertex
    for (int i = -segments; i <= segments; i += 2) {
        GLfloat angle = i * M_PI / segments;
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        glVertex3f(x, y, height/2);
    }
    glEnd();
}

void robotBase(GLfloat width, GLfloat height, GLfloat depth) {
    glPushMatrix();

    if (usingTextures) {
      getCubeVertices(width, height, depth);
    }
    else{
      getCubeVerticesNoTexture(width, height, depth);
    }

    glColor3f(0.0, 1.0, 0.0);  // Blue color
    glLineWidth(4.0f); // Set line width to 2.0 pixels
    glBegin(GL_LINES);
      getCubeEdges(width, height, depth);
    glEnd();
    
    float axisLen = 0.5;
    drawAxes(axisLen);

    // Draw first semi-cylinder
    glTranslatef(0.0, width/2, 0.0);
    drawSemiCylinder(height/2, depth, 1000);  // radius, height, segments

    glPopMatrix();
}

void robotLeg(GLfloat width, GLfloat height, GLfloat depth) {
    glPushMatrix();

    if (usingTextures) {
      getCubeVertices(width, height, depth);
    }
    else{
      getCubeVerticesNoTexture(width, height, depth);
    }

    glColor3f(1.0, 0.0, 0.0);  // Blue color
    glLineWidth(4.0f); // Set line width to 2.0 pixels
    glBegin(GL_LINES);
      getCubeEdges(width, height, depth);
    glEnd();
    
    float axisLen = 0.5;
    drawAxes(axisLen);

    // Draw first semi-cylinder
    glTranslatef(0.0, width/2, 0.0);
    //drawSemiCylinder(height/2, depth, 1000);  // radius, height, segments

    glPopMatrix();
}

void robotLink(GLfloat width, GLfloat height, GLfloat depth) {
    glPushMatrix();

    if (usingTextures) {
      getCubeVertices(width, height, depth);
    }
    else{
      getCubeVerticesNoTexture(width, height, depth);
    }

    glColor3f(0.0, 0.0, 1.0);  // Blue color
    glLineWidth(4.0f); // Set line width to 2.0 pixels
    glBegin(GL_LINES);
      getCubeEdges(width, height, depth);
    glEnd();

    // Draw first semi-cylinder
    glTranslatef(width/2, 0.0, 0.0);
    drawSemiCylinder(height/2, depth, 1000);  // radius, height, segments

    glPopMatrix();
}

void robotEndEffector(GLfloat width, GLfloat height, GLfloat depth) {
    glPushMatrix();

    // Draw gripper base
    if (usingTextures) {
      getCubeVertices(height, depth,  width*0.75);
    }
    else{
      getCubeVerticesNoTexture(height, depth,  width*0.75);
    }

    glColor3f(0.0, 0.0, 1.0);  // Blue color
    glLineWidth(4.0f); // Set line width to 2.0 pixels
    glBegin(GL_LINES);
      getCubeEdges(height, depth,  width*0.75);
    glEnd();

    // Draw left gripper
    glTranslatef(0.3, 0.0, -gripperDist);
    glRotatef(90.0, 0.0, 0.0, 1.0);

    if (usingTextures) {
      getCubeVertices(height, width*0.4, depth);
    }
    else{
      getCubeVerticesNoTexture(height, width*0.4, depth);
    }

    glColor3f(0.0, 0.0, 1.0);     // Blue color
    glLineWidth(4.0f);            // Set line width to 2.0 pixels
    glBegin(GL_LINES);
      getCubeEdges(height, width*0.4, depth);
    glEnd();

    // Draw right gripper
    glTranslatef(0.0, 0.0, gripperDist*2);
    glRotatef(0.0, 0.0, 0.0, 1.0);

    if (usingTextures) {
      getCubeVertices(height, width*0.4, depth);
    }
    else{
      getCubeVerticesNoTexture(height, width*0.4, depth);
    }

    glColor3f(0.0, 0.0, 1.0);     // Blue color
    glLineWidth(4.0f);            // Set line width to 2.0 pixels
    glBegin(GL_LINES);
      getCubeEdges(height, width*0.4, depth);
    glEnd(); 

    glPopMatrix();
}

void drawRobotArm() {
  float axisLen = 0.5;
  drawAxes(axisLen);

  // Joint0: Base
  glTranslatef(0.0, 0.0, 0.0);
  glRotatef((GLfloat)joint0Angle, 0.0, 1.0, 0.0);

  glTranslatef(0.0, 0.1, 0.0);
  robotBase(0.2, 0.2, 0.2);

  // Joint0: robotLeftLeg
  glRotatef((GLfloat)leftHipAngle, 0.0, 0.0, 1.0);
  glTranslatef(0.0, -1.25, 0.5);
  robotLeg(0.2, 2.5, 0.2);
  glTranslatef(0.0, 1.25, -0.5);
  glRotatef((GLfloat)leftHipAngle, 0.0, 0.0, -1.0);

  // Joint0: robotRightLeg
  glRotatef((GLfloat)rightHipAngle, 0.0, 0.0, 1.0);
  glTranslatef(0.0, -1.25, -0.5);
  robotLeg(0.2, 2.5, 0.2);
  glTranslatef(0.0,  1.25, 0.5);
  glRotatef((GLfloat)rightHipAngle, 0.0, 0.0, -1.0);

  // Joint1 & Link1
  glTranslatef(0.0, 0.1, 0.0); // At origin
  glRotatef((GLfloat)joint1Angle, 0.0, 0.0, 1.0);

  drawAxes(axisLen);
  glTranslatef(0.5, 0.0, 0.0);
  robotLink(1.0, 0.2, 0.2);
  
  // Joint2 & Link2
  glTranslatef(0.5, 0.0, 0.0);
  glRotatef((GLfloat)joint2Angle, 0.0, 0.0, 1.0);

  drawAxes(axisLen);
  glTranslatef(0.5, 0.0, 0.0);
  robotLink(1.0, 0.2, 0.2);

  // Joint3 & Link3
  glTranslatef(0.5, 0.0, 0.0);
  glRotatef((GLfloat)joint3Angle, 0.0, 0.0, 1.0);

  drawAxes(axisLen);
  glTranslatef(0.25, 0.0, 0.0);
  robotLink(0.5, 0.2, 0.2);

  // Joint4 & End Effector
  glTranslatef(0.25, 0.0, 0.0);
  glRotatef((GLfloat)gripperRollAngle, 1.0, 0.0, 0.0);

  drawAxes(axisLen);
  glTranslatef(0.1, 0.0, 0.0);
  robotEndEffector(1.0, 0.2, 0.2);

  computeForwardKinematics();
}
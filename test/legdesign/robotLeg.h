// Created by: Doncey Albin

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
    // face colors
    glColor3f(1.0, 165.0/255.0, 0.0);  // Orange color
  
    // Front face
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glNormal3f(0, 0,-1);
    glVertex3f(-width/2, -height/2, -depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f( width/2, -height/2, -depth/2);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f(-width/2, -height/2, -depth/2);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f( width/2, -height/2, -depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
    glEnd();

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

    glColor3f(1.0, 1.0, 1.0);  // White color
    glLineWidth(4.0f); // Set line width to 2.0 pixels
    glBegin(GL_LINES);
      getCubeEdges(width, height, depth);
    glEnd();
}

void drawSemiCylinderEdges(GLfloat radius, GLfloat height, int segments, double percentFull) {
    glColor3f(1.0, 1.0, 1.0);  // White color

    // glLineWidth(4.0f);          // Set line width to 2.0 pixels
    // glBegin(GL_LINES);
    // for (int i = 0; i <= segments; i += 60) {
    //   GLfloat angle = i * M_PI / segments; 
    //   GLfloat x = radius * sin(angle);
    //   GLfloat y = radius * cos(angle);

    //   glNormal3f(x, y, 0.0f);
    //   glVertex3f(x, y, -height/2);  // Lower ring
    //   glVertex3f(x, y, height/2);   // Upper ring
    // }
    // glEnd();

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

    glLineWidth(4.0f);          // Set line width to 2.0 pixels
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
    glColor3f(1.0, 165.0/255.0, 0.0);  // Orange color

    // Draw Outer Edge
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= segments; ++i) {
        GLfloat angle = -M_PI/2.0 + i * percentFull*2.0*M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        glNormal3f(x, y, 0.0f);
        glVertex3f(x, y, -height/2);  // Lower ring
        glVertex3f(x, y, height/2);  // Upper ring
    }
    glEnd();

    // Draw front face
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, height/2); // Center vertex Normal
    glVertex3f(0, 0, height/2);       // Center vertex
    for (int i = 0; i <= segments; ++i) {
        GLfloat angle = -M_PI/2.0 + i * percentFull*2.0*M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        glNormal3f(x, y, height/2);
        glVertex3f(x, y, height/2);
    }
    glEnd();

    // Draw back face
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, -height/2); // Center vertex
    glNormal3f(0.0f, 0.0f, -height/2);
    for (int i = 0; i <= segments; ++i) {
        GLfloat angle = -M_PI/2.0 + i * percentFull*2.0*M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        glNormal3f(x, y, 0.0f);
        glVertex3f(x, y, -height/2);
    }
    glEnd();

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
    // face colors
    glColor3f(1.0, 165.0/255.0, 0.0);  // Orange color

    // Front face
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(-width/4, -height/2,  depth/2);
    glVertex3f( width/4, -height/2,  depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glNormal3f(0, 0,-1);
    glVertex3f(-width/4, -height/2, -depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f( width/4, -height/2, -depth/2);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-width/4, -height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f(-width/4, -height/2, -depth/2);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f( width/4, -height/2, -depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f( width/4, -height/2,  depth/2);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);   // White color
    glLineWidth(4.0f);          // Set line width to 2.0 pixels
    getParallelogramEdges(width, height, depth);
}

void robotThigh() {
    glPushMatrix();
    
    drawSemiCylinder(0.2, 0.2, 1000, 0.5);

    glTranslatef(0.0, -0.05, 0.0);
    getCube(0.4, 0.1, 0.2);

    glTranslatef(0.0, -0.1, 0.0);
    getParallelogram(0.4, 0.1, 0.2);

    glTranslatef(0.0, -0.25, 0.0);
    getCube(0.2, 0.4, 0.2);

    glTranslatef(0.0, -0.22, 0.0);
    drawSemiCylinder(0.12, 0.2, 1000,1.0);
    
    glPopMatrix();
}

void drawRobotArm() {
  // Joint0: robotLeftLeg
  glRotatef(45.0, 0.0, 0.0, 1.0);
  robotThigh();

  glTranslatef(0.0, -1.0, 0.0);
  glRotatef(45.0, 0.0, 0.0, 1.0);
  robotThigh();
  //glRotatef(0.0, 0.0, 0.0, -1.0);
}
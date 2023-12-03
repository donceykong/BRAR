#ifndef ROBOT_ARM_H
#define ROBOT_ARM_H

void drawNormalArrow(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat scale) {
    glBegin(GL_LINES);
    glVertex3f(x, y, z);  // start point of the line (original vertex)
    glVertex3f(x + nx * scale, y + ny * scale, z + nz * scale);  // end point of the line
    glEnd();
}

void robotBase(GLfloat width, GLfloat height, GLfloat depth, double faceC[3]) {
    glPushMatrix();

    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    BMPtexture = BMPtexture5;
    getCuboid(width, height, depth);
    BMPtexture = BMPtexture1;

    float axisLen = 0.5;
    drawFrame(axisLen);

    // Draw first semi-cylinder
    glTranslatef(0.0, width/2, 0.0);
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    BMPtexture = BMPtexture3;
    drawSemiCylinder(height/2, depth, 1000, 0.5);  // radius, height, segments, percent full
    BMPtexture = BMPtexture1;

    glPopMatrix();
}

void robotLink(GLfloat width, GLfloat height, GLfloat depth, double faceC[3]) {
    glPushMatrix();

    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getCuboid(width, 0.75*height, 0.75*depth);
    // glTranslatef(width/2, 0.0, 0.0);

    // glTranslatef(width*0.5, 0.0, 0.0);
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    BMPtexture = BMPtexture2;
    getCuboid(width*0.5, height, depth);
    BMPtexture = BMPtexture1;

    // Draw first semi-cylinder
    glTranslatef(width*0.5, 0.0, 0.0);
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    BMPtexture = BMPtexture3;
    drawSemiCylinder(height/2, depth, 1000, 1.0);   // radius, height, segments, percent full
    BMPtexture = BMPtexture1;

    glPopMatrix();
}

void robotEndEffector(GLfloat width, GLfloat height, GLfloat depth, double faceC[3]) {
    glPushMatrix();
    //glColor3f(0.8, 0.8, 1.0);   // Purpleish color

    // Draw gripper base
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getCuboid(height, depth,  width*0.75);

    // Draw left gripper
    glTranslatef(0.3, 0.0, -gripperDist);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getCuboid(height, width*0.4, depth);

    // Draw right gripper
    glTranslatef(0.0, 0.0, gripperDist*2);
    glRotatef(0.0, 0.0, 0.0, 1.0);
    
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getCuboid(height, width*0.4, depth);

    glPopMatrix();
}

void drawRobotArm() {
  float axisLen = 0.5;
  drawFrame(axisLen);

  BMPtexture = BMPtexture1;
  double faceC[3] = {1.0, 1.0, 1.0};              // White face color

  // // Joint0: Base
  //glRotatef((GLfloat)joint0Angle, 0.0, 1.0, 0.0);

  glTranslatef(0.0, 0.1, 0.0);
  robotBase(0.2, 0.2, 0.2, faceC);

  // Joint1 & Link1
  glTranslatef(0.0, 0.1, 0.0); // At origin
  glRotatef((GLfloat)joint1Angle, 0.0, 0.0, 1.0);

  drawFrame(axisLen);
  glTranslatef(0.5, 0.0, 0.0);
  robotLink(1.0, 0.2, 0.2, faceC);
  
  // Joint2 & Link2
  glTranslatef(0.5, 0.0, 0.0);
  glRotatef((GLfloat)joint2Angle, 0.0, 0.0, 1.0);

  drawFrame(axisLen);
  glTranslatef(0.5, 0.0, 0.0);
  robotLink(1.0, 0.2, 0.2, faceC);

  // Joint3 & Link3
  glTranslatef(0.5, 0.0, 0.0);
  glRotatef((GLfloat)joint3Angle, 0.0, 0.0, 1.0);

  drawFrame(axisLen);
  glTranslatef(0.25, 0.0, 0.0);
  robotLink(0.5, 0.2, 0.2, faceC);

  // Joint4 & End Effector
  glTranslatef(0.25, 0.0, 0.0);
  glRotatef((GLfloat)gripperRollAngle, 1.0, 0.0, 0.0);

  drawFrame(axisLen);
  glTranslatef(0.1, 0.0, 0.0);
  robotEndEffector(1.0, 0.2, 0.2, faceC);

  //adjustAngles();
}

#endif // ROBOT_ARM_H
#ifndef MISC_OBJECTS_H
#define MISC_OBJECTS_H

// Draw frames on robot joints
extern bool showFrames;  // Show joint frames

void drawFrame(float length) {
    if (showFrames) { 
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
}

void drawAxes(float length) {
    glBegin(GL_LINES);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(length,0.0,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,length,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,0.0,length);
    glEnd();
    
    //  Label axes
    glRasterPos3d(length,0.0,0.0);
    Print("X");
    glRasterPos3d(0.0,length,0.0);
    Print("Y");
    glRasterPos3d(0.0,0.0,length);
    Print("Z");
}

void drawText3D() {
    if (ballInHandBool) {
        for (double i = 0.0; i < 2*M_PI; i+=0.5) {
            for (double j = 0.0; j < 2*M_PI; j+=0.5) {
                double textPosX = runnerPosX + (i/3)*8.0*cos(j);
                double textPosY = runnerPosY - (i/3)*8.0*sin(i);
                double textPosZ = runnerPosZ - (i/3)*8.0*sin(j);
                glRasterPos3d(textPosX, textPosY, textPosZ);
                Print("YOU LOSE");
            }
        }
    }
    else {
        glRasterPos3d(runnerPosX + 0.5, runnerPosY + 0.5, runnerPosZ - 2.0);
        Print("runner speed: %f, chaser speed %f", runnerSpeed, monsterRobotSpeed);
    }
}

#endif // MISC_OBJECTS_H
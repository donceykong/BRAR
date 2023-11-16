
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

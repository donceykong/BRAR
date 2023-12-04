#ifndef VIEWS_H
#define VIEWS_H

// Global Variables
int viewMode = 1;  // 1 = First Person, 2 = Orbit
GLfloat perspectiveCamX = 0, perspectiveCamY = 0, perspectiveCamZ = 4;
GLfloat firstPersonCamZPrev = 0;
GLfloat firstPersonCamX = 0.0, firstPersonCamY = 5.0, firstPersonCamZ = 0.0;
GLfloat fpCamZoomX = 0.0, fpCamZoomY = 5.0, fpCamZoomZ = 10.0;
GLfloat fpCamZoom = 1.0;

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLfloat distance = 0.0f;

int mouseX, mouseY;
int isDragging = 0;

void perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar) {
    GLfloat f = 1.0f / tan(fovy / 2.0f);
    GLfloat depth = zNear - zFar;

    GLfloat m[16] = {
        f / aspect, 0, 0, 0,
        0, f, 0, 0,
        0, 0, (zFar + zNear) / depth, 2 * zFar * zNear / depth,
        0, 0, -1, 0
    };
    glMultMatrixf(m);
}

// void setOrthogonalProjection() {
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(-4, 4, -4, 4, -4, 4);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
// }

// void setPerspectiveProjection() {
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     perspective((GLfloat)45, 1.0f, (GLfloat)1, (GLfloat)10);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();

//     glRotatef(0, 1, 0, 0);
//     glRotatef(0, 0, 1, 0);
//     glRotatef(0, 0, 0, 1);

//     glTranslatef(-perspectiveCamX, -perspectiveCamY, -perspectiveCamZ);
// }

void setFirstPersonView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspective(45.0f, 1.0f, 1.0f, 10.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0, -fpCamZoomY*fpCamZoom, -fpCamZoomZ*fpCamZoom);
    glRotatef(-angleY, 0, 1, 0);
    glTranslatef(-firstPersonCamX, -firstPersonCamY, -firstPersonCamZ);
}

void setOrbit() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspective(45.0f, 1.0f, 1.0f, 10.0f);

    glMatrixMode(GL_MODELVIEW);
    perspective(45.0f, 1.0f, 1.0f, 10.0f);

    glLoadIdentity();

    glRotatef(90, 1, 0, 0);
    glRotatef(-runnerYawAngle+180, 0, 1, 0);
    //glRotatef(90, 1, 0, 0);
    double poseDiff = 0.5*sqrt((runnerPosX-chaserPosX)*(runnerPosX-chaserPosX) + (runnerPosZ-chaserPosZ)*(runnerPosZ-chaserPosZ));
    glTranslatef(-runnerPosX + (runnerPosX-chaserPosX)/2.0, -10 - poseDiff, -runnerPosZ + (runnerPosZ-chaserPosZ)/2.0); //glTranslatef(-posX, -posY -10, -posZ);
}

void displayView() {
    if (viewMode == 1) {
        setFirstPersonView();
    } else if (viewMode == 2) {
        setOrbit();
    }
}

#endif // VIEWS_H
// Doncey Albin
// CS, Fall 2023

#include "views.h"

// Global Variables
int viewMode = 1;  // 1 = First Person, 2 = Orbit

// GLfloat perspectiveCamX = 0, perspectiveCamY = 0, perspectiveCamZ = 4;

GLfloat OrbitCamZPrev = 0;
GLfloat orbitCamX = 0.0, orbitCamY = 5.0, orbitCamZ = 0.0;
GLfloat orbitCamAngleY = 0.0f;

GLfloat fpCamZoomX = 0.0, fpCamZoomY = 5.0, fpCamZoomZ = 10.0;
GLfloat fpCamZoom = 1.0;

GLfloat overheadCamX = 0.0, overheadCamY = 5.0, overheadCamZ = 0.0;
GLfloat overheadCamAngleY = 0.0f;

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

void setOrbitView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspective(45.0f, 1.0f, 1.0f, 10.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0, -fpCamZoomY*fpCamZoom, -fpCamZoomZ*fpCamZoom);
    glRotatef(-orbitCamAngleY, 0, 1, 0);
    glTranslatef(-orbitCamX, -orbitCamY, -orbitCamZ);
}

void setOverheadView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspective(45.0f, 1.0f, 1.0f, 10.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0, -fpCamZoomY*fpCamZoom, -fpCamZoomZ*fpCamZoom);
    glRotatef(90, 1, 0, 0);
    glRotatef(-overheadCamAngleY, 0, 1, 0);
    glTranslatef(overheadCamX, overheadCamY, overheadCamZ);
}

void displayView() {
    if (viewMode == 1) {
        setOrbitView();
    } else if (viewMode == 2) {
        setOverheadView();
    }
}
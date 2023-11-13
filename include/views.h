// Created by: Doncey Albin

// Global Variables
int viewMode = 1;  // 1 = Orthogonal, 2 = Perspective, 3 = First Person, 4 = Top-Down
GLfloat perspectiveCamX = 0, perspectiveCamY = 0, perspectiveCamZ = 4;
GLfloat firstPersonCamZPrev = 0;
GLfloat firstPersonCamX = 0.0, firstPersonCamY = 0.0, firstPersonCamZ = 4.0;

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

void setOrthogonalProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4, 4, -4, 4, -4, 4);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setPerspectiveProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspective((GLfloat)45, 1.0f, (GLfloat)1, (GLfloat)10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(0, 1, 0, 0);
    glRotatef(0, 0, 1, 0);
    glRotatef(0, 0, 0, 1);

    glTranslatef(-perspectiveCamX, -perspectiveCamY, -perspectiveCamZ);
}

void setFirstPersonView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspective(45.0f, 1.0f, 1.0f, 10.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-angleY, 0, 1, 0);
    glTranslatef(-firstPersonCamX, -firstPersonCamY, -firstPersonCamZ);
}

void setTopDownView() {
    GLfloat topDownCamX = 0.0f; // or any desired X position
    GLfloat topDownCamY = 10.0f; // or any desired height
    GLfloat topDownCamZ = 0.0f; // or any desired Z position
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4, 4, -4, 4, -10, 20); // Adjust as necessary
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        topDownCamX, topDownCamY, topDownCamZ,  // Camera position
        0, 0, 0,  // Look at the center of the scene
        0, 0, -1  // Up is in the negative Z direction
    );
}

void setOrbit() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspective(45.0f, 1.0f, 1.0f, 10.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(90, 1, 0, 0);
    glRotatef(-angleYObject+180, 0, 1, 0);
    glTranslatef(-posX, -posY -10, -posZ);
}

void displayView() {
    if (viewMode == 1) {
        setOrthogonalProjection();
    } else if (viewMode == 2) {
        setOrbit();
    } else if (viewMode == 3) {
        setFirstPersonView();
    } else if (viewMode == 4) {
        setTopDownView();
    }
}
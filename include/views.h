// Created by: Doncey Albin

// Global Variables
int viewMode = 1;  // 1 = Orthogonal, 2 = Perspective, 3 = First Person
GLfloat perspectiveCamX = 0, perspectiveCamY = 0, perspectiveCamZ = 4;
GLfloat firstPersonCamZPrev = 0;
GLfloat firstPersonCamX = 0.0, firstPersonCamY = 0.0, firstPersonCamZ = 4.0;

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLfloat distance = 0.0f;
int mouseX, mouseY;
int isDragging = 0;

/*
 * Handles the perspective view. 
 * 
*/
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

    //glRotatef(-angleX, 1, 0, 0);
    glRotatef(-angleY, 0, 1, 0);
    //glRotatef(0, 0, 0, 1);
    
    glTranslatef(-firstPersonCamX, -firstPersonCamY, -firstPersonCamZ);
}

void displayView() {
    if (viewMode == 1) {
        setOrthogonalProjection();
    } else if (viewMode == 2) {
        setPerspectiveProjection();
    } else if (viewMode == 3) {
        setFirstPersonView();
    }
}
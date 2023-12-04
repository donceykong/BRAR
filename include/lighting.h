#ifndef LIGHTING_H
#define LIGHTING_H

bool lightsEnabled = true;
double lightrot = 0.0;

double lightingDist = 4.0;

GLfloat light1_X = 0.80, light1_Y = 2.00, light1_Z = 0.00;
GLfloat light1Rotation = 0.0f;
const GLfloat light1RotationSpeed = 1.5f;

GLfloat light2_X = 0.80, light2_Y = 2.00, light2_Z = 0.00;
GLfloat light2Rotation = 0.0f;
const GLfloat light2RotationSpeed = 1.5f;

double ambient = 0.2, diffuse = 1.0, specular = 1.0;  
GLfloat spotExponent = 1.0; // for a moderately focused light
GLfloat spotCutoff = 45.0; // for a 45-degree cone of light

const GLfloat rectangleWidth = 0.5, rectangleHeight = 0.5;
const GLfloat prismHeight = 1.0, prismBase = 0.5;

void drawLightSource() {
    GLfloat emissiveColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; // RGBA
    glMaterialfv(GL_FRONT, GL_EMISSION, emissiveColor);
    glColor3f(1, 0.5, 0);                                           
    glBegin(GL_QUADS);
        glVertex3f(-rectangleWidth / 2, -rectangleHeight / 2, 0);
        glVertex3f( rectangleWidth / 2, -rectangleHeight / 2, 0);
        glVertex3f( rectangleWidth / 2,  rectangleHeight / 2, 0);
        glVertex3f(-rectangleWidth / 2,  rectangleHeight / 2, 0);
    glEnd();

    GLfloat lessEmission[] = {0.1f, 0.1f, 0.1f, 1.0f}; // Black (no emission)
    glMaterialfv(GL_FRONT, GL_EMISSION, lessEmission);
    glColor3f(1, 1, 1);
    // Draw the prism to represent the direction
    glBegin(GL_QUADS);
        glVertex3f(-prismBase / 2, -prismBase / 2, 0);
        glVertex3f( prismBase / 2, -prismBase / 2, 0);
        glVertex3f( prismBase / 2,  prismBase / 2, 0);
        glVertex3f(-prismBase / 2,  prismBase / 2, 0);
    glEnd();

    glBegin(GL_TRIANGLES);  // Top face of the prism
        glVertex3f(0, 0, prismHeight);
        glVertex3f(-prismBase / 2, -prismBase / 2, 0);
        glVertex3f(prismBase / 2, -prismBase / 2, 0);

        glVertex3f(0, 0, prismHeight);
        glVertex3f(prismBase / 2, -prismBase / 2, 0);
        glVertex3f(prismBase / 2,  prismBase / 2, 0);

        glVertex3f(0, 0, prismHeight);
        glVertex3f(prismBase / 2,  prismBase / 2, 0);
        glVertex3f(-prismBase / 2,  prismBase / 2, 0);

        glVertex3f(0, 0, prismHeight);
        glVertex3f(-prismBase / 2,  prismBase / 2, 0);
        glVertex3f(-prismBase / 2, -prismBase / 2, 0);
    glEnd();

    GLfloat noEmission[] = {0.0f, 0.0f, 0.0f, 1.0f}; // Black (no emission)
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
}

void drawLightSourceEdges() {
    GLfloat emissiveColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; // RGBA
    glMaterialfv(GL_FRONT, GL_EMISSION, emissiveColor);
    glColor3f(0, 0, 0);
    // Draw the rectangle
    glBegin(GL_LINES);
        glVertex3f(-rectangleWidth / 2, -rectangleHeight / 2, 0);
        glVertex3f( rectangleWidth / 2, -rectangleHeight / 2, 0);
        glVertex3f( rectangleWidth / 2,  rectangleHeight / 2, 0);
        glVertex3f(-rectangleWidth / 2,  rectangleHeight / 2, 0);
    glEnd();

    // Draw the prism to represent the direction
    glBegin(GL_LINES);
        glVertex3f(-prismBase / 2, -prismBase / 2, 0);
        glVertex3f( prismBase / 2, -prismBase / 2, 0);
        glVertex3f( prismBase / 2,  prismBase / 2, 0);
        glVertex3f(-prismBase / 2,  prismBase / 2, 0);
    glEnd();

    glBegin(GL_LINES);  // Top face of the prism
        glVertex3f(0, 0, prismHeight);
        glVertex3f(-prismBase / 2, -prismBase / 2, 0);
        glVertex3f(prismBase / 2, -prismBase / 2, 0);

        glVertex3f(0, 0, prismHeight);
        glVertex3f(prismBase / 2, -prismBase / 2, 0);
        glVertex3f(prismBase / 2,  prismBase / 2, 0);

        glVertex3f(0, 0, prismHeight);
        glVertex3f(prismBase / 2,  prismBase / 2, 0);
        glVertex3f(-prismBase / 2,  prismBase / 2, 0);

        glVertex3f(0, 0, prismHeight);
        glVertex3f(-prismBase / 2,  prismBase / 2, 0);
        glVertex3f(-prismBase / 2, -prismBase / 2, 0);
    glEnd();
    GLfloat noEmission[] = {0.0f, 0.0f, 0.0f, 1.0f}; // Black (no emission)
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noEmission);
}

void showLights() {
    float ambientColor[]    = {ambient, ambient, ambient, 1.0};
    float diffuseColor[]    = {diffuse, diffuse, diffuse, 1.0};
    float specularColor[]   = {specular, specular, specular, 1.0};
    float light1Position[]  = {light1_X, light1_Y, light1_Z, 1.0};
    float light2Position[]  = {light2_X, light2_Y, light2_Z, 1.0};

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glEnable(GL_LIGHT1);

    // Set ambient, diffuse, specular components, position, and direction of light 1
    glLightfv(GL_LIGHT1, GL_AMBIENT,  ambientColor);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  diffuseColor);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularColor);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);   // Translate the light
    GLfloat light1Direction[] = {sin(light1Rotation * M_PI / 180.0), 0.0, cos(light1Rotation * M_PI / 180.0), 1.0};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1Direction);

    // glEnable(GL_LIGHT2);

    // // Set ambient, diffuse, specular components, position, and direction of light 1
    // glLightfv(GL_LIGHT2, GL_AMBIENT,  ambientColor);
    // glLightfv(GL_LIGHT2, GL_DIFFUSE,  diffuseColor);
    // glLightfv(GL_LIGHT2, GL_SPECULAR, specularColor);
    // glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);
    // glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutoff);
    // glLightfv(GL_LIGHT2, GL_POSITION, light2Position);   // Translate the light
    // GLfloat light2Direction[] = {sin((light2Rotation) * M_PI / 180.0), 0.0, cos((light2Rotation) * M_PI / 180.0), 1.0};
    // glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2Direction);
}

void drawLights() {
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(light1_X, light1_Y, light1_Z);
    glRotatef(light1Rotation + 180.0, 0.0f, 1.0f, 0.0f);
    drawLightSource();
    drawLightSourceEdges();
    glPopMatrix();

    // glPushMatrix();
    // glColor3f(1, 1, 1);
    // glTranslatef(light2_X, light2_Y, light2_Z);
    // glRotatef(light2Rotation + 180.0, 0.0f, 1.0f, 0.0f);
    // drawLightSource();
    // drawLightSourceEdges();
    // glPopMatrix();
}

void setupLighting() {
    if (lightsEnabled) {
        drawLights();
        showLights();
    } 
    else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
    }
}

#endif // LIGHTING_H
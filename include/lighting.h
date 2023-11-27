#ifndef LIGHTING_H
#define LIGHTING_H

GLfloat light1_X = 0.80, light1_Y = 2.00, light1_Z = 0.00;
GLfloat light1Rotation = 0.0f;
const GLfloat light1RotationSpeed = 1.5f;

GLfloat light2_X = 0.80, light2_Y = 2.00, light2_Z = 0.00;
GLfloat light2Rotation = 0.0f;
const GLfloat light2RotationSpeed = 1.5f;

GLfloat light3_X = 0.80, light3_Y = 2.00, light3_Z = 0.00;
GLfloat light3Rotation = 0.0f;
const GLfloat light3RotationSpeed = 1.5f;

bool lightEnabled = true;
double ambient = 0.4, diffuse = 0.8, specular = 0.6;  
GLfloat spotExponent = 1.0; // for a moderately focused light
GLfloat spotCutoff = 45.0; // for a 45-degree cone of light

const GLfloat rectangleWidth = 0.2, rectangleHeight = 0.2;
const GLfloat prismHeight = 0.4, prismBase = 0.2;

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

void DrawLight1() {
    float ambientColor[]   = {0.8 * ambient, 0.8 * ambient, 0.8 * ambient, 1.0};
    float diffuseColor[]   = {0.8 * diffuse, 0.8 * diffuse, 0.8 * diffuse, 1.0};
    float specularColor[]  = {0.8 * specular, 0.8 * specular, 0.8 * specular, 1.0};
    float light1Position[]  = {light1_X, light1_Y, light1_Z + 3, 1.0};

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glColor3f(1, 1, 1);
    glTranslatef(light1_X, light1_Y, light1_Z);
    glRotatef(light1Rotation + 180, 0.0f, 1.0f, 0.0f);
    //glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
    //glTranslatef(0.0f, 0.0f, 3.0f);
    drawLightSource();
    drawLightSourceEdges();
    glPopMatrix();

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    // Set ambient, diffuse, specular components, position, and direction of light 1
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT,  ambientColor);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  diffuseColor);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularColor);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);   // Translate the light
    GLfloat light1Direction[] = {sin(light1Rotation * M_PI / 180.0), 0.0, cos(light1Rotation * M_PI / 180.0), 1.0};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1Direction);
}

void DrawLight2() {
    float ambientColor[]   = {0.8 * ambient, 0.8 * ambient, 0.8 * ambient, 1.0};
    float diffuseColor[]   = {0.8 * diffuse, 0.8 * diffuse, 0.8 * diffuse, 1.0};
    float specularColor[]  = {0.8 * specular, 0.8 * specular, 0.8 * specular, 1.0};
    float light2Position[]  = {light2_X, light2_Y, light2_Z, 1.0};

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glColor3f(1, 1, 1);
    glTranslatef(light2_X, light2_Y, light2_Z);
    glRotatef(light2Rotation + 180.0, 0.0f, 1.0f, 0.0f);
    //glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    //glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 3.0f);
    drawLightSource();
    drawLightSourceEdges();
    glPopMatrix();

    // Set ambient, diffuse, specular components, position, and direction of light 1
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_AMBIENT,  ambientColor);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  diffuseColor);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specularColor);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutoff);
    glLightfv(GL_LIGHT2, GL_POSITION, light2Position);   // Translate the light
    GLfloat light2Direction[] = {sin(light2Rotation * M_PI / 180.0), 0.0, cos(light2Rotation * M_PI / 180.0), 1.0};
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2Direction);
}

void DrawLight3() {
    float ambientColor[]   = {0.8 * ambient, 0.8 * ambient, 0.8 * ambient, 1.0};
    float diffuseColor[]   = {0.8 * diffuse, 0.8 * diffuse, 0.8 * diffuse, 1.0};
    float specularColor[]  = {0.8 * specular, 0.8 * specular, 0.8 * specular, 1.0};
    float light3Position[]  = {light3_X, light3_Y, light3_Z, 1.0};

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    glColor3f(1, 1, 1);
    glTranslatef(light3_X, light3_Y, light3_Z);
    glRotatef(light3Rotation+180.0, 0.0f, 1.0f, 0.0f);
    //glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    //glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 3.0f);
    drawLightSource();
    drawLightSourceEdges();
    glPopMatrix();

    // Set ambient, diffuse, specular components, position, and direction of light 1
    glEnable(GL_LIGHT3);
    glLightfv(GL_LIGHT3, GL_AMBIENT,  ambientColor);
    glLightfv(GL_LIGHT3, GL_DIFFUSE,  diffuseColor);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specularColor);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, spotExponent);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spotCutoff);
    glLightfv(GL_LIGHT3, GL_POSITION, light3Position);   // Translate the light
    GLfloat light3Direction[] = {sin(light3Rotation * M_PI / 180.0), 0.0, cos(light3Rotation * M_PI / 180.0), 1.0};
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3Direction);
}

void setupLighting() {
    if (lightEnabled) {
        // glEnable(GL_NORMALIZE);
        // glEnable(GL_LIGHTING);
        // glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

        DrawLight1();
        DrawLight2();
        DrawLight3();

        //GLfloat global_ambient[] = {0.1, 0.1, 0.1, 1.0};  // This will give a very dim light to everything in the scene
        //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

        // // Set ambient, diffuse, specular components, and position of light 0
        // glEnable(GL_LIGHT0);
        // glLightfv(GL_LIGHT0, GL_AMBIENT,  ambientColor);
        // glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuseColor);
        // glLightfv(GL_LIGHT0, GL_SPECULAR, specularColor);
        // glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);   // Translate the light

        // // Set ambient, diffuse, specular components, position, and direction of light 1
        // glEnable(GL_LIGHT1);
        // glLightfv(GL_LIGHT1, GL_AMBIENT,  ambientColor);
        // glLightfv(GL_LIGHT1, GL_DIFFUSE,  diffuseColor);
        // glLightfv(GL_LIGHT1, GL_SPECULAR, specularColor);
        // glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExponent);
        // glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
        // glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);   // Translate the light
        // GLfloat light1Direction[] = {sin(lightRotation * M_PI / 180.0), 0.0, cos(lightRotation * M_PI / 180.0), 1.0};
        // glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1Direction);  
    } 
    else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
    }
}

#endif // LIGHTING_H
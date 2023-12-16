// Doncey Albin
// lighting library

#include "lighting.h"

float sinInc = 0.0;

double ambientLightVal = 0.02;
double diffuseLightVal = 0.64;
double specularLightVal = 1.0;

void enableLights(LightArray* lights) {
    glEnable(GL_LIGHT0);
    for (int i = 1; i < 8; i++) {
        GLenum glLight = i;
        glEnable(glLight);
    }
}

void disableLights(LightArray* lights) {
    glEnable(GL_LIGHT0);
    for (int i = 1; i < 8; i++) {
        GLenum glLight = i;
        glDisable(glLight);
    }
}

void illumLight(lightStruct* light, int lightIter) {
    GLfloat ambient = light->ambient;
    GLfloat diffuse = light->diffuse;
    GLfloat specular = light->specular;

    GLfloat spotExponent = light->spotExponent;
    GLfloat spotCutoff = light->spotCutoff;
    
    float rotation = light->angularPos.y;
    Vector3 position = light->position;

    float ambientColor[]  = {ambient, ambient, ambient, 1.0};
    float diffuseColor[]  = {diffuse, diffuse, diffuse, 1.0};
    float specularColor[] = {specular, specular, specular, 1.0};
    float lightPosition[] = {position.x, position.y, position.z, 1.0};

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    // Determine which OpenGL light to use based on lightIter
    GLenum glLight = GL_LIGHT0 + lightIter;

    glLightfv(glLight, GL_AMBIENT, ambientColor);
    glLightfv(glLight, GL_DIFFUSE, diffuseColor);
    glLightfv(glLight, GL_SPECULAR, specularColor);
    glLightfv(glLight, GL_POSITION, lightPosition);   // Translate the light

    // Set ambient, diffuse, specular components, position, and direction of light
    if (light->spotlightOn) {
        glLightf(glLight, GL_SPOT_EXPONENT, spotExponent);
        glLightf(glLight, GL_SPOT_CUTOFF, spotCutoff);
        GLfloat lightDirection[] = {sin(rotation * M_PI / 180.0), 0.0, cos(rotation * M_PI / 180.0), 1.0};
        glLightfv(glLight, GL_SPOT_DIRECTION, lightDirection);
    }
    else {
        // Set spot cutoff to 180 to effectively disable the spotlight effect
        glLightf(glLight, GL_SPOT_CUTOFF, 180.0);
    }
}

void drawLight(lightStruct* light) {
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glEnable(GL_COLOR_MATERIAL);

    glPushMatrix();
    glColor3f(0, 1, 1);

    glTranslatef(light->position.x, light->position.y, light->position.z);
    glRotatef(light->angularPos.y + 180.0, 0.0f, 1.0f, 0.0f);
    drawSphere(0.2, 100, 100);
    drawPrism(light->rectangleWidth, light->rectangleHeight, light->prismBase, light->prismHeight);
    glPopMatrix();

    glDisable(GL_DEPTH_TEST);
}

void showLights(bool lightingEnabled, bool spotlightsEnabled, LightArray* lights) {
    for (int i = 0; i < 8; i++) {
        illumLight(&(lights->light[i]), i); // Regular light illumination
        
        // generate random position and angle increments for lights
        if (i > 0 && lightingEnabled) {
            lights->light[i].ambient = ambientLightVal;
            lights->light[i].diffuse = diffuseLightVal;
            lights->light[i].specular = specularLightVal;
            lights->light[i].position.x += 0.1*cos(sinInc)*(rand() % 2 - 1);     // +/- 100 units from center.x
            lights->light[i].position.z += 0.1*sin(sinInc)*(rand() % 2 - 1);     // +/- 100 units from center.z
            lights->light[i].angularPos.y += 0.1*sin(sinInc)*(rand() % 21 - 10);   // 0 to 10 increments
            sinInc += 0.01;
            drawLight(&(lights->light[i])); // Draw the light
        } 
        else if (i == 0) {
            lights->light[i].ambient = ambientLightVal;
            lights->light[i].diffuse = diffuseLightVal;
            lights->light[i].specular = specularLightVal;
            drawLight(&(lights->light[i])); // Draw the light
        }
        if (spotlightsEnabled) {
            lights->light[i].spotlightOn = true;
        } else {
            lights->light[i].spotlightOn = false;
        }
    }
    glEnable(GL_DEPTH_TEST);
}

void resetLightingView(LightArray* lights) {
    for (int i = 1; i < 8; i++) {
        if (i < 2) {
            // Set light parameters
            lights->light[i].ambient = ambientLightVal;
            lights->light[i].diffuse = diffuseLightVal;
            lights->light[i].specular = specularLightVal;
            lights->light[i].spotExponent = 1.0;
            lights->light[i].spotCutoff = 10.0; //45
            lights->light[i].rectangleWidth = 0.5;
            lights->light[i].rectangleHeight = 0.5;
            lights->light[i].prismHeight = 1.0;
            lights->light[i].prismBase = 0.5;
        }
        else {
            GLenum glLight = GL_LIGHT0 + i;
            glDisable(glLight);
            // Random positions around the map center
            lights->light[i].position.x = INFINITY;
            lights->light[i].position.z = INFINITY;
            lights->light[i].position.y = INFINITY;
        }
    }
}

// Reset lights 3 though 8: lights[2] : lights[9] as map has updated
void resetLighting(Vector3 mapCenter, LightArray* lights) {
    for (int i = 0; i < 8; i++) { // Starting from 2, as the array is 0-indexed (3rd light is at index 2)
        if (i < 1) {
            // Set light parameters
            lights->light[i].ambient = ambientLightVal;
            lights->light[i].diffuse = diffuseLightVal;
            lights->light[i].specular = specularLightVal;
            lights->light[i].spotExponent = 1.0;
            lights->light[i].spotCutoff = 45.0;
            lights->light[i].rectangleWidth = 0.5;
            lights->light[i].rectangleHeight = 0.5;
            lights->light[i].prismHeight = 1.0;
            lights->light[i].prismBase = 0.5;
        }
        else {
            // Random positions around the map center
            lights->light[i].position.x = mapCenter.x + (rand() % 201 - 100); // +/- 100 units from center.x
            lights->light[i].position.z = mapCenter.z + (rand() % 201 - 100); // +/- 100 units from center.z
            lights->light[i].position.y = 10 + (rand() % 11 - 5); // 10 +/- 5 units
            // Random angular position
            lights->light[i].angularPos.y = rand() % 361; // 0 to 360 degrees
            // Set light parameters
            lights->light[i].ambient = ambientLightVal;
            lights->light[i].diffuse = diffuseLightVal;
            lights->light[i].specular = specularLightVal;
            lights->light[i].spotExponent = 1.0;
            lights->light[i].spotCutoff = 45.0;
            lights->light[i].rectangleWidth = 1.0;
            lights->light[i].rectangleHeight = 1.0;
            lights->light[i].prismHeight = 2.0;
            lights->light[i].prismBase = 1.0;
        }
    }
}

void initLighting(Vector3 mapCenter, LightArray* lights) {
    for (int i = 0; i < 8; i++) { // Starting from 2, as the array is 0-indexed (3rd light is at index 2)
        if (i < 1) {
            lights->light[i].position.x = 0.00;
            lights->light[i].position.y = 0.00;
            lights->light[i].position.z = 0.00;
            lights->light[i].angularPos.y = 0.00;
            // Set light parameters
            lights->light[i].ambient = ambientLightVal;
            lights->light[i].diffuse = diffuseLightVal;
            lights->light[i].specular = specularLightVal;
            lights->light[i].spotExponent = 1.0;
            lights->light[i].spotCutoff = 45.0;
            lights->light[i].rectangleWidth = 0.5;
            lights->light[i].rectangleHeight = 0.5;
            lights->light[i].prismHeight = 1.0;
            lights->light[i].prismBase = 0.5;
        }
        else {
            // Random positions around the map center
            lights->light[i].position.x = mapCenter.x + (rand() % 201 - 100); // +/- 100 units from center.x
            lights->light[i].position.z = mapCenter.z + (rand() % 201 - 100); // +/- 100 units from center.z
            lights->light[i].position.y = 10 + (rand() % 11 - 5); // 10 +/- 5 units
            // Random angular position
            lights->light[i].angularPos.y = rand() % 361; // 0 to 360 degrees
            // Set light parameters
            lights->light[i].ambient = ambientLightVal;
            lights->light[i].diffuse = diffuseLightVal;
            lights->light[i].specular = specularLightVal;
            lights->light[i].spotExponent = 1.0;
            lights->light[i].spotCutoff = 45.0;
            lights->light[i].rectangleWidth = 1.0;
            lights->light[i].rectangleHeight = 1.0;
            lights->light[i].prismHeight = 2.0;
            lights->light[i].prismBase = 1.0;
        }
    }
}

void updateLighting(bool lightsEnabled, bool spotlightsEnabled, LightArray* lights) {
    if (lightsEnabled) {
        enableLights(lights);
    } 
    else {
        disableLights(lights);
    }

    showLights(lightsEnabled, spotlightsEnabled, lights);
}
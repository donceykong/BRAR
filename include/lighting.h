#ifndef LIGHTING_H
#define LIGHTING_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdbool.h>

// local
#include "draw.h"
#include "matrixMath.h"

extern double ambientLightVal;
extern double diffuseLightVal;
extern double specularLightVal;

typedef struct {
    double speed;              
    bool inCollision;           

    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

    Vector3 angularPos;  
    Vector3 angularVel;

    // Light source parameters
    GLfloat ambient, diffuse, specular;  

    // If light source has spotlight, define focus of light and cone
    bool spotlightOn;
    GLfloat spotExponent, spotCutoff;

    // For drawing the light
    GLfloat rectangleWidth, rectangleHeight, prismHeight, prismBase;
} lightStruct;

typedef struct {
    lightStruct light[8];
} LightArray;

void enableLights(LightArray* lights);

void disableLights(LightArray* lights);

void illumLight(lightStruct* light, int lightIter);

void drawLight(lightStruct* light);

void showLights (bool lightsEnabled, bool spotlightsEnabled, LightArray* lights);

void initLighting(Vector3 mapCenter, LightArray* lights);

// Reset lights
void resetLighting(Vector3 mapCenter, LightArray* lights);

void resetLightingView(LightArray* lights);

void updateLighting(bool lightsEnabled, bool spotlightsEnabled, LightArray* lights);

#endif // LIGHTING_H
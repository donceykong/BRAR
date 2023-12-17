#ifndef KEY_UPDATE_H
#define KEY_UPDATE_H

// local
#include "mapManager.h"         // merge in keyUpdate as a controller? rename to controller?
#include "views.h"
#include "lighting.h"
#include "keys.h"

extern double lightRotation;
extern double fpCamRotation;
extern double lightZoomInc;

void updateRunner(LightArray* lights);

void updateTimeCrunch(LightArray* lights);

void updateViewRobot(LightArray* lights);

#endif // KEY_UPDATE_H
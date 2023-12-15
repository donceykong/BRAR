#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdbool.h>

#include "lighting.h"

extern bool showFrames;
extern bool showPoseHist;

extern bool RRTSTAR_ACTIVE;
extern bool waypointTracking;
extern bool displayRRTSPath;
extern bool lightKeyPressed;

extern bool lightsEnabled;
extern bool spotlightsEnabled;

typedef struct {
  bool space;       // Jump robot
  bool spacePrev;   //

  bool right;       // Rotate to right
  bool left;        // Rotate to left
  bool up;          // Traverse forward
  bool down;        // Traverse backwards

  bool a;           // Rotate lights in "view robots"
  bool d;           // Rotate lights in "view robots"

  bool f;           // show robot coordinate frames
  bool i;           // Zoom light in
  bool k;           // Zoom light out
  bool p;           // show robot pose history (100 prev poses) 

  bool l;           // Zoom out
  bool o;           // Zoom in

  bool r;           // RRTSTAR_ACTIVE ENABLE/DISABLE (default is off)
  bool R;           // RRTSTAR_TREE show/hide
  bool s;           // 
  bool t;           // Visualize 't'ree from RRT search (default is off)
  bool T;           // Switch RRT* to use my heuristic search or map (default is on) -> viz by Pressing q

  bool v;           // switch view from oribit to overhead and visa-versa

  bool w;           // enable/disable waypoint tracking from RRT* (rrt* must be active to work)

  bool x;           // decrease diffuse light value
  bool X;           // Increase diffuse light value
  bool c;           // Decrease specular light value
  bool C;           // Increase specular light value
  bool z;           // decrease ambient light value
  bool Z;           // increase ambient light value

  bool key0;        // Turn flying lights off/on (default on)
  bool key1;        // Orbit view
  bool key2;        // Overhead view

  bool key3;        // Rotate Camera about robot Y
  bool key4;        // Rotate Camera about robot Y
} KeyStatesStruct;

extern KeyStatesStruct keyStates;

void setRegularKeyState(unsigned char key, bool state);

void setSpecialKeyState (int key, bool state);

void special(int key, int x, int y);

void specialUp(int key, int x, int y);

void handleKeys(unsigned char key, int x, int y);

void handleKeysUp(unsigned char key, int x, int y);

#endif // KEY_HANDLER_H
// Doncey Albin
// Keys library
#include "keys.h"

bool RRTSTAR_ACTIVE = false;    //
bool displayRRTSPath = false;   // Show RRT Tree
bool lightKeyPressed = false;   // Keep track of whether '0' key is pressed
bool lightsEnabled = false;     //
bool spotlightsEnabled = false; //
bool displayRRTSearch = true;   //
bool useMapArea = false;        //
bool waypointTracking = false;  // follow rrt* waypoints
bool showFrames = false;        //
bool showPoseHist = false;      //

KeyStatesStruct keyStates;

void setRegularKeyState(unsigned char key, bool state) {
   switch (key) {
        case 32: // ASCII value for space bar
          keyStates.space = state;
          break;
        case 'a':
            keyStates.a = state;
            break;
        case 's':
            keyStates.s = state;
            if (state) {spotlightsEnabled = !spotlightsEnabled;}
            break;
        case 'r':
            keyStates.r = state;
            if (keyStates.r) {RRTSTAR_ACTIVE = !RRTSTAR_ACTIVE;}
        case 'R':
            keyStates.R = state;
            if (keyStates.R) {displayRRTSPath = !displayRRTSPath;}
            break;
        case 'c':
            keyStates.c = state;
            if (state && specularLightVal > 0.0) {
                specularLightVal -= 0.01;
                printf("ambientLightVal: %f, diffuseLightVal: %f, specularLightVal: %f\n", ambientLightVal, diffuseLightVal, specularLightVal);
            }
            break;
        case 'C':
            keyStates.C = state;
            if (state && specularLightVal < 1.0) {
                specularLightVal += 0.01;
                printf("ambientLightVal: %f, diffuseLightVal: %f, specularLightVal: %f\n", ambientLightVal, diffuseLightVal, specularLightVal);
            }
            break;
        case 'd':
            keyStates.d = state;
            break;
        case 't':
            keyStates.t = state;
            if (state) {displayRRTSearch = !displayRRTSearch;}
            break;
        case 'T':
            keyStates.t = state;
            if (state) {useMapArea = !useMapArea;}
            break;
        case 'f':
            keyStates.f = state;
            if (state) {showFrames = !showFrames;}
            break;
        case 'i':
            keyStates.i = state;
            break;
        case 'k':
            keyStates.k = state;
            break;
        case 'o':
            keyStates.o = state;
            break;
        case 'l':
            keyStates.l = state;
            break;
        case 'p':
            keyStates.p = state;
            if (state) {showPoseHist = !showPoseHist;}
            break;
        case 'w':
            keyStates.w = state;
            if (state) {waypointTracking = !waypointTracking;}
            break;
        case 'x':
            keyStates.x = state;
            if (state && diffuseLightVal > 0.0) {
                diffuseLightVal -= 0.01;
                printf("ambientLightVal: %f, diffuseLightVal: %f, specularLightVal: %f\n", ambientLightVal, diffuseLightVal, specularLightVal);
            }
            break;
        case 'X':
            keyStates.X = state;
            if (state && diffuseLightVal < 1.0) {
                diffuseLightVal += 0.01;
                printf("ambientLightVal: %f, diffuseLightVal: %f, specularLightVal: %f\n", ambientLightVal, diffuseLightVal, specularLightVal);
            }
            break;
        case 'z':
            keyStates.z = state;
            if (state && ambientLightVal > 0.0) {
                ambientLightVal -= 0.01;
                printf("ambientLightVal: %f, diffuseLightVal: %f, specularLightVal: %f\n", ambientLightVal, diffuseLightVal, specularLightVal);
            }
            break;
        case 'Z':
            keyStates.Z = state;
            if (state && ambientLightVal < 1.0) {
                ambientLightVal += 0.01;
                printf("ambientLightVal: %f, diffuseLightVal: %f, specularLightVal: %f\n", ambientLightVal, diffuseLightVal, specularLightVal);
            }
            break;
        case '0':
            keyStates.key0 = state;
            if (state) {lightKeyPressed = !lightKeyPressed; lightsEnabled = lightKeyPressed;}
            break;
        case '1':
            keyStates.key1 = state;
            break;
        case '2':
            keyStates.key2 = state;
            break;
        case '3':
            keyStates.key3 = state;
            break;
        case '4':
            keyStates.key4 = state;
            break;
        default:
            return;
    }
}

void setSpecialKeyState (int key, bool state) {
  switch (key) {
    case GLUT_KEY_RIGHT: 
      keyStates.right = state;
      break;
    case GLUT_KEY_LEFT: 
      keyStates.left = state;
      break;
    case GLUT_KEY_UP: 
      keyStates.up = state;
      break;
    case GLUT_KEY_DOWN: 
      keyStates.down = state;
      break;
    default: 
      return;
  }
}

void special(int key, int x, int y) {
    setSpecialKeyState(key, true);
}

void specialUp(int key, int x, int y) {
    setSpecialKeyState(key, false);
}

void handleKeys(unsigned char key, int x, int y) {
    setRegularKeyState(key, true);
}

void handleKeysUp(unsigned char key, int x, int y) {
    setRegularKeyState(key, false);
}
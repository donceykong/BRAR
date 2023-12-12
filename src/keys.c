// keys library
// Doncey Albin
#include "keyHandler.h"

bool RRTSTAR_ACTIVE = false;
bool RRTSTAR_TREE_SHOW = false;     // Show RRT Tree
bool lightKeyPressed = false;       // Keep track of whether '0' key is pressed
KeyStatesStruct keyStates;

void setRegularKeyState(unsigned char key, bool state) {
   switch (key) {
        case 32: // ASCII value for space bar
          keyStates.space = state;
          break;
        case 'w':
            keyStates.w = state;
            break;
        case 's':
            keyStates.s = state;
            // if (state) {SPOTLIGHT_ACTIVE = !SPOTLIGHT_ACTIVE;}
            break;
        case 'r':
            keyStates.r = state;
            if (keyStates.r) {RRTSTAR_ACTIVE = !RRTSTAR_ACTIVE;}
        case 'R':
            keyStates.R = state;
            if (keyStates.R) {RRTSTAR_TREE_SHOW = !RRTSTAR_TREE_SHOW;}
            break;
        case 'a':
            keyStates.a = state;
            break;
        case 'd':
            keyStates.d = state;
            break;
        case 'j':
            keyStates.j = state;
            break;
        case 'k':
            keyStates.k = state;
            break;
        case 'y':
            keyStates.y = state;
            break;
        case 'h':
            keyStates.h = state;
            break;
        case 't':
            keyStates.t = state;
            break;
        case 'f':
            keyStates.f = state;
            // if (state) {showFrames = !showFrames;}
            break;
        case 'g':
            keyStates.g = state;
            break;
        case 'v':
            keyStates.v = state;
            break;
        case 'o':
            keyStates.o = state;
            break;
        case 'l':
            keyStates.l = state;
            break;
        case 'p':
            keyStates.p = state;
            // if (state) {showPoseHist = !showPoseHist;}
            break;
        case 'i':
            keyStates.i = state;
            break;
        case '0':
            keyStates.key0 = state;
            // if (state) {lightKeyPressed = !lightKeyPressed; lightsEnabled = lightKeyPressed;}
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
        case '5':
            keyStates.key5 = state;
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
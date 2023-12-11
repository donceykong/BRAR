#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdbool.h>

extern bool RRTSTAR_ACTIVE;
extern bool lightKeyPressed;

typedef struct {
  bool space;       // space bar key - jump robot controlled by user
  bool spacePrev;   //

  bool right;       //
  bool left;        //
  bool up;          //
  bool down;        //

  bool w;           // UNUSED
  bool s;           // UNUSED
  bool a;           // UNUSED
  bool d;           // UNUSED
  bool y;           // UNUSED
  bool h;           // UNUSED
  bool j;           // UNUSED
  bool k;           // UNUSED

  bool t;           // UNUSED
  bool f;           // UNUSED
  bool g;           // UNUSED
  bool v;           // UNUSED
  bool r;           // RRTSTAR_ACTIVE ENABLE/DISABLE
  bool o;           // UNUSED
  bool l;           // UNUSED
  bool p;           // UNUSED
  bool i;           // UNUSED

  bool key0;           //
  bool key1;           //  
  bool key2;           //
  bool key3;           // UNUSED
  bool key4;           // Inc runner speed
  bool key5;           // dec runner speed
} KeyStatesStruct;

extern KeyStatesStruct keyStates;

void setRegularKeyState(unsigned char key, bool state);

void setSpecialKeyState (int key, bool state);

void special(int key, int x, int y);

void specialUp(int key, int x, int y);

void handleKeys(unsigned char key, int x, int y);

void handleKeysUp(unsigned char key, int x, int y);

#endif // KEY_HANDLER_H
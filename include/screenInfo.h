#ifndef SCREEN_INFO_H
#define SCREEN_INFO_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <ft2build.h>   // FreeType (used in main screen buttons)
#include FT_FREETYPE_H

#include "textureUtils.h"       // NO DEPENDS

// WINDOW INFO
extern const int windowXPos;
extern const int windowYPos;
extern const int windowXDiff;
extern const int windowYDiff;

// First Button
extern const float button1XDiff, button1XMin, button1XMax;
extern const float button1YDiff, button1YMin, button1YMax, button1YCenter;
extern const float buttonSepY;

// Second button
extern const float button2XDiff, button2XMin, button2XMax;
extern const float button2YDiff, button2YMin, button2YMax, button2YCenter;

// third button
extern const float button3XDiff, button3XMin, button3XMax;
extern const float button3YDiff, button3YMin, button3YMax, button3YCenter;

// First Button
extern const float SIbutton1XDiff, SIbutton1XMin, SIbutton1XMax;
extern const float SIbutton1YDiff, SIbutton1YMin, SIbutton1YMax, SIbutton1YCenter;
extern const float SIbuttonSepY;

// Second button
extern const float SIbutton2XDiff, SIbutton2XMin, SIbutton2XMax;
extern const float SIbutton2YDiff, SIbutton2YMin, SIbutton2YMax, SIbutton2YCenter;

extern char SIstr1[50];
extern char SIstr2[50];
extern char SITopPlayer[50];

// Structure to hold glyph data
typedef struct {
    GLuint textureID;   // ID handle of the glyph texture
    int width;          // Glyph width
    int height;         // Glyph height
    int bearingX;       // Offset from baseline to left/top of glyph
    int bearingY;       // Offset from baseline to left/top of glyph
    GLuint advance;     // Offset to advance to next glyph
} Character;

void setupTextRendering(FT_Face face);

void renderText(const char* text, float x, float y, float scale);

// Function to draw a button
void drawButton(float x, float y, float width, float height);

void drawBackground();

void drawButtons();

void drawButtonScreen();

void drawSIBackground();

void drawSI(const char *str1, const char *str2);

// void drawScreenInfo();

#endif // SCREEN_INFO_H
#include "screenInfo.h"

// WINDOW INFO
const int windowXPos = 600;
const int windowYPos = 100;
const int windowXDiff = 1200;
const int windowYDiff = 1200;

// First Button
const float button1XDiff = 700;
const float button1XMin = windowXDiff/2 - button1XDiff/2;
const float button1XMax = button1XMin + button1XDiff;

const float button1YDiff = 100.0;
const float button1YMin = windowYDiff/2 - button1YDiff/2;
const float button1YMax = button1YMin + button1YDiff;
const float button1YCenter = button1YDiff/2.0 + button1YMin;

const float buttonSepY = 20.0;

// Second button
const float button2XDiff = button1XDiff;
const float button2XMin = button1XMin;
const float button2XMax = button2XMin + button2XDiff;

const float button2YDiff = button1YDiff;
const float button2YMin = button1YMax + buttonSepY;
const float button2YMax = button2YMin + button2YDiff;
const float button2YCenter = button2YDiff/2.0 + button2YMin;

// third button
const float button3XDiff = button2XDiff;
const float button3XMin = button2XMin;
const float button3XMax = button3XMin + button3XDiff;

const float button3YDiff = button2YDiff;
const float button3YMin = button2YMax + buttonSepY;
const float button3YMax = button3YMin + button3YDiff;
const float button3YCenter = button3YDiff/2.0 + button3YMin;

// First Button
const float SIbutton1XDiff = 700;
const float SIbutton1XMin = windowXDiff/2 - SIbutton1XDiff/2;
const float SIbutton1XMax = SIbutton1XMin + SIbutton1XDiff;

const float SIbutton1YDiff = 100.0;
const float SIbutton1YMin = windowYDiff/2 - SIbutton1YDiff/2;
const float SIbutton1YMax = SIbutton1YMin + SIbutton1YDiff;
const float SIbutton1YCenter = SIbutton1YDiff/2.0 + SIbutton1YMin;

const float SIbuttonSepY = 20.0;

// Second button
const float SIbutton2XDiff = SIbutton1XDiff;
const float SIbutton2XMin = SIbutton1XMin;
const float SIbutton2XMax = SIbutton2XMin + SIbutton2XDiff;

const float SIbutton2YDiff = SIbutton1YDiff;
const float SIbutton2YMin = SIbutton1YMax + SIbuttonSepY;
const float SIbutton2YMax = SIbutton2YMin + SIbutton2YDiff;
const float SIbutton2YCenter = SIbutton2YDiff/2.0 + SIbutton2YMin;

char SIstr1[50] = "";
char SIstr2[50] = "";
char SITopPlayer[50] = "";

Character characters[128]; // Array to store character data

void setupTextRendering(FT_Face face) {
    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    FT_Set_Pixel_Sizes(face, 0, 48); // Set size to load glyphs

    for (unsigned char c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            fprintf(stderr, "Failed to load Glyph\n");
            continue;
        }

        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_ALPHA,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_ALPHA,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Store character for later use
        Character character = {
            texture,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            face->glyph->bitmap_left,
            face->glyph->bitmap_top,
            face->glyph->advance.x
        };
        characters[c] = character;
    }
    glDisable(GL_TEXTURE_2D);
}

void renderText(const char* text, float x, float y, float scale) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (const char* c = text; *c; c++) {
        Character ch = characters[(unsigned char)*c];

        GLfloat xpos = x + ch.bearingX * scale;
        // Flip the y position
        GLfloat ypos = y - (ch.height - ch.bearingY) * scale;

        GLfloat w = ch.width * scale;
        GLfloat h = ch.height * scale;

        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        glBegin(GL_QUADS);
            // Flip the texture coordinates along the y-axis
            glTexCoord2d(0, 1); glVertex2f(xpos, ypos);
            glTexCoord2d(1, 1); glVertex2f(xpos + w, ypos);
            glTexCoord2d(1, 0); glVertex2f(xpos + w, ypos + h);
            glTexCoord2d(0, 0); glVertex2f(xpos, ypos + h);
        glEnd();

        // Advance cursors for next glyph
        x += (ch.advance >> 6) * scale; // Bitshift by 6 to convert units from 1/64th pixels to pixels
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

// Function to draw a button
void drawButton(float x, float y, float width, float height) {
    glPushMatrix(); // Save the current matrix
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
    glPopMatrix(); // Restore the previous matrix
}

void drawBackground() {
    // Set up the view
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowXDiff, 0, windowYDiff);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw the first button
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    // GLuint splashTex = loadTexture("./assets/robot_body.bmp");
    // glBindTexture(GL_TEXTURE_2D, splashTex);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex2f(0, 0);
        glTexCoord2d(1, 0); glVertex2f(windowXDiff, 0);
        glTexCoord2d(1, 1); glVertex2f(windowXDiff, windowYDiff);
        glTexCoord2d(0, 1); glVertex2f(0, windowYDiff);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void drawButtons() {
    // Set up the view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowXDiff, 0.0, windowYDiff);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the first button
    glColor3f(1.0, 0.0, 0.0); // Set color for the button (e.g., red)
    drawButton(button1XMin, button1YMin, button1XDiff, button1YDiff);

    // Draw the second button
    glColor3f(0.0, 1.0, 0.0); // Set color for the button (e.g., blue)
    drawButton(button2XMin, button2YMin, button2XDiff, button2YDiff);

    // Draw the third button
    glColor3f(0.0, 0.0, 1.0); // Set color for the button (e.g., blue)
    drawButton(button3XMin, button3YMin, button3XDiff, button2YDiff);

    // Render some text on the screen
    glColor3f(0.0, 1.0, 0.0); // Set text color (green)
    renderText("GAME MODE 3: VIEW ROBOT", button1XMin + 20, button1YCenter - 10, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    renderText("GAME MODE 1: TIME CRUNCH", button2XMin + 20, button2YCenter - 10, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    renderText("GAME MODE 0: RUNNER", button3XMin + 20, button3YCenter - 10, 1.0);
}

void drawButtonScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawBackground();
    drawButtons();
    glutSwapBuffers();
    glutPostRedisplay();
}

void drawSIBackground() {
    // Set up the view
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowXDiff, 0, windowYDiff);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw the first button
    glColor3f(1.0, 1.0, 1.0); // Set color for the button (e.g., red)
    glEnable(GL_TEXTURE_2D);
    // GLuint splashTex = loadTexture("./assets/robot_body.bmp");
    // glBindTexture(GL_TEXTURE_2D, splashTex);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex2f(0, 0);
        glTexCoord2d(1, 0); glVertex2f(windowXDiff, 0);
        glTexCoord2d(1, 1); glVertex2f(windowXDiff, windowYDiff);
        glTexCoord2d(0, 1); glVertex2f(0, windowYDiff);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void drawSI(const char *str1, const char *str2) {
    glDisable(GL_LIGHTING);

    // Set up the view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowXDiff, 0.0, windowYDiff);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the first button
    glColor3f(1.0, 0.0, 0.0); // Set color for the button (e.g., red)
    drawButton(windowXDiff-SIbutton1XDiff, windowYDiff- (SIbutton1YDiff), SIbutton1XDiff, SIbutton1YDiff);

    // Draw the second button
    glColor3f(0.0, 1.0, 0.0); // Set color for the button (e.g., blue)
    drawButton(windowXDiff-SIbutton1XDiff, windowYDiff- (2*SIbutton2YDiff+SIbuttonSepY), SIbutton2XDiff, SIbutton2YDiff);

    // Render some text on the screen
    glColor3f(0.0, 1.0, 0.0); // Set text color (green)
    renderText(str1, windowXDiff-SIbutton1XDiff + 70, windowYDiff- (SIbutton1YDiff) + 20, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    renderText(str2, windowXDiff-SIbutton1XDiff + 70, windowYDiff- (2*SIbutton2YDiff+SIbuttonSepY) + 20, 1.0);
}

// void drawScreenInfo() {
//     //drawBackground();
//     drawSI();
// }
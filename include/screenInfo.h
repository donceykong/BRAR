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

char SIstr1[50] = "Hello, world!";
char SIstr2[50] = "Hello again, world!";

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
    GLuint splashTex = loadTexture("./assets/robot_body.bmp");
    glBindTexture(GL_TEXTURE_2D, splashTex);
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
    // glDisable(GL_LIGHT0);
    // glDisable(GL_LIGHT1);
    // glDisable(GL_LIGHT2);

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
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
}
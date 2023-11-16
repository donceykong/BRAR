
GLfloat GroundPlaneVertices[] = {
    // Position Indices:            (0 - 2)         
    // Texture Coordinates Indices: (3 - 4)
    100.0f,  0.0f,  100.0f,  1.0f, 1.0f,
   -100.0f,  0.0f,  100.0f,  0.0f, 1.0f,
   -100.0f,  0.0f, -100.0f,  0.0f, 0.0f,

    100.0f,  0.0f,  100.0f,  1.0f, 1.0f,
   -100.0f,  0.0f, -100.0f,  0.0f, 0.0f,
    100.0f,  0.0f, -100.0f,  1.0f, 0.0f
};

void drawGroundPlane() {
    glColor3f(1.0, 1.0, 1.0);     // Blue color

    glBegin(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
//    groundTexture = loadTexture(GroundTexturePath);
    glBindTexture(GL_TEXTURE_2D, terrainTextureID);
    
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 1.0f, 0.0f);
    for (int i = 0; i < 6 * 5; i += 5) {
        // Optionally set texture coordinates if you're using them.
        glTexCoord2f(GroundPlaneVertices[i + 3], GroundPlaneVertices[i + 4]);
        glVertex3f(GroundPlaneVertices[i], GroundPlaneVertices[i + 1], GroundPlaneVertices[i + 2]);
    }
    
    glEnd();

    glColor3f(1.0, 1.0, 1.0);     // Back to white
}

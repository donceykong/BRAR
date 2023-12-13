// Doncey Albin
// draw library
// Fall 2023, Computer Graphics, CU Boulder

#include "draw.h"

/*
 * Misc
 */
void drawNormal(GLfloat x, GLfloat y, GLfloat z, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat length) {
    //glColor3f(1.0, 0.0, 0.0); // Red color for normals
    glLineWidth(2.0f); // Set line width for normals
    glBegin(GL_LINES);
        glVertex3f(x, y, z);
        glVertex3f(x + nx * length, y + ny * length, z + nz * length);
    glEnd();
}

/*
 * Shape edges
 */
void drawPrismEdges(float rectangleWidth, float rectangleHeight, float prismBase, float prismHeight) {
    // GLfloat emissiveColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; // RGBA
    // glMaterialfv(GL_FRONT, GL_EMISSION, emissiveColor);

    glColor3f(0, 0, 0);
    // Draw the rectangle
    glBegin(GL_LINES);
        glVertex3f(-rectangleWidth / 2, -rectangleHeight / 2, 0);
        glVertex3f( rectangleWidth / 2, -rectangleHeight / 2, 0);
        glVertex3f( rectangleWidth / 2,  rectangleHeight / 2, 0);
        glVertex3f(-rectangleWidth / 2,  rectangleHeight / 2, 0);
    glEnd();

    // // Draw the prism to represent the direction
    // glBegin(GL_LINES);
    //     glVertex3f(-prismBase / 2, -prismBase / 2, 0);
    //     glVertex3f( prismBase / 2, -prismBase / 2, 0);
    //     glVertex3f( prismBase / 2,  prismBase / 2, 0);
    //     glVertex3f(-prismBase / 2,  prismBase / 2, 0);
    // glEnd();

    // glBegin(GL_LINES);  // Top face of the prism
    //     glVertex3f(0, 0, prismHeight);
    //     glVertex3f(-prismBase / 2, -prismBase / 2, 0);
    //     glVertex3f(prismBase / 2, -prismBase / 2, 0);

    //     glVertex3f(0, 0, prismHeight);
    //     glVertex3f(prismBase / 2, -prismBase / 2, 0);
    //     glVertex3f(prismBase / 2,  prismBase / 2, 0);

    //     glVertex3f(0, 0, prismHeight);
    //     glVertex3f(prismBase / 2,  prismBase / 2, 0);
    //     glVertex3f(-prismBase / 2,  prismBase / 2, 0);

    //     glVertex3f(0, 0, prismHeight);
    //     glVertex3f(-prismBase / 2,  prismBase / 2, 0);
    //     glVertex3f(-prismBase / 2, -prismBase / 2, 0);
    // glEnd();
    // GLfloat noEmission[] = {0.0f, 0.0f, 0.0f, 1.0f}; // Black (no emission)
    // glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noEmission);
}

void drawCuboidEdges(GLfloat width, GLfloat height, GLfloat depth) {
    // Front face
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);

    // Back face
    glVertex3f(-width/2, -height/2, -depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f( width/2, -height/2, -depth/2);

    // Left face
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f(-width/2, -height/2, -depth/2);

    // Right face
    glVertex3f( width/2, -height/2, -depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f( width/2, -height/2,  depth/2);

    // Top face
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f( width/2,  height/2,  depth/2);
    glVertex3f( width/2,  height/2, -depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);

    // Bottom face
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2, -height/2, -depth/2);
    glVertex3f( width/2, -height/2, -depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
}

void drawRightTriPrismEdges(GLfloat width, GLfloat height, GLfloat depth) {
    // Front face
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);

    // Back face
    glVertex3f(-width/2, -height/2, -depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f( width/2, -height/2, -depth/2);

    // Left face
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);
    glVertex3f(-width/2, -height/2, -depth/2);

    // Top face
    glVertex3f(-width/2,  height/2,  depth/2);
    glVertex3f( width/2,  -height/2,  depth/2);
    glVertex3f( width/2,  -height/2, -depth/2);
    glVertex3f(-width/2,  height/2, -depth/2);

    // Bottom face
    glVertex3f(-width/2, -height/2,  depth/2);
    glVertex3f(-width/2, -height/2, -depth/2);
    glVertex3f( width/2, -height/2, -depth/2);
    glVertex3f( width/2, -height/2,  depth/2);
}

void drawSemiCylinderEdges(GLfloat radius, GLfloat height, int segments, double percentFull) {
    glColor3f(0.8, 0.8, 1.0);   // Purpleish color

    glLineWidth(4.0f);          // Set line width to 2.0 pixels
    glBegin(GL_LINES);
    glVertex3f(0, 0, -height/2);  // Center vertex
    for (int i = 0; i <= segments; i += 2) {
        GLfloat angle = -M_PI/2.0 + i * percentFull*2.0*M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        glNormal3f(x, y, -height/2);
        glVertex3f(x, y, -height/2);
    }
    glEnd();

    glLineWidth(4.0f);            // Set line width to 2.0 pixels
    glBegin(GL_LINES);
    glVertex3f(0, 0, height/2);   // Center vertex
    for (int i = 0; i <= segments; i += 2) {
        GLfloat angle = -M_PI/2.0 + i * percentFull*2.0*M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        glNormal3f(x, y, height/2);
        glVertex3f(x, y, height/2);
    }
    glEnd();
}

void drawParallelogramEdges(GLfloat width, GLfloat height, GLfloat depth) {
    // Front face
    glBegin(GL_LINES);
    glVertex3f(-width/4, -height/2,  depth/2); // bottom
    glVertex3f( width/4, -height/2,  depth/2);

    glVertex3f(-width/4, -height/2, depth/2); // left
    glVertex3f(-width/2,  height/2, depth/2);

    glVertex3f( width/2,  height/2, depth/2); // right
    glVertex3f( width/4, -height/2, depth/2);
    glEnd();

    // Back face
    glBegin(GL_LINES);
    glVertex3f(-width/4, -height/2,  -depth/2); // bottom
    glVertex3f( width/4, -height/2,  -depth/2);

    glVertex3f(-width/4, -height/2, -depth/2); // left
    glVertex3f(-width/2,  height/2, -depth/2);

    glVertex3f( width/2,  height/2, -depth/2); // right
    glVertex3f( width/4, -height/2, -depth/2);
    glEnd();

    // Left face bottom
    glBegin(GL_LINES);
    glVertex3f(-width/4, -height/2,  depth/2);
    glVertex3f(-width/4, -height/2, -depth/2);
    glEnd();

    // Right face
    glBegin(GL_LINES);
    glVertex3f( width/4, -height/2, -depth/2);
    glVertex3f( width/4, -height/2,  depth/2);
    glEnd();
}

/*
 * Solid shapes
 */
void drawCuboid(GLfloat width, GLfloat height, GLfloat depth) {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    
    // Front face
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1); 
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2, -height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glEnd();

    // // Draw normals for front face
    // GLfloat normalLength = 0.25; // Adjust this value as needed
    // drawNormal(-width/2, -height/2,  depth/2, 0, 0, 1, normalLength);
    // drawNormal( width/2, -height/2,  depth/2, 0, 0, 1, normalLength);
    // drawNormal( width/2,  height/2,  depth/2, 0, 0, 1, normalLength);
    // drawNormal(-width/2,  height/2,  depth/2, 0, 0, 1, normalLength);

    // Back face;
    glBegin(GL_QUADS);
    glNormal3f(0, 0,-1); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2, -depth/2);
    glEnd();
    // drawNormal(-width/2, -height/2,  -depth/2, 0, 0, -1, normalLength);
    // drawNormal(-width/2,  height/2,  -depth/2, 0, 0, -1, normalLength);
    // drawNormal( width/2,  height/2,  -depth/2, 0, 0, -1, normalLength);
    // drawNormal( width/2, -height/2,  -depth/2, 0, 0, -1, normalLength);

    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f( width/2, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2,  depth/2);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2, -height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2,  depth/2);
    glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // glColor3f(0.8, 0.8, 1.0);   // Purpleish color
    // glLineWidth(4.0f);          // Set line width to 2.0 pixels
    // glBegin(GL_LINES);
    //   drawCuboidEdges(width, height, depth);
    // glEnd();
}

void drawPrism(float rectangleWidth, float rectangleHeight, float prismBase, float prismHeight) {
    // GLfloat emissiveColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; // RGBA
    // glMaterialfv(GL_FRONT, GL_EMISSION, emissiveColor);

    glColor3f(0, 1, 0);
    // glNormal3f(0, 0, -1);                                           
    // glBegin(GL_QUADS);
    //     glVertex3f(-rectangleWidth / 2, -rectangleHeight / 2, 0);
    //     glVertex3f( rectangleWidth / 2, -rectangleHeight / 2, 0);
    //     glVertex3f( rectangleWidth / 2,  rectangleHeight / 2, 0);
    //     glVertex3f(-rectangleWidth / 2,  rectangleHeight / 2, 0);
    // glEnd();

    // GLfloat lessEmission[] = {0.1f, 0.1f, 0.1f, 1.0f}; // Black (no emission)
    // glMaterialfv(GL_FRONT, GL_EMISSION, lessEmission);

    // glColor3f(1, 0.5, 1);
    // Draw the prism to represent the direction
    glNormal3f(0, 0, 1);
    glBegin(GL_QUADS);
        glVertex3f(-prismBase / 2, -prismBase / 2, 0);
        glVertex3f( prismBase / 2, -prismBase / 2, 0);
        glVertex3f( prismBase / 2,  prismBase / 2, 0);
        glVertex3f(-prismBase / 2,  prismBase / 2, 0);
    glEnd();

    glBegin(GL_TRIANGLES);  // Top face of the prism
        glVertex3f(0, 0, prismHeight);
        glVertex3f(-prismBase / 2, -prismBase / 2, 0);
        glVertex3f(prismBase / 2, -prismBase / 2, 0);

        glVertex3f(0, 0, prismHeight);
        glVertex3f(prismBase / 2, -prismBase / 2, 0);
        glVertex3f(prismBase / 2,  prismBase / 2, 0);

        glVertex3f(0, 0, prismHeight);
        glVertex3f(prismBase / 2,  prismBase / 2, 0);
        glVertex3f(-prismBase / 2,  prismBase / 2, 0);

        glVertex3f(0, 0, prismHeight);
        glVertex3f(-prismBase / 2,  prismBase / 2, 0);
        glVertex3f(-prismBase / 2, -prismBase / 2, 0);
    glEnd();

    drawPrismEdges(rectangleWidth, rectangleHeight, prismBase, prismHeight);
    // GLfloat noEmission[] = {0.0f, 0.0f, 0.0f, 1.0f}; // Black (no emission)
    // glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
}

void drawRightTriPrism(GLfloat width, GLfloat height, GLfloat depth) {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);

    // Front face
    glBegin(GL_TRIANGLES);
    glNormal3f(0.0f, 0, 1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2, -height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glEnd();

    // Back face
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0,-1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2, -depth/2);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  -height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2,  -height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2, -height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/2, -height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2, -height/2,  depth/2);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    // glColor3f(0.8, 0.8, 1.0);   // Purpleish color
    // glLineWidth(4.0f);          // Set line width to 2.0 pixels
    // glBegin(GL_LINES);
    //   drawRightTriPrismEdges(width, height, depth);
    // glEnd();
}

void drawSemiCylinder(GLfloat radius, GLfloat height, int segments, double percentFull) {
    /*
     * Draw outer edge
     */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= segments; ++i) {
        GLfloat angle = -M_PI / 2.0 + i * percentFull * 2.0 * M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        // Texture coordinates
        GLfloat s = (float)i / segments; // Assuming horizontal wrap of texture
        GLfloat t_lower = 0.0f; // Texture coordinate for lower ring
        GLfloat t_upper = 1.0f; // Texture coordinate for upper ring

        glNormal3f(x, y, 0.0f);
        glTexCoord2f(s, t_lower); glVertex3f(x, y, -height / 2);  // Lower ring
        glTexCoord2f(s, t_upper); glVertex3f(x, y, height / 2);   // Upper ring
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    /*
     * Draw front face
     */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_TRIANGLE_FAN);

    // Center vertex and its texture coordinate
    glTexCoord2f(0.5f, 0.5f);   // Texture coordinate for the center
    glVertex3f(0, 0, height/2); // Center vertex
    glNormal3f(0.0f, 0.0f, height/2);
    for (int i = 0; i <= segments; ++i) {
        GLfloat angle = -M_PI / 2.0 + i * percentFull * 2.0 * M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        // Calculate texture coordinates for the perimeter vertices
        GLfloat s = 0.5 + 0.5 * cos(angle); // Map the angle to [0, 1] range
        GLfloat t = 0.5 + 0.5 * sin(angle);

        glTexCoord2f(s, t); // Texture coordinate for each perimeter vertex
        glNormal3f(x, y, height/2);
        glVertex3f(x, y, height/2); // Perimeter vertex
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);


    /*
     * Draw back face
     */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_TRIANGLE_FAN);

    glTexCoord2f(0.5f, 0.5f);     // Texture coordinate for the center
    glVertex3f(0, 0, -height/2);  // Center vertex
    glNormal3f(0.0f, 0.0f, -height/2);
    for (int i = 0; i <= segments; ++i) {
        GLfloat angle = -M_PI/2.0 + i * percentFull*2.0*M_PI / segments; 
        GLfloat x = radius * sin(angle);
        GLfloat y = radius * cos(angle);

        // Calculate texture coordinates for the perimeter vertices
        GLfloat s = 0.5 + 0.5 * cos(angle); // Map the angle to [0, 1] range
        GLfloat t = 0.5 + 0.5 * sin(angle);

        glTexCoord2f(s, t); // Texture coordinate for each perimeter vertex
        glNormal3f(x, y, -height/2);
        glVertex3f(x, y, -height/2);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    // drawSemiCylinderEdges(radius, height, segments, percentFull);
}

void drawParallelogram(GLfloat width, GLfloat height, GLfloat depth) {
    // bool opaque = false;
    // bool aone = true;
    // float alpha = 0.2;
    // glColor4f(1,1,1,alpha);

    // if (!opaque)
    // {
    //     glEnable(GL_BLEND);
    //     glColor4f(1,1,1,alpha);
    //     if (aone)
    //         glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    //     else
    //         glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    //     glDepthMask(0);
    // }

    // Front face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, BMPtexture);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/4, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/4, -height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glNormal3f(0, 0,-1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/4, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/4, -height/2, -depth/2);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/4, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/4, -height/2, -depth/2);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( width/4, -height/2, -depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/4, -height/2,  depth/2);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/2,  height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( width/2,  height/2,  depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/2,  height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width/2,  height/2, -depth/2);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-width/4, -height/2,  depth/2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-width/4, -height/2, -depth/2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( width/4, -height/2, -depth/2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( width/4, -height/2,  depth/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // glColor3f(1.0, 1.0, 1.0);   // White color
    // glLineWidth(4.0f);          // Set line width to 2.0 pixels
    // drawParallelogramEdges(width, height, depth);
}

void drawSphere(double r, int lats, int longs) {
    int i, j;
    for(i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(r * x * zr0, r * y * zr0, r * z0);

            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(r * x * zr1, r * y * zr1, r * z1);
        }
        glEnd();
    }
}
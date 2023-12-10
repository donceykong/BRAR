// Structure to hold glyph data
typedef struct {
    GLuint textureID;   // ID handle of the glyph texture
    int width;          // Glyph width
    int height;         // Glyph height
    int bearingX;       // Offset from baseline to left/top of glyph
    int bearingY;       // Offset from baseline to left/top of glyph
    GLuint advance;     // Offset to advance to next glyph
} Character;

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
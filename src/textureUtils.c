#include <stdlib.h>
#include "textureUtils.h"

// Ground texture
GLuint terrainTexture = 0;
GLuint portalTexture = 0;
GLuint splashTexture = 0;

// Robot textures
GLuint BMPtexture1 = 0;
GLuint BMPtexture2 = 0;
GLuint BMPtexture3 = 0;
GLuint BMPtexture4 = 0;
GLuint BMPtexture5 = 0;   
GLuint BMPtexture6 = 0;  
GLuint BMPtexture7 = 0;  
GLuint BMPtexture  = 0;     // Main texture (set to 1:4 as desired)

GLuint loadTexture(const char* filepath) {
    FILE* file = fopen(filepath, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    BMPHeader header;
    BMPInfoHeader infoHeader;

    // Read headers
    if (fread(&header, sizeof(BMPHeader), 1, file) != 1 ||
        fread(&infoHeader, sizeof(BMPInfoHeader), 1, file) != 1 ||
        header.type != 0x4D42 || infoHeader.compression != 0) {
        fclose(file);
        fprintf(stderr, "Not a correct BMP file or unsupported format.\n");
        return 0;
    }

    // Allocate memory for the pixel data
    unsigned char* data = (unsigned char*)malloc(infoHeader.imageSize);
    if (!data) {
        fclose(file);
        fprintf(stderr, "Cannot allocate memory for BMP data buffer.\n");
        return 0;
    }

    // Move the file pointer to the start of pixel data
    fseek(file, header.offset, SEEK_SET);
    if (fread(data, infoHeader.imageSize, 1, file) != 1) {
        fclose(file);
        free(data);
        fprintf(stderr, "Error reading BMP data.\n");
        return 0;
    }
    fclose(file);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Determine the format of the texture
    GLenum format = (infoHeader.bits == 24) ? GL_RGB : GL_RGBA;

    for (int i = 0; i < infoHeader.imageSize; i += 3) {
        unsigned char tmp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = tmp;
    }

    // Create the texture
    glTexImage2D(GL_TEXTURE_2D, 0, format, infoHeader.width, infoHeader.height, 0, format, GL_UNSIGNED_BYTE, data);

    // Release the allocated memory after setting texture
    free(data);
    data = NULL; // Avoid dangling pointer

    return textureID;
}
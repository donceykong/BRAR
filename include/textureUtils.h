#ifndef TEXTURE_UTILS_H
#define TEXTURE_UTILS_H

#include <stdlib.h>

//  cos and sin in degrees
#define Cos(th) cos(3.14159265/180*(th))
#define Sin(th) sin(3.14159265/180*(th))

#pragma pack(push, 1)
typedef struct {
    unsigned short type;             // Magic identifier
    unsigned int fileSize;          // File size in bytes
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;            // Offset to image data, bytes
} BMPHeader;

typedef struct {
    unsigned int size;              // Header size in bytes
    int width, height;              // Width and height of image
    unsigned short planes;
    unsigned short bits;            // Number of bits per pixel
    unsigned int compression;      
    unsigned int imageSize;         // Image size in bytes
    int xResolution, yResolution;
    unsigned int nColors;
    unsigned int importantColors;
} BMPInfoHeader;
#pragma pack(pop)

// Global Vars
extern GLuint BMPtextureID = 0;
extern GLuint GroundtextureID = 1;
int BMPImgNum = 1;
bool usingTextures = true;

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

    // Release the allocated memory once we have set up the texture
    free(data);

    return textureID;
}

void loadTextureFromFile(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open BMP file");
    }

    BMPHeader header;
    BMPInfoHeader infoHeader;
    fread(&header, sizeof(header), 1, file);
    fread(&infoHeader, sizeof(infoHeader), 1, file);

    // Check for valid BMP file
    if (header.type != 0x4D42 || infoHeader.compression != 0) {
        fprintf(stderr, "Unsupported BMP format\n");
        fclose(file);
    }

    unsigned char *data = (unsigned char*)malloc(infoHeader.imageSize);
    fseek(file, header.offset, SEEK_SET);
    fread(data, infoHeader.imageSize, 1, file);
    fclose(file);

    glGenTextures(1, &BMPtextureID);
    glBindTexture(GL_TEXTURE_2D, BMPtextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = (infoHeader.bits == 24) ? GL_RGB : GL_RGBA;

    for (int i = 0; i < infoHeader.imageSize; i += 3) {
        unsigned char tmp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = tmp;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, infoHeader.width, infoHeader.height, 0, format, GL_UNSIGNED_BYTE, data);

    free(data);
}

void switchBMPImage(){
    if (BMPImgNum == 1){
        loadTextureFromFile("./assets/sheet_metal.bmp");
    }
    else {
        loadTextureFromFile("./assets/cool2.bmp");
    }

    BMPImgNum = -1*BMPImgNum;
}

#endif // TEXTURE_UTILS_H
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

    glTexImage2D(GL_TEXTURE_2D, 0, format, infoHeader.width, infoHeader.height, 0, format, GL_UNSIGNED_BYTE, data);

    free(data);
}

void switchBMPImage(){
    if (BMPImgNum == 1){
        loadTextureFromFile("./assets/cool2.bmp");
    }
    else {
        loadTextureFromFile("./assets/cool.bmp");
    }

    BMPImgNum = -1*BMPImgNum;
}

#endif // TEXTURE_UTILS_H
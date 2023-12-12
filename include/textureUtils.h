#ifndef TEXTURE_UTILS_H
#define TEXTURE_UTILS_H

// Extern
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>

#pragma pack(push, 1)
typedef struct {
    unsigned short type;            // Magic identifier
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

// Ground texture
extern GLuint terrainTexture;
extern GLuint portalTexture;
extern GLuint splashTexture;

// Robot textures
extern GLuint BMPtexture1;
extern GLuint BMPtexture2;
extern GLuint BMPtexture3;
extern GLuint BMPtexture4;
extern GLuint BMPtexture5;   
extern GLuint BMPtexture6;  
extern GLuint BMPtexture7;  
extern GLuint BMPtexture;     // Main texture (set to 1:4 as desired)

GLuint loadTexture(const char* filepath);

#endif // TEXTURE_UTILS_H
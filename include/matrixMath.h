#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include <math.h>

#define PI 3.14159265358979323846

//  cos and sin in degrees
// #define Cos(th) cos(3.14159265/180*(th))
// #define Sin(th) sin(3.14159265/180*(th))

typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    float m[4][4];
} Matrix4x4;

double getEulerDistanceXZ(double pos1X, double pos1Z, double pos2X, double pos2Z);

double getEulerDistanceXYZ(double pos1X, double pos1Y, double pos1Z, double pos2X, double pos2Y, double pos2Z);

extern Matrix4x4 identityMatrix;

Matrix4x4 multiplyMatrix(Matrix4x4 a, Matrix4x4 b);

Matrix4x4 translationMatrix(float x, float y, float z);

Vector3 extractPosition(Matrix4x4 matrix);

Matrix4x4 rotationMatrix(float angle, float x, float y, float z);

#endif // MATRIX_MATH_H
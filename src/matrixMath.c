#include "matrixMath.h"

double getEulerDistanceXZ(double pos1X, double pos1Z, double pos2X, double pos2Z) {
    double xDist = pos1X - pos2X;
    double zDist = pos1Z - pos2Z;
    double eulerDist = sqrt(xDist * xDist + zDist * zDist);
    return eulerDist;
}

double getEulerDistanceXYZ(double pos1X, double pos1Y, double pos1Z, double pos2X, double pos2Y, double pos2Z) {
    double xDist = pos1X - pos2X;
    double yDist = pos1Y - pos2Y;
    double zDist = pos1Z - pos2Z;
    double eulerDist = sqrt(xDist * xDist + yDist * yDist + zDist * zDist);
    return eulerDist;
}

Matrix4x4 identityMatrix = {
    .m = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }
};

Matrix4x4 multiplyMatrix(Matrix4x4 a, Matrix4x4 b) {
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return result;
}

Matrix4x4 translationMatrix(float x, float y, float z) {
    Matrix4x4 result = identityMatrix;
    result.m[0][3] = x;
    result.m[1][3] = y;
    result.m[2][3] = z;
    return result;
}

Vector3 extractPosition(Matrix4x4 matrix) {
    Vector3 position;
    position.x = matrix.m[0][3];
    position.y = matrix.m[1][3];
    position.z = matrix.m[2][3];
    return position;
}

Matrix4x4 rotationMatrix(float angle, float x, float y, float z) {
    Matrix4x4 result = identityMatrix;
    float rad = angle * PI / 180.0;
    float c = cos(rad);
    float s = sin(rad);
    
    // Assuming the axis of rotation is normalized.
    float xx = x * x;
    float yy = y * y;
    float zz = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;

    result.m[0][0] = xx * (1-c) + c;
    result.m[0][1] = xy * (1-c) - z*s;
    result.m[0][2] = xz * (1-c) + y*s;

    result.m[1][0] = xy * (1-c) + z*s;
    result.m[1][1] = yy * (1-c) + c;
    result.m[1][2] = yz * (1-c) - x*s;

    result.m[2][0] = xz * (1-c) - y*s;
    result.m[2][1] = yz * (1-c) + x*s;
    result.m[2][2] = zz * (1-c) + c;

    return result;
}
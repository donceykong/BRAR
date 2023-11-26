/*
 * math_testing.c
*/

#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    float m[4][4];
} Matrix4x4;

Matrix4x4 identityMatrix = {
    .m = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
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

Matrix4x4 rotationMatrix(float angle, float x, float y, float z) {
    Matrix4x4 result = identityMatrix;
    float rad = angle * PI / 180.0;
    float c = cos(rad);
    float s = sin(rad);
    
    // Assuming the axis of rotation is normalized. (x^2 + y^2 + z^2 = 1)
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

Vector3 extractPosition(Matrix4x4 matrix) {
    Vector3 position;
    position.x = matrix.m[0][3];
    position.y = matrix.m[1][3];
    position.z = matrix.m[2][3];
    return position;
}

void printMatrix4x4(Matrix4x4 matrix) {
    printf("Matrix: \n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f ", matrix.m[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    
    Matrix4x4 transformationMatrix = identityMatrix;
    
    printMatrix4x4(transformationMatrix);
    printf("\n");

    // Example of translating and rotating
    Vector3 translation = {-2.0f, 0.0f, 3.0f};
    Matrix4x4 newMatrix = translationMatrix(translation.x, translation.y, translation.z);
    transformationMatrix = multiplyMatrix(newMatrix, transformationMatrix);
    
    printMatrix4x4(transformationMatrix);
    printf("\n");

    float angle = -atan(2.0f/3.0f);
    float angle_deg = angle * 180.0 / PI;
    printf("angle: %f degrees\n", angle_deg);

    Vector3 axisOfRotation = {0.0f, 1.0f, 0.0f}; // Rotate around the z-axis
    Matrix4x4 rMatrix = rotationMatrix(angle_deg, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);
    transformationMatrix = multiplyMatrix(rMatrix, transformationMatrix);

    printMatrix4x4(transformationMatrix);
    printf("\n");

    return 0;
}

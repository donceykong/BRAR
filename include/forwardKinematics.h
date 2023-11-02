typedef struct {
    float x, y, z;
} Vector3;

Vector3 extractPosition(Matrix4x4 matrix) {
    Vector3 position;
    position.x = matrix.m[0][3];
    position.y = matrix.m[1][3];
    position.z = matrix.m[2][3];
    return position;
}

Vector3 endEffectorPosition;

void computeForwardKinematics() {
    Matrix4x4 transformationMatrix = identityMatrix;

    // Joint0: Base
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(robotXPos, 2.5, robotZPos));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(joint0Angle, 0.0, 1.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.0, 0.1, 0.0));

    // Joint1 & Link1
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.0, 0.1, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(joint1Angle, 0.0, 0.0, 1.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.5, 0.0, 0.0));

    // Joint2 & Link2
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.5, 0.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(joint2Angle, 0.0, 0.0, 1.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.5, 0.0, 0.0));

    // Joint3 & Link3
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.5, 0.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(joint3Angle, 0.0, 0.0, 1.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.25, 0.0, 0.0));

    // Joint4 & End Effector
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.25, 0.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(gripperRollAngle, 1.0, 0.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.1, 0.0, 0.0));

    endEffectorPosition = extractPosition(transformationMatrix);
    
    // Print or store the end effector position as required.
    //printf("End Effector Position: X=%f, Y=%f, Z=%f\n", endEffectorPosition.x, endEffectorPosition.y, endEffectorPosition.z);
}

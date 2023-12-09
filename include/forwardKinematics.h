#ifndef FORWARD_KINEMATICS_H
#define FORWARD_KINEMATICS_H

void computeForwardKinematics() {
    Matrix4x4 transformationMatrix = identityMatrix;

    // Joint0: Base
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(chaserRobot.position.x, chaserRobot.position.y, chaserRobot.position.z));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(chaserRobot.yawAngle + chaserRobot.yawAdd, 0.0, 1.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.0, 0.1, 0.0));

    // Joint1 & Link1
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.0, 0.1, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(chaserRobot.joint1Angle, 0.0, 0.0, 1.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.5, 0.0, 0.0));

    // Joint2 & Link2
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.5, 0.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(chaserRobot.joint2Angle, 0.0, 0.0, 1.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.5, 0.0, 0.0));

    // Joint3 & Link3
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.5, 0.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(chaserRobot.joint3Angle, 0.0, 0.0, 1.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.25, 0.0, 0.0));

    // Joint4 & End Effector
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.25, 0.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, rotationMatrix(chaserRobot.gripperRollAngle, 1.0, 0.0, 0.0));
    transformationMatrix = multiplyMatrix(transformationMatrix, translationMatrix(0.1, 0.0, 0.0));

    chaserRobot.endEffectorPosition = extractPosition(transformationMatrix);
}

#endif // FORWARD_KINEMATICS_H
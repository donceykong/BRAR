#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

double getBallAngle(double posX, double posZ) {
    double ballAngle = atan2(posZ, posX);
    return ballAngle;
}

double getXDist(double robotXPos, double posX) {
    double xDist = posX - robotXPos;
    return xDist;
}

double getZDist(double robotZPos, double posZ) {
    double zDist = posZ - robotZPos;
    return zDist;
}

double getEulerDistanceXZ(double robotXPos, double robotZPos, double posX, double posZ) {
    double xDist = getXDist(robotXPos, posX);
    double zDist = getZDist(robotZPos, posZ);
    double eulerDist = sqrt(xDist * xDist + zDist * zDist);
    return eulerDist;
}

double getYawOffset(double joint0Angle, double robotXPos, double robotZPos, double objPosX, double objPosY, double objPosZ) {

    Matrix4x4 transformationMatrix = identityMatrix;
    Vector3 axisOfRotation = {0.0f, 1.0f, 0.0f}; // Rotate around the y-axis
    Matrix4x4 rMatrix = rotationMatrix(-joint0Angle, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);
    
    transformationMatrix = multiplyMatrix(rMatrix, transformationMatrix);

    // Set Obj pos as a Matrix
    Matrix4x4 objPosMatrix = translationMatrix(objPosX - robotXPos, objPosY, objPosZ - robotZPos);
    transformationMatrix = multiplyMatrix(transformationMatrix, objPosMatrix);

    Vector3 relativeObjPos = extractPosition(transformationMatrix);
    //printf("relativeObjPos.x: %f, relativeObjPos.z: %f\n\n", relativeObjPos.x, relativeObjPos.z);

    double yawAngle = atanf(relativeObjPos.z / relativeObjPos.x);

    return yawAngle;
}

double getPitchOffset(double joint1Angle, double robotXPos, double robotZPos, double objPosX, double objPosY, double objPosZ) {
    Matrix4x4 transformationMatrix = identityMatrix;
    Vector3 axisOfRotation = {1.0f, 0.0f, 0.0f}; // Rotate around the x-axis
    Matrix4x4 rMatrix = rotationMatrix(-joint1Angle, axisOfRotation.x, axisOfRotation.y, axisOfRotation.z);
    
    transformationMatrix = multiplyMatrix(rMatrix, transformationMatrix);

    // Set Obj pos as a Matrix
    Matrix4x4 objPosMatrix = translationMatrix(objPosX - endEffectorPosition.x, objPosY - endEffectorPosition.y, objPosZ - endEffectorPosition.z);
    transformationMatrix = multiplyMatrix(transformationMatrix, objPosMatrix);

    Vector3 relativeObjPos = extractPosition(transformationMatrix);
    //printf("relativeObjPos.x: %f, relativeObjPos.z: %f\n\n", relativeObjPos.x, relativeObjPos.z);

    double pitchAngle = atanf(relativeObjPos.y / relativeObjPos.z);

    return pitchAngle;
}

#endif // ROBOT_CONTROLLER_H

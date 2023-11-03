#ifndef ROBOTCONTROLLER_H
#define ROBOTCONTROLLER_H

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

#endif // ROBOTCONTROLLER_H

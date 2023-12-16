#ifndef KEY_UPDATE_H
#define KEY_UPDATE_H

// local
#include "lighting.h"
#include "keys.h"

double lightRotation = 0.0;
double fpCamRotation = 0.0;
double lightZoomInc = 0.25;

void updateRunner(LightArray* lights)
{
  double gripperRollinc     = 0.00;
  double gripperDistinc     = 0.00;
  
  runnerRobot.speedAdjust   = 0.00;

  // Gripper Adjust
  if (keyStates.up)
    runnerRobot.speedAdjust =  2.00 * SPEED;
  if (keyStates.down)
    runnerRobot.speedAdjust = -2.00 * SPEED;
  if (keyStates.right)
    gripperRollinc          = -5.00 * SPEED;
  if (keyStates.left)
    gripperRollinc          =  5.00 * SPEED;

  runnerRobot.speed = runnerRobot.speedAdjust;

  // JUMP ROBOT
  if (keyStates.space && !keyStates.spacePrev) {
    runnerRobot.externalForce.y = 20000;
  }
  else {
    runnerRobot.externalForce.y = 0;
  }
  keyStates.spacePrev = keyStates.space;

  // set CHASER & RUNNER prev XZ to current while not in collision
  if (!runnerRobot.inCollision) {
    runnerRobot.prevPos.x = runnerRobot.position.x;
    runnerRobot.prevPos.y = runnerRobot.position.y;
    runnerRobot.prevPos.z = runnerRobot.position.z;
  }
  if (!chaserRobot.inCollision) {
    // set prev position and joint angles
    chaserRobot.prevPos.x = chaserRobot.position.x;
    chaserRobot.prevPos.y = chaserRobot.position.y;
    chaserRobot.prevPos.z = chaserRobot.position.z;

    chaserRobot.prevJoint1Angle = chaserRobot.joint1Angle;
    chaserRobot.prevJoint2Angle = chaserRobot.joint2Angle;
    chaserRobot.prevJoint3Angle = chaserRobot.joint3Angle;
  }

  // CHASER & RUNNER Control, depending if RUNNER captured or not
  if (!runnerRobot.captured) {
    // Move runner
    runnerRobot.yawAngle   += gripperRollinc;
    double angleYradians    = runnerRobot.yawAngle * PI / 180;
    runnerRobot.position.z += runnerRobot.speed * cos(angleYradians);
    runnerRobot.position.x += runnerRobot.speed * sin(angleYradians);

    // Move chaser
    double chaserGain;
    if (waypointTracking) {
      chaserGain = 0.2;
      chaserRobot.position.x -= chaserRobot.speedAdjust * chaserGain * (chaserRobot.endEffectorPosition.x-WaypointPosX);
      chaserRobot.position.z -= chaserRobot.speedAdjust * chaserGain * (chaserRobot.endEffectorPosition.z-WaypointPosZ);
      chaserRobot.speed       = chaserRobot.speedAdjust * getEulerDistanceXZ(chaserRobot.endEffectorPosition.x, chaserRobot.endEffectorPosition.z, WaypointPosX, WaypointPosZ);
    }
    else {
      chaserGain = 0.02;
      chaserRobot.position.x -= chaserRobot.speedAdjust * chaserGain * (chaserRobot.endEffectorPosition.x-runnerRobot.position.x);
      chaserRobot.position.z -= chaserRobot.speedAdjust * chaserGain * (chaserRobot.endEffectorPosition.z-runnerRobot.position.z);
      chaserRobot.speed       = chaserRobot.speedAdjust * getEulerDistanceXZ(chaserRobot.endEffectorPosition.x, chaserRobot.endEffectorPosition.z, runnerRobot.position.x, runnerRobot.position.z);
    }
  }
  else {
    if (chaserRobot.joint1Angle <= 90.0) {
      chaserRobot.joint1Angle += 1.0;
    }
    else {
      runnerRobot.taken = true;
    }
  }

  // set CHASER & RUNNER current XZ to prev XZ to if in collision
  if (runnerRobot.inCollision) {
    runnerRobot.position.x = runnerRobot.prevPos.x;
    runnerRobot.position.y = runnerRobot.prevPos.y;
    runnerRobot.position.z = runnerRobot.prevPos.z;
  }
  if (chaserRobot.inCollision) {
    chaserRobot.position.x = chaserRobot.prevPos.x;
    chaserRobot.position.y = chaserRobot.prevPos.y;
    chaserRobot.position.z = chaserRobot.prevPos.z;

    chaserRobot.joint1Angle = chaserRobot.prevJoint1Angle;
    chaserRobot.joint2Angle = chaserRobot.prevJoint2Angle;
    chaserRobot.joint3Angle = chaserRobot.prevJoint3Angle;
  }

  // THE LIGHTING
  double lightRotInc = 0.00;

  if (keyStates.a)
    lightRotInc = 5.00 * SPEED;
  if (keyStates.d)
    lightRotInc = -5.00 * SPEED;
  if (keyStates.i)
    lightZoomInc -= 0.01;
  if (keyStates.k)
    lightZoomInc += 0.01;
  
  if (lightZoomInc < 0.00) {
    lightZoomInc = 0.00;
  }
  if (lightZoomInc > 1.0) {
    lightZoomInc = 1.0;
  }
  double orbitRadius = 2.0 + 8.0*lightZoomInc;
  lightRotation += lightRotInc;
  lights->light[0].angularPos.y += 0.05*(runnerRobot.yawAngle + 45.0 + lightRotation - lights->light[0].angularPos.y);
  lights->light[0].position.x   += 0.05*(runnerRobot.position.x - lights->light[0].position.x - orbitRadius*sin(lights->light[0].angularPos.y * PI / 180));
  lights->light[0].position.y   += 0.05*(runnerRobot.position.y - lights->light[0].position.y);
  lights->light[0].position.z   += 0.05*(runnerRobot.position.z - lights->light[0].position.z - orbitRadius*cos(lights->light[0].angularPos.y * PI / 180));

  // CAMERA VIEWING
    double fpCamRotInc = 0.00;
  if (keyStates.key1) {
    viewMode = 1;
  } 
  else if (keyStates.key2) {
    viewMode = 2;
  }
  if (keyStates.o)
    fpCamZoom *= 0.99;
  else if (keyStates.l)
    fpCamZoom *= 1.1;
  if (keyStates.key3)
    fpCamRotInc = 5.00 * SPEED;
  else if (keyStates.key4)
    fpCamRotInc = -5.00 * SPEED;

  fpCamRotation += fpCamRotInc;
  if (viewMode == 1) {
    orbitCamAngleY -= 0.05*(orbitCamAngleY-runnerRobot.yawAngle + 180 + fpCamRotation);
    orbitCamZ      -= 0.08*(orbitCamZ-runnerRobot.position.z);
    orbitCamY      -= 0.10*(orbitCamY-runnerRobot.position.y);
    orbitCamX      -= 0.08*(orbitCamX-runnerRobot.position.x);
  }
  else if (viewMode == 2) {
    overheadCamAngleY -= 0.04*(overheadCamAngleY - runnerRobot.yawAngle + 180.0 + fpCamRotation);
    overheadCamX -= 0.08*(overheadCamX + runnerRobot.position.x);
    overheadCamY -= 0.08*(overheadCamY + runnerRobot.position.y);
    overheadCamZ -= 0.08*(overheadCamZ + runnerRobot.position.z);

    // // FOLLOW MIDLINE BW CHASER AND RUNNER (YAW ANGLE IS ONLY ON RUNNER AND NEEDS TO BE ANGLE OF LINE FROM CHASER TO RUNNER)
    // overheadCamAngleY = runnerRobot.yawAngle - 180.0;
    // double poseDiff = 0.5*sqrt((runnerRobot.position.x-chaserRobot.position.x)*(runnerRobot.position.x-chaserRobot.position.x) + (runnerRobot.position.z-chaserRobot.position.z)*(runnerRobot.position.z-chaserRobot.position.z));
    // overheadCamX = -runnerRobot.position.x + (runnerRobot.position.x-chaserRobot.position.x)/2.0;
    // overheadCamY = -1 - poseDiff;
    // overheadCamZ = -runnerRobot.position.z + (runnerRobot.position.z-chaserRobot.position.z)/2.0;
  }

  // Adjust joint angles
  double yawDeg;
  if (waypointTracking && RRTSTAR_ACTIVE) {
    yawDeg = 10.0*getYawOffset(chaserRobot.yawAngle, chaserRobot.position.x, chaserRobot.position.z, 
                          WaypointPosX, 2.0, WaypointPosZ) 
                          * 180 / PI;
  }
  else {
    yawDeg = getYawOffset(chaserRobot.yawAngle, chaserRobot.position.x, chaserRobot.position.z, 
                                           runnerRobot.position.x, runnerRobot.position.y, runnerRobot.position.z) 
                                           * 180 / PI;
  }

  chaserRobot.yawAngle     -= chaserRobot.speedAdjust * 0.1 * yawDeg; 
  chaserRobot.joint1Angle  += (runnerRobot.position.y - chaserRobot.endEffectorPosition.y);

  computeForwardKinematics(); // call to get new endeffector pos
  chaserRobot.joint2Angle     += (runnerRobot.position.y - chaserRobot.endEffectorPosition.y);

  runnerRobot.viewableSpeed = 20.0*fabsf(runnerRobot.speed) + 5.0*fabsf(gripperRollinc);
  chaserRobot.viewableSpeed = fabsf(chaserRobot.speed) + fabsf(0.1*yawDeg);

  // Grab runner robot
  if (!chaserRobot.gripperClosed && 
      fabsf(runnerRobot.position.x-chaserRobot.endEffectorPosition.x)<0.1 && 
      fabsf(runnerRobot.position.y-chaserRobot.endEffectorPosition.y)<0.1 && 
      fabsf(runnerRobot.position.z-chaserRobot.endEffectorPosition.z)<0.1) 
  {
      gripperDistinc = -0.01;
  }

  // chaserRobot.joint3Angle += joint3inc;
  chaserRobot.gripperDist += gripperDistinc;
  chaserRobot.gripperRollAngle += gripperRollinc;

  if (chaserRobot.joint1Angle >= 250.00) {
    chaserRobot.joint1Angle = 250.00;
  } else if (chaserRobot.joint1Angle <= -70.00) {
    chaserRobot.joint1Angle = -70.00;
  }

  if (chaserRobot.joint2Angle >= 90.00) {
    chaserRobot.joint2Angle = 90.00;
  } else if (chaserRobot.joint2Angle <= -90.00) {
    chaserRobot.joint2Angle = -90.00;
  }

  // if (chaserRobot.joint3Angle > 90.00) {
  //   chaserRobot.joint3Angle -= joint3inc;
  // } else if (chaserRobot.joint3Angle < -90.00) {
  //   chaserRobot.joint3Angle -= joint3inc;
  // }

  if (chaserRobot.gripperDist >= 0.30) {
    chaserRobot.gripperDist -= gripperDistinc;
  } else if (chaserRobot.gripperDist <= 0.10) {
    chaserRobot.gripperDist -= gripperDistinc;
  }
    
  if (chaserRobot.gripperDist <= 0.20){
    chaserRobot.gripperClosed = true;
  }
  else {
    chaserRobot.gripperClosed = false;
  }
} 

























void updateTimeCrunch(LightArray* lights)
{
//   double robotXPosInc = 0.00;
//   double robotZPosInc = 0.00;
//   double joint3inc = 0.00;
  double gripperRollinc = 0.00;
  double gripperDistinc = 0.00;
  chaserRobot.speedAdjust = 0.0;

  // ROBOT POS ADJUST
  if (keyStates.up)
    chaserRobot.speedAdjust =  2.00 * SPEED;
  if (keyStates.down)
    chaserRobot.speedAdjust = -2.00 * SPEED;
  if (keyStates.right)
    gripperRollinc = -10.00 * SPEED;
  if (keyStates.left)
    gripperRollinc = 10.00 * SPEED;

  // JUMPING
  if (keyStates.space && !keyStates.spacePrev) {
    chaserRobot.externalForce.y = 20000;
  }
  else {
    chaserRobot.externalForce.y = 0;
  }
  keyStates.spacePrev = keyStates.space;

  // Move chaser
  chaserRobot.speed = chaserRobot.speedAdjust;
  chaserRobot.yawAngle += gripperRollinc;
  double angleYradians = chaserRobot.yawAngle * PI / 180;
  computeForwardKinematics(); // call to get new endeffector pos
  if (chaserRobot.inCollision) {
    chaserRobot.endEffectorPosition.z = chaserRobot.prevPos.z;
    chaserRobot.endEffectorPosition.x = chaserRobot.prevPos.x;
  }
  else {
    chaserRobot.prevPos.z = chaserRobot.endEffectorPosition.z;
    chaserRobot.prevPos.x = chaserRobot.endEffectorPosition.x;
    chaserRobot.position.z -= chaserRobot.speed*cos(angleYradians);
    chaserRobot.position.x -= chaserRobot.speed*sin(angleYradians);
  }

  chaserRobot.viewableSpeed = 20.0*fabsf(chaserRobot.speed) + 5.0*fabsf(gripperRollinc);

  // LIGHTING
  double lightRotInc = 0.00;

  if (keyStates.a)
    lightRotInc = 5.00 * SPEED;
  if (keyStates.d)
    lightRotInc = -5.00 * SPEED;
  if (keyStates.i)
    lightZoomInc -= 0.01;
  if (keyStates.k)
    lightZoomInc += 0.01;

  if (lightZoomInc < 0.00) {
    lightZoomInc = 0.00;
  }
  if (lightZoomInc > 1.0) {
    lightZoomInc = 1.0;
  }
  double orbitRadius = 2.0 + 8.0*lightZoomInc;
  lightRotation += lightRotInc;
  lights->light[0].angularPos.y += 0.05*(chaserRobot.yawAngle + 225.0 + lightRotation - lights->light[0].angularPos.y);
  lights->light[0].position.x   += 0.05*(chaserRobot.position.x - lights->light[0].position.x - orbitRadius*sin(lights->light[0].angularPos.y * PI / 180));
  lights->light[0].position.y   += 0.05*(chaserRobot.position.y - lights->light[0].position.y);
  lights->light[0].position.z   += 0.05*(chaserRobot.position.z - lights->light[0].position.z - orbitRadius*cos(lights->light[0].angularPos.y * PI / 180));

  // Camera Position & Orientation
  // View Zoom Adjust
  double fpCamRotInc = 0.00;

  if (keyStates.key1) {
    viewMode = 1;
  } 
  else if (keyStates.key2) {
    viewMode = 2;
  }
  if (keyStates.o)
    fpCamZoom *= 0.99;
  if (keyStates.l)
    fpCamZoom *= 1.1;
  if (keyStates.key3)
    fpCamRotInc = 5.00 * SPEED;
  if (keyStates.key4)
    fpCamRotInc = -5.00 * SPEED;

  // CAMERA POS CONTROL (IMITATES CAM STAYING AT LAST POSITION UNTIL SUMMONED :D)
  fpCamRotation += fpCamRotInc;
  if (viewMode == 1) {
    orbitCamAngleY -= 0.05*(orbitCamAngleY-chaserRobot.yawAngle + fpCamRotation);
    orbitCamZ -= 0.08*(orbitCamZ-chaserRobot.position.z);
    orbitCamY -= 0.10*(orbitCamY-chaserRobot.position.y);
    orbitCamX -= 0.08*(orbitCamX-chaserRobot.position.x);
  }
  else if (viewMode == 2) {
    overheadCamAngleY -= 0.04*(overheadCamAngleY - chaserRobot.yawAngle + fpCamRotation);
    overheadCamX -= 0.08*(overheadCamX + chaserRobot.position.x);
    overheadCamY -= 0.08*(overheadCamY + chaserRobot.position.y);
    overheadCamZ -= 0.08*(overheadCamZ + chaserRobot.position.z);
  }

  // ROBOT POSE
  chaserRobot.joint1Angle += 5.0*(nearestMapItem->position.y -chaserRobot.endEffectorPosition.y);
  computeForwardKinematics(); // call to get new endeffector pos
  chaserRobot.joint2Angle += 5.0*(nearestMapItem->position.y -chaserRobot.endEffectorPosition.y);

  if (chaserRobot.joint1Angle >= 90.00) {
    chaserRobot.joint1Angle = 90.00;
  } else if (chaserRobot.joint1Angle <= -70.00) {
    chaserRobot.joint1Angle = -70.00;
  }

  if (chaserRobot.joint2Angle >= 45.00) {
    chaserRobot.joint2Angle = 45.00;
  } else if (chaserRobot.joint2Angle <= -45.00) {
    chaserRobot.joint2Angle = -45.00;
  }

  chaserRobot.gripperDist += gripperDistinc;
  chaserRobot.gripperRollAngle += gripperRollinc;

  // if (chaserRobot.joint3Angle > 90.00) {
  //   chaserRobot.joint3Angle -= joint3inc;
  // } else if (chaserRobot.joint3Angle < -90.00) {
  //   chaserRobot.joint3Angle -= joint3inc;
  // }

  if (chaserRobot.gripperDist >= 0.30) {
    chaserRobot.gripperDist -= gripperDistinc;
  } else if (chaserRobot.gripperDist <= 0.10) {
    chaserRobot.gripperDist -= gripperDistinc;
  }
    
  if (chaserRobot.gripperDist <= 0.20){
    chaserRobot.gripperClosed = true;
  }
  else {
    chaserRobot.gripperClosed = false;
  }
} 

























void updateViewRobot(LightArray* lights)
{
  double lightRotInc = 0.00;
  double fpCamRotInc = 0.00;
  
  // lighting rotate
  if (keyStates.a)
    lightRotInc = 5.00 * SPEED;
  if (keyStates.d)
    lightRotInc = -5.00 * SPEED;
  if (keyStates.i)
    lightZoomInc -= 0.01;
  if (keyStates.k)
    lightZoomInc += 0.01;

  if (keyStates.key1) {
    viewMode = 1;
  } 
  else if (keyStates.key2) {
    viewMode = 2;
  }
  if (keyStates.key3)
    fpCamRotInc = 5.00 * SPEED;
  else if (keyStates.key4)
    fpCamRotInc = -5.00 * SPEED;

  chaserRobot.joint1Angle += 0.01;
  chaserRobot.joint2Angle -= 0.02;
  chaserRobot.joint3Angle += 0.02;
  chaserRobot.gripperRollAngle += 0.05;

  // LIGHTING
  if (lightZoomInc < 0.00) {
    lightZoomInc = 0.00;
  }
  if (lightZoomInc > 1.0) {
    lightZoomInc = 1.0;
  }
  double orbitRadius = 2.0 + 8.0*lightZoomInc;
  lightRotation += lightRotInc;
  lights->light[0].angularPos.y = lightRotation + 180;
  lights->light[0].position.x = -orbitRadius * sin(lights->light[0].angularPos.y * PI / 180);
  lights->light[0].position.y = 2.0;
  lights->light[0].position.z = -orbitRadius * cos(lights->light[0].angularPos.y * PI / 180);

  if (keyStates.o)
    fpCamZoom *= 0.99;
  if (keyStates.l)
    fpCamZoom *= 1.1;
  if (keyStates.key3)
    fpCamRotInc = 5.00 * SPEED;
  if (keyStates.key4)
    fpCamRotInc = -5.00 * SPEED;

  // CAMERA POS CONTROL (IMITATES CAM STAYING AT LAST POSITION UNTIL SUMMONED :D)
  fpCamRotation += fpCamRotInc;
  if (viewMode == 1) {
    orbitCamAngleY -= 0.05*(orbitCamAngleY-chaserRobot.yawAngle + fpCamRotation);
    orbitCamZ -= 0.08*(orbitCamZ-chaserRobot.position.z);
    orbitCamY -= 0.10*(orbitCamY-chaserRobot.position.y);
    orbitCamX -= 0.08*(orbitCamX-chaserRobot.position.x);
  }
  else if (viewMode == 2) {
    overheadCamAngleY -= 0.04*(overheadCamAngleY - chaserRobot.yawAngle + fpCamRotation);
    overheadCamX -= 0.08*(overheadCamX + chaserRobot.position.x);
    overheadCamY -= 0.08*(overheadCamY + chaserRobot.position.y);
    overheadCamZ -= 0.08*(overheadCamZ + chaserRobot.position.z);
  }
} 

#endif // KEY_UPDATE_H
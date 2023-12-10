#ifndef KEY_UPDATE_H
#define KEY_UPDATE_H

#include "keyHandler.h"

void updateRunner()
{
//   double robotXPosInc       = 0.00;
//   double robotZPosInc       = 0.00;
//   double joint2inc          = 0.00;
  // double joint3inc = 0.00;
  double gripperRollinc     = 0.00;
  double gripperDistinc     = 0.00;
  
  runnerRobot.speedAdjust   = 0.00;

//   // Joint 2 Adjust
//   if (keyStates.y)
//     joint2inc               =  5.00 * SPEED;
//   if (keyStates.h)
//     joint2inc               = -5.00 * SPEED;

  // Gripper Adjust
  if (keyStates.up)
    runnerRobot.speedAdjust =  2.00 * SPEED;
  if (keyStates.down)
    runnerRobot.speedAdjust = -2.00 * SPEED;
  if (keyStates.right)
    gripperRollinc          = -5.00 * SPEED;
  if (keyStates.left)
    gripperRollinc          =  5.00 * SPEED;

  // if (key4) {
  //   runnerRobot.speedAdjust += 0.01;
  // } else if (key5) {
  //   runnerRobot.speedAdjust -= 0.01;
  // }

  // Gripper Adjust
  if (keyStates.j)
    gripperDistinc          = -0.01 * SPEED;
  if (keyStates.k)
    gripperDistinc          =  0.01 * SPEED;

  if (keyStates.key1) {
    viewMode                = 1;
  } 
  else if (keyStates.key2) {
    viewMode                = 2;
  }

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
    runnerRobot.prevPos.z = runnerRobot.position.z;
    runnerRobot.prevPos.x = runnerRobot.position.x;
  }
  if (!chaserRobot.inCollision) {
    chaserRobot.prevPos.z = chaserRobot.position.z;
    chaserRobot.prevPos.x = chaserRobot.position.x;
  }

  // CHASER & RUNNER Control, depending if RUNNER captured or not
  if (!runnerRobot.captured) {
    // Move runner
    runnerRobot.yawAngle   += gripperRollinc;
    double angleYradians    = runnerRobot.yawAngle * PI / 180;
    runnerRobot.position.z += runnerRobot.speed * cos(angleYradians);
    runnerRobot.position.x += runnerRobot.speed * sin(angleYradians);

    // Move chaser
    chaserRobot.position.x -= chaserRobot.speedAdjust * 0.02 * (chaserRobot.endEffectorPosition.x-runnerRobot.position.x);
    chaserRobot.position.z -= chaserRobot.speedAdjust * 0.02 * (chaserRobot.endEffectorPosition.z-runnerRobot.position.z);
    chaserRobot.speed       = chaserRobot.speedAdjust * getEulerDistanceXZ(chaserRobot.endEffectorPosition.x, chaserRobot.endEffectorPosition.z, runnerRobot.position.x, runnerRobot.position.z);
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
    runnerRobot.position.z = runnerRobot.prevPos.z;
    runnerRobot.position.x = runnerRobot.prevPos.x;
  }
  if (chaserRobot.inCollision) {
    chaserRobot.position.z = chaserRobot.prevPos.z;
    chaserRobot.position.x = chaserRobot.prevPos.x;
  }

  // THE LIGHTING
  double orbitRadius = 4.0;
  light1Rotation = lightrot + runnerRobot.yawAngle + 45.0;
  light1_X = -orbitRadius * sin(light1Rotation * PI / 180) + runnerRobot.position.x;
  light1_Y = runnerRobot.position.y;
  light1_Z = -orbitRadius * cos(light1Rotation * PI / 180) + runnerRobot.position.z;

  light2Rotation = lightrot + runnerRobot.yawAngle - 45.0;
  light2_X = -orbitRadius * sin(light2Rotation * PI / 180) + runnerRobot.position.x;
  light2_Y = runnerRobot.position.y;
  light2_Z = -orbitRadius * cos(light2Rotation * PI / 180) + runnerRobot.position.z;
  lightrot += 0.5;

  // Camera Position & Orientation
  // View Zoom Adjust
  if (keyStates.o)
    fpCamZoom *= 0.99;
  if (keyStates.l)
    fpCamZoom *= 1.1;

  if (viewMode == 1) {
    orbitCamAngleY -= 0.05*(orbitCamAngleY-runnerRobot.yawAngle + 180);
    orbitCamZ      -= 0.08*(orbitCamZ-runnerRobot.position.z);
    orbitCamX      -= 0.08*(orbitCamX-runnerRobot.position.x);
  }
  
  double poseDiff = 0.5*sqrt((runnerRobot.position.x-chaserRobot.position.x)*(runnerRobot.position.x-chaserRobot.position.x) + (runnerRobot.position.z-chaserRobot.position.z)*(runnerRobot.position.z-chaserRobot.position.z));
  overheadCamX = -runnerRobot.position.x + (runnerRobot.position.x-chaserRobot.position.x)/2.0;
  overheadCamY = -1 - poseDiff;
  overheadCamZ = -runnerRobot.position.z + (runnerRobot.position.z-chaserRobot.position.z)/2.0;

  // Adjust joint angles
  double yaw = getYawOffset(chaserRobot.yawAngle, chaserRobot.position.x, chaserRobot.position.z, runnerRobot.position.x, runnerRobot.position.y, runnerRobot.position.z) * 180 / PI;
  chaserRobot.yawAngle  -= chaserRobot.speedAdjust * 0.1 * yaw; 
  chaserRobot.joint1Angle     += (runnerRobot.position.y - chaserRobot.endEffectorPosition.y);
  computeForwardKinematics(); // call to get new endeffector pos
  chaserRobot.joint2Angle     += (runnerRobot.position.y - chaserRobot.endEffectorPosition.y);

  runnerRobot.viewableSpeed = 20.0*fabsf(runnerRobot.speed) + 5.0*fabsf(gripperRollinc);
  chaserRobot.viewableSpeed = fabsf(chaserRobot.speed) + fabsf(0.1*yaw);

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

























void updateTimeCrunch()
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
  
  // Gripper Adjust
  if (keyStates.j)
    gripperDistinc = -0.01 * SPEED;
  if (keyStates.k)
    gripperDistinc = 0.01 * SPEED;

  // View Zoom Adjust
  if (keyStates.o)
    fpCamZoom *= 0.99;
  if (keyStates.l)
    fpCamZoom *= 1.1;

  if (keyStates.key1) {
    viewMode = 1;
  } 
  else if (keyStates.key2) {
    viewMode = 2;
  }

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
  if (chaserRobot.inCollision) {
    chaserRobot.position.z = chaserRobot.prevPos.z;
    chaserRobot.position.x = chaserRobot.prevPos.x;
  }
  else {
    chaserRobot.prevPos.z = chaserRobot.position.z;
    chaserRobot.prevPos.x = chaserRobot.position.x;
    chaserRobot.position.z -= chaserRobot.speed*cos(angleYradians);
    chaserRobot.position.x -= chaserRobot.speed*sin(angleYradians);
  }

  chaserRobot.viewableSpeed = 20.0*fabsf(chaserRobot.speed) + 5.0*fabsf(gripperRollinc);

  // TODO: FIX THE LIGHTING
  double orbitRadius = 4.0;
  light1Rotation = lightrot + chaserRobot.yawAngle + 45.0 + 180;
  light1_X = -orbitRadius * sin(light1Rotation * PI / 180) + chaserRobot.position.x;
  light1_Y = chaserRobot.position.y;
  light1_Z = -orbitRadius * cos(light1Rotation * PI / 180) + chaserRobot.position.z;

  light2Rotation = lightrot + chaserRobot.yawAngle + -45 + 180;
  light2_X = -orbitRadius * sin(light2Rotation * PI / 180) + chaserRobot.position.x;
  light2_Y = chaserRobot.position.y;
  light2_Z = -orbitRadius * cos(light2Rotation * PI / 180) + chaserRobot.position.z;
  lightrot += 0.5;

  // CAMERA POS
  if (viewMode == 1) {
    // Compute the camera position using spherical coordinates.
    orbitCamAngleY -= 0.05*(orbitCamAngleY-chaserRobot.yawAngle);
    orbitCamY = 0.0;
    orbitCamZ -= 0.08*(orbitCamZ-chaserRobot.position.z);
    orbitCamX -= 0.08*(orbitCamX-chaserRobot.position.x);
  }

  overheadCamX = -chaserRobot.position.x;
  overheadCamY = -1;
  overheadCamZ = -chaserRobot.position.z;
  
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

























void updateViewRobot()
{
//   double robotXPosInc = 0.00;
//   double robotZPosInc = 0.00;
  // double joint0inc = 0.00;
  // double joint1inc = 0.00;
//   double joint2inc = 0.00;
//   double joint3inc = 0.00;
  double gripperRollinc = 0.00;
  double gripperDistinc = 0.00;

//   // Joint 2 Adjust
//   if (keyStates.y)
//     joint2inc = 5.00 * SPEED;
//   if (keyStates.h)
//     joint2inc = -5.00 * SPEED;

//   // Gripper Adjust
//   if (keyStates.up)
//     joint3inc = 5.00 * SPEED;
//   if (keyStates.down)
//     joint3inc = -5.00 * SPEED;
  if (keyStates.right)
    gripperRollinc = -5.00 * SPEED;
  if (keyStates.left)
    gripperRollinc = 5.00 * SPEED;
  
  // Gripper Adjust
  if (keyStates.j)
    gripperDistinc = -0.01 * SPEED;
  if (keyStates.k)
    gripperDistinc = 0.01 * SPEED;
  // Grab runner robot
  if (!chaserRobot.gripperClosed && fabsf(runnerRobot.position.x-chaserRobot.endEffectorPosition.x)<0.1 && fabsf(runnerRobot.position.y-chaserRobot.endEffectorPosition.y)<0.1 && fabsf(runnerRobot.position.z-chaserRobot.endEffectorPosition.z)<0.1) {
      gripperDistinc = -0.01;
  }

  // lighting Distance Adjust
  if (keyStates.o)
    lightingDist *= 0.99;
  if (keyStates.l)
    lightingDist *= 1.1;

  // View Zoom Adjust
  if (keyStates.o)
    fpCamZoom *= 0.99;
  if (keyStates.l)
    fpCamZoom *= 1.1;

  if (keyStates.key1) {
    viewMode = 1;
  } 
  else if (keyStates.key2) {
    viewMode = 2;
  }

  // TODO: FIX THE LIGHTING
  double orbitRadius = 4.0;
  light1Rotation = lightrot + chaserRobot.yawAngle + 45.0 + 180;
  light1_X = -orbitRadius * sin(light1Rotation * PI / 180) + chaserRobot.position.x;
  light1_Y = chaserRobot.position.y + 1;
  light1_Z = -orbitRadius * cos(light1Rotation * PI / 180) + chaserRobot.position.z;

  light2Rotation = lightrot + chaserRobot.yawAngle - 45.0 + 180;
  light2_X = -orbitRadius * sin(light2Rotation * PI / 180) + chaserRobot.position.x;
  light2_Y = chaserRobot.position.y + 1;
  light2_Z = -orbitRadius * cos(light2Rotation * PI / 180) + chaserRobot.position.z;
  lightrot += 0.8;

  if (viewMode == 1) {
    orbitCamAngleY += 0.5*gripperRollinc;
    orbitCamZ = chaserRobot.position.z;
    orbitCamY = 1.0;
    orbitCamX = chaserRobot.position.x;
  }

//   if (chaserRobot.joint1Angle >= 250.00) {
//     chaserRobot.joint1Angle = 250.00;
//   } else if (chaserRobot.joint1Angle <= -70.00) {
//     chaserRobot.joint1Angle = -70.00;
//   }

//   if (chaserRobot.joint2Angle >= 90.00) {
//     chaserRobot.joint2Angle = 90.00;
//   } else if (chaserRobot.joint2Angle <= -90.00) {
//     chaserRobot.joint2Angle = -90.00;
//   }

//   chaserRobot.joint3Angle += joint3inc;
  chaserRobot.gripperDist += gripperDistinc;
  chaserRobot.gripperRollAngle += gripperRollinc;

//   if (chaserRobot.joint3Angle > 90.00) {
//     chaserRobot.joint3Angle -= joint3inc;
//   } else if (chaserRobot.joint3Angle < -90.00) {
//     chaserRobot.joint3Angle -= joint3inc;
//   }

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

#endif // KEY_UPDATE_H
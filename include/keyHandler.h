#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

bool keyRight = false;
bool keyLeft = false;
bool keyUp = false;
bool keyDown = false;

bool keyW = false;
bool keyS = false;
bool keyA = false;
bool keyD = false;
bool keyY = false;
bool keyH = false;

bool keyJ = false;
bool keyK = false;

// UNUSED
bool keyT = false;  // UNUSED
bool keyF = false;  // UNUSED
bool keyG = false;  // UNUSED
bool keyV = false;  // UNUSED

// UNUSED
bool keyO = false;  // UNUSED
bool keyL = false;  // UNUSED
bool keyP = false;  // UNUSED
bool keyI = false;  // UNUSED

bool key0 = false;
bool key1 = false;
bool key2 = false;
bool key3 = false;  // UNUSED
bool key4 = false;  // Inc runner speed
bool key5 = false;  // dec runner speed

bool lightKeyPressed = false;  // Keep track of whether '0' key is pressed

void special(int key, int x, int y) 
{
  switch (key) {
    case GLUT_KEY_RIGHT: 
      keyRight = true;
      break;
    case GLUT_KEY_LEFT: 
      keyLeft = true;
      break;
    case GLUT_KEY_UP: 
      keyUp = true;
      break;
    case GLUT_KEY_DOWN: 
      keyDown = true;
      break;
    default: 
      return;
  }
}

void specialUp(int key, int x, int y) 
{
  switch (key) {
    case GLUT_KEY_RIGHT: 
      keyRight = false;
      break;
    case GLUT_KEY_LEFT: 
      keyLeft = false;
      break;
    case GLUT_KEY_UP: 
      keyUp = false;
      break;
    case GLUT_KEY_DOWN: 
      keyDown = false;
      break;
    default: 
      return;
  }
}

void handleKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            keyW = true;
            break;
        case 's':
            keyS = true;
            break;
        case 'a':
            keyA = true;
            break;
        case 'd':
            keyD = true;
            break;
        case 'j':
            keyJ = true;
            break;
        case 'k':
            keyK = true;
            break;
        case 'y':
            keyY = true;
            break;
        case 'h':
            keyH = true;
            break;
        case 't':
            keyT = true;
            break;
        case 'f':
            keyF = true;
            break;
        case 'g':
            keyG = true;
            break;
        case 'v':
            keyV = true;
            break;
        case 'o':
            keyO = true;
            break;
        case 'l':
            keyL = true;
            break;
        case 'p':
            keyP = true;
            break;
        case 'i':
            keyI = true;
            break;
        case '0':
            lightKeyPressed = !lightKeyPressed; // Toggle the light key state
            lightEnabled = lightKeyPressed; // Update lightEnabled accordingly
            key0 = true;
            break;
        case '1':
            key1 = true;
            break;
        case '2':
            key2 = true;
            break;
        case '3':
            key3 = true;
            break;
        case '4':
            //usingTextures = !usingTextures;
            runnerSpeed += 1.0;
            key4 = true;
            break;
        case '5':
            //switchBMPImage();
            runnerSpeed -= 1.0;
            key5 = true;
            break;
        default:
            return;
    }
}

void handleKeysUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            keyW = false;
            break;
        case 's':
            keyS = false;
            break;
        case 'a':
            keyA = false;
            break;
        case 'd':
            keyD = false;
            break;
        case 'j':
            keyJ = false;
            break;
        case 'k':
            keyK = false;
            break;
        case 'y':
            keyY = false;
            break;
        case 'h':
            keyH = false;
            break;
        case 't':
            keyT = false;
            break;
        case 'f':
            keyF = false;
            break;
        case 'g':
            keyG = false;
            break;
        case 'v':
            keyV = false;
            break;
        case 'o':
            keyO = false;
            break;
        case 'l':
            keyL = false;
            break;
        case 'p':
            keyP = false;
            break;
        case 'i':
            keyI = false;
            break;
        case '0':
            key0 = false;
            break;
        case '1':
            key1 = false;
            break;
        case '2':
            key2 = false;
            break;
        case '3':
            key3 = false;
            break;
        case '4':
            key4 = false;
            break;
        case '5':
            key5 = false;
            break;
        default:
            return;
    }
}

void update()
{
  double robotXPosInc = 0.00;
  double robotZPosInc = 0.00;
  double joint0inc = 0.00;
  double joint1inc = 0.00;
  double joint2inc = 0.00;
  double joint3inc = 0.00;
  double gripperRollinc = 0.00;
  double gripperDistinc = 0.00;

  // Base Adjust 
  if (keyA)
    joint0inc = -5.00 * SPEED;
  if (keyD)
    joint0inc = 5.00 * SPEED;

  // Joint 1 Adjust
  if (keyW)
    joint1inc = 2.00 * SPEED;
  if (keyS)
    joint1inc = -2.00 * SPEED;

  // Joint 2 Adjust
  if (keyY)
    joint2inc = 5.00 * SPEED;
  if (keyH)
    joint2inc = -5.00 * SPEED;

  // Gripper Adjust
  if (keyUp)
    joint3inc = 5.00 * SPEED;
  if (keyDown)
    joint3inc = -5.00 * SPEED;
  if (keyRight)
    gripperRollinc = -5.00 * SPEED;
  if (keyLeft)
    gripperRollinc = 5.00 * SPEED;

  runnerVelHeading = joint3inc;
  
  // Gripper Adjust
  if (keyJ)
    gripperDistinc = -0.01 * SPEED;
  if (keyK)
    gripperDistinc = 0.01 * SPEED;
  // Grab runner robot
  if (!gripperClosed && fabsf(runnerPosX-endEffectorPosition.x)<0.1 && fabsf(runnerPosY-endEffectorPosition.y)<0.1 && fabsf(runnerPosZ-endEffectorPosition.z)<0.1) {
      gripperDistinc = -0.01;
  }

  if (key1) {
    viewMode = 1;
  } else if (key2) {
    viewMode = 2;
  }

  if (robotCaptured) {
    chaserYawAngle += chaserSpeed*0.5*gripperRollinc;
    double chaserYawRad = chaserYawAngle * PI / 180;
    chaserPosZ -= chaserSpeed*0.1*joint3inc*cos(chaserYawRad);
    chaserPosX -= chaserSpeed*0.1*joint3inc*sin(chaserYawRad);

    if (joint1Angle <= 90.0) {
      joint1Angle += 1.0;
    }
  }
  else {
    runnerYawAngle += runnerSpeed*0.5*gripperRollinc;
    double angleYradians = runnerYawAngle * PI / 180;

    runnerPosZ += runnerSpeed*0.1*joint3inc*cos(angleYradians);
    runnerPosX += runnerSpeed*0.1*joint3inc*sin(angleYradians);

    // Move chaser
    chaserPosX -= chaserSpeed*0.02*(endEffectorPosition.x-runnerPosX);
    chaserPosZ -= chaserSpeed*0.02*(endEffectorPosition.z-runnerPosZ);
  }

  // TODO: FIX THE LIGHTING
  light1_X = runnerPosX;
  light1_Y = runnerPosY;
  light1_Z = runnerPosZ;
  light1Rotation = runnerYawAngle;

  light2_X = runnerPosX;
  light2_Y = runnerPosY;
  light2_Z = runnerPosZ;
  light2Rotation = runnerYawAngle + 45.0;

  light3_X = runnerPosX;
  light3_Y = runnerPosY;
  light3_Z = runnerPosZ;
  light3Rotation = runnerYawAngle - 45.0;

  // light1_X -= 0.005*(light1_X-runnerPosX);
  // light1_Y = runnerPosY + 0.1;
  // light1_Z -= 0.005*(light1_Z-runnerPosZ);
  // light1Rotation = runnerYawAngle;

  // light2_X -= 0.005*(light2_X-runnerPosX) + 0.2;
  // light2_Y = runnerPosY + 0.4;
  // light2_Z -= 0.005*(light2_Z-runnerPosZ) + 0.2;
  // light2Rotation = runnerYawAngle;

  // light3_X -= 0.005*(light3_X-runnerPosX) - 0.2;
  // light3_Y = runnerPosY + 0.2;
  // light3_Z -= 0.005*(light3_Z-runnerPosZ) + 0.2;
  // light3Rotation = runnerYawAngle;

  if (viewMode == 1) {
    // Compute the camera position using spherical coordinates.

    angleY += 0.5*gripperRollinc;
    // double angleYradians = angleY * (M_PI / 180.0); // M_PI is a constant for π provided in <cmath>
    // firstPersonCamZPrev = firstPersonCamZ;
    // firstPersonCamZ -= 0.01*joint3inc * cos(angleYradians);
    // firstPersonCamX -= 0.01*joint3inc * sin(angleYradians);

    firstPersonCamZ = runnerPosZ;// - 20.0/2.0;
    firstPersonCamX = runnerPosX;
  }
  
  // Adjust joint angles
  double yaw = getYawOffset(chaserYawAngle, chaserPosX, chaserPosZ, runnerPosX, runnerPosY, runnerPosZ) * 180 / PI;
  //printf("roll: %f, joint0Angle: %f\n", roll, joint0Angle);
  chaserYawAngle += joint0inc - chaserSpeed*0.1*yaw; 
  //joint0Angle += joint0inc - chaserSpeed*0.1*yaw;
  joint1Angle += joint1inc + chaserSpeed*(runnerPosY - endEffectorPosition.y);// 0.1*pitch;
  joint2Angle += joint2inc;

  // leftHipAngle  +=  leftHipSign*50.0*(0.02*joint0inc+fabsf(robotXPosInc)+fabsf(robotZPosInc));
  // rightHipAngle +=  rightHipSign*50.0*(0.02*joint0inc+fabsf(robotXPosInc)+fabsf(robotZPosInc));

  // if (fabsf(leftHipAngle) > 60.0) {
  //   leftHipSign = -1*leftHipSign;
  // }
  // if (fabsf(rightHipAngle) > 60.0) {
  //   rightHipSign = -1*rightHipSign;
  // }

  if (joint1Angle >= 250.00) {
    joint1Angle = 250.00;
  } else if (joint1Angle <= -70.00) {
    joint1Angle = -70.00;
  }

  if (joint2Angle >= 90.00) {
    joint2Angle = 90.00;
  } else if (joint2Angle <= -90.00) {
    joint2Angle = -90.00;
  }

  joint3Angle += joint3inc;
  gripperDist += gripperDistinc;
  gripperRollAngle += gripperRollinc;

  if (joint3Angle > 90.00) {
    joint3Angle -= joint3inc;
  } else if (joint3Angle < -90.00) {
    joint3Angle -= joint3inc;
  }

  if (gripperDist >= 0.30) {
    gripperDist -= gripperDistinc;
  } else if (gripperDist <= 0.10) {
    gripperDist -= gripperDistinc;
  }
    
  if (gripperDist <= 0.20){
    gripperClosed = true;
  }
  else {
    gripperClosed = false;
  }
} 

void updateTimeCrunch()
{
  double robotXPosInc = 0.00;
  double robotZPosInc = 0.00;
  double joint0inc = 0.00;
  double joint1inc = 0.00;
  double joint2inc = 0.00;
  double joint3inc = 0.00;
  double gripperRollinc = 0.00;
  double gripperDistinc = 0.00;

  // Base Adjust 
  if (keyA)
    joint0inc = -5.00 * SPEED;
  if (keyD)
    joint0inc = 5.00 * SPEED;

  // Joint 1 Adjust
  if (keyW)
    joint1inc = 2.00 * SPEED;
  if (keyS)
    joint1inc = -2.00 * SPEED;

  // Joint 2 Adjust
  if (keyY)
    joint2inc = 5.00 * SPEED;
  if (keyH)
    joint2inc = -5.00 * SPEED;

  // Gripper Adjust
  if (keyUp)
    joint3inc = 5.00 * SPEED;
  if (keyDown)
    joint3inc = -5.00 * SPEED;
  if (keyRight)
    gripperRollinc = -5.00 * SPEED;
  if (keyLeft)
    gripperRollinc = 5.00 * SPEED;
  
  // Gripper Adjust
  if (keyJ)
    gripperDistinc = -0.01 * SPEED;
  if (keyK)
    gripperDistinc = 0.01 * SPEED;

  // // Grab runner robot
  // if (!gripperClosed && fabsf(runnerPosX-endEffectorPosition.x)<0.1 && fabsf(runnerPosY-endEffectorPosition.y)<0.1 && fabsf(runnerPosZ-endEffectorPosition.z)<0.1) {
  //     gripperDistinc = -0.01;
  // }

  if (key1) {
    viewMode = 1;
  } else if (key2) {
    viewMode = 2;
  }

  // Move chaser
  chaserYawAngle += chaserSpeed*0.5*gripperRollinc;
  double angleYradians = chaserYawAngle * PI / 180;

  chaserPosZ -= chaserSpeed*0.1*joint3inc*cos(angleYradians);
  chaserPosX -= chaserSpeed*0.1*joint3inc*sin(angleYradians);

  // TODO: FIX THE LIGHTING
  light1_X = chaserPosX;
  light1_Y = chaserPosY;
  light1_Z = chaserPosZ;
  light1Rotation = chaserYawAngle + 180;

  light2_X = chaserPosX;
  light2_Y = chaserPosY;
  light2_Z = chaserPosZ;
  light2Rotation = chaserYawAngle + 45.0 + 180;

  light3_X = chaserPosX;
  light3_Y = chaserPosY;
  light3_Z = chaserPosZ;
  light3Rotation = chaserYawAngle - 45.0 + 180;

  if (viewMode == 1) {
    // Compute the camera position using spherical coordinates.
    angleY += 0.5*gripperRollinc;
    firstPersonCamZ = chaserPosZ;// - 20.0/2.0;
    firstPersonCamX = chaserPosX;
  }
  
  // Adjust joint angles
  //double yaw = getYawOffset(joint0Angle, chaserPosX, chaserPosZ, nearestObj->posX, nearestObj->posY, nearestObj->posZ) * 180 / PI;
  //joint0Angle += runnerSpeed*0.5*gripperRollinc* PI / 180;;
  
  joint1Angle += 5.0*(nearestMapItem->position.y - endEffectorPosition.y);
  double diffX = nearestMapItem->position.x - endEffectorPosition.x;
  double diffY = nearestMapItem->position.y - endEffectorPosition.y;
  double diffZ = nearestMapItem->position.z - endEffectorPosition.z;
  // printf("nearestObjX: %f, endEffX: %f, diffX: %f\n\n", nearestObj->posX, endEffectorPosition.x, diffX);
  // printf("nearestObjY: %f, endEffY: %f, diffY: %f\n\n", nearestObj->posY, endEffectorPosition.y, diffY);
  // printf("nearestObjZ: %f, endEffY: %f, diffZ: %f\n\n", nearestObj->posZ, endEffectorPosition.z, diffZ);
  // printf("diffX: %f, diffY: %f, diffZ: %f\n\n", diffX, diffY, diffZ);

  joint2Angle += joint2inc;

  if (joint1Angle >= 90.00) {
    joint1Angle = 90.00;
  } else if (joint1Angle <= -70.00) {
    joint1Angle = -70.00;
  }

  if (joint2Angle >= 90.00) {
    joint2Angle = 90.00;
  } else if (joint2Angle <= -90.00) {
    joint2Angle = -90.00;
  }

  //joint3Angle += joint3inc;
  gripperDist += gripperDistinc;
  gripperRollAngle += gripperRollinc;

  if (joint3Angle > 90.00) {
    joint3Angle -= joint3inc;
  } else if (joint3Angle < -90.00) {
    joint3Angle -= joint3inc;
  }

  if (gripperDist >= 0.30) {
    gripperDist -= gripperDistinc;
  } else if (gripperDist <= 0.10) {
    gripperDist -= gripperDistinc;
  }
    
  if (gripperDist <= 0.20){
    gripperClosed = true;
  }
  else {
    gripperClosed = false;
  }
} 

#endif // KEY_HANDLER_H
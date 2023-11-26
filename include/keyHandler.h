#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

double joint3inc = 0.00;

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

// Light control
// TODO: REMOVE ca[ability
bool keyT = false;  // UNUSED
bool keyF = false;  // UNUSED
bool keyG = false;  // UNUSED
bool keyV = false;  // UNUSED

// Robot position
bool keyO = false;  // Robot +Z
bool keyL = false;  // Robot -Z
bool keyP = false;  // Robot +X
bool keyI = false;  // Robot -X;

bool key0 = false;
bool key1 = false;
bool key2 = false;
bool key3 = false;
bool key4 = false;  // UNUSED
bool key5 = false;  // UNUSED

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
  joint3inc = 0.00;
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

  if (key1) {
    viewMode = 1;
  } else if (key2) {
    viewMode = 2;
  } else if (key3) {
    viewMode = 3;
  }

  // Light Adjust
  if (keyO)
    robotZPosInc = 0.2 * SPEED;
  if (keyL)
    robotZPosInc -= 0.2 * SPEED;
  if (keyP)
    robotXPosInc = 0.2 * SPEED;
  if (keyI)
    robotXPosInc -= 0.2 * SPEED;

  if (!ballInHandBool) {
    robotXPos += robotXPosInc - monsterRobotSpeed*0.02*(endEffectorPosition.x-runnerPosX);
    robotZPos += robotZPosInc - monsterRobotSpeed*0.02*(endEffectorPosition.z-runnerPosZ);
  }
  else if (ballInHandBool){
    //joint0Angle += monsterRobotSpeed*0.5*gripperRollinc;
    //joint1Angle = 90.0;
    //double angleYradians = joint0Angle * PI / 180;

    //robotZPos += monsterRobotSpeed*0.1*joint3inc*cos(angleYradians);
    //robotXPos += monsterRobotSpeed*0.1*joint3inc*sin(angleYradians);
  }

  light1_X -= 0.005*(light1_X-runnerPosX);
  light1_Y = runnerPosY + 2;
  light1_Z -= 0.005*(light1_Z-runnerPosZ);
  lightRotation = runnerYawAngle;

  // // Light Adjust
  // if (keyT)
  //   light1_Y += 0.2 * SPEED;
  // if (keyV)
  //   light1_Y -= 0.2 * SPEED;
  // if (keyG)
  //   light1_X += 0.2 * SPEED;
  // if (keyF)
  //   light1_X -= 0.2 * SPEED;

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
  double yaw = getYawOffset(joint0Angle, robotXPos, robotZPos, runnerPosX, runnerPosY, runnerPosZ) * 180 / PI;
  double pitch = getPitchOffset(joint0Angle, robotXPos, robotZPos, runnerPosX, runnerPosY, runnerPosZ) * 180 / PI;
  //printf("roll: %f, joint0Angle: %f\n", roll, joint0Angle);
  joint0Angle += joint0inc - monsterRobotSpeed*0.1*yaw;
  joint1Angle += joint1inc + monsterRobotSpeed*(runnerPosY - endEffectorPosition.y);// 0.1*pitch;
  joint2Angle += joint2inc;

  leftHipAngle  +=  leftHipSign*50.0*(0.02*joint0inc+fabsf(robotXPosInc)+fabsf(robotZPosInc));
  rightHipAngle +=  rightHipSign*50.0*(0.02*joint0inc+fabsf(robotXPosInc)+fabsf(robotZPosInc));

  if (fabsf(leftHipAngle) > 60.0) {
    leftHipSign = -1*leftHipSign;
  }
  if (fabsf(rightHipAngle) > 60.0) {
    rightHipSign = -1*rightHipSign;
  }

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

  // Gripper Adjust
  if (!gripperClosed && fabsf(runnerPosX-endEffectorPosition.x)<0.1 && fabsf(runnerPosY-endEffectorPosition.y)<0.1 && fabsf(runnerPosZ-endEffectorPosition.z)<0.1) {
      gripperDistinc = -0.01;
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
    //posX -= 0.050*gripperRollinc;
    //posX -= 0.050*joint3inc;

    // Just for testing to move the robot
    runnerYawAngle += runnerSpeed*0.5*gripperRollinc;
    double angleYradians = runnerYawAngle * PI / 180;

    runnerPosZ += runnerSpeed*0.1*joint3inc*cos(angleYradians);
    runnerPosX += runnerSpeed*0.1*joint3inc*sin(angleYradians);
  }
} 

#endif // KEY_HANDLER_H
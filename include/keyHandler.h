#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

bool keySpace = false;  // space bar key - jump robot controlled by user
bool keySpacePrev = false;

bool keyRight = false;
bool keyLeft = false;
bool keyUp = false;
bool keyDown = false;

bool keyW = false;  // UNUSED
bool keyS = false;  // UNUSED
bool keyA = false;  // UNUSED
bool keyD = false;  // UNUSED
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
      case 32: // ASCII value for space bar
          keySpace = true;
          break;
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
            lightsEnabled = lightKeyPressed; // Update lightEnabled accordingly
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
        case 32: // ASCII value for space bar
          keySpace = false;
          break;
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

void updateRunner()
{
  double robotXPosInc = 0.00;
  double robotZPosInc = 0.00;
  // double joint0inc = 0.00;
  // double joint1inc = 0.00;
  double joint2inc = 0.00;
  double joint3inc = 0.00;
  double gripperRollinc = 0.00;
  double gripperDistinc = 0.00;

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
  
  runnerSpeed = runnerSpeedAdjust*joint3inc;

  // Gripper Adjust
  if (keyJ)
    gripperDistinc = -0.01 * SPEED;
  if (keyK)
    gripperDistinc = 0.01 * SPEED;
  // Grab runner robot
  if (!chaserRobot.gripperClosed && fabsf(runnerPosX-chaserRobot.endEffectorPosition.x)<0.1 && fabsf(runnerPosY-chaserRobot.endEffectorPosition.y)<0.1 && fabsf(runnerPosZ-chaserRobot.endEffectorPosition.z)<0.1) {
      gripperDistinc = -0.01;
  }

  if (key1) {
    viewMode = 1;
  } else if (key2) {
    viewMode = 2;
  }

  // Runner Control
  if (!runnerInCollision) {
    prevRunnerPosZ = runnerPosZ;
    prevRunnerPosX = runnerPosX;
  }
  
  if (keySpace && !keySpacePrev) {
    externalForceY = 20000;
  }
  else {
    externalForceY = 0;
  }
  keySpacePrev = keySpace;

  // Chaser Control
  if (!chaserInCollision) {
    chaserRobot.prevPos.z = chaserRobot.position.z;
    chaserRobot.prevPos.x = chaserRobot.position.x;
  }

  if (robotCaptured) {
    chaserRobot.yawAngle += 0.5*gripperRollinc;
    double chaserYawRad = chaserRobot.yawAngle * PI / 180;
    chaserRobot.position.z -= 0.1*joint3inc*cos(chaserYawRad);
    chaserRobot.position.x -= 0.1*joint3inc*sin(chaserYawRad);

    if (chaserRobot.joint1Angle <= 90.0) {
      chaserRobot.joint1Angle += 1.0;
    }
    else {
      robotTaken = true;
    }
  }
  else {
    runnerYawAngle += gripperRollinc;
    double angleYradians = runnerYawAngle * PI / 180;

    runnerPosZ += runnerSpeed*cos(angleYradians);
    runnerPosX += runnerSpeed*sin(angleYradians);

    // Move chaser
    chaserRobot.position.x -= chaserRobot.speedAdjust*0.02*(chaserRobot.endEffectorPosition.x-runnerPosX)*chaserRobot.speedAdjust;
    chaserRobot.position.z -= chaserRobot.speedAdjust*0.02*(chaserRobot.endEffectorPosition.z-runnerPosZ)*chaserRobot.speedAdjust;
    chaserRobot.speed = chaserRobot.speedAdjust*sqrt((chaserRobot.endEffectorPosition.x-runnerPosX)*(chaserRobot.endEffectorPosition.x-runnerPosX) + (chaserRobot.endEffectorPosition.z-runnerPosZ)*(chaserRobot.endEffectorPosition.z-runnerPosZ))*chaserRobot.speedAdjust;
  }

  if (runnerInCollision) {
    runnerPosZ = prevRunnerPosZ;
    runnerPosX = prevRunnerPosX;
  }
  // Chaser Control
  if (chaserInCollision) {
    chaserRobot.position.z = chaserRobot.prevPos.z;
    chaserRobot.position.x = chaserRobot.prevPos.x;
  }

  // THE LIGHTING
  double orbitRadius = 4.0;
  light1Rotation = lightrot + runnerYawAngle + 45.0;
  light1_X = -orbitRadius * sin(light1Rotation * PI / 180) + runnerPosX;
  light1_Y = runnerPosY;
  light1_Z = -orbitRadius * cos(light1Rotation * PI / 180) + runnerPosZ;

  light2Rotation = lightrot + runnerYawAngle - 45.0;
  light2_X = -orbitRadius * sin(light2Rotation * PI / 180) + runnerPosX;
  light2_Y = runnerPosY;
  light2_Z = -orbitRadius * cos(light2Rotation * PI / 180) + runnerPosZ;
  lightrot += 0.5;

  // Camera Position & Orientation
  // View Zoom Adjust
  if (keyO)
    fpCamZoom *= 0.99;
  if (keyL)
    fpCamZoom *= 1.1;


  if (viewMode == 1) {
    orbitCamAngleY = runnerYawAngle + 180;
    orbitCamZ = runnerPosZ;
    orbitCamX = runnerPosX;
  }
  
  double poseDiff = 0.5*sqrt((runnerPosX-chaserRobot.position.x)*(runnerPosX-chaserRobot.position.x) + (runnerPosZ-chaserRobot.position.z)*(runnerPosZ-chaserRobot.position.z));
  overheadCamX = -runnerPosX + (runnerPosX-chaserRobot.position.x)/2.0;
  overheadCamY = -1 - poseDiff;
  overheadCamZ = -runnerPosZ + (runnerPosZ-chaserRobot.position.z)/2.0;

  // Adjust joint angles
  double yaw = getYawOffset(chaserRobot.yawAngle, chaserRobot.position.x, chaserRobot.position.z, runnerPosX, runnerPosY, runnerPosZ) * 180 / PI;
  chaserRobot.yawAngle  -= chaserRobot.speedAdjust*0.1*yaw; 
  chaserRobot.joint1Angle     += (runnerPosY -chaserRobot.endEffectorPosition.y);
  computeForwardKinematics(); // call to get new endeffector pos
  chaserRobot.joint2Angle     += (runnerPosY -chaserRobot.endEffectorPosition.y); // joint2inc;

  runnerViewableSpeed = abs(runnerSpeed) + abs(gripperRollinc);
  chaserRobot.viewableSpeed = abs(chaserRobot.speed) + abs(0.1*yaw);

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

  chaserRobot.joint3Angle += joint3inc;
  chaserRobot.gripperDist += gripperDistinc;
  chaserRobot.gripperRollAngle += gripperRollinc;

  if (chaserRobot.joint3Angle > 90.00) {
    chaserRobot.joint3Angle -= joint3inc;
  } else if (chaserRobot.joint3Angle < -90.00) {
    chaserRobot.joint3Angle -= joint3inc;
  }

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
  double robotXPosInc = 0.00;
  double robotZPosInc = 0.00;
  // double joint0inc = 0.00;
  // double joint1inc = 0.00;
  double joint2inc = 0.00;
  double joint3inc = 0.00;
  double gripperRollinc = 0.00;
  double gripperDistinc = 0.00;

  // Joint 2 Adjust
  if (keyY)
    joint2inc = 5.00 * SPEED;
  if (keyH)
    joint2inc = -5.00 * SPEED;

  // ROBOT POS ADJUST
  if (keyUp)
    joint3inc = 5.00 * SPEED;
  if (keyDown)
    joint3inc = -5.00 * SPEED;
  if (keyRight)
    gripperRollinc = -10.00 * SPEED;
  if (keyLeft)
    gripperRollinc = 10.00 * SPEED;
  
  // Gripper Adjust
  if (keyJ)
    gripperDistinc = -0.01 * SPEED;
  if (keyK)
    gripperDistinc = 0.01 * SPEED;

  // View Zoom Adjust
  if (keyO)
    fpCamZoom *= 0.99;
  if (keyL)
    fpCamZoom *= 1.1;

  if (key1) {
    viewMode = 1;
  } else if (key2) {
    viewMode = 2;
  }

  if (keySpace && !keySpacePrev) {
    externalForceY = 20000;
  }
  else {
    externalForceY = 0;
  }
  keySpacePrev = keySpace;

  // Move chaser
  chaserRobot.speed = 4.0*joint3inc*chaserRobot.speedAdjust;
  chaserRobot.yawAngle += gripperRollinc;
  double angleYradians = chaserRobot.yawAngle * PI / 180;
  if (chaserInCollision) {
    chaserRobot.position.z = chaserRobot.prevPos.z;
    chaserRobot.position.x = chaserRobot.prevPos.x;
  }
  else {
    chaserRobot.prevPos.z = chaserRobot.position.z;
    chaserRobot.prevPos.x = chaserRobot.position.x;
    chaserRobot.position.z -= chaserRobot.speed*0.1*cos(angleYradians);
    chaserRobot.position.x -= chaserRobot.speed*0.1*sin(angleYradians);
  }

  chaserRobot.viewableSpeed = abs(chaserRobot.speed) + abs(gripperRollinc);

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
    orbitCamAngleY += 0.5*gripperRollinc;
    orbitCamY = 0.0;
    orbitCamZ = chaserRobot.position.z;
    orbitCamX = chaserRobot.position.x;
  }

  overheadCamX = -chaserRobot.position.x;
  overheadCamY = -1;
  overheadCamZ = -chaserRobot.position.z;
  
  // ROBOT POSE
  chaserRobot.joint1Angle += 5.0*(nearestMapItem->position.y -chaserRobot.endEffectorPosition.y);
  computeForwardKinematics(); // call to get new endeffector pos
  chaserRobot.joint2Angle += 5.0*(nearestMapItem->position.y -chaserRobot.endEffectorPosition.y); // joint2inc;

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

  //chaserRobot.joint3Angle += joint3inc;
  chaserRobot.gripperDist += gripperDistinc;
  chaserRobot.gripperRollAngle += gripperRollinc;

  if (chaserRobot.joint3Angle > 90.00) {
    chaserRobot.joint3Angle -= joint3inc;
  } else if (chaserRobot.joint3Angle < -90.00) {
    chaserRobot.joint3Angle -= joint3inc;
  }

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
  double robotXPosInc = 0.00;
  double robotZPosInc = 0.00;
  // double joint0inc = 0.00;
  // double joint1inc = 0.00;
  double joint2inc = 0.00;
  double joint3inc = 0.00;
  double gripperRollinc = 0.00;
  double gripperDistinc = 0.00;

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
  // Grab runner robot
  if (!chaserRobot.gripperClosed && fabsf(runnerPosX-chaserRobot.endEffectorPosition.x)<0.1 && fabsf(runnerPosY-chaserRobot.endEffectorPosition.y)<0.1 && fabsf(runnerPosZ-chaserRobot.endEffectorPosition.z)<0.1) {
      gripperDistinc = -0.01;
  }

  // lighting Distance Adjust
  if (keyO)
    lightingDist *= 0.99;
  if (keyL)
    lightingDist *= 1.1;

  // View Zoom Adjust
  if (keyO)
    fpCamZoom *= 0.99;
  if (keyL)
    fpCamZoom *= 1.1;

  if (key1) {
    viewMode = 1;
  } else if (key2) {
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

  chaserRobot.joint3Angle += joint3inc;
  chaserRobot.gripperDist += gripperDistinc;
  chaserRobot.gripperRollAngle += gripperRollinc;

  if (chaserRobot.joint3Angle > 90.00) {
    chaserRobot.joint3Angle -= joint3inc;
  } else if (chaserRobot.joint3Angle < -90.00) {
    chaserRobot.joint3Angle -= joint3inc;
  }

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

#endif // KEY_HANDLER_H
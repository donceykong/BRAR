// Created by: Doncey Albin

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

bool key1 = false;
bool key2 = false;
bool key3 = false;

bool key4 = false;             // Toggle Texture on/off
bool key5 = false;             // Switch texture Bitmap

bool key0 = false;
bool lightKeyPressed = false;  // Keep track of whether '0' key is pressed

bool keyT = false;
bool keyF = false;
bool keyG = false;
bool keyV = false;

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
            usingTextures = !usingTextures;
            key4 = true;
            break;
        case '5':
            switchBMPImage();
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
  int joint0inc = 0;
  int joint1inc = 0;
  int joint2inc = 0;
  int joint3inc = 0;
  double gripperRollinc = 0.00;
  double gripperDistinc = 0.00;

  // Base Adjust 
  if (keyA)
    joint0inc = -5;
  if (keyD)
    joint0inc = 5;

  // Joint 1 Adjust
  if (keyW)
    joint1inc = 2;
  if (keyS)
    joint1inc = -2;

  // Joint 2 Adjust
  if (keyY)
    joint2inc = 5;
  if (keyH)
    joint2inc = -5;

  // Gripper Adjust
  if (keyUp)
    joint3inc = 5;
  if (keyDown)
    joint3inc = -5;
  if (keyRight)
    gripperRollinc = -5;
  if (keyLeft)
    gripperRollinc = 5;

  // Gripper Adjust
  if (keyJ)
    gripperDistinc = -0.01;
  if (keyK)
    gripperDistinc = 0.01;

  if (key1) {
    viewMode = 1;
  } else if (key2) {
    viewMode = 2;
  } else if (key3) {
    viewMode = 3;
  }

  // Light Adjust
  if (keyT)
    light1_Y += 0.2;
  if (keyV)
    light1_Y -= 0.2;
  if (keyG)
    light1_X += 0.2;
  if (keyF)
    light1_X -= 0.2;
  
  lightRotation += rotationSpeed;

  if (viewMode == 3) {
    // Compute the camera position using spherical coordinates.
    angleY += 0.5*gripperRollinc;

    if (angleY > 180) {
      angleY = 180;
    }
    else if (angleY < -180) {
      angleY = -180;  
    }

    double angleYradians = angleY * (M_PI / 180.0); // M_PI is a constant for π provided in <cmath>

    firstPersonCamZPrev = firstPersonCamZ;
    firstPersonCamZ -= 0.01*joint3inc * (firstPersonCamZ*cos(angleYradians) - firstPersonCamX*sin(angleYradians)); //joint3inc; //distance * cosf(angleY);
    firstPersonCamX -= 0.01*joint3inc * (firstPersonCamZPrev*sin(angleYradians) + firstPersonCamX*cos(angleYradians)); //distance * sinf(angleY) * cosf(angleX);
    
    float xpos = firstPersonCamX;
    float zpos = firstPersonCamZ;
    
    //plotData(xpos, zpos); // Save robot pos data to png file

    //printf("AngleY: %.6f\n", angleY);
    //printf("firstPersonCamX: %.6f, firstPersonCamZ: %.6f\n", firstPersonCamX, firstPersonCamZ);
  }
  
  // Adjust joint angles
  joint0Angle += joint0inc;
  joint1Angle += joint1inc;
  joint2Angle += joint2inc;

  // Gripper Adjust
  joint3Angle += joint3inc;
  gripperDist += gripperDistinc;
  gripperRollAngle += gripperRollinc;

  if (gripperDist > 0.3) {
    gripperDist = 0.3;
  } else if (gripperDist < 0.1) {
    gripperDist = 0.1;
  }

  // Request Display update
  glutPostRedisplay();
} 
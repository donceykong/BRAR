#ifndef ROBOT_LEGS_H
#define ROBOT_LEGS_H

enum legType {
    LEFT_LEG,   // 0
    RIGHT_LEG   // 1
};

typedef struct {
  enum legType type;

  double thighBendAngle;
  double thighSign;

  double kneeBendAngle;  // Init right knee angle
  double kneeSign;

  double ankleBendAngle;   // Init right ankle angle
  double ankleSign;
} legStruct;

// Joint to Joint length is 0.66
void robotThigh(double percentFull, double thickness, double faceC[3], bool topLayer) {
    glPushMatrix();

    GLuint BMPtexturePrev = BMPtexture;
    BMPtexture = BMPtexture3;
    // Draw motor shaft
    if (!topLayer) {
      glTranslatef(0.0, 0.0, -(0.5*thickness+0.75*thickness));      // Move out 0.5 len thigh and shaft thickness
      glColor3f(1.0, 1.0, 1.0);                                     // face color
      drawSemiCylinder(0.1, 1.5*thickness, 1000, 1.0);              // Draw motor cylindrical shaft
      glTranslatef(0.0, 0.0, (0.5*thickness+0.75*thickness));       // Move back to thigh
    }
    BMPtexture = BMPtexturePrev;

    // face colors
    glColor3f(faceC[0], faceC[1], faceC[2]);                        // face color
    drawSemiCylinder(0.2*percentFull, thickness, 1000, 0.5);        // Draw top semi cylinder

    glTranslatef(0.0, -0.05, 0.0);                                  // Move cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);                        // face color
    getCuboid(0.4*percentFull, 0.1, thickness);                       // Draw cube

    glTranslatef(0.0, -0.1, 0.0);                                   // Translate to bring parallelogram top down
    glColor3f(faceC[0], faceC[1], faceC[2]);                        // face color
    getParallelogram(0.4*percentFull, 0.1, thickness);              // Draw parallelogram

    glTranslatef(0.0, -0.25, 0.0);                                  // Move cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);                        // face color
    getCuboid(0.2*percentFull, 0.4, thickness);                       // Draw cube
    glTranslatef(0.0, -0.2, 0.0);                                   // To get to end of cube

    if (!topLayer) {
        glTranslatef(0.0, -0.06, thickness/4);      // To get to end cylinder center
        glColor3f(faceC[0], faceC[1], faceC[2]);    // face color
        drawSemiCylinder(0.12*percentFull, thickness/2, 1000, 1.0);      // Draw semi-cylinder
        glTranslatef(0.0, 0.0, -thickness/4);      // To get to end cylinder center
    }
    else {
        glTranslatef(0.0, -0.06, 0.0);      // To get to end cylinder center
        glColor3f(faceC[0], faceC[1], faceC[2]);    // face color
        drawSemiCylinder(0.12*percentFull, thickness, 1000, 1.0);      // Draw semi-cylinder      
    }

    glPopMatrix();
}

// Joint to Joint length is 1.00
void robotShin(double percentFull, double thickness, double faceC[3], bool topLayer) {
    glPushMatrix();
    glTranslatef(0.0, 0.0, -thickness/4);             // To shift to 3/4 of thickness
    if (!topLayer) {
        glColor3f(faceC[0], faceC[1], faceC[2]);                        // Green face color
        drawSemiCylinder(0.12*percentFull, thickness/2, 1000, 1.0);     // Draw Semi-cylinder
        // end of cylinder
    }

    glTranslatef(0.0, -0.1, 0.0);               // Translate to bring cube top down
    if (!topLayer) {
        glColor3f(faceC[0], faceC[1], faceC[2]);    // Green face color
        getCuboid(0.2*percentFull, 0.15, thickness/2);   // Draw Cube
    }
    glTranslatef(0.0, -0.15/2, 0.0);               // To get to end of cube
    glTranslatef(0.0, 0.0, thickness/4);              // To shift back from 3/4 of thickness
    
    glTranslatef(0.0, -0.15, 0.0);               // Translate to bring cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);    // Green face color
    getCuboid(0.2*percentFull, 0.3, thickness);   // Draw Cube
    glTranslatef(0.0, -0.15, 0.0);               // To get to end of cube
    
    glTranslatef(0.0, -0.05, 0.0);              // Translate to bring parallelogram top down
    glColor3f(faceC[0], faceC[1], faceC[2]);    // Green face color
    getParallelogram(0.2*percentFull, 0.1, thickness);            // Draw parallelogram
    glTranslatef(0.0, -0.05, 0.0);              // To get to end of parallelogram
    
    glTranslatef(0.0, -0.2, 0.0);               // Translate to bring cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);    // Green face color
    getCuboid(0.1*percentFull, 0.4, thickness);                     // Draw Cube
    glTranslatef(0.0, -0.2, 0.0);               // To get to end of cube

    //0.1 + 0.075 + 0.3 + 0.1 + 0.4  = 0.975 -> length so far
    glTranslatef(0.0, -(1.0-0.975), 0.0);               // Translate to bring cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);            // Green face color
    drawSemiCylinder(0.075*percentFull, thickness/2, 1000, 1.0);     // Draw Semi-cylinder
    glTranslatef(0.0, -0.0, 0.0);               // To get to end of cube

    glPopMatrix();
}

// Joint to Joint length is 
void robotFoot() {
    BMPtexture = BMPtexture2;
    glPushMatrix();
    
    int faceC[3] = {1.0, 1.0, 1.0};                 // face color

    // Ankle of foot
    glColor3f(faceC[0], faceC[1], faceC[2]);            // Green face color
    drawSemiCylinder(0.075, 0.05, 1000, 1.0);     // Draw Semi-cylinder

    // Front of foot
    glRotatef(-20.0, 0.0, 0.0, 1.0);                //
    glTranslatef(0.15, 0.0, 0.0);                   // Translate to bring cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getRightTriPrism(0.3, 0.15, 0.05);
    glTranslatef(0.0, -0.075, 0.0); 

    glTranslatef(0.0, -0.025, 0.125);               // Translate to bring cube top down
    glRotatef(90.0, 1.0, 0.0, 0.0);                 //
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getRightTriPrism(0.3, 0.15, 0.05);
    glRotatef(-90.0, 1.0, 0.0, 0.0);                //
    glTranslatef(0.0, 0.025,  -0.125); 

    glTranslatef(0.0, -0.025, -0.125);              // Translate to bring cube top down
    glRotatef(-90.0, 1.0, 0.0, 0.0);                //
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getRightTriPrism(0.3, 0.15, 0.05);              // 
    glRotatef(90.0, 1.0, 0.0, 0.0);                 //
    glTranslatef(0.0, 0.025,  0.125); 

    glTranslatef(0.15 - 0.1/2.0, -0.025, 0.0);      // Translate prism center to bottom of foot
    glRotatef(20.0, 0.0, 0.0, 1.0);                
    glRotatef(180.0, 0.0, 0.0, 1.0);                // 
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getParallelogram(0.2, 0.05, 0.2);               // Draw parallelogram
    glRotatef(180.0, 0.0, 0.0, 1.0); 
    glRotatef(-20.0, 0.0, 0.0, 1.0); 
    glTranslatef(-(0.15 - 0.1/2.0), 0.025, 0.0);    // Translate back

    // Translate back to ankle
    glTranslatef(-0.15, 0.075, 0.0); 
    glRotatef(20.0, 0.0, 0.0, 1.0);                 // 
    
    // Heel of foot
    glRotatef(180.0, 0.0, 1.0, 0.0);                //

    glRotatef(-6.66, 0.0, 0.0, 1.0);                //
    glTranslatef(0.225, 0.0, 0.0);                   // Translate to bring cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getRightTriPrism(0.45, 0.05, 0.05);
    glTranslatef(0.0, -0.05, 0.0); 

    glTranslatef(0.45/2.0 - 0.1/2.0, -0.0, 0.0);      // Translate prism center to bottom of foot
    glRotatef(20.0, 0.0, 0.0, 1.0);                
    glRotatef(180.0, 0.0, 0.0, 1.0);                // 
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getParallelogram(0.2, 0.05, 0.1);               // Draw parallelogram
    glRotatef(180.0, 0.0, 0.0, 1.0); 
    glRotatef(-20.0, 0.0, 0.0, 1.0); 
    glTranslatef(-(0.45/2.0 - 0.1/2.0), 0.0, 0.0);    // Translate back
    
    glPopMatrix();
}

void drawLeg(bool rightLeg, double runSpeed, legStruct *leg) {
  // Joint0: robotLeftLeg
  double totalThickness = 0.0;
  double prevThickness = 0.0;

  /*
   * * * * * * * * * * * ballInHandBool* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * Begin Thigh
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  if (leg->type == LEFT_LEG) {
    glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate thigh 180
  }
  
  BMPtexture = BMPtexture1;

  // Update thigh bend angle
  if (leg->thighBendAngle > 40.0) {
      leg->thighSign = -1.0;
  } else if (leg->thighBendAngle < -80.0) {
      leg->thighSign = 1.0;
  }
  leg->thighBendAngle += leg->thighSign * 0.9*runSpeed;
  
  if (leg->type == RIGHT_LEG) {
    glRotatef(leg->thighBendAngle, 0.0, 0.0, 1.0);
  }
  else {
    glRotatef(leg->thighBendAngle*-1.0, 0.0, 0.0, 1.0);
  }
  
  drawFrame(1.0);

  //double faceC[3] = {1.0, 165.0/255.0, 0.0};      // Orange face color
  double faceC[3] = {1.0, 1.0, 1.0};                // White face color
  double thickness = 0.2;                           //
  totalThickness = totalThickness + thickness/2;    //
  prevThickness = thickness;                        //
  robotThigh(1.0, thickness, faceC, false);         // Draw thigh

  BMPtexture = BMPtexture4;

  faceC[1] = 0.5;                                   // face color
  thickness = prevThickness*0.2;                    //
  totalThickness = totalThickness + thickness;      //
  glTranslatef(0.0, 0.0, (thickness+prevThickness)/2.0);    // Translate to face of thigh
  robotThigh(0.75, thickness, faceC, true);         // Draw thigh top layer
  prevThickness = thickness;

  faceC[0] = 0.5;                                   // face color
  thickness = prevThickness*0.2;                    //
  totalThickness = totalThickness + thickness/2;    //
  glTranslatef(0.0, 0.0,(thickness+prevThickness)/2.0);    // Translate to face of thigh
  robotThigh(0.4, thickness, faceC, true);          // Draw thigh top layer
  prevThickness = thickness;

  glTranslatef(0.0, 0.0, -totalThickness);          // Translate back to center of bottom thigh layer
  glTranslatef(0.0, -0.66, 0.0);                    // Translate to end of thigh

  /*
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * Begin shin
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  
  BMPtexture = BMPtexture1;
  totalThickness = 0.0;                             // reset total thickness

  //*kneeBendAngle += *kneeSign*1.8; // Knee angle
  double kneeBendAnglePrev = leg->kneeBendAngle;
  if (leg->thighBendAngle > 0.0) {
    leg->kneeBendAngle -= 1.8*runSpeed; // Knee angle
    leg->kneeSign = 1.0;
  }
  else if (leg->thighBendAngle < 0.0) {
    leg->kneeBendAngle += 1.8*0.5*runSpeed; // Knee angle
    leg->kneeSign = -1.0;
  }
  
  //if (rightLeg) {printf("kneeBendAngle: %f\n", *thighBendAngle);}
  //*kneeBendAngle += *kneeSign*0.45; // Knee angle
  if (leg->kneeBendAngle >= 135.0) {
    leg->kneeBendAngle = kneeBendAnglePrev;
  }
  else if (leg->kneeBendAngle <= 0.0) {
    leg->kneeBendAngle = kneeBendAnglePrev;
  }
  if (rightLeg) {
    glRotatef(leg->kneeBendAngle, 0.0, 0.0, 1.0);          // Rotate shin
  }
  else {
    glRotatef(-1*leg->kneeBendAngle, 0.0, 0.0, 1.0);          // Rotate shin
  }
  
  drawFrame(1.0);         
  
  double faceCShin[3] = {1.0, 1.0, 1.0};            // White face color
  thickness = 0.2;                                  //
  totalThickness = totalThickness + thickness/2;    //
  prevThickness = thickness;                        //
  robotShin(1.0, thickness, faceCShin, false);      // Draw shin

  BMPtexture = BMPtexture4;

  faceCShin[1] = 0.5;                               // Shin face color
  thickness = prevThickness*0.2;                    //
  totalThickness = totalThickness + thickness;      //
  glTranslatef(0.0, 0.0, (thickness+prevThickness)/2.0);    // Translate to face of thigh
  robotShin(0.75, thickness, faceCShin, true);      // Draw shin
  prevThickness = thickness;                        //

  faceCShin[0] = 0.5;                               // Shin face color
  thickness = prevThickness*0.2;                    //
  totalThickness = totalThickness + thickness/2;    //
  glTranslatef(0.0, 0.0, (thickness+prevThickness)/2.0);    // Translate to face of thigh
  robotShin(0.4, thickness, faceCShin, true);       // Draw shin
  prevThickness = thickness;                        //
  
  glTranslatef(0.0, -1.0, 0.0);                     // Translate to end of shin
  glTranslatef(0.0, 0.0, -totalThickness);          // Translate back to center of bottom thigh layer

  /*
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   * Begin foot
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  */
  if (!rightLeg) {
    glRotatef(180.0f, 0.0, 1.0, 0.0);  // Rotate shin 180
  }

  BMPtexture = BMPtexture1;

  //*ankleBendAngle += *ankleSign*1.80;  // ankle angle
  if (leg->ankleBendAngle > 0) {
    leg->ankleSign = -1.0;
  }
  else if (leg->ankleBendAngle < -90) {
    leg->ankleSign = 1.0;
  }
  //ankleBendAngle = 0;
  glRotatef(leg->ankleBendAngle, 0.0, 0.0, 1.0);        // Rotate foot
  drawFrame(1.0);  
  robotFoot();                                      // Draw foot
}

#endif // ROBOT_LEGS_H
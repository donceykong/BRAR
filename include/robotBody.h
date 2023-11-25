
void robotTorso(double percentFull, double thickness, double faceC[3], bool topLayer) {
    glPushMatrix();

    glTranslatef(0.0, -0.2, 0.0);     // Translate to bring cube top down
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getParallelogram(0.5*percentFull, 0.4, thickness);  // Draw paralellogram
    glTranslatef(0.0, 0.2, 0.0);    

    glTranslatef(0.0, 0.05, 0.0);
    glColor3f(faceC[0], faceC[1], faceC[2]); // face color  
    getCube(0.5*percentFull, 0.1, thickness);
    glTranslatef(0.0, 0.05, 0.0);     // top of cube

    glTranslatef(0.0, 0.05, 0.0);     // shift halfway of parallelogram
    glRotatef(180, 0.0, 0.0, 1.0);    // Rotate 180
    glColor3f(faceC[0], faceC[1], faceC[2]);        // face color
    getParallelogram(0.5*percentFull, 0.1, thickness);

    glPopMatrix();
}

void drawBody() {
    double totalThickness = 0.0;
    double prevThickness = 0.0;

    BMPtexture = BMPtexture5;                         // TODO: Change initial texture
    double faceC[3] = {1.0, 1.0, 1.0};                // White face color
    double thickness = 0.4;                           //
    totalThickness = totalThickness + thickness/2;    //
    prevThickness = thickness;                        //
    robotTorso(1.0, thickness, faceC, false);

    BMPtexture = BMPtexture4;                         // TODO: Change initial texture
    // add layers to right
    faceC[1] = 0.5;                                   // face color
    thickness = prevThickness*0.1;                    //
    totalThickness = totalThickness + thickness;      //
    glTranslatef(0.0, 0.0, (thickness+prevThickness)/2.0);    // Translate to face of thigh
    robotTorso(0.75, thickness, faceC, true);         // Draw thigh top layer
    prevThickness = thickness;

    faceC[0] = 0.5;                                   // face color
    thickness = prevThickness*0.1;                    //
    totalThickness = totalThickness + thickness/2;    //
    glTranslatef(0.0, 0.0,(thickness+prevThickness)/2.0);    // Translate to face of thigh
    robotTorso(0.4, thickness, faceC, true);          // Draw thigh top layer
    prevThickness = thickness;

    glTranslatef(0.0, 0.0, -totalThickness);          // Translate back to center of bottom thigh layer

    drawFrame(3.0);  

    // add layers to left side
    glRotatef(180.0, 0.0, 1.0, 0.0);                  // Rotate thigh about hip

    totalThickness = 0.0;
    faceC[0] = 1.0; 
    thickness = 0.4;                                  //
    totalThickness = totalThickness + thickness/2;    //
    prevThickness = thickness;

    thickness = prevThickness*0.1;                    //
    totalThickness = totalThickness + thickness;      //
    glTranslatef(0.0, 0.0, (thickness+prevThickness)/2.0);    // Translate to face of thigh
    robotTorso(0.75, thickness, faceC, true);         // Draw thigh top layer
    prevThickness = thickness;

    faceC[0] = 0.5;                                   // face color
    thickness = prevThickness*0.1;                    //
    totalThickness = totalThickness + thickness/2;    //
    glTranslatef(0.0, 0.0,(thickness+prevThickness)/2.0);    // Translate to face of thigh
    robotTorso(0.4, thickness, faceC, true);          // Draw thigh top layer
    prevThickness = thickness;
}
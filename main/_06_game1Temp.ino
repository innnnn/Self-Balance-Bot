float offsetPhi = 0.02;

//                                 0,     1,     2,     3,     4,     5,          6,          7,
float desireDistanceArray[] = { -100,  -100,  -200,  -200,  -300,  -300, -300-50*PI, -300-50*PI};
float desirePhiArray[]      = {    0,  PI/2,  PI/2,    PI,    PI,  2*PI-offsetPhi,       2*PI,         PI};
bool desirePhiTFArray[]     = {false, false, false, false, false, false,       true,      false};
//float desirePhiTF = false;
float offset = 0;

void game1Temp(){
    if( !posController.getSteady() || !phiController.getSteady() ){
        startTime = currentTime;
        if( !posController.getSteady() && (currentTime - gameTime)/1000 > 10 ){
            offset = -0.005;
            offsetTime = currentTime;
        } else {
            offset = 0;
        }
    }

    steadyTime = (currentTime - startTime)/1000;
    Serial.println(currentTime0);
    Serial.println(startTime);
    Serial.println(steadyTime);
    if(steadyTime > 0.5){
        startTime = currentTime;
        gameTime = currentTime;

        if(index<7){
            index ++;
        }

        posController.setReference(desireDistanceArray[index]);
        phiController.setReference(desirePhiArray[index]);

        psiController.clearIntegral();

        // positionController
        /*
        if( index==0 ){
            posController.setSaturation(0.04, -0.005);
        } else if( index==4 ){
            posController.setSaturation(0.02, -0.025);
        } else{
            posController.setSaturation(0.02, -0.02);
        }

        // phiController
        if( index==5 ){
            phiController.setPID(0.5);
        } else{
            phiController.setPID(1);
        }*/
    }
    
    desirePsi = posController.update(theta, Speed);
    if( (currentTime - offsetTime) >50 ){
        offset = 0;
    }
    psiController.setReference(desirePsi + offset);
    
    output = -psiController.update(psi, samplingTime);
    if(desirePhiTFArray[index]){
        phiController.setReference(2*PI + (theta+300)/100 );
    }
    outputDiff = phiController.update(phi);
    outputL = output + outputDiff;
    outputR = output - outputDiff;
}

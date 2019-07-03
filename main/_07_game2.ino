// Goal: Joystick Remote Control with Station Keeping

bool stationKeeping = true;

void game2(){
    // chech station keeping
    if( desirePsi!=0 || desirePhi!=0 ){
        stationKeeping = false;
    } else {
        if(!stationKeeping){
            stationKeeping = true;
            posController.setReference(theta);
        }
    }

    if( stationKeeping ){
        desirePsi = posController.update(theta, Speed);
    }

    // set psi reference
    psiController.setReference(desirePsi);
    output = -psiController.update(psi, samplingTime);

    // set phi reference
    phiController.setReference(desirePhi);
    outputDiff = phiController.update(phi);
    
    // calculate the left, right motor output
    outputL = output + outputDiff;
    outputR = output - outputDiff;

    // if desirePhi<0.001, which means the car turns right or left
    // reset the encoder
    if( fabs(desirePhi)<0.0001 ){
        encoderL.reset();
        encoderR.reset();
    }
}

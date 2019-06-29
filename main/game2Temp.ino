bool stationKeep = true;

void Game2Temp(){
    if( psi < PI/4 && psi > - PI/4 ){  // not falling
        // chech station keeping
        if( desirePsi!=0 || desirePhi!=0 ){
            stationKeep = false;
        } else {
            if(!stationKeep){
                stationKeep = true;
                posController.setReference(theta);
            }
        }

        if( stationKeep ){
            desirePsi = posController.update(theta);
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
    } else {
        outputL = 0;
        outputR = 0;
    }
}

String dataString = "~";

void game3(){
    if(startTurn){
        switch(Move){
            case 'S':
                dataString += "go straight ";
                break;
            case 'L':
                desirePhi += PI/2;
                dataString += "turn left and go straight ";
                break;
            case 'R':
                desirePhi -= PI/2;
                dataString += "turn right and go straight ";
                break;
        }
        phiController.setReference(desirePhi);
        startTurn = false;
    }

    if(phiController.getSteady()){
        startMove = true;
    }

    if(startMove){
        switch(Color){
            case 'R':
                desirePos -= 40.0;
                dataString += "1 block ";
                break;
            case 'G':
                desirePos -= 80.0;
                dataString += "2 blocks ";
                break;
            case 'B':
                desirePos -= 120.0;
                dataString += "3 blocks ";
                break;
        }
        startMove = false;
        dataString += "#";
        Serial.println(dataString);
        dataString = "~";
    }
    
    //desirePsi = positionController.Update(theta, Speed);
    psiController.setReference(desirePsi);
    // update
    output = -psiController.update(psi, samplingTime);
    outputDiff = phiController.update(phi);
    
    // calculate the left, right motor output
    outputL = output + outputDiff;
    outputR = output - outputDiff;
}

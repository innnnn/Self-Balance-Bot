void Game3(){
    if(startTurn){
        switch(Move){
            case 'S':
                break;
            case 'L':
                desirePhi += PI/2;
                break;
            case 'R':
                desirePhi -= PI/2;
                break;
        }
        phiController.setReference(desirePhi);
        startTurn = false;
    }

    if(phiController.isSteady()){
        startMove = true;
    }

    if(startMove){
        switch(Color){
            case 'R':
                desirePos -= 40.0;
                break;
            case 'G':
                desirePos -= 80.0;
                break;
            case 'B':
                desirePos -= 120.0;
                break;
        }
        startMove = false;
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

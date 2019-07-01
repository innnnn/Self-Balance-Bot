// Goal: Process the Command which is reveived from Car ang Rpi

void joystickControl(){
    if( fabs(data[2])<=maxPsi && fabs(data[3])<=maxPhi ){
        desirePsi = data[2];
        desirePhi = data[3];
    }
}

void setController(){
    switch( (int)data[2] ){
        case 1:  // psi
            psiController.setPID(data[3], data[4], data[5]);
            psiController.setReference(data[6]);
            sendParticularData(1);
            break;
        case 2:  // pos
            posController.setPID(data[3]);
            posController.setReference(data[4]);
            //SendParticularData(2);
            break;
        case 3:  // phi
            phiController.setPID(data[3]);
            phiController.setReference(data[4]);
            break;
    }
}

/*
//int index = -1;
float offsetPos = 5;
float offsetPhi = -0.1047;
//                                         0,              1,             2,              3,             4,              5,              6,        7
float desireDistanceArray[] = {100+offsetPos,              0, 100+offsetPos,              0, 100+offsetPos,              0,              0, 100*sqrt(2) };
float desirePhiArray[]      = {            0, PI/2+offsetPhi,             0, PI/2+offsetPhi,             0, PI/2+offsetPhi, PI/4-offsetPhi,        0};
bool desirePhiTFArray[]     = {        false,          false,         false,          false,         false,          false,          false,     false};
float desirePhiTF = false;
float offset = 0;

void Game1(){
    if( !positionController.IsSteady() || !phiController.IsSteady() ){
        startTime = currentTime;
        if( !positionController.IsSteady() && (currentTime - gameTime)/1000 > 10 ){
            offset = -0.002;
        } else {
            offset = 0;
        }
    }
    
    steadyTime = (currentTime - startTime)/1000;
    if(steadyTime > 1.5){
        startTime = currentTime;
        gameTime = currentTime;
        index ++;
        positionController.SetReference(desireDistanceArray[index]);
        desirePhi = desirePhiArray[index];
        
        phiController.SetReference(desirePhi);
        desirePhiTF = desirePhiTFArray[index];
        
        psiController.ClearIntegral();
        encoderL.Reset();
        encoderR.Reset();
    }
    
    switch(index){
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            desirePsi = -positionController.Update(y, speedY);
            //Serial.println(desirePsi, 4);
            psiController.SetReference(desirePsi + offset);
            break;
        default:
            phiController.SetPID(150);
            phiController.SetSaturation(10, -10);
            desirePsi = -positionController.Update(-theta, -Speed);
            psiController.SetReference(desirePsi + offset);
            break;
    }
    output = -psiController.Update(psi, samplingTime);

    if(desirePhiTF){
        desirePhi = theta/100.0;
        phiController.SetReference(desirePhi);
    }
    outputDiff = phiController.Update(phi);
    outputL = output + outputDiff;
    outputR = output - outputDiff;
} */

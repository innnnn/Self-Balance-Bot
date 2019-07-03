float offsetPhi = 0.1;

//                                 0,     1,     2,     3,     4,     5,          6,          7,
float desireDistanceArray[] = { -100,  -100,  -200,  -200,  -300,  -300, -300-50*PI, -300-50*PI};
float desirePhiArray[]      = {    0,  PI/2-offsetPhi,  PI/2-offsetPhi,    PI-2*offsetPhi,    PI-2*offsetPhi,  2*PI-4*offsetPhi,       2*PI-4*offsetPhi,         PI};
bool desirePhiTFArray[]     = {false, false, false, false, false, false,       true,      false};
//float desirePhiTF = false;
float offset = 0;

void game1(){
    if( !posController.getSteady() || !phiController.getSteady() ){
        startTime = currentTime;
        if( !posController.getSteady() && (currentTime - gameTime)/1000 > 2.5 ){
            offset = -0.002;
            offsetTime = currentTime;
        } else {
            offset = 0;
        }
    }
    
    steadyTime = (currentTime - startTime)/1000.0;
    if(steadyTime > 2){
        startTime = currentTime;
        gameTime = currentTime;
        offset = 0;
  
        if(index<7){
            index ++;
        }
    
        posController.setReference(desireDistanceArray[index]);
        phiController.setReference(desirePhiArray[index]);
   
        psiController.clearIntegral();
    }
        
    desirePsi = posController.update(theta, Speed);
    if( (currentTime - offsetTime) >125 ){
        offset = 0;
    }
    psiController.setReference(desirePsi + offset);
        
    output = -psiController.update(psi, samplingTime);
    if(desirePhiTFArray[index]){
        phiController.setReference(2*PI-4*offsetPhi + (theta+300)/100 );
    }
    outputDiff = phiController.update(phi);
    outputL = output + outputDiff;
    outputR = output - outputDiff;
}

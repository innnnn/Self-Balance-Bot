// Goal: Receive and Send Data through Serial & Bluetooth

// sampling time
// max sampling time: 0.025s
// max sampling rate: 40Hz
void setupMsTimer2(){
    MsTimer2::set(200, TimerInterrupt);  // 0.1 second update
    MsTimer2::start();
}

void TimerInterrupt(){
    sei();

    //receiveDataBluetooth();
    
    //Game3
    //ReceiveDataSerial();
    
    sendData();
}

// start: "~", end: "#"
void receiveDataBluetooth(){
    while(BTSerial.available()){
        char c = BTSerial.read();

        if(startReadData){
            if(c=='#'){  // end of data
                data[len++] = rawData.toFloat();
                rawData = "";
                
                if( len>=2 ){
                    if( ((int)data[0]) == 1 ){
                        switch( (int)data[1] ){
                            case 1:
                                joystickControl();
                                break;
                            case 2:
                                setController();
                                break;
                        }
                    } else if ( ((int)data[0]) == 2 ) {
                        sendParticularData((int)data[1]);
                    }
                }
                
                startReadData = false;
                len = 0;
                break;
            } else {
                if( c == '-' || c == '.' || isDigit(c) ){
                    rawData += String(c);
                } else if (c == ','){
                    data[len++] = rawData.toFloat();
                    rawData = "";
                } else {
                    startReadData = false;
                    rawData = "";
                    len = 0;
                    break;
                }
            }
        } else if (c=='~') {  // start receiving data
            startReadData = true;
        }
    }
}

void receiveDataSerial(){
    while(Serial.available()){
        char c = Serial.read();

        if(startReadData){
            if(c=='#'){
                char m = rawData[0];
                char c = rawData[1];

                if( posController.getSteady() && phiController.getSteady() ){
                    Move = m;
                    Color = c;
                    startTurn = true;
                    startReadData = false;
                }
            }
            else{
                rawData += String(c);
            }
        }
        else if(c=='~'){
            startReadData = true;
        }
    }
}

void parseData(){
    char *temp = new char[rawData.length()];
    rawData.toCharArray(temp, rawData.length());
    char *token;
    
    // get the first token
    token = strtok(temp, ",");
    do{
        data[len++] = atof(token);
        token = strtok (NULL, ",");
    } while (token != NULL);
}

void sendData(){
    //String data = "~1,1," + psiController.getErrorIntegral() + "#";
    String data = "~1,3," + String(psi, 3) + "," + String(output, 1) + ","
                          + String(thetaL) + "," + String(thetaR) + ","
                          + String(theta) + "," + String(phi, 2) + ","
                          + String(index) + "#";
    BTSerial.println(data);
}

void sendParticularData(int mode){
    String data = "";
    switch(mode){
        case 1:
            data = "~1,2," + psiController.getInformation() + "#";
            break;
        case 2:
            data = "~1,2," + posController.getInformation() + "#";
            break;
        case 3:
            break;
    }
    BTSerial.println(data);
}

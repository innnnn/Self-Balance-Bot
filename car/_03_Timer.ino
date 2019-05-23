// Goal: Bluetooth

bool startReadData = false;
String rawData = "";
int len = 0;
float *data = new float[10];
int count = 0;

// sampling time
// max sampling time: 0.025s
// max sampling rate: 40Hz
void SetupMsTimer(){
    MsTimer2::set(200, TimerInterrupt);  // 0.2s update
    MsTimer2::start();
}

void TimerInterrupt(){
    sei();

    ReceiveData();
    SendData();
}

// start: "~"
// end: "#"
void ReceiveData(){
    while(BTSerial.available()){
        char c = BTSerial.read();
        Serial.println(c);

        if(startReadData){
            if(c=='#'){
                Serial.println(rawData);
                rawData += ',';
                ParseData();
            
                if(len>=2){
                    switch( (int)data[0] ){
                        case 1:
                            break;
                        case 2:
                            SetController();
                            break;
                        case 3:
                            break;
                    }
                }
                else{
                    BTSerial.println("");
                }
                
                startReadData = false;
                rawData = "";
                len = 0;
                break;
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

void ParseData(){
    char *temp = new char[rawData.length()];
    rawData.toCharArray(temp, rawData.length());
    char *token;
    
    /* get the first token */
    token = strtok(temp, ",");
    do{
        data[len++] = atof(token);
        token = strtok (NULL, ",");
    } while (token != NULL);
}

void SendData(){
    float leftWheelAngle = motor_A.GetAngle();
    float rightWheelAngle = motor_B.GetAngle();
    String data = "~1," + String(psi) + "," + String(leftWheelAngle) + "," + String(rightWheelAngle) + "#";
    BTSerial.println(data);
}

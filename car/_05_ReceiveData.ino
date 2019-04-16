// Goal: Receive data from serial port and bluetooth

// For any kinds of input
String data = "";
bool isFinished = false;
//int count = 0;

void UpdateSerial(){
    if(Serial.available()){
        
    }
}

void UpdateBlueTooth(){
    while(BTSerial.available()){
        char c = BTSerial.read();
        Serial.println(c);
        
        if(c=='#'){
            Serial.println(data);
            //RemoteControl(data);
            data = "";
            break;
        }
        else{
            data += String(c);
        }
    }
    //count++;
    //Serial.println(count);
}

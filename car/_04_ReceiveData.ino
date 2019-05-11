// Goal: Receive data from serial port and Bluetooth

// For any kinds of input
String data = "";
bool isFinished = false;
//int count = 0;

void UpdateSerial(){
    if(Serial.available()){
        // To do
    }
}

// To do
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
    Serial.println(data);
    data = "";
    //count++;
    //Serial.println(count);
}

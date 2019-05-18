// Goal: Receive data from serial port and Bluetooth

// For any kinds of input
String rawData = "";
int len = 0;
float *data = new float[10];

void UpdateSerial(){
    if(Serial.available()){
        // To do
    }
}

void UpdateBlueTooth(){
    while(BTSerial.available()){
        char c = BTSerial.read();
        
        if(c=='#'){
            rawData += ',';
            ParseData();
            
            if(len>0){
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
            
            rawData = "";
            len = 0;
            break;
        }
        else{
            rawData += String(c);
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

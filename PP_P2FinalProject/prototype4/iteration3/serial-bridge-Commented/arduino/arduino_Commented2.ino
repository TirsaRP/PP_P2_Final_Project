// Serial I/O based on example http://forum.arduino.cc/index.php?topic=396450

//added extra comments to better understand what is going on in the code

const int buttonPin2 = 2;
const int buttonPin3 = 3; // the number of the pushbutton pin
const int buttonPin4 = 4;
const int buttonPin5 = 5;
const int buttonPin6 = 6;
const int ledPin =  9;      // the number of the LED pin

// variables will change:
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
int buttonState6 = 0;
// Serial communication
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;  
boolean newData = false;

long lastFakeReport = 0;

enum {                  //look up table. the variables equal the numbers that are commented
  MsgAcknowledge, // 0
  MsgError,       // 1
  MsgMove,        // 2
  MsgMoveResult,  // 3
  MsgPosition,    // 4
};


void setup()  {
   
  pinMode(ledPin, OUTPUT); // LED as output
  pinMode(buttonPin2, INPUT); // Buttons as input
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
 Serial.begin(115200);        //starts serial communication
  
 report(MsgAcknowledge, "Ready");  //report(0, "ready");
} 

void loop() {
  
  buttonState2 = digitalRead(buttonPin2);     // read the state of the pushbutton value:
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);


  if (buttonState2 == HIGH) { // Changes the brightness of the LED
    analogWrite(ledPin, 63);
  } 

 else if (buttonState3 == HIGH) {
    analogWrite(ledPin, 126); // Brightness value goes up
  } 

 else if (buttonState4 == HIGH) {
    analogWrite(ledPin, 192);
  } 

 else if (buttonState5 == HIGH) {
    analogWrite(ledPin, 255); // Highest value of brighness
  } 
  
 if (buttonState6 == HIGH) { // Button to turn of LED
    analogWrite(ledPin, 0); 
 }
  // Process serial communication
  recvWithStartEndMarkers();

  // If we received a command, process it
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();
    switch (integerFromPC) {
      case MsgPosition:               //4
        // Report fake result
        report(MsgPosition, 10);      //report(4,10);
        break;
      case MsgMove:                   //2
        // Pretend to do something
        report(MsgMoveResult, 10);    //report(3, 10);
        break;
      }
      
      // Debug: print parsed command to serial
      // showParsedData();
      newData = false;
    }

  // Every so often report a fake position
  if (millis() - lastFakeReport > 2000) {
    report(MsgPosition, (random(0,100)));
    lastFakeReport = millis();    
  }
}

// ---- Serial communication
void report(int code, const char *message) {
  Serial.print("<");                          //prints "<ws-bridge, code, message >"
  Serial.print("ws-bridge,");
  Serial.write(code);
  Serial.write(",");
  Serial.write(message);
  Serial.print(">\r\n");
  Serial.flush();
}

void report(int code, int message) {
  Serial.print("<");                          //prints "<ws-bridge, code, message >"
  Serial.print("ws-bridge,");
  Serial.print(code);
  Serial.print(",");
  Serial.print(message);
  Serial.print(">\r\n");
  Serial.flush();
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();  // rc= received char?? 

        if (recvInProgress == true) { 
            if (rc != endMarker) {     //if the rc isn't the endmarker">" then receiving data 
                receivedChars[ndx] = rc;    //received[i] = rc
                ndx++;      //ndx = similar to "i" used as an incrementer 
                if (ndx >= numChars) {    //if "i" is greater or equal to numChars
                    ndx = numChars - 1;   //make "i" equal numChar -1. if i goes outside of the buffer, it puts it in the last index of the array
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string   (no char received)
                recvInProgress = false;   //if  receiving is NOT in progress (false) 
                ndx = 0;                  //and no bytes are coming in    --terminate string 
                newData = true;           
            }
        }

        else if (rc == startMarker) {   //looking for the start marker "<"
            recvInProgress = true;      //receive data in progress 
        }
    }
}

void parseData() {      // split the data into its parts
    char * strtokIndx; // this is used by strtok() as an index  [string token]

    strtokIndx = strtok(tempChars,",");      // get the first part - the string like a split()
    strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
 
    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    integerFromPC = atoi(strtokIndx);     // convert the ascii to an integer

    strtokIndx = strtok(NULL, ",");
    floatFromPC = atof(strtokIndx);     // convert ascii to a float
}

void showParsedData() {
    Serial.print("Message ");
    Serial.println(messageFromPC);
    Serial.print("Integer ");
    Serial.println(integerFromPC);
    Serial.print("Float ");
    Serial.println(floatFromPC);
}


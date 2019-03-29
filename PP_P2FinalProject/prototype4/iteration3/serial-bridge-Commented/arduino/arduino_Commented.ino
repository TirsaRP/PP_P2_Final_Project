// Serial I/O based on example http://forum.arduino.cc/index.php?topic=396450

//added extra comments to better understand what is going on in the code

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

//////////////////// OUR CODE ONE //////////////////
/*#define trigPin 12  //ultrasonic sensor trig pin
#define echoPin 11  //ultrasonic sensor echo pin
#define led 10
#define led2 9
#define led3 8
#define led4 

void setup()  {
 Serial.begin(115200);        //starts serial communication

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT); // added a third led to the original code

// report(MsgAcknowledge, "Ready");  //report(0, "ready");
} */

///////////// END OUR CODE ONE ///////

void loop() {
  // Process serial communication
  recvWithStartEndMarkers();

  // If we received a command, process it
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    parseData();

      newData = false;
    }
}
 long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line -LOW turns off light
  delayMicroseconds(2); // Added this line - delay
  digitalWrite(trigPin, HIGH); // HIGH turns light on

//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line - decrease delay time

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance <= 100) {  // First LED is turned on within the distance of one meter. 
    digitalWrite(led,HIGH); 
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
}

else if (distance > 100 && distance <= 200) { // between the distance of 1 and 2 meters, the second LED lights up.
  digitalWrite(led,LOW);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,LOW);
}

else { // If above conditions are not met, the third LED will be lit (over 2 meters).
    digitalWrite(led,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,HIGH);
  }

 
  if (distance > 300 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print("<");
    Serial.print(distance);
    Serial.print(">\r\n");
    Serial.flush();
  }
  delay(500);

  //////////////// TEST CODE //////////////////

  //make switch statement if 1-3 turn a certain light now. 

switch (messageFromPC[0]) {
  case 1:
   digitalWrite(trigPin, HIGH);
    break;
  case 2:
   
    break;
  case 3:
    
    break;

    default:

}
////////// END TEST CODE /////////////


// ---- Serial communication
/*void report(int code, const char *message) {
  Serial.print("<");                          //prints "<ws-bridge, code, message >"
  Serial.print("COLOR");
  Serial.write(code);
  Serial.write(",");
  Serial.write(message);
  Serial.print(">\r\n");
  Serial.flush();
}
*/
void report(int code, int message) {
  Serial.print("<");                          //prints "<ws-bridge, code, message >"
  Serial.print("Color");
  Serial.print(code);
  Serial.print(",");
  Serial.print(message);
  Serial.print(">\r\n");
  Serial.flush();
} 

//// KEEP CODE BELOW ////

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
                Serial.println(receivedChars);      
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
   // integerFromPC = atoi(strtokIndx);     // convert the ascii to an integer

   // strtokIndx = strtok(NULL, ",");
   // floatFromPC = atof(strtokIndx);     // convert ascii to a float
}

void showParsedData() {
    Serial.print("Message ");
    Serial.println(messageFromPC);
   // Serial.print("Integer ");
   // Serial.println(integerFromPC);
   // Serial.print("Float ");
   // Serial.println(floatFromPC);
}


//code fixed by Georgi
// this example was taken from arduino analog out serial.

/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0; // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0; // value read from the pot
int outputValue = 0; // value output to the PWM (analog out)

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;
boolean newData = false;

long lastFakeReport = 0;

enum
{
  MsgAcknowledge, // 0
  MsgError,       // 1
  MsgMove,        // 2
  MsgMoveResult,  // 3
  MsgPosition,    // 4
};

void setup()
{
  // initialize serial communications at 9600 bps:
  Serial.begin(115200); // CHANGED SERIAL PORT

  report(MsgAcknowledge, "Ready");
}

void loop()
{
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // Process serial communucation
  recvWithStartEndMarkers();

  // If we received a command, process it
  if (newData == true)
  {
    strcpy(tempChars, receivedChars);
    parseData();
    switch (integerFromPC)
    {
    case MsgPosition:
      // Report fake result
      report(MsgPosition, 10);
      break;
    case MsgMove:
      // Pretend to do something
      report(MsgMoveResult, 10);
      break;
    }

    // Debug: print parsed command to serial
    // showParsedData();
    newData = false;
  }

  // Every so often report a fake position
  if (millis() - lastFakeReport > 2000)
  {
    report(MsgPosition, (random(0, 100)));
    lastFakeReport = millis();
  }
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(0);
}



//---------------------------------

// ---- Serial communication
void report(int code, const char *message)
{
  Serial.print("<");
  Serial.print("ws-bridge,");
  Serial.write(code);
  Serial.write(",");
  Serial.write(message);
  Serial.print(">\r\n");
  Serial.flush();
}

void report(int code, int message)
{
  Serial.print("<");
  Serial.print("ws-bridge,");
  Serial.print(code);
  Serial.print(",");
  Serial.print(message);
  Serial.print(">\r\n");
  Serial.flush();
}

void recvWithStartEndMarkers()
{
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false)
  {
    rc = Serial.read();

    if (recvInProgress == true)
    {
      if (rc != endMarker)
      {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars)
        {
          ndx = numChars - 1;
        }
      }
      else
      {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker)
    {
      recvInProgress = true;
    }
  }
}

void parseData()
{                   // split the data into its parts
  char *strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, ","); // get the first part - the string
  strcpy(messageFromPC, strtokIndx);   // copy it to messageFromPC

  strtokIndx = strtok(NULL, ",");   // this continues where the previous call left off
  integerFromPC = atoi(strtokIndx); // convert this part to an integer

  strtokIndx = strtok(NULL, ",");
  floatFromPC = atof(strtokIndx); // convert this part to a float
}

void showParsedData()
{
  Serial.print("Message ");
  Serial.println(messageFromPC);
  Serial.print("Integer ");
  Serial.println(integerFromPC);
  Serial.print("Float ");
  Serial.println(floatFromPC);
}
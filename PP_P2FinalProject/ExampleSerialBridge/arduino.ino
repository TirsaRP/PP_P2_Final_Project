void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); // initialize serial comminications
pinMode(11, OUTPUT); // set digital pin 11 to be an output, to control
}

void loop() {
  // put your main code here, to run repeatedly:
int sensorValue = analogRead(A0);
Serial.println(sensorValue);
delay(1);


 if (Serial.available() > 0) {
   char input = Serial.read();  // read first available byte into a variable
   if (input == 'H') {          // if the variable equals H, or ASCII 72
    digitalWrite(11, HIGH);     // turn on the LED
   }
   if (input == 'L') {          // if the variable equals L, or ASCII 76
    digitalWrite(11, LOW);      // turn off the LED
   }
 }

}

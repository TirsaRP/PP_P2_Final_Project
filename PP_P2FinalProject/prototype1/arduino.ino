/*
this example was taken from knight rider 3: https://www.arduino.cc/en/Tutorial/KnightRider and
https://www.arduino.cc/en/Tutorial/KnightRider  the two examples were combined. 
*/


// constants won't change. They're used here to set pin numbers:
const int buttonPin = 8;     // the number of the pushbutton pin
const int ledPin[] =  {2, 3, 4, 5, 6, 7};      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int count = 0;
int timer = 20;

void setup() {
  // initialize the LED pin as an output:
for (count=0;count<6;count++) {
  pinMode(ledPin[count], OUTPUT);
 }
 // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
 }

void loop() {

buttonState = digitalRead(buttonPin);


if (buttonState == HIGH) {  
  for (count=0;count<6;count++) {
   digitalWrite(ledPin[count], HIGH);
   delay(timer);
   
   digitalWrite(ledPin[count + 1], HIGH);
   delay(timer);
   
   digitalWrite(ledPin[count], LOW);
   delay(timer*2);
   }
  for (count=5;count>=0;count--) {
   digitalWrite(ledPin[count], HIGH);
   delay(timer);

   digitalWrite(ledPin[count - 1], HIGH);
   delay(timer);
   
   digitalWrite(ledPin[count], LOW);
   delay(timer*2);
  }
} else {
  digitalWrite(ledPin[count], LOW);
}
}
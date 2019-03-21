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

void setup() {
  pinMode(ledPin, OUTPUT); // LED as output
  pinMode(buttonPin2, INPUT); // Buttons as input
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
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
}

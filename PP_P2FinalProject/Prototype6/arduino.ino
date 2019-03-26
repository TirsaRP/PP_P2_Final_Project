// arduino code taken from: https://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/
// edited by: Christoffer Zackheden

#define trigPin 12
#define echoPin 11
const int ledPin[] =  {2, 3, 4, 5, 6, 7};      // the number of the LED pin
int count = 0;
int timer = 20;

#define led 10
#define led2 9
#define led3 8

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //pinMode(led, OUTPUT);
  //pinMode(led2, OUTPUT);
 // pinMode(led3, OUTPUT); // added a third led to the original code

  for (count=0;count<6;count++) {
  pinMode(ledPin[count], OUTPUT);
 }
 

}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;


  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'a') {
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


      
      //digitalWrite(led,HIGH); 
      //digitalWrite(led2,LOW);
      //digitalWrite(led3,LOW);
    }
    if (ch == 'b') {
      digitalWrite(led,HIGH); 
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);      
    }
    if (ch == 'c') {
      digitalWrite(led,LOW); 
      digitalWrite(led2,HIGH);
      digitalWrite(led3,LOW);      
    }

    if (ch == 'd') {
      digitalWrite(led,LOW); 
      digitalWrite(led2,LOW);
      digitalWrite(led3,HIGH);      
    }
  }


 
  if (distance > 300 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println("");
  }
  delay(100);
}

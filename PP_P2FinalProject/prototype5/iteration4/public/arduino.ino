// arduino code taken from: https://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/
// edited by: Christoffer Zackheden

#define trigPin 12
#define echoPin 11
#define led 10
#define led2 9
#define led3 8

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT); // added a third led to the original code
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
      digitalWrite(led,HIGH); 
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
    }
    if (ch == 'b') {
      digitalWrite(led,LOW); 
      digitalWrite(led2,HIGH);
      digitalWrite(led3,LOW);      
    }
    if (ch == 'c') {
      digitalWrite(led,LOW); 
      digitalWrite(led2,LOW);
      digitalWrite(led3,HIGH);      
    }

    if (ch == 'd') {
      digitalWrite(led,LOW); 
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);      
    }
  }


   if (distance > 300 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println("");
  }
  delay(50);

}

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
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}
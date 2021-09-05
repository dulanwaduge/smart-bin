

#define echoPin 2  // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3  //attach pin D3 Arduino to pin Trig of HC-SR04
#include <Servo.h> //Header to include Servo motor

// defines variables
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement

Servo myServo; //Servo motor object reference
int pos = 0;   //servo motor position
int RED = 6;   //Red LED pin number
int GREEN = 7; //Green LED pin number

void setup()
{
  myServo.attach(9);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
  pinMode(RED, OUTPUT);     //Sets the Green LED as an OUTPUT
  pinMode(GREEN, OUTPUT);   //Sets the Red LED as an OUTPUT
  Serial.begin(9600);       // Serial Communication is starting with 9600 of baudrate speed
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
}
void loop()
{

  myServo.write(pos); //Setting the motor to zero position

  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(RED, HIGH); //if closed LED red
  delay(500);
  digitalWrite(RED, HIGH); //if closed LED red
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  //Open the bin lid
  if (distance < 30)
  { //if the sensor detects distance is less than 30cm, the motor turns 180 degrees
    pos = 180;
    myServo.write(pos);
    Serial.print("Open ");
    digitalWrite(GREEN, HIGH); //if open LED green
    digitalWrite(RED, LOW);
    delay(3000);             // 3 second delay (!)
    digitalWrite(RED, HIGH); //if closed LED red
    digitalWrite(GREEN, LOW);
    pos = 0;
  }
  //close bin lid
}

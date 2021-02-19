#include <NewPing.h>
#include<Servo.h>
//Aici se declara pinii digitali de pe placuta.
const int LEDpin = 13; // pentru testari.

//Aici declar pinii analogi de pe SHIELD.
#define trig_pin  A4
#define echo_pin  A3
#define distanta_maxima 200 // (in cm);
//------------- pana aici s-au declarat elementele unui obiect de tip NewPing (senzor ultrasonic) ------------]
//pinii pentru driver-ul motoarelor
const int RightMotorForward = 5;
const int RightMotorBackward = 4;
const int LeftMotorForward = 3;
const int LeftMotorBackward = 2;
//alte variabile

int distance,distanceRight,distanceLeft,cm,i;
boolean goesForward;

//initializarea obiectelor pentru senzori
NewPing sonar(trig_pin,echo_pin,distanta_maxima);
Servo servo_motor;

void setup() {
  pinMode(13,OUTPUT);
  pinMode(RightMotorForward,OUTPUT);
  pinMode(RightMotorBackward,OUTPUT);
  pinMode(LeftMotorForward,OUTPUT);
  pinMode(LeftMotorBackward,OUTPUT);
  servo_motor.attach(8);
  Serial.begin(9600);



  servo_motor.write(90);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {

  delay(50);
  if (distance <= 20){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}
int readPing(){
  delay(70);
  cm = sonar.ping_cm();
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}
int lookRight(){  
  servo_motor.write(0);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){
  servo_motor.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}
void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}
void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 
  }
}
void moveBackward(){

  goesForward=false;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}
void turnRight(){

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(550);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
void turnLeft(){

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(550);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

#include <AFMotor.h>

AF_DCMotor motord(1);
AF_DCMotor motort(2);

const int trigPin_D=30;
const int echoPin_D=31;

const int trigPin_I=53;
const int echoPin_I=33;

long duration,inches;

int cm_d,cm_i;

int pared=52;


void setup(){
  Serial.begin(9600);
  pinMode(trigPin_D, OUTPUT);
  pinMode(echoPin_D, INPUT);
  digitalWrite(trigPin_D, LOW);

  pinMode(trigPin_I, OUTPUT);
  pinMode(echoPin_I, INPUT);
  digitalWrite(trigPin_I, LOW);

}

void loop(){
  ult_I();
  ult_D();

  if(cm_i>pared){
    motord.setSpeed(224);
    motord.run(FORWARD);
    motort.setSpeed(197);
    motort.run(FORWARD);
  }

  if(cm_d>pared){
    motord.setSpeed(224);
    motord.run(BACKWARD);
    motort.setSpeed(197);
    motort.run(BACKWARD);
  }

}

void ult_D(){
  digitalWrite(trigPin_D, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_D, LOW);
  duration = pulseIn(echoPin_D, HIGH);
  inches = microsecondsToInches(duration);
  cm_d = microsecondsToCentimeters(duration);

}

void ult_I(){
  digitalWrite(trigPin_I, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_I, LOW);
  duration = pulseIn(echoPin_I, HIGH);
  inches = microsecondsToInches(duration);
  cm_i = microsecondsToCentimeters(duration);
}

long microsecondsToInches(long microseconds){
  return microseconds/148;
}

long microsecondsToCentimeters(long microseconds){
  return microseconds/58;
}

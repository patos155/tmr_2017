#include <AFMotor.h>

AF_DCMotor motord(1);
AF_DCMotor motort(2);

const int trigPin_D=30;  //Sensor ultrasónico derecho
const int echoPin_D=31;

const int trigPin_I=53;  //Sensor ultrasónico izquierdo
const int echoPin_I=33;

long duration;    //Declarar variables

int cm_d,cm_i;   //Distancia en centímetros del sensor derecho e izquierdo

int pared=52;    //Distancia del sensor a la pared


void setup(){
  Serial.begin(9600);
//Declaramos los sensores y se declara el Pin trig en Low para asegurarnos de que esté apagado
  pinMode(trigPin_D, OUTPUT);
  pinMode(echoPin_D, INPUT);
  digitalWrite(trigPin_D, LOW);
//Declaramos los sensores y ponemos el Pin trig en Low para asegurarnos de que esté apagado
  pinMode(trigPin_I, OUTPUT);
  pinMode(echoPin_I, INPUT);
  digitalWrite(trigPin_I, LOW);

}

void loop(){
  //Inician funciones para convertir la duración a centímetros
  ult_I();
  ult_D();

  if(cm_i>pared){  //Si la distancia del sensor izquierdo a la pared es mayor a 52, avanza hacia la izquierda
    motord.setSpeed(224);
    motord.run(FORWARD);
    motort.setSpeed(197);
    motort.run(FORWARD);
  }

  if(cm_d>pared){  //Si la distancia del sensor derecho a la pared es mayor a 52, avanza hacia la derecha
    motord.setSpeed(224);
    motord.run(BACKWARD);
    motort.setSpeed(197);
    motort.run(BACKWARD);
  }

}

void ult_D(){
  // Pulso de 10us para inicial el modulo
  digitalWrite(trigPin_D, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_D, LOW);
  duration = pulseIn(echoPin_D, HIGH);  //Devuelve la longitud del pulso del pin Echo en us
  cm_d = microsecondsToCentimeters(duration);  //Convierte la duración en cm

}

void ult_I(){
  // Pulso de 10us para inicial el modulo
  digitalWrite(trigPin_I, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_I, LOW);
  duration = pulseIn(echoPin_I, HIGH);  //Devuelve la longitud del pulso del pin Echo en us
  cm_i = microsecondsToCentimeters(duration);  //Convierte la duración en cm
}

//Calcula distancia en centímetros
long microsecondsToCentimeters(long microseconds){
  return microseconds/58;
 }

#include <AFMotor.h>

// variables del ultrasonico
const int trigPin = 51; // Pin disparador. Se puede usar otro pin digital
const int echoPin = 53; // Pin eco. Se puede usar otro pin digital
long duration, inches, cm; // Declara variables
//int leeultra=0;
AF_DCMotor motori(1);
AF_DCMotor motord(3);
void setup() {
  Serial.begin(9600);
    // sensor ultrasonico
  pinMode(trigPin, OUTPUT); // Establece pin como salida
  pinMode(echoPin, INPUT); // Establece pin como entrada
  digitalWrite(trigPin, LOW); // Pone el pin a un estado logico bajo
  

}

void loop() {
           // Pulso de 10us para inicial el modulo
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH); //Devuelve la longitud del pulso del pin Echo en us
        // Imprime valores por el puerto serie:
       // Convierte el tiempo de recepción del eco en distancia:
       inches = microsecondsToInches(duration);
       cm = microsecondsToCentimeters(duration);
       // Imprime valores por el puerto serie:
       Serial.println("--------------------------------------------------------------");
       Serial.print(inches);
       Serial.print("in, ");
       Serial.print(cm);
       Serial.print("cm, ");
       Serial.println();
      // delay(3000);
       
       motori.setSpeed(100);
       motori.run(FORWARD);
       motord.setSpeed(100);
       motord.run(FORWARD);
       if(cm<=4){
        
                          motori.setSpeed(0);
                          motori.run(RELEASE);
                          motord.setSpeed(0);
                          motord.run(RELEASE);
                         delay(100);       
                          motori.setSpeed(190);
                          motori.run(BACKWARD);
                          motord.setSpeed(190);
                          motord.run(BACKWARD);
                          delay(300);
                            motori.setSpeed(160);
                            motori.run(BACKWARD);
                            motord.setSpeed(190);
                            motord.run(FORWARD);
                            delay(300);
                            motori.setSpeed(100);
                            motori.run(FORWARD);
                            motord.setSpeed(100);
                            motord.run(FORWARD);
                            delay(2500);
                             motord.setSpeed(160);
                             motord.run(BACKWARD);
                             motori.setSpeed(190);
                             motori.run(FORWARD);
                             delay(300);
                               }
       

}
// Calcula la distancia en pulgadas
long microsecondsToInches(long microseconds) {
return microseconds/148;
}
// Calcula la distancia en cm
long microsecondsToCentimeters(long microseconds) {
return microseconds/58;
} 

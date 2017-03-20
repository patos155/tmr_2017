#include <AFMotor.h>
AF_DCMotor motori(1);
AF_DCMotor motord(3);
AF_DCMotor motort(4);

const int sen_c = A14;//sensor centro 
const int sen_i = A13;//sensor izquierdo
const int sen_d = A15;//sensor derecho
int val_c = 0; 
int val_i = 0;
int val_d = 0;

// Inicializamos el valor del sensor a 0

void setup() 
{
  Serial.begin(9600);
 pinMode(sen_c,INPUT);
 pinMode(sen_i,INPUT);
 pinMode(sen_d,INPUT);

}
void loop()
{
  // leemos el pin y asignamos el valor a la variable.  
  val_c = analogRead(sen_c);//sensor centro
  val_i = analogRead(sen_i);//sensor izquierdo
  val_d = analogRead(sen_d);//sensor derecho
 Serial.println("Sensor_centro");
 Serial.println(val_c);   
 Serial.println("Sensor_izquierdo");
 Serial.println(val_i);
 Serial.println("Sensor_derecho");
 Serial.println(val_d);
   
   //centro detecat la pelota
   if(val_c>=920){
    motori.setSpeed(250);
    motori.run(FORWARD);
    motord.setSpeed(250);
    motord.run(FORWARD);
    motort.setSpeed(0);
    motort.run(RELEASE);
   }
    if(val_i>=920){
    motori.setSpeed(250);
    motori.run(BACKWARD);
    motord.setSpeed(250);
    motord.run(FORWARD);
    motort.setSpeed(150);
    motort.run(BACKWARD);
   }
     if(val_d>=920){
    motori.setSpeed(250);
    motori.run(FORWARD);
    motord.setSpeed(250);
    motord.run(BACKWARD);
    motort.setSpeed(150);
    motort.run(FORWARD);
   }
            delay(1000); 
}

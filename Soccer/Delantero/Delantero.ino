#include <AFMotor.h>
AF_DCMotor motori(1);
AF_DCMotor motord(3);
AF_DCMotor motort(4);

const int sen_c = A14;//sensor centro 
const int sen_i = A13;//sensor izquierdo
const int sen_d = A15;//sensor derecho
const int sen_d_t = A12;//sensor derecho trasero
const int sen_i_t = A10;//sensor izquierdo trasero
int val_c = 0; 
int val_i = 0;
int val_d = 0;
int val_i_t = 0;
int val_d_t = 0;

// Inicializamos el valor del sensor a 0

void setup() 
{
  Serial.begin(9600);
 pinMode(sen_c,INPUT);
 pinMode(sen_i,INPUT);
 pinMode(sen_d,INPUT);
 pinMode(sen_i_t,INPUT);
 pinMode(sen_d_t,INPUT);

}
void loop()
{
  // leemos el pin y asignamos el valor a la variable.  
  val_c = analogRead(sen_c);//sensor centro
  val_i = analogRead(sen_i);//sensor izquierdo
  val_d = analogRead(sen_d);//sensor derecho
  val_i_t = analogRead(sen_i_t);//sensor izquierdo trasero
  val_d_t = analogRead(sen_d_t);// sensor derecho trasero
 Serial.println("Sensor_centro");
 Serial.println(val_c);   
 Serial.println("Sensor_izquierdo");
 Serial.println(val_i);
 Serial.println("Sensor_derecho");
 Serial.println(val_d);
 Serial.println("Sensor_izquierdo_trasero");
 Serial.println(val_i_t);
 Serial.println("Sensor_derecho_trasero");
 Serial.println(val_d_t);
   //centro no detecta la pelota
   if(val_c<920){
    motori.setSpeed(0);
    motori.run(BACKWARD);
    motord.setSpeed(0);
    motord.run(BACKWARD);
    motort.setSpeed(0);
    motort.run(RELEASE);
   }

   //centro detecat la pelota
   if(val_i<920 && val_c>=920 && val_d<920 && val_i_t<920 && val_d_t<920){
    motori.setSpeed(250);
    motori.run(FORWARD);
    motord.setSpeed(250);
    motord.run(FORWARD);
    motort.setSpeed(0);
    motort.run(RELEASE);
   }//IZQUIEROD DETECTA LA PELOTA
   if(val_i>=920 && val_c<920 && val_d<920 && val_i_t<920 && val_d_t<920){
    motori.setSpeed(250);
    motori.run(BACKWARD);
    motord.setSpeed(0);
    motord.run(RELEASE);
    motort.setSpeed(100);
    motort.run(BACKWARD);
    delay(185);
   }//DERECHO DETECTA LA PELOTA
   if(val_i<920 && val_c<920 && val_d>=920 && val_i_t<920 && val_d_t<920){
    motori.setSpeed(250);
    motori.run(FORWARD);
    motord.setSpeed(250);
    motord.run(BACKWARD);
    motort.setSpeed(100);
    motort.run(FORWARD);
    delay(185);
   }//IZQUIERDO TRASERO DETECTA LA PELOTA
   if(val_i<920 && val_c<920 && val_d<920 && val_i_t>=920 && val_d_t<920){
    motori.setSpeed(0);
    motori.run(RELEASE);
    motord.setSpeed(0);
    motord.run(RELEASE);
    motort.setSpeed(250);
    motort.run(FORWARD);
   }//DERECHO TRASERO DETECTA LA PELOTA
   if(val_i<920 && val_c<920 && val_d && val_i_t<920 && val_d_t>=920){
    motori.setSpeed(0);
    motori.run(RELEASE);
    motord.setSpeed(0);
    motord.run(RELEASE);
    motort.setSpeed(250);
    motort.run(BACKWARD);
   }
  
           delay(1000); 
}

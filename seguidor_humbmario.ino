#include <AFMotor.h>
AF_DCMotor motor_derecho(4);   //motor derecho
AF_DCMotor motor_izquierdo(3);   //motor izquierdo
// TCS230 color recognition sensor 
// Sensor connection pins to Arduino are shown in comments
/*
Color Sensor derecho  Arduino
-----------      --------
 VCC               5V
 GND               GND
 s0                22
 s1                24
 s2                28
 s3                26
 OUT               30
 OE                GND
Color Sensor izquierdo Arduino
-----------      --------
 VCC               5V
 GND               GND
 s0                52
 s1                53
 s2                50
 s3                51
 OUT               49
 OE                GND
*/
//VARIABLES DEL SENSOR INFRARROJO

//s2
int izq_1=22;
//s3
int izq_2=24;
//s4
int centro_3=26;
//s6
int der_4=28;
//s7
int der_5=30;
// lectura de sensores
int l1=1;
int l2=1;
int l3=1;
int l4=1;
int l5=1;
int l6=1;
int l7=1;
int l8=1;
//colores 
int neg=0;
int bco=1;

void setup() {
  Serial.begin(9600);
  //s1
   pinMode(izq_1,INPUT);
   //s2
   pinMode(izq_2,INPUT);
   //s3
   pinMode(centro_3,INPUT);
   //s4
   pinMode(der_4,INPUT);
   //s5
   pinMode(der_5,INPUT);
}
  void loop() {
   
   l5=digitalRead(izq_1);
   l4=digitalRead(izq_2);
   l3=digitalRead(centro_3);
   l2=digitalRead(der_4);
   l1=digitalRead(der_5);
   
   if(l5==neg ){
        motor_derecho.setSpeed(250);
       motor_derecho.run(BACKWARD);
       motor_izquierdo.setSpeed(200);
       motor_izquierdo.run(FORWARD);
  }
   if(l1==neg ){
        motor_derecho.setSpeed(175);
       motor_derecho.run(FORWARD);
       motor_izquierdo.setSpeed(250);
       motor_izquierdo.run(BACKWARD);
  }

if((l1==bco && l2==bco && l4==bco && l5==bco)){ 
       motor_derecho.setSpeed(130);
       motor_derecho.run(FORWARD);
       motor_izquierdo.setSpeed(130);
       motor_izquierdo.run(FORWARD);
}
   
if (l2==neg && l5==bco && l1==bco ){
       motor_derecho.setSpeed(100);
       motor_derecho.run(FORWARD);
       motor_izquierdo.setSpeed(20);
       motor_izquierdo.run(BACKWARD);
}

if (l4==neg && l1==bco && l5==bco ){
       motor_derecho.setSpeed(20);
       motor_derecho.run(BACKWARD);
       motor_izquierdo.setSpeed(150);
       motor_izquierdo.run(FORWARD);
     }
}



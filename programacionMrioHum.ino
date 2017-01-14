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
//VARIABLES DEL SENSOR INFRARROJO//•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○•○
//s1
int izq_1=33;
//s2
int izq_2=35;
//s3
int izq_3=37;
//s4
int izq_centro=39;
//s5
int der_centro=41;
//s6
int der_6=43;
//s7
int der_7=45;
//s8
int der_8=47;
// lectura de sensores
int l1=0;
int l2=0;
int l3=0;
int l4=0;
int l5=0;
int l6=0;
int l7=0;
int l8=0;
//colores 
int neg=1;
int bco=0;


void setup() {
  Serial.begin(9600);
  //s1
   pinMode(izq_1,INPUT);
   //s2
   pinMode(izq_2,INPUT);
   //s3
   pinMode(izq_3,INPUT);
   //s4
   pinMode(izq_centro,INPUT);
   //s5
   pinMode(der_centro,INPUT);
   //s6
   pinMode(der_6,INPUT);
   //s7
   pinMode(der_7,INPUT);
   //s8
   pinMode(der_8,INPUT);
}
  void loop() {
   
   l1=digitalRead(izq_1);
   l2=digitalRead(izq_2);
   l3=digitalRead(izq_3);
   l4=digitalRead(izq_centro);
   l5=digitalRead(der_centro);
   l6=digitalRead(der_6);
   l7=digitalRead(der_7);
   l8=digitalRead(der_8);
   Serial.print(l1);
   Serial.print(l2);
   Serial.print(l3);
   Serial.print(l4);
   Serial.print(l5);
   Serial.print(l6);
   Serial.print(l7);
   Serial.print(l8);
   Serial.println("____________________");


 if (l1==bco && l2==bco && l3==bco && l4==bco && l5==bco && l6==bco && l7==bco  && l8==bco){
       motor_derecho.setSpeed(125);
       motor_derecho.run(FORWARD);
       motor_izquierdo.setSpeed(125);
       motor_izquierdo.run(FORWARD);
 }
//RECTA ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if ((l1==bco && l2==bco && l3==bco) && (l4==neg  || l5==neg) && (l6==bco && l7==bco  && l8==bco)){  
       motor_derecho.setSpeed(125);
       motor_derecho.run(FORWARD);
       motor_izquierdo.setSpeed(125);
       motor_izquierdo.run(FORWARD);

    }
//DESVIADO A LA DAERECHA
     if ((l3==neg) && (l6==bco && l7==bco  && l8==bco)){
       motor_derecho.setSpeed(125);
       motor_derecho.run(FORWARD);
       motor_izquierdo.setSpeed(25);
       motor_izquierdo.run(BACKWARD);
     }
     //ESQUINA A LA DAERECHA//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
     if ((l1==neg) && ( l8==bco)){
       motor_derecho.setSpeed(150);
       motor_derecho.run(FORWARD);
       motor_izquierdo.setSpeed(125);
       motor_izquierdo.run(BACKWARD);
       
     }
// DESVIADO A LA IZQUIERDA       
     if ((l1==bco && l2==bco && l3==bco) && (l6==neg )){
       motor_derecho.setSpeed(25);
       motor_derecho.run(BACKWARD);
       motor_izquierdo.setSpeed(125);
       motor_izquierdo.run(FORWARD);
     }
     // ESQUINAS A LA IZQUIERDA//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLl       

 
 if ((l1==bco) && (l8==neg)){ 
       motor_derecho.setSpeed(125);
       motor_derecho.run(BACKWARD);
       motor_izquierdo.setSpeed(150);
       motor_izquierdo.run(FORWARD);
     }
               
}


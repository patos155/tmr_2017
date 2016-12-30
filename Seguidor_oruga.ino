#include <AFMotor.h>
//define tipo de variable motor y puerto
////////////////////////////////////////////////////////////////////////////////////
AF_DCMotor motori(4); //motor derecho
AF_DCMotor motord(1);//motor izquierdo
////////////////////////////////////////////////////////////////////////////////////
//definicion de pines de los sensores
//s1 cable verde
int izq_ext=44;
//s2 cable amarillo
int izq_int=46;
//s3 cable naranja
int centro=48;
//s4 cable cafe
int der_int=50;
//s5 cable negro
int der_ext=52;
/////////////////////////////////////////////////////////////////////////////////////////
// lectura de sensores
int l1=0;
int l2=0;
int l3=0;
int l4=0;
int l5=0;
int neg=0;
int bco=1;
///////////////////////////////////////////////////////////////////////////////////////////

void setup() {
   Serial.begin(9600); 
   pinMode(izq_ext,INPUT);
   pinMode(izq_int,INPUT);
   pinMode(centro,INPUT);
   pinMode(der_int,INPUT);
   pinMode(der_ext,INPUT);
}
void loop(){
  
// lectura de sensores bco/ngo
   l1=digitalRead(izq_ext);
   l2=digitalRead(izq_int);
   l3=digitalRead(centro);
   l4=digitalRead(der_int);
   l5=digitalRead(der_ext);
/*
 Serial.println("____Sensores de Izq. a Derecha_____");
   Serial.println(l1);
   Serial.println(l2);
   Serial.println(l3);
   Serial.println(l4);
   Serial.println(l5);
   delay(5000);
   */
   //robot centrado 
if( l2==bco && l3==neg && l4==bco){
  
     motori.setSpeed(250);
     motori.run(FORWARD);
     motord.setSpeed(230);
     motord.run(FORWARD);
}else{
  //robot desviado a la derecha
  if(l2==neg && l3==bco && l4==bco){
   motori.setSpeed(230);
  motori.run(FORWARD);
  motord.setSpeed(250);
  motord.run(FORWARD);
}
else{
  //robot desviado a la izquierda 
  if(l2==bco && l3==bco && l4==neg){
    motori.setSpeed(0);
    motori.run(FORWARD);
    motord.setSpeed(250);
    motord.run(BACKWARD);
  }
else{
  if (l2==neg && l3==neg && l4==neg){
    motori.setSpeed(0);
    motori.run(FORWARD);
    motord.setSpeed(0);
    motord.run(BACKWARD);
  }
else{
  if(l2==bco && l3==bco && l4==bco){
    motori.setSpeed(250);
    motori.run(FORWARD);
    motord.setSpeed(240);
    motord.run(BACKWARD);
  }

}
if(l1==neg && l2==bco && l3==bco && l4==bco){
  motori.setSpeed(230);
  motori.run(FORWARD);
  motord.setSpeed(250);
  motord.run(FORWARD);
}else{
  if(l2==bco && l3==bco && l4==bco && l5==neg){
     motori.setSpeed(0);
    motori.run(FORWARD);
    motord.setSpeed(250);
    motord.run(BACKWARD);
  }
}
}
}
}

}







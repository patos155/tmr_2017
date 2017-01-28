#include <AFMotor.h>
/*
  Color Sensor1      Arduino IZQUIERDO
  -----------      --------
  VCC               5V
  GND               GND
  s0                30(8)
  s1                32(9)
  s2                34(12)
  s3                36(11)
  OUT               38(10)
  OE                GND
  Color Sensor2      Arduino DERECHO
  -----------      --------
  VCC               5V
  GND               GND
  s0                31(8)
  s1                33(9)
  s2                35(12)
  s3                37(11)
  OUT               39(10)
  OE                GND
*/
AF_DCMotor motord(4); //motor derecho
AF_DCMotor motori(1);//motor izquierdo
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
int suma=0;
// variables del ultrasonico
const int trigPin = 51; // Pin disparador. Se puede usar otro pin digital
const int echoPin = 53; // Pin eco. Se puede usar otro pin digital
long duration, inches, cm; // Declara variables
// inicializacion de variables para los pins de sensor 1 izquierdo
const int s1_0 = 30;
const int s1_1 = 32;
const int s1_2 = 34;
const int s1_3 = 36;
const int out_1 = 38;
// inicializacion de variables para los pins de sensor 2 derecho
const int s2_0 = 31;
const int s2_1 = 33;
const int s2_2 = 35;
const int s2_3 = 37;
const int out_2 = 39;
// Variables  sensor 1 izquierdo
int red1=0;
int green1=0;
int blue1=0;
// Variables  sensor 2 derecho
int red2=0;
int green2=0;
int blue2=0;
int des=5;
// lectura de colores encontrados en sensor 1 izquierdo
int ler_bco_1=5;
int leg_bco_1=5;
int leb_bco_1=5;

int ler_vde_1=18;
int leg_vde_1=15;
int leb_vde_1=15;
// lectura de colores encontrados en sensor 2 derecho
int ler_bco_2=5;
int leg_bco_2=5;
int leb_bco_2=5;

int ler_vde_2=14;
int leg_vde_2=13;
int leb_vde_2=13;
// colores encontrados en sensor 1 izquierdo
int enc_bco_1=0;
int enc_vde_1=0;
// colores encontrados en sensor 2 derecho
int enc_bco_2=0;
int enc_vde_2=0;
void setup() {
   Serial.begin(9600); 
   //////////////////////////////////////////////////////////////////////////////
   pinMode(izq_ext,INPUT);
   pinMode(izq_int,INPUT);
   pinMode(centro,INPUT);
   pinMode(der_int,INPUT);
   pinMode(der_ext,INPUT);
   /////////////////////////////////////////////////////
   pinMode(trigPin, OUTPUT); // Establece pin como salida
   pinMode(echoPin, INPUT); // Establece pin como entrada
   digitalWrite(trigPin, LOW); // Pone el pin a un estado logico bajo
   ///////////////////////
   pinMode(s1_0, OUTPUT);
   pinMode(s1_1, OUTPUT);
   pinMode(s1_2, OUTPUT);
   pinMode(s1_3, OUTPUT);
   //Pines s0,s1,s2 y s3 como salidas para el sensor2
   pinMode(s2_0, OUTPUT);
   pinMode(s2_1, OUTPUT);
   pinMode(s2_2, OUTPUT);
   pinMode(s2_3, OUTPUT);
   // pin OUT_1 como entrada para el sensor 1
   pinMode(out_1, INPUT);
   // pin OUTT_2 como entrada para el sensor 2
   pinMode(out_2, INPUT);
   // S0 y S1 en alto color base rojo para sensor 1
   digitalWrite(s1_0, HIGH);
   digitalWrite(s1_1, HIGH);
   // S0 y S1 en alto color base rojo para sensor 2
   digitalWrite(s2_0, HIGH);
   digitalWrite(s2_1, HIGH);
}

void loop() {
   //lectura de sensores bco/ngo
   l1=digitalRead(izq_ext);
   l2=digitalRead(izq_int);
   l3=digitalRead(centro);
   l4=digitalRead(der_int);
   l5=digitalRead(der_ext); 
   
   ///////////////////////////////////////////////////
/*   Serial.print(l1);
   Serial.print(l2);
   Serial.print(l3);
   Serial.print(l4);
   Serial.println(l5);
   Serial.println("--------------------------------------------------------------");
   Serial.print(cm);
   Serial.print("cm, ");
   delay(1000);*/
   //robot centrado 
   if(l2==bco && l3==neg && l4==bco){
       motori.setSpeed(100);
       motori.run(FORWARD);
       motord.setSpeed(100);
       motord.run(FORWARD);
   }//robot centrado todos los sensores en blanco 
   if(l2==bco && l3==bco && l4==bco){
      motori.setSpeed(100);
      motori.run(FORWARD);
      motord.setSpeed(100);
      motord.run(FORWARD);
   }//curva a la izquierda
   if(l2==neg && l3==bco && l4==bco){
      motori.setSpeed(110);//110
      motori.run(BACKWARD);
      motord.setSpeed(125);//150
      motord.run(FORWARD);
   }//curva  a la derecha
   if(l2==bco && l3==bco && l4==neg){
      motori.setSpeed(125);
      motori.run(FORWARD);
      motord.setSpeed(110);
      motord.run(BACKWARD);
   }// curva a la izquierda (caso extremo)
   if(l1==neg && l2==bco && l3==bco){
      motori.setSpeed(120);
      motori.run(BACKWARD);
      motord.setSpeed(150);
      motord.run(FORWARD);
   }//curva a la derecha (caso extremo)
   if(l3==bco && l4==bco && l5==neg){
       motori.setSpeed(150);
       motori.run(FORWARD);
       motord.setSpeed(120);
       motord.run(BACKWARD);        
   }//curva a la izquierda (caso especifico)
   if(l1==neg && l2==neg && l3==bco){
       motori.setSpeed(110);
       motori.run(BACKWARD);
       motord.setSpeed(125);
       motord.run(FORWARD);
   }//curva a la derecha (caso especifico)
   if(l3==bco && l4==neg && l5==neg){
      motori.setSpeed(125);
      motori.run(FORWARD);
      motord.setSpeed(110);
      motord.run(BACKWARD);
   }//curva a izquierda (caso especifico)
   if(l1==neg && l2==neg && l3==neg){
      motori.setSpeed(110);
      motori.run(BACKWARD);
      motord.setSpeed(125);
      motord.run(FORWARD);
   }//curva a la derecha(caso especifico)
   if(l3==neg && l4==neg && l5==neg){
      motori.setSpeed(125);
      motori.run(FORWARD);
      motord.setSpeed(110);
      motord.run(BACKWARD);
   }      
   //detiene en interseccion
   suma=l1+l2+l4+l5;
   if(suma<2){
      motori.setSpeed(0);
      motori.run(FORWARD);
      motord.setSpeed(0);
      motord.run(FORWARD);
      delay(200);
   }
      // derecho verde (vuelta a la derecha)(1==izquierda && 2==derecha)
/*      color();
      if(enc_bco_1==1 && enc_vde_2==1) {
           motori.setSpeed(150);
           motori.run(FORWARD);
           motord.setSpeed(130);
           motord.run(BACKWARD);
           delay(200);
      }//izquierdo verde (vuelta a la izquierda) (1==izquierdo && 2==derecha)
      if(enc_vde_1==1 && enc_bco_2==1) {
           motori.setSpeed(130);
           motori.run(BACKWARD);
           motord.setSpeed(150);
           motord.run(FORWARD);
      }//detecta blanco en los dos lados(1==izquierdo && 2==derecha)
      if(enc_bco_1==1 && enc_bco_2==1){
           motori.setSpeed(100);
           motori.run(FORWARD);
           motord.setSpeed(100);
           motord.run(FORWARD);
      }
   }*/
   //rodear un objeto
   ultra();
   if(cm<=5){
      //Serial.print("entre ultra");
      motori.setSpeed(0);
      motori.run(RELEASE);
      motord.setSpeed(0);
      motord.run(RELEASE);
      delay(100);       
      motori.setSpeed(190);
      motori.run(BACKWARD);
      motord.setSpeed(190);
      motord.run(BACKWARD);
      delay(350);
      motori.setSpeed(160);
      motori.run(BACKWARD);
      motord.setSpeed(190);
      motord.run(FORWARD);
      delay(300);
      motori.setSpeed(100);
      motori.run(FORWARD);
      motord.setSpeed(100);
      motord.run(FORWARD);
      delay(2600);
      motori.setSpeed(190);
      motori.run(FORWARD);
      motord.setSpeed(160);
      motord.run(BACKWARD);
      delay(300);
   }
//}
   
/*void color() {
  // color en sensor 1 Izquierdo
  enc_bco_1 = 0;
  enc_vde_1 = 0;
  // color en sensor 2 Derecho
  enc_bco_2 = 0;
  enc_vde_2 = 0;

  /////////////////////////////////////////////////
  // pin s2 en bajo, s3 en bajo (ro44jo)
  digitalWrite(s1_2, LOW);
  digitalWrite(s1_3, LOW);

  //count OUT_1, pRed, RED
  // pulso en el pin out_1 lee en out_1
  red1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);
  // pin 12 en bajo y pin 11 alto (azul)
  digitalWrite(s1_3, HIGH);
  //count OUT, pBLUE, BLUE
  blue1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);
  // pin 12 en alto y pin 11 en alto (verde)
  digitalWrite(s1_2, HIGH);
  //count OUT, pGreen, GREEN
  green1 = pulseIn(out_1, digitalRead(out_1) == HIGH ? LOW : HIGH);

  // pin s2 en bajo, s3 en bajo (rojo)
  digitalWrite(s2_2, LOW);
  digitalWrite(s2_3, LOW);

  //count OUT_2, pRed, RED
  // pulso en el pin out_1 lee en out_1
  red2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
  // pin 12 en bajo y pin 11 alto (azul)
  digitalWrite(s2_3, HIGH);
  //count OUT_2, pBLUE, BLUE
  blue2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
  // pin 12 en alto y pin 11 en alto (verde)
  digitalWrite(s2_2, HIGH);
  //count OUT_2, pGreen, GREEN
  green2 = pulseIn(out_2, digitalRead(out_2) == HIGH ? LOW : HIGH);
 // Serial.println("Sensor Izquierdo");*/
/*
  // muestra la intensidad (los milisegunods que tardo en la lectura para el rojo
  Serial.print("R1 Intensity:");
  Serial.println(red1, DEC);
  // muestra la intensidad (los milisegunods que tardo en la lectura para el verde
  Serial.print(" G1 Intensity: ");
  Serial.println(green1, DEC);
  // muestra la intensidad (los milisegunods que tardo en la lectura para el blue
  Serial.print(" B1 Intensity : ");
  Serial.println(blue1, DEC);

  Serial.println("Sensor Derecho");
  // muestra la intensidad (los milisegunods que tardo en la lectura para el rojo
  Serial.print("R2 Intensity:");
  Serial.println(red2, DEC);
  // muestra la intensidad (los milisegunods que tardo en la lectura para el verde
  Serial.print(" G2 Intensity: ");
  Serial.println(green2, DEC);
  // muestra la intensidad (los milisegunods que tardo en la lectura para el blue
  Serial.print(" B2 Intensity : ");
  Serial.println(blue2, DEC);
  */

  // colores en sensor 1
  if ((red1 >= ler_bco_1 - des && red1 <= ler_bco_1 + des) && (green1 >= leg_bco_1 - des && green1 <= leg_bco_1 + des) && (blue1 >= leb_bco_1 - des && blue1 <= leb_bco_1 + des)) {
       enc_bco_1 = 1;
      // Serial.println(" -   BLANCO sensor Izquierdo ");
  }
  if ((red1 >= ler_vde_1 - des && red1 <= ler_vde_1 + des) && (green1 >= leg_vde_1 - des && green1 <= leg_vde_1 + des) && (blue1 >= leb_vde_1 - des && blue1 <= leb_vde_1 + des)) {
       enc_vde_1 = 1;
      // Serial.println(" -   VERDE sensor Izquierdo ");
  }
  // colores en sensor 2
  if ((red2 >= ler_bco_2 - des && red2 <= ler_bco_2 + des) && (green2 >= leg_bco_2 - des && green2 <= leg_bco_2 + des) && (blue2 >= leb_bco_2 - des && blue2 <= leb_bco_2 + des)) {
       enc_bco_2 = 1;
      // Serial.println(" -   BLANCO sensor derecho ");
  }
  if ((red2 >= ler_vde_2 - des && red2 <= ler_vde_2 + des) && (green2 >= leg_vde_2 - des && green2 <= leg_vde_2 + des) && (blue2 >= leb_vde_2 - des && blue2 <= leb_vde_2 + des)) {
       enc_vde_2 = 1;
      // Serial.println(" -   VERDE sensor derecho ");
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

void ultra(){
     // lectura ultrasonico
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH); //Devuelve la longitud del pulso del pin Echo en us
   // Imprime valores por el puerto serie:
   // Convierte el tiempo de recepción del eco en distancia:
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);

}

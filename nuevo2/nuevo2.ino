//Incluimos la libreria SD.
#include <SD.h>
//#include <QTRSensors.h>
#include <AFMotor.h>

//define motores por cada puerto
AF_DCMotor motori_D(1); //motor izquierdo delantero
AF_DCMotor motori_T(4); //motor izquierdo trasero
AF_DCMotor motord_D(2);   //motor derecho
AF_DCMotor motord_T(3);   //motor izquierdo


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
int suma=0;
int sum_der=0;
int sum_izq=0;
// COLORES
int neg=1;
int bco=0;
//////////Potencias
int ade_ordi=200;
int medioi=120;
int ade_ordd=200;
int mediod=150;
int dife=3;
// dirección y tiempo de regreso
int tr=40;
int rl=100;
int al=60;
int dif=20;
String dire="";


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


void alto(){
   motori_D.setSpeed(0);//velocidad de motor izquierdo
   motori_D.run(FORWARD); //polaridad de motor izquierdo
   motord_D.setSpeed(0);//velocidad de motor derecho
   motord_D.run(FORWARD);//polaridad de motor  derecho
   motori_T.setSpeed(0);//velocidad de motor izquierdo
   motori_T.run(FORWARD); //polaridad de motor izquierdo
   motord_T.setSpeed(0);//velocidad de motor derecho
   motord_T.run(FORWARD);//polaridad de motor  derecho
   Serial.println("____ALTO____________________");
   delay(200);
}


void loop() {
   //lectura de sensores bco/ngo
  
   l1=digitalRead(izq_1);
   l2=digitalRead(izq_2);
   l3=digitalRead(izq_3);
   l4=digitalRead(izq_centro);
   l5=digitalRead(der_centro);
   l6=digitalRead(der_6);
   l7=digitalRead(der_7);
   l8=digitalRead(der_8);
   Serial.println("____Sensores de Izq. a Derecha_____");
   Serial.print("l1- ");
   Serial.println(l1);
   Serial.print("l2- ");
   Serial.println(l2);
   Serial.print("l3- ");
   Serial.println(l3);
   Serial.print("l4- ");
   Serial.println(l4);
   Serial.print("l5- ");
   Serial.println(l5);
   Serial.print("l6- ");
   Serial.println(l6);
   Serial.print("l7- ");
   Serial.println(l7);
   Serial.print("l8- ");
   Serial.println(l8);
   
   //delay(4000);
   
   suma=(l1+l2+l3+l4+l5+l6+l7+l8);
   //if (suma<=2){  
      ///////////////////////////////////// RECTA
      if (l1==bco && l2==bco && l3==bco && l4==bco && l5==bco && l6==bco && l7==bco  && l8==bco){
        dire="C0";
        motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
        motori_D.run(FORWARD); //polaridad de motor izquierdo
        motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
        motord_D.run(FORWARD);//polaridad de motor  derecho
        motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
        motori_T.run(FORWARD); //polaridad de motor izquierdo
        motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
        motord_T.run(FORWARD);//polaridad de motor  derecho
      }else{
        if (l1==bco && l2==bco && l3==bco && l4==neg && l5==neg && l6==bco && l7==bco  && l8==bco){ 
           //viene desviado de la derecha
           if (dire=="C2" || dire=="C3" || dire=="C4"){
              motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
              motori_D.run(FORWARD); //polaridad de motor izquierdo
              motord_D.setSpeed(mediod);//velocidad de motor derecho
              motord_D.run(BACKWARD);//polaridad de motor  derecho
              motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
              motori_T.run(FORWARD); //polaridad de motor izquierdo
              motord_T.setSpeed(mediod);//velocidad de motor derecho
              motord_T.run(BACKWARD);//polaridad de motor  derecho
              delay(tr);
           }
           //viene desviado de la izquierda
           if (dire=="C5" || dire=="C6" || dire=="C7"){
              motori_D.setSpeed(medioi);//velocidad de motor izquierdo
              motori_D.run(BACKWARD); //polaridad de motor izquierdo
              motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
              motord_D.run(FORWARD);//polaridad de motor  derecho
              motori_T.setSpeed(medioi);//velocidad de motor izquierdo
              motori_T.run(BACKWARD); //polaridad de motor izquierdo
              motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
              motord_T.run(FORWARD);//polaridad de motor  derecho
              delay(tr);
           }
           dire="C1";
           motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
           motori_D.run(FORWARD); //polaridad de motor izquierdo
           motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
           motord_D.run(FORWARD);//polaridad de motor  derecho
           motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
           motori_T.run(FORWARD); //polaridad de motor izquierdo
           motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
           motord_T.run(FORWARD);//polaridad de motor  derecho
        } else {
            // desviado a la derecha gira acelerando motor derecho
            if ((l1==neg || l2==neg || l3==neg) && (l5==bco && l6==bco && l7==bco  && l8==bco)){
               dire="C2";
               motori_D.setSpeed(medioi);//velocidad de motor izquierdo
               motori_D.run(BACKWARD); //polaridad de motor izquierdo
               motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
               motord_D.run(FORWARD);//polaridad de motor  derecho
               motori_T.setSpeed(medioi+dif);//velocidad de motor izquierdo
               motori_T.run(BACKWARD); //polaridad de motor izquierdo
               motord_T.setSpeed(ade_ordd+dif);//velocidad de motor derecho
               motord_T.run(FORWARD);//polaridad de motor  derecho
            } else {
               if ((l1==bco && l2==bco && l3==bco && l4==bco) && (l6==neg ) && (l7==bco  && l8==bco)){
                  dire="C5";
                  motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
                  motori_D.run(FORWARD); //polaridad de motor izquierdo
                  motord_D.setSpeed(mediod);//velocidad de motor derecho
                  motord_D.run(BACKWARD);//polaridad de motor  derecho
                  motori_T.setSpeed(ade_ordi+dif);//velocidad de motor izquierdo
                  motori_T.run(FORWARD); //polaridad de motor izquierdo
                  motord_T.setSpeed(mediod+dif);//velocidad de motor derecho
                  motord_T.run(BACKWARD);//polaridad de motor  derecho
                  //delay(200);*/
               } 
            }
            }
        }
   
}
   


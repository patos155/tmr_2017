
#include <AFMotor.h>
//define tipo de variable motor y puerto
AF_DCMotor motori(1); //motor izquierdo
AF_DCMotor motord(4);//motor derecho


//diferencia de velocidades para retomar la linea
int dif_ret=20;
//retraso de lecturas para regresar al centro
int ret=0;
//retraso para avanzar al centro
int alce=0;
//s1
int izq_ext=53;
//s2
int izq_int=51;
//s3
int centro=49;
//s4
int der_int=47;
//s5
int der_ext=45;
// lectura de sensores
int l1=0;
int l2=0;
int l3=0;
int l4=0;
int l5=0;
int neg=0;
int bco=1;
int ade_ord=200;
String dire="CE";

void setup() {
   Serial.begin(9600); 
   pinMode(izq_ext,INPUT);
   pinMode(izq_int,INPUT);
   pinMode(centro,INPUT);
   pinMode(der_int,INPUT);
   pinMode(der_ext,INPUT);
}

void loop() {

   //lectura de sensores bco/ngo
   l1=digitalRead(izq_ext);
   l2=digitalRead(izq_int);
   l3=digitalRead(centro);
   l4=digitalRead(der_int);
   l5=digitalRead(der_ext);



   Serial.println(l1);
   Serial.println(l2);
   Serial.println(l3);
   Serial.println(l4);
   Serial.println(l5);
   Serial.println("_____________________________________________");
   //delay(500);

    //motori.setSpeed(200);//velocidad de motor izquierdo
    //motori.run(FORWARD); //polaridad de motor izquierdo
    //motord.setSpeed(200);//velocidad de motor derecho
    //motord.run(FORWARD);//polaridad de motor  derecho

   
   //al centro
   if (l1==bco && l2==bco && l3==bco && l4==bco && l5==bco) {
          motori.setSpeed(0);//velocidad de motor izquierdo
          motori.run(RELEASE); //polaridad de motor izquierdo
          motord.setSpeed(0);//velocidad de motor derecho
          motord.run(RELEASE);//polaridad de motor  derecho
          dire="CE";
   }else {
       if (l1==bco && l2==bco && l3==neg && l4==bco && l5==bco){
          if (dire="CE"){
             motori.setSpeed(ade_ord);//velocidad de motor izquierdo
             motori.run(FORWARD); //polaridad de motor izquierdo
             motord.setSpeed(ade_ord);//velocidad de motor derecho
             motord.run(FORWARD);//polaridad de motor  derecho
             dire="CE";
          }else {
             if (dire="RD"){
                delay(alce);
                motori.setSpeed(ade_ord+dif_ret);//velocidad de motor izquierdo
                motori.run(FORWARD); //polaridad de motor izquierdo
                motord.setSpeed(ade_ord-(2*dif_ret));//velocidad de motor derecho          
                motord.run(FORWARD);//polaridad de motor  derecho
                delay(ret);  
                dire="CE";
             } else {
                delay(alce);
                motori.setSpeed(ade_ord-(2*dif_ret));//velocidad de motor izquierdo
                motori.run(FORWARD); //polaridad de motor izquierdo
                motord.setSpeed(ade_ord+dif_ret);//velocidad de motor derecho          
                motord.run(FORWARD);//polaridad de motor  derecho
                delay(ret);
                dire="CE";
             }
          }
       } else {
         // desviado a la derecha gira acelerando motor derecho
         if (l1==bco && l2==neg && l3==bco && l4==bco && l5==bco){
             motori.setSpeed(ade_ord-(2*dif_ret));//velocidad de motor izquierdo
             motori.run(FORWARD); //polaridad de motor izquierdo
             motord.setSpeed(ade_ord+dif_ret);//velocidad de motor derecho          
             motord.run(FORWARD);//polaridad de motor derecho
             dire="RD";
         } else {
             // desviado a la derecha gira acelerando motor izquierdo
             if (l1==bco && l2==bco && l3==bco && l4==neg && l5==bco){
                motori.setSpeed(ade_ord+dif_ret);//velocidad de motor izquierdo
                motori.run(FORWARD); //polaridad de motor izquierdo
                motord.setSpeed(ade_ord-(2*dif_ret));//velocidad de motor derecho          
                motord.run(FORWARD);//polaridad de motor  derecho
                dire="RI";
             } else{
                 if (l1==bco && l2==bco && l3==bco && l4==bco && l5==bco){
                   motori.setSpeed(0);//para
                   motori.run(RELEASE); //para
                   motord.setSpeed(0);//para
                   motord.run(RELEASE);//para
                   dire="CE";
                }
             }
         }
      } 
   }
}

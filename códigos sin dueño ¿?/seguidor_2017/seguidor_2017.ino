
#include <AFMotor.h>
//define tipo de variable motor y puerto
AF_DCMotor motori(2); //motor izquierdo
AF_DCMotor motord(4);//motor derecho


//retraso de lecturas para regresar al centro
int ret=500;
//retraso para avanzar al centro
int alce=0;
//s1
int izq_1=53;
//s2
int izq_2=51;
//s3
int izq_3=49;
//s4
int izq_centro=47;
//s5
int der_centro=45;
//s6
int der_6=43;
//s7
int der_7=41;
//s8
int der_8=39;
// arranca
int arre=1;
// lectura de sensores
int l1=0;
int l2=0;
int l3=0;
int l4=0;
int l5=0;
int l6=0;
int l7=0;
int l8=0;
int neg=1;
int bco=0;

//Potencias
int ade_ordi=180;
int medioi=150;
int ade_ordd=180;
int mediod=150;
//Velocidades
int VI=0;
int VD=0;
int reloj=0;
float velocidad_i=0;
float velocidad_d=0;
float porc_i=0;
float porc_d=0;
int cuantos_i=0;
int cuantos_d=0;
int vel_max=150;
int vel_med=150;
///////////




//diferencia de velocidades para retomar la linea
int dif_ret=70;
String dire="CE";


void setup() {
   Serial.begin(57600);
   attachInterrupt(3,interrupciond,RISING);
   attachInterrupt(2,interrupcioni,RISING);
   //Serial.begin(9600); 
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


void potencia_max(){
  //lectura sensor de volicidad
  reloj++;
  if (reloj>100){
      reloj=0;
      if (cuantos_i==0){
        porc_i=1.5;
      }else{
        porc_i=vel_max/cuantos_i;  
      }
      if (cuantos_d==0){
        porc_d=1.5;
      }else{
        porc_d=vel_max/cuantos_d;  
      }
      //Serial.print("porc_i : ");
      //Serial.println(porc_i);
      //Serial.print("porc_d : ");
      //Serial.println(porc_d);
      cuantos_i=0;
      cuantos_d=0;
      ade_ordi=ade_ordi*porc_i;
      ade_ordd=ade_ordd*porc_d;
      if (ade_ordi>250){
         ade_ordi=250;
      }
      if (ade_ordd>250){
         ade_ordd=250;
      }      
   }
   //Serial.println(reloj);
}

void potencia_med(){
  //lectura sensor de volicidad
  reloj++;
  if (reloj>100){
      reloj=0;
      if (cuantos_i==0){
        porc_i=1.5;
      }else{
        porc_i=vel_med/cuantos_i;  
      }
      if (cuantos_d==0){
        porc_d=1.5;
      }else{
        porc_d=vel_med/cuantos_d;  
      }
      //Serial.print("porc_i : ");
      //Serial.println(porc_i);
      //Serial.print("porc_d : ");
      //Serial.println(porc_d);
      cuantos_i=0;
      cuantos_d=0;
      medioi=medioi*porc_i;
      mediod=mediod*porc_d;
      if (ade_ordi>250){
         medioi=250;
      }
      if (ade_ordd>250){
         mediod=250;
      }      
   }
   //Serial.println(reloj);
}
void arranca(){
  motori.setSpeed(200);//velocidad_i de motor izquierdo
  motori.run(FORWARD); //polaridad de motor izquierdo
  motord.setSpeed(200);//velocidad de motor derecho          
  motord.run(FORWARD);//polaridad de motor  derecho
  delay(500);
}

void alto(){
  motori.setSpeed(10);//velocidad de motor izquierdo
  motori.run(BACKWARD); //polaridad de motor izquierdo
  motord.setSpeed(10);//velocidad de motor derecho          
  motord.run(BACKWARD);//polaridad de motor  derecho
  motori.setSpeed(0);//velocidad de motor izquierdo
  motori.run(RELEASE); //polaridad de motor izquierdo
  motord.setSpeed(0);//velocidad de motor derecho          
  motord.run(RELEASE);//polaridad de motor  derecho
  delay(100);
}

void interrupcioni()    // Funcion que se ejecuta durante cada interrupion
{
  cuantos_i++;           // Se incrementa en uno el contador
}

void interrupciond()    // Funcion que se ejecuta durante cada interrupion
{
  cuantos_d++;           // Se incrementa en uno el contador
}

void loop() {

    /*if (arre==1){
        arranca();
        arre=0;
    }*/

   potencia_med();
   Serial.println("____cuantos____________________");
   Serial.println(cuantos_i);
   Serial.println(cuantos_d);
    
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
   
   Serial.println(l1);
   Serial.println(l2);
   Serial.println(l3);
   Serial.println(l4);
   Serial.println(l5);
   Serial.println(l6);
   Serial.println(l7);
   Serial.println(l8);
   
   //delay(1000);

   //al centro
   /*motori.setSpeed(ade_ordi);//velocidad de motor izquierdo
   motori.run(FORWARD); //polaridad de motor izquierdo
   motord.setSpeed(ade_ordd);//velocidad de motor derecho
   motord.run(FORWARD);//polaridad de motor  derecho
   */
   if (l1==bco && l2==bco && l3==bco && l4==bco && l5==bco && l6==bco && l7==bco  && l8==bco){
       delay(300);
       alto();
   }else{  
     /*if (l1==bco && l2==bco && l3==bco && l4==neg && l5==neg && l6==bco && l7==bco  && l8==bco){ 
        motori.setSpeed(medioi);//velocidad de motor izquierdo
        motori.run(FORWARD); //polaridad de motor izquierdo
        motord.setSpeed(mediod);//velocidad de motor derecho
        motord.run(FORWARD);//polaridad de motor  derecho
     } else {*/
         // desviado a la derecha gira acelerando motor derecho
         if (l4==neg){
            //alto();
            motori.setSpeed(medioi);//velocidad de motor izquierdo
            motori.run(RELEASE); //polaridad de motor izquierdo
            motord.setSpeed(mediod);//velocidad de motor derecho          
            motord.run(FORWARD);//polaridad de motor derecho
         } else {
            if (l3==neg){
               //alto();
               motori.setSpeed(medioi-10);//velocidad de motor izquierdo
               motori.run(RELEASE); //polaridad de motor izquierdo
               motord.setSpeed(mediod);//velocidad de motor derecho          
               motord.run(FORWARD);//polaridad de motor derecho
            } else {
              if (l2==neg){
                  //alto();
                  motori.setSpeed(medioi-20);//velocidad de motor izquierdo
                  motori.run(RELEASE); //polaridad de motor izquierdo
                  motord.setSpeed(mediod);//velocidad de motor derecho          
                  motord.run(FORWARD);//polaridad de motor derecho
               } else {
                  if (l1==neg){
                     //alto();
                     motori.setSpeed(medioi-30);//velocidad de motor izquierdo
                     motori.run(RELEASE); //polaridad de motor izquierdo
                     motord.setSpeed(mediod);//velocidad de motor derecho          
                     motord.run(FORWARD);//polaridad de motor derecho
                  } else {
                      if (l5==neg){
                         //alto();
                         motori.setSpeed(medioi);//velocidad de motor izquierdo
                         motori.run(FORWARD); //polaridad de motor izquierdo
                         motord.setSpeed(mediod);//velocidad de motor derecho          
                         motord.run(RELEASE);//polaridad de motor  derecho
                      } else {
                          if (l6==neg){
                             //alto();
                             motori.setSpeed(medioi);//velocidad de motor izquierdo
                             motori.run(FORWARD); //polaridad de motor izquierdo
                             motord.setSpeed(mediod-10);//velocidad de motor derecho          
                             motord.run(RELEASE);//polaridad de motor  derecho
                          } else {
                             if (l7==neg){
                                //alto();
                                motori.setSpeed(medioi);//velocidad de motor izquierdo
                                motori.run(FORWARD); //polaridad de motor izquierdo
                                motord.setSpeed(mediod-20);//velocidad de motor derecho          
                                motord.run(RELEASE);//polaridad de motor  derecho
                             } else {
                                if (l5==neg){
                                   // alto();
                                    motori.setSpeed(medioi);//velocidad de motor izquierdo
                                    motori.run(FORWARD); //polaridad de motor izquierdo
                                    motord.setSpeed(mediod);//velocidad de motor derecho          
                                    motord.run(RELEASE);//polaridad de motor  derecho
                                }
                             }
                          }
                      }
                  }
               }
           }
        }
   }
}
   


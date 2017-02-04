
#include <AFMotor.h>
//define tipo de variable motor y puerto
AF_DCMotor motori(2); //motor izquierdo
AF_DCMotor motord(4);//motor derecho

///////////
int v1=0;
int v2=0;
int reloj=0;
int reloj2=0;
float velocidad=0;
float velocidad2=0;
int cuantos=0;
int cuantos2=0;
///////////
//retraso de lecturas para regresar al centro
int ret=500;
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
//ei
int ext_izq=43;
//ed
int ext_der=41;
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
int neg=0;
int bco=1;

//Potencias
int ade_ordi=0;
int medioi=0;
int ade_ordd=0;
int mediod=0;

//diferencia de velocidades para retomar la linea
int dif_ret=70;
String dire="CE";


void setup() {
   Serial.begin(9600); 
   pinMode(izq_ext,INPUT);
   pinMode(izq_int,INPUT);
   pinMode(centro,INPUT);
   pinMode(der_int,INPUT);
   pinMode(der_ext,INPUT);
}

void arranca(){
  motori.setSpeed(ade_ordi);//velocidad de motor izquierdo
  motori.run(FORWARD); //polaridad de motor izquierdo
  motord.setSpeed(ade_ordd);//velocidad de motor derecho          
  motord.run(FORWARD);//polaridad de motor  derecho
  delay(300);
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
  delay(300);
}


void loop() {

    if (arre==1){
        arranca();
        arre=0;
    }
   
   //lectura de sensores bco/ngo
   l1=digitalRead(izq_ext);
   l2=digitalRead(izq_int);
   l3=digitalRead(ext_izq);
   l4=digitalRead(centro);
   l5=digitalRead(ext_der);
   if (l5==0){
       l5=1;
   }else{
      l5=0;
   }
   l6=digitalRead(der_int);
   l7=digitalRead(der_ext);
   
   //lectura sensor de volicidad
   v1=digitalRead(52);
   v2=digitalRead(50);
  
   if ((millis()-reloj)>1000){
       reloj=millis();
       velocidad=cuantos*60/20;
       cuantos=0;
       reloj2=millis();
       velocidad2=cuantos2*60/20;
       cuantos2=0;
   }
     
    if (v1==0){
        cuantos=cuantos+1;
    }
    Serial.println("____motor derecho____________________");
    Serial.println(v1);
    Serial.println(reloj);
    Serial.println(cuantos);
    Serial.println(millis());
    Serial.println(velocidad);
    //Rueda izquierda
    if (v2==0){
        cuantos2=cuantos2+1;
    }
    Serial.println("________motor izquierdo_________");
    Serial.println(v2);
    Serial.println(reloj2);
    Serial.println(cuantos2);
    Serial.println(millis());
    Serial.println(velocidad2);

   Serial.println("____Sensores de Izq. a Derecha_____");
   Serial.println(l1);
   Serial.println(l2);
   Serial.println(l3);
   Serial.println(l4);
   Serial.print("____");
   Serial.println(l5);
   Serial.println(l6);
   Serial.println(l7);
   
   delay(5000);

   //al centro
   if (l1==bco && l2==bco && l3==bco && l4==bco && l5==bco && l6==bco && l7==bco) {
          motori.setSpeed(medioi);//velocidad de motor izquierdo
          motori.run(FORWARD); //polaridad de motor izquierdo
          motord.setSpeed(mediod);//velocidad de motor derecho
          motord.run(FORWARD);//polaridad de motor  derecho
          //dire="CE";
   }else {
       if (l1==bco && l2==bco && l3==bco && l4==neg && l5==bco && l6==bco && l7==bco){
          //if (dire="CE"){
             motori.setSpeed(ade_ordi);//velocidad de motor izquierdo
             motori.run(FORWARD); //polaridad de motor izquierdo
             motord.setSpeed(ade_ordd);//velocidad de motor derecho
             motord.run(FORWARD);//polaridad de motor  derecho
             //dire="CE";
          
       } else {
         // desviado a la derecha gira acelerando motor derecho
         if (l1==bco && l2==bco && l3==neg && l4==neg && l5==bco && l6==bco && l7==bco){
             //alto();
             motori.setSpeed(medioi);//velocidad de motor izquierdo
             motori.run(FORWARD); //polaridad de motor izquierdo
             motord.setSpeed(ade_ordd);//velocidad de motor derecho          
             motord.run(FORWARD);//polaridad de motor derecho
             //delay(50);
             //dire="RD";
         } else {
             // desviado a la izquierda gira acelerando motor izquierdo
             if (l1==bco && l2==bco && l3==bco && l4==neg && l5==neg && l6==bco && l7==bco){
                //alto();
                motori.setSpeed(ade_ordi);//velocidad de motor izquierdo
                motori.run(FORWARD); //polaridad de motor izquierdo
                motord.setSpeed(mediod);//velocidad de motor derecho          
                motord.run(FORWARD);//polaridad de motor  derecho
                //delay(50);
                //dire="RI";
             }
          }
         
      } 
   }
}

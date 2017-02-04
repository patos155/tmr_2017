//Incluimos la libreria SD.
#include <SD.h>
//#include <QTRSensors.h>
#include <AFMotor.h>

//define motores por cada puerto
AF_DCMotor motori_D(4); //motor izquierdo delantero
AF_DCMotor motori_T(1); //motor izquierdo trasero
AF_DCMotor motord_D(2);   //motor derecho
AF_DCMotor motord_T(3);   //motor izquierdo

// TCS230 color recognition sensor 
// Sensor connection pins to Arduino are shown in comments
/*
Color Sensor1 (Izquierdo)     Arduino
-----------      --------
 VCC               5V
 GND               GND
 s0                31
 s1                30
 s2                24
 s3                26
 OUT               22
 OE                GND
Color Sensor2  (Derecho)    Arduino
-----------      --------
 VCC               5V
 GND               GND
 s0                34
 s1                36
 s2                40
 s3                42
 OUT               38
 OE                GND
*/

// inicializacion de variables para los pins de sensor 1 (izquierdo)
const int s1_0 = 31;  
const int s1_1 = 30;  
const int s1_2 = 24;  
const int s1_3 = 26;  
const int out_1 = 22;   

// inicializacion de variables para los pins de sensor 2 (derecho)
const int s2_0 = 34;  
const int s2_1 = 36;  
const int s2_2 = 40;  
const int s2_3 = 42;  
const int out_2 = 38;   

// Variables  sensor 1
int red1 = 0;  
int green1 = 0;  
int blue1 = 0;  
    
// Variables  sensor 2
int red2 = 0;  
int green2 = 0;  
int blue2 = 0;  
int des = 10;

// lectura de colores encontrados en sensor 1
int ler_vde_1=30;
int leg_vde_1=25;
int leb_vde_1=30;

// lectura de colores encontrados en sensor 2
int ler_vde_2=30;
int leg_vde_2=25;
int leb_vde_2=30;

// colores encontrados en sensor 1
int enc_vde_1=0;
int mem_vde_1=0;

// colores encontrados en sensor 2
int enc_vde_2=0;
int mem_vde_2=0;
int tie_mem=0;

//pines para sensor infrarojo (b/n)
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
int medioi=100;
int ade_ordd=200;
int mediod=100;
int dife=7;
// dirección y tiempo de regreso
int tr=40;
int rl=100;
int al=60;
String dire="";

// Guardamos en que entrada de Arduino esta conectado el pin CS del modulo.
const int chipSelect = 44;

//Variables sensor ultrasonico 
const int trigPin = 49; // Pin disparador. Se puede usar otro pin digital
const int echoPin = 48; // Pin eco. Se puede usar otro pin digital
long duration, inches, cm; // Declara variables


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

  //Pines s0,s1,s2 y s3 como salidas para el RGB sensor1  
  pinMode(s1_0, OUTPUT);  
  pinMode(s1_1, OUTPUT);  
  pinMode(s1_2, OUTPUT);  
  pinMode(s1_3, OUTPUT);
  
  //Pines s0,s1,s2 y s3 como salidas para el RGB sensor2  
  pinMode(s2_0, OUTPUT);  
  pinMode(s2_1, OUTPUT);  
  pinMode(s2_2, OUTPUT);  
  pinMode(s2_3, OUTPUT);
  
  // pin OUT_1 como entrada para el sensor 1  
  pinMode(out_1, INPUT);
  
  // pin OUT_2 como entrada para el sensor 1  
  pinMode(out_1, INPUT);  
  
  // S0 y S1 en alto color base rojo para sensor 1  
  digitalWrite(s1_0, HIGH);  
  digitalWrite(s1_1, HIGH);
  // S0 y S1 en alto color base rojo para sensor 2  
  digitalWrite(s2_0, HIGH);  
  digitalWrite(s2_1, HIGH);  

      
   // El pin CS por defecto de la placa arduino debe ser configurado como salida
   // aunque no se use (10 en la mayoria de las placas, 53 en Arduino Mega).
   pinMode(53, OUTPUT);
   // Si ha habido error al leer la tarjeta informamos por el puerto serie.
   if (!SD.begin(chipSelect)){
      Serial.println("Error al leer la tarjeta.");
      return;
   }

   // Sensor ultrasonico
   pinMode(trigPin, OUTPUT); // Establece pin como salida
   pinMode(echoPin, INPUT); // Establece pin como entrada
   digitalWrite(trigPin, LOW); // Pone el pin a un estado logico bajo
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
   //Serial.println("____ALTO____________________");
   delay(400);
}
void regresa(){
   motori_D.setSpeed(100);//velocidad de motor izquierdo
   motori_D.run(BACKWARD); //polaridad de motor izquierdo
   motord_D.setSpeed(100);//velocidad de motor derecho
   motord_D.run(BACKWARD);//polaridad de motor  derecho
   motori_T.setSpeed(100);//velocidad de motor izquierdo
   motori_T.run(BACKWARD); //polaridad de motor izquierdo
   motord_T.setSpeed(100);//velocidad de motor derecho
   motord_T.run(BACKWARD);//polaridad de motor  derecho
   //Serial.println("____regresa____________________");
   delay(700);
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
   
   /*
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
   */
         
   //------------------------------------------------------------------------------
   // color en sensor 1 
   enc_vde_1=0;
   // color en sensor 1 
   enc_vde_2=0;
   
   // Abrimos el fichero donde vamos a guardar los datos (Si no existe se crea automaticamente).
   File dataFile = SD.open("valores.txt", FILE_WRITE);

   // determina el tiempo de lectura para cada color (rojo, azul, verde
   
   //------------------------------------------------------------------------------
     
   // Si el fichero es correcto escribimos en el.
   if (dataFile) {
      dataFile.print(millis());
      dataFile.print(",");
      dataFile.print(l1);
      dataFile.print(l2);
      dataFile.print(l3);
      dataFile.print(l4);
      dataFile.print(l5);
      dataFile.print(l6);
      dataFile.print(l7);
      dataFile.print(l8);
      if (enc_vde_1==1)
        {  
          dataFile.println(" ");
          dataFile.print(" -    VERDE sensor 1 ");
        }
      if (enc_vde_2==1)
        {  
          dataFile.println(" ");
          dataFile.print(" -    VERDE sensor 2 ");  
        }
      
   }else{
      Serial.println("Error al escribir en valores.txt");
   }
   //delay(4000);
   int suma=l1+l2+l3+l4+l5+l6+l7+l8;
   int sum_izq=l1+l2+l3+l4;
   int sum_der=l5+l6+l7+l8;
   cm=100;


   if (l1==bco && l2==bco && l3==bco && l4==bco && l5==bco && l6==bco && l7==bco  && l8==bco){
      dire="C0";
      dataFile.print(",C0.");
      motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
      motori_D.run(FORWARD); //polaridad de motor izquierdo
      motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
      motord_D.run(FORWARD);//polaridad de motor  derecho
      motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
      motori_T.run(FORWARD); //polaridad de motor izquierdo
      motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
      motord_T.run(FORWARD);//polaridad de motor  derecho
      ultra();
      dataFile.println(cm);
   }
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
      ultra();
      dire="C1";
      dataFile.print(",C1.");
      motori_D.setSpeed(ade_ordi+20);//velocidad de motor izquierdo
      motori_D.run(FORWARD); //polaridad de motor izquierdo
      motord_D.setSpeed(ade_ordd+20);//velocidad de motor derecho
      motord_D.run(FORWARD);//polaridad de motor  derecho
      motori_T.setSpeed(ade_ordi+20);//velocidad de motor izquierdo
      motori_T.run(FORWARD); //polaridad de motor izquierdo
      motord_T.setSpeed(ade_ordd+20);//velocidad de motor derecho
      motord_T.run(FORWARD);//polaridad de motor  derecho
      dataFile.println(cm);
   } 
   // desviado a la derecha gira acelerando motor derecho
   if ((l1==bco && l2==bco) && (l3==neg || l4==neg) && (l5==bco && l6==bco && l7==bco  && l8==bco)){
      dire="C2";
      dataFile.print(",C2.");
      motori_D.setSpeed(0);//medioi velocidad de motor izquierdo
      motori_D.run(BACKWARD); //polaridad de motor izquierdo
      motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
      motord_D.run(FORWARD);//polaridad de motor  derecho
      motori_T.setSpeed(0);//medioi velocidad de motor izquierdo
      motori_T.run(BACKWARD); //polaridad de motor izquierdo
      motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
      motord_T.run(FORWARD);//polaridad de motor  derecho
   }
   if ((l1==bco) && (l2==neg || l3==neg) && (l4==bco && l5==bco && l6==bco && l7==bco  && l8==bco)){
      //Serial.println("C3");
      dire="C3";
      dataFile.print(",C3.");
      motori_D.setSpeed(medioi+(dife));//velocidad de motor izquierdo
      motori_D.run(BACKWARD); //polaridad de motor izquierdo
      motord_D.setSpeed(ade_ordd+(dife));//velocidad de motor derecho
      motord_D.run(FORWARD);//polaridad de motor  derecho
      motori_T.setSpeed(medioi+(dife));//velocidad de motor izquierdo
      motori_T.run(BACKWARD); //polaridad de motor izquierdo
      motord_T.setSpeed(ade_ordd+(dife));//velocidad de motor derecho
      motord_T.run(FORWARD);//polaridad de motor  derecho
   }
   if (((l1==neg || l2==neg) && (l3==bco && l4==bco && l5==bco && l6==bco && l7==bco  && l8==bco)) || (sum_izq>2 && sum_der<2)) {
      dire="C4";
      dataFile.print(",C4.");
      motori_D.setSpeed(medioi+(dife*2));//velocidad de motor izquierdo
      motori_D.run(BACKWARD); //polaridad de motor izquierdo
      motord_D.setSpeed(ade_ordd+(dife*2));//velocidad de motor derecho
      motord_D.run(FORWARD);//polaridad de motor  derecho
      motori_T.setSpeed(medioi+(dife*2));//velocidad de motor izquierdo
      motori_T.run(BACKWARD); //polaridad de motor izquierdo
      motord_T.setSpeed(ade_ordd+(dife*2));//velocidad de motor derecho
      motord_T.run(FORWARD);//polaridad de motor  derecho
   }
   if ((l1==bco && l2==bco && l3==bco && l4==bco) && (l5==neg || l6==neg) && (l7==bco  && l8==bco)){
      dire="C5";
      dataFile.print(",C5.");
      motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
      motori_D.run(FORWARD); //polaridad de motor izquierdo
      motord_D.setSpeed(0);// mediod velocidad de motor derecho
      motord_D.run(BACKWARD);//polaridad de motor  derecho
      motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
      motori_T.run(FORWARD); //polaridad de motor izquierdo
      motord_T.setSpeed(0);//mediod velocidad de motor derecho
      motord_T.run(BACKWARD);//polaridad de motor  derecho
      //delay(200);*/
   }
   if ((l1==bco && l2==bco && l3==bco && l4==bco && l5==bco) && (l6==neg || l7==neg)  && (l8==bco)){
      dire="C6";
      dataFile.print(",C6.");
      motori_D.setSpeed(ade_ordi+(dife));//velocidad de motor izquierdo
      motori_D.run(FORWARD); //polaridad de motor izquierdo
      motord_D.setSpeed(mediod+(dife));//velocidad de motor derecho
      motord_D.run(BACKWARD);//polaridad de motor  derecho
      motori_T.setSpeed(ade_ordi+(dife));//velocidad de motor izquierdo
      motori_T.run(FORWARD); //polaridad de motor izquierdo
      motord_T.setSpeed(mediod+(dife));//velocidad de motor derecho
      motord_T.run(BACKWARD);//polaridad de motor  derecho
   }
   if (((l1==bco && l2==bco && l3==bco && l4==bco && l5==bco && l6==bco) && (l7==neg  || l8==neg))  || (sum_izq<2 && sum_der>2)){
      dire="C7";
      dataFile.print(",C7.");
      motori_D.setSpeed(ade_ordi+(dife*2));//velocidad de motor izquierdo
      motori_D.run(FORWARD); //polaridad de motor izquierdo
      motord_D.setSpeed(mediod+(dife*2)+20);//velocidad de motor derecho
      motord_D.run(BACKWARD);//polaridad de motor  derecho
      motori_T.setSpeed(ade_ordi+(dife*2));//velocidad de motor izquierdo
      motori_T.run(FORWARD); //polaridad de motor izquierdo
      motord_T.setSpeed(mediod+(dife*2)+20);//velocidad de motor derecho
      motord_T.run(BACKWARD);//polaridad de motor  derecho
      //delay(300);
   } 
   if (suma>5){
       dataFile.print("alto");
       dataFile.print("regresa");
       dataFile.print("alto");
       alto();
       regresa();
       alto();
       //-----------------------------busca color-------------------------------------------------------------------
       
       tie_mem=millis();
       //while (millis()<=tie_mem+1000){
           color(); 
       //}
       if (enc_vde_1==1)
         {  
           dataFile.println(" ");
           dataFile.print(" -    VERDE sensor 1 ");
           mem_vde_1=1;
         }
       if (enc_vde_2==1)
         {  
           dataFile.println(" ");
           dataFile.print(" -    VERDE sensor 2 ");  
           mem_vde_2=1;
         }
       
       //------------------ muestra la intensidad (los milisegunods que tardo en la lectura para el rojo
       dataFile.print(" R1 ");  
       dataFile.print(red1, DEC);  
       // muestra la intensidad (los milisegunods que tardo en la lectura para el verde
       dataFile.print(" G1 ");  
       dataFile.print(green1, DEC);  
       // muestra la intensidad (los milisegunods que tardo en la lectura para el blue
       dataFile.print(" B1 ");  
       dataFile.print(blue1, DEC);  
       // determina el color sensor 1
       if (enc_vde_1==1)
         {  
           dataFile.print(" -    VERDE sensor 1 ");  
         }
       // muestra la intensidad (los milisegunods que tardo en la lectura para el rojo
       dataFile.print(" R2 ");  
       dataFile.print(red2, DEC);  
       // muestra la intensidad (los milisegunods que tardo en la lectura para el verde
       dataFile.print(" G2 ");  
       dataFile.print(green2, DEC);  
       // muestra la intensidad (los milisegunods que tardo en la lectura para el blue
       dataFile.print(" B2 ");  
       dataFile.print(blue2, DEC);  
       if (enc_vde_2==1)
         {  
           dataFile.print(" -    VERDE sensor 2 ");  
         }

       
       //------------------------------------------------------------------------------------------------
       
       dataFile.print("+++++");
       dataFile.print(mem_vde_1);
       dataFile.print(mem_vde_2);
       //adelante
       motori_D.setSpeed(100);//velocidad de motor izquierdo
       motori_D.run(FORWARD); //polaridad de motor izquierdo
       motord_D.setSpeed(100);//velocidad de motor derecho
       motord_D.run(FORWARD);//polaridad de motor  derecho
       motori_T.setSpeed(100);//velocidad de motor izquierdo
       motori_T.run(FORWARD); //polaridad de motor izquierdo
       motord_T.setSpeed(100);//velocidad de motor derecho
       motord_T.run(FORWARD);//polaridad de motor  derecho
       delay(700);

       if (mem_vde_1==1){
          dire="+izquierda";
          dataFile.print("+izquierda");
          motori_D.setSpeed(medioi+(dife*2));//velocidad de motor izquierdo
          motori_D.run(BACKWARD); //polaridad de motor izquierdo
          motord_D.setSpeed(ade_ordd+(dife*2));//velocidad de motor derecho
          motord_D.run(FORWARD);//polaridad de motor  derecho
          motori_T.setSpeed(medioi+(dife*2));//velocidad de motor izquierdo
          motori_T.run(BACKWARD); //polaridad de motor izquierdo
          motord_T.setSpeed(ade_ordd+(dife*2));//velocidad de motor derecho
          motord_T.run(FORWARD);//polaridad de motor  derecho
          mem_vde_1=0;
          delay(1100);
       }
       if (mem_vde_2==1){
          dire="+derecha";
          dataFile.print("+derecha");
          motori_D.setSpeed(ade_ordi+(dife*2));//velocidad de motor izquierdo
          motori_D.run(FORWARD); //polaridad de motor izquierdo
          motord_D.setSpeed(mediod+(dife*2)+20);//velocidad de motor derecho
          motord_D.run(BACKWARD);//polaridad de motor  derecho
          motori_T.setSpeed(ade_ordi+(dife*2));//velocidad de motor izquierdo
          motori_T.run(FORWARD); //polaridad de motor izquierdo
          motord_T.setSpeed(mediod+(dife*2)+20);//velocidad de motor derecho
          motord_T.run(BACKWARD);//polaridad de motor  derecho
          delay(1400);
          mem_vde_2=0;
       }
   }
   
   if(cm<=5){
      alto();
      //  --||| regresa
      motori_D.setSpeed(190);
      motori_D.run(BACKWARD);
      motord_D.setSpeed(190);
      motord_D.run(BACKWARD);
      motori_T.setSpeed(190);
      motori_T.run(BACKWARD);
      motord_T.setSpeed(190);
      motord_T.run(BACKWARD);
      delay(800);
      // <<--- izquierda
      motori_D.setSpeed(160);
      motori_D.run(BACKWARD);
      motord_D.setSpeed(190);
      motord_D.run(FORWARD);
      motori_T.setSpeed(160);
      motori_T.run(BACKWARD);
      motord_T.setSpeed(190);
      motord_T.run(FORWARD);
      delay(1400);
      // frente
      motori_D.setSpeed(100);
      motori_D.run(FORWARD);
      motord_D.setSpeed(100);
      motord_D.run(FORWARD);
      motori_T.setSpeed(100);
      motori_T.run(FORWARD);
      motord_T.setSpeed(100);
      motord_T.run(FORWARD);
      delay(3200);
      //-->> derecha
      motord_D.setSpeed(160);
      motord_D.run(BACKWARD);
      motori_D.setSpeed(190);
      motori_D.run(FORWARD);
      motord_T.setSpeed(160);
      motord_T.run(BACKWARD);
      motori_T.setSpeed(190);
      motori_T.run(FORWARD);
      delay(1000);
      // frente
      motori_D.setSpeed(100);
      motori_D.run(FORWARD);
      motord_D.setSpeed(100);
      motord_D.run(FORWARD);
      motori_T.setSpeed(100);
      motori_T.run(FORWARD);
      motord_T.setSpeed(100);
      motord_T.run(FORWARD);
      delay(2500);
      //-->> derecha
      motord_D.setSpeed(160);
      motord_D.run(BACKWARD);
      motori_D.setSpeed(190);
      motori_D.run(FORWARD);
      motord_T.setSpeed(160);
      motord_T.run(BACKWARD);
      motori_T.setSpeed(190);
      motori_T.run(FORWARD);
      delay(1200);
      // frente
      motori_D.setSpeed(100);
      motori_D.run(FORWARD);
      motord_D.setSpeed(100);
      motord_D.run(FORWARD);
      motori_T.setSpeed(100);
      motori_T.run(FORWARD);
      motord_T.setSpeed(100);
      motord_T.run(FORWARD);
      delay(2300);
      // <<--- izquierda
      motori_D.setSpeed(160);
      motori_D.run(BACKWARD);
      motord_D.setSpeed(190);
      motord_D.run(FORWARD);
      motori_T.setSpeed(160);
      motori_T.run(BACKWARD);
      motord_T.setSpeed(190);
      motord_T.run(FORWARD);
      delay(1200);
      // frente
      motori_D.setSpeed(100);
      motori_D.run(FORWARD);
      motord_D.setSpeed(100);
      motord_D.run(FORWARD);
      motori_T.setSpeed(100);
      motori_T.run(FORWARD);
      motord_T.setSpeed(100);
      motord_T.run(FORWARD);
      delay(500);
      
   }
   // Cerramos el archivo.
   dataFile.println(".");
   dataFile.close();   
}

   
// Lectura de colores rojo,azul y verde
void color()  
{   
    // pin s2 en bajo, s3 en bajo (rojo)
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
   
    // color verde en sensor 1
    if ((red1>=ler_vde_1-des && red1<=ler_vde_1+des) && (green1>=leg_vde_1-des && green1<=leg_vde_1+des) && (blue1>=leb_vde_1-des && blue1<=leb_vde_1+des)){
         enc_vde_1=1;  
       }
    // color verde en sensor 2
    if ((red2>=ler_vde_2-des && red2<=ler_vde_2+des) && (green2>=leg_vde_2-des && green2<=leg_vde_2+des) && (blue2>=leb_vde_2-des && blue2<=leb_vde_2+des)){
        enc_vde_2=1;  
      }
}

void ultra(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //Devuelve la longitud del pulso del pin Echo en us
  // Imprime valores por el puerto serie:
  // Convierte el tiempo de recepción del eco en distancia:
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
}
// Calcula la distancia en pulgadas
long microsecondsToInches(long microseconds) {
    return microseconds/148;
}
// Calcula la distancia en cm
long microsecondsToCentimeters(long microseconds) {
    return microseconds/58;
} 

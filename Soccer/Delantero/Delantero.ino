<<<<<<< Updated upstream
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
/* Serial.println("Sensor_centro");
 Serial.println(val_c);   
 Serial.println("Sensor_izquierdo");
 Serial.println(val_i);
 Serial.println("Sensor_derecho");
 Serial.println(val_d);
 Serial.println("Sensor_izquierdo_trasero");
 Serial.println(val_i_t);
 Serial.println("Sensor_derecho_trasero");
 Serial.println(val_d_t);*/
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
  
  //         delay(1000); 
=======
// TCS230 color recognition sensor 
// Sensor connection pins to Arduino are shown in comments
/*
Color Sensor1      Arduino delantero derecho
-----------      --------
 VCC               5V
 GND               GND
 s0                46(8)
 s1                48(9)
 s2                50(12)
 s3                52(11)
 OUT               44(10)
 OE                GND
Color Sensor2      Arduino trasero izquierdo
-----------      --------
 VCC               5V
 GND               GND
 s0                22(8)
 s1                24(9)
 s2                26(12)
 s3                28(11)
 OUT               30(10)
 OE                GND
 */
 #include <AFMotor.h>
AF_DCMotor motori(1);
AF_DCMotor motord(3);
AF_DCMotor motort(4);
//////////////////////////////////////////////////////////////////////////
//INRARROJOS
const int sen_c = A14;//sensor centro 
const int sen_i = A13;//sensor izquierdo
const int sen_d = A15;//sensor derecho
const int sen_d_t = A11;//sensor derecho trasero
const int sen_i_t = A10;//sensor izquierdo trasero
int val_c = 0; 
int val_i = 0;
int val_d = 0;
int val_i_t = 0;
int val_d_t = 0;
/////////////////////////////////////////////////////////////////////////

//RGB
// inicializacion de variables para los pins de sensor 1 delantero derecho
const int s1_0 = 46;  
const int s1_1 = 48;  
const int s1_2 = 50;  
const int s1_3 = 52;  
const int out_1 =44;   

// inicializacion de variables para los pins de sensor 2 trasero izquierdo
const int s2_0 = 22;  
const int s2_1 = 24;  
const int s2_2 = 26;  
const int s2_3 = 28;  
const int out_2 = 30;   

// Variables  sensor 1 delantero
int red1 = 0;  
int green1 = 0;  
int blue1 = 0;  
    
// Variables  sensor 2 trasero
int red2 = 0;  
int green2 = 0;  
int blue2 = 0;  
int des = 5 ;

// lectura de colores encontrados en sensor 1 delantero
int ler_bco_1=5;
int leg_bco_1=3;
int leb_bco_1=4;

int ler_ngo_1=32;
int leg_ngo_1=23;
int leb_ngo_1=24;

int ler_vde_1=52;
int leg_vde_1=40;
int leb_vde_1=43;
// lectura de colores encontrados en sensor 2 trasero
int ler_bco_2=4;
int leg_bco_2=5;
int leb_bco_2=3;

int ler_ngo_2=10;
int leg_ngo_2=10;
int leb_ngo_2=10;

int ler_vde_2=25;
int leg_vde_2=24;
int leb_vde_2=23;
// colores encontrados en sensor 1 delantero
int enc_bco_1=0;
int enc_ngo_1=0;
int enc_vde_1=0;
// colores encontrados en sensor 2 trasero
int enc_bco_2=0;
int enc_ngo_2=0;
int enc_vde_2=0;

void setup()   
{  
  //velocidad del puerto serie
  Serial.begin(9600); 
  ////////////////////////////////////////////////////////////////////////////////
  //infrarrojos
 pinMode(sen_c,INPUT);
 pinMode(sen_i,INPUT);
 pinMode(sen_d,INPUT);
 pinMode(sen_i_t,INPUT);
 pinMode(sen_d_t,INPUT);
  ////////////////////////////////////////////////////////////////////////////////
  //RGB
  //Pines s0,s1,s2 y s3 como salidas para el sensor1  delantero
  pinMode(s1_0, OUTPUT);  
  pinMode(s1_1, OUTPUT);  
  pinMode(s1_2, OUTPUT);  
  pinMode(s1_3, OUTPUT);
  
  //Pines s0,s1,s2 y s3 como salidas para el sensor2  trasero
  pinMode(s2_0, OUTPUT);  
  pinMode(s2_1, OUTPUT);  
  pinMode(s2_2, OUTPUT);  
  pinMode(s2_3, OUTPUT);
  
  // pin OUT_1 como entrada para el sensor 1  delantero
  pinMode(out_1, INPUT);
  
  // pin OUTT_2 como entrada para el sensor 2 trasero
  pinMode(out_2, INPUT);  
  
  // S0 y S1 en alto color base rojo para sensor 1  delantero
  digitalWrite(s1_0, HIGH);  
  digitalWrite(s1_1, HIGH);
  // S0 y S1 en alto color base rojo para sensor 2  trasero
  digitalWrite(s2_0, HIGH);  
  digitalWrite(s2_1, HIGH);  
}  
    
void loop(){
  /////////////////////////////////////////////////////////////////
  val_c = analogRead(sen_c);//sensor centro
  val_i = analogRead(sen_i);//sensor izquierdo
  val_d = analogRead(sen_d);//sensor derecho
  val_i_t = analogRead(sen_i_t);//sensor izquierdo trasero
  val_d_t = analogRead(sen_d_t);// sensor derecho trasero
  ////////////////////////////////////////////////////////////////
/*Serial.println("Sensor_centro");
 Serial.println(val_c);   
 Serial.println("Sensor_izquierdo");
 Serial.println(val_i);
 Serial.println("Sensor_derecho");
 Serial.println(val_d);
 Serial.println("Sensor_izquierdo_trasero");
 Serial.println(val_i_t);
 Serial.println("Sensor_derecho_trasero");
 Serial.println(val_d_t);*/


    // color en sensor 1 
    enc_bco_1=0;
    enc_ngo_1=0;
    enc_vde_1=0;
    // color en sensor 2
    enc_bco_2=0;
    enc_ngo_2=0;
    enc_vde_2=0;
  
  // determina el tiempo de lectura para cada color (rojo, azul, verde)
  color(); 
  if(enc_vde_1==1 || enc_vde_2==1){
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
    delay(190);
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
    motori.setSpeed(200);
    motori.run(BACKWARD);
    motord.setSpeed(250);
    motord.run(BACKWARD);
    motort.setSpeed(250);
    motort.run(FORWARD);
   }
  }
   if(enc_bco_1==1){
    motori.setSpeed(200);
    motori.run(BACKWARD);
    motord.setSpeed(200);
    motord.run(BACKWARD);
    motort.setSpeed(250);
    motort.run(BACKWARD);
   }
   if(enc_bco_2==1){
    motori.setSpeed(250);
    motori.run(FORWARD);
    motord.setSpeed(250);
    motord.run(FORWARD);
    motort.setSpeed(250);
    motort.run(FORWARD);
   }
   if(enc_ngo_1==1){
    motori.setSpeed(200);
    motori.run(BACKWARD);
    motord.setSpeed(200);
    motord.run(BACKWARD);
    motort.setSpeed(250);
    motort.run(BACKWARD);
   }
   if(enc_ngo_2==1){
    motori.setSpeed(250);
    motori.run(FORWARD);
    motord.setSpeed(250);
    motord.run(FORWARD);
    motort.setSpeed(250);
    motort.run(FORWARD);
   }
    delay(1000);
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

    // muestra la intensidad (los milisegunods que tardo en la lectura para el rojo
  Serial.print("R1 Intensity:");  
  Serial.println(red1, DEC);  
  // muestra la intensidad (los milisegunods que tardo en la lectura para el verde
  Serial.print(" G1 Intensity: ");  
  Serial.println(green1, DEC);  
  // muestra la intensidad (los milisegunods que tardo en la lectura para el blue
  Serial.print(" B1 Intensity : ");  
  Serial.println(blue1, DEC);  
  //Serial.println();  

  // determina el color sensor 1 delantero derecho
  if (enc_bco_1==1)
     {  
       Serial.println(" -   BLANCO sensor_delantero ");  
     }
  if (enc_ngo_1==1)
     {  
       Serial.println(" -    NEGRO sensor_delantero ");  
     }
  if (enc_vde_1==1)
     {  
       Serial.println(" -    VERDE sensor _delantero ");  
     }
// muestra la intensidad (los milisegunods que tardo en la lectura para el rojo
  Serial.print("R2 Intensity:");  
  Serial.println(red2, DEC);  
  // muestra la intensidad (los milisegunods que tardo en la lectura para el verde
  Serial.print(" G2 Intensity: ");  
  Serial.println(green2, DEC);  
  // muestra la intensidad (los milisegunods que tardo en la lectura para el blue
  Serial.print(" B2 Intensity : ");  
  Serial.println(blue2, DEC);  
  //Serial.println();  

  // determina el color sensor 2 trasero izquierdo
  if (enc_bco_2==1)
     {  
       Serial.println(" -   BLANCO sensor_trasero ");  
     }
  if (enc_ngo_2==1)
     {  
       Serial.println(" -    NEGRO sensor_trasero ");  
     }
  if (enc_vde_2==1)
     {  
       Serial.println(" -    VERDE sensor_trasero ");  
     }

    
    // colores en sensor 1
    if ((red1>=ler_bco_1-des && red1<=ler_bco_1+des) && (green1>=leg_bco_1-des && green1<=leg_bco_1+des) && (blue1>=leb_bco_1-des && blue1<=leb_bco_1+des)){
        enc_bco_1=1;  
      Serial.println("Blanco_sensor_delantero");
      }
    if ((red1>=ler_ngo_1-des && red1<=ler_ngo_1+des) && (green1>=leg_ngo_1-des && green1<=leg_ngo_1+des) && (blue1>=leb_ngo_1-des && blue1<=leb_ngo_1+des)){
        enc_ngo_1=1;  
      Serial.println("Negro_sensor_delantero");
      }
   if ((red1>=ler_vde_1-des && red1<=ler_vde_1+des) && (green1>=leg_vde_1-des && green1<=leg_vde_1+des) && (blue1>=leb_vde_1-des && blue1<=leb_vde_1+des)){
        enc_vde_1=1;  
      Serial.println("Verde_sensor_delantero");
      }
    // colores en sensor 2
    if ((red2>=ler_bco_2-des && red2<=ler_bco_2+des) && (green2>=leg_bco_2-des && green2<=leg_bco_2+des) && (blue2>=leb_bco_2-des && blue2<=leb_bco_2+des)){
        enc_bco_2=1;  
        Serial.println("Blanco_sensor_trasero");
      }
    if ((red2>=ler_ngo_2-des && red2<=ler_ngo_2+des) && (green2>=leg_ngo_2-des && green2<=leg_ngo_2+des) && (blue2>=leb_ngo_2-des && blue2<=leb_ngo_2+des)){
        enc_ngo_2=1;  
       Serial.println("Negro_sensor_trasero");
      }
   if ((red2>=ler_vde_2-des && red2<=ler_vde_2+des) && (green2>=leg_vde_2-des && green2<=leg_vde_2+des) && (blue2>=leb_vde_2-des && blue2<=leb_vde_2+des)){
        enc_vde_2=1;  
        Serial.println("Verde_sensor_trasero");
      }

      
>>>>>>> Stashed changes
}

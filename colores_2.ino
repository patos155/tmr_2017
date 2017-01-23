// TCS230 color recognition sensor 
// Sensor connection pins to Arduino are shown in comments
/*
Color Sensor1      Arduino
-----------      --------
 VCC               5V
 GND               GND
 s0                31(8)
 s1                33(9)
 s2                35(12)
 s3                37(11)
 OUT               39(10)
 OE                GND

Color Sensor2      Arduino
-----------      --------
 VCC               5V
 GND               GND
 s0                30(8)
 s1                32(9)
 s2                34(12)
 s3                36(11)
 OUT               38(10)
 OE                GND


 
*/


// inicializacion de variables para los pins de sensor 1 
const int s1_0 = 52;  
const int s1_1 = 50;  
const int s1_2 = 48;  
const int s1_3 = 46;  
const int out_1 = 44;   

// inicializacion de variables para los pins de sensor 2 
const int s2_0 = 31;  
const int s2_1 = 33;  
const int s2_2 = 35;  
const int s2_3 = 37;  
const int out_2 = 39;   

// Variables  sensor 1
int red1 = 0;  
int green1 = 0;  
int blue1 = 0;  
    
// Variables  sensor 2
int red2 = 0;  
int green2 = 0;  
int blue2 = 0;  
int des = 4;

// lectura de colores encontrados en sensor 1
int ler_bco_1=5;
int leg_bco_1=3;
int leb_bco_1=4;

int ler_ngo_1=33;
int leg_ngo_1=38;
int leb_ngo_1=29;

int ler_vde_1=24;
int leg_vde_1=16;
int leb_vde_1=14;

int ler_ama_1=4;
int leg_ama_1=6;
int leb_ama_1=9;


int ler_azu_1=26;
int leg_azu_1=25;
int leb_azu_1=15;

int ler_roj_1=6;
int leg_roj_1=16;
int leb_roj_1=13;


// lectura de colores encontrados en sensor 2
int ler_bco_2=4;
int leg_bco_2=5;
int leb_bco_2=3;

int ler_ngo_2=26;
int leg_ngo_2=29;
int leb_ngo_2=23;

int ler_ama_2=4;
int leg_ama_2=6;
int leb_ama_2=9;

int ler_vde_2=19;
int leg_vde_2=13;
int leb_vde_2=13;

int ler_azu_2=21;
int leg_azu_2=21;
int leb_azu_2=13;

int ler_roj_2=6;
int leg_roj_2=16;
int leb_roj_2=13;


// colores encontrados en sensor 1
int enc_bco_1=0;
int enc_ngo_1=0;
int enc_ama_1=0;
int enc_vde_1=0;
int enc_azu_1=0;
int enc_roj_1=0;

// colores encontrados en sensor 2
int enc_bco_2=0;
int enc_ngo_2=0;
int enc_ama_2=0;
int enc_vde_2=0;
int enc_azu_2=0;
int enc_roj_2=0;





void setup()   
{  
  //velocidad del puerto serie
  Serial.begin(9600); 
  
  //Pines s0,s1,s2 y s3 como salidas para el sensor1  
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
  
  // pin OUTT_2 como entrada para el sensor 1  
  pinMode(out_1, INPUT);  
  
  // S0 y S1 en alto color base rojo para sensor 1  
  digitalWrite(s1_0, HIGH);  
  digitalWrite(s1_1, HIGH);
  // S0 y S1 en alto color base rojo para sensor 2  
  digitalWrite(s2_0, HIGH);  
  digitalWrite(s2_1, HIGH);  

  
}  
    
void loop() 
{  
delay(1000);
    // color en sensor 1 
    enc_bco_1=0;
    enc_ngo_1=0;
    enc_ama_1=0;
    enc_vde_1=0;
    enc_azu_1=0;
    enc_roj_1=0;

    // color en sensor 2
    enc_bco_2=0;
    enc_ngo_2=0;
    enc_ama_2=0;
    enc_vde_2=0;
    enc_azu_2=0;
    enc_roj_2=0;


  
  // determina el tiempo de lectura para cada color (rojo, azul, verde)
  color(); 
  
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

  // determina el color sensor 1
  if (enc_bco_1==1)
     {  
       Serial.println(" -   BLANCO sensor 1 ");  
     }
  if (enc_ngo_1==1)
     {  
       Serial.println(" -    NEGRO sensor 1 ");  
     }
 if (enc_ama_1==1)
     {  
       Serial.println(" - AMARILLO sensor 1 ");  
     }
  if (enc_vde_1==1)
     {  
       Serial.println(" -    VERDE sensor 1 ");  
     }
 if (enc_azu_1==1)
     {  
       Serial.println(" -     AZUL sensor 1 ");  
     }
 if (enc_roj_1==1)
     {  
       Serial.println(" -     ROJO sensor 1 ");  
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

  // determina el color sensor 2
  if (enc_bco_2==1)
     {  
       Serial.println(" -   BLANCO sensor 2 ");  
     }
  if (enc_ngo_2==1)
     {  
       Serial.println(" -    NEGRO sensor 2 ");  
     }
 if (enc_ama_2==1)
     {  
       Serial.println(" - AMARILLO sensor 2 ");  
     }
  if (enc_vde_2==1)
     {  
       Serial.println(" -    VERDE sensor 2 ");  
     }
 if (enc_azu_2==1)
     {  
       Serial.println(" -     AZUL sensor 2 ");  
     }
 if (enc_roj_2==1)
     {  
       Serial.println(" -     ROJO sensor 2 ");  
     }

  delay(5000);

  
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
    
    // colores en sensor 1
    if ((red1>=ler_bco_1-des && red1<=ler_bco_1+des) && (green1>=leg_bco_1-des && green1<=leg_bco_1+des) && (blue1>=leb_bco_1-des && blue1<=leb_bco_1+des)){
        enc_bco_1=1;  
      }
    if ((red1>=ler_ngo_1-des && red1<=ler_ngo_1+des) && (green1>=leg_ngo_1-des && green1<=leg_ngo_1+des) && (blue1>=leb_ngo_1-des && blue1<=leb_ngo_1+des)){
        enc_ngo_1=1;  
      }
   if ((red1>=ler_ama_1-des && red1<=ler_ama_1+des) && (green1>=leg_ama_1-des && green1<=leg_ama_1+des) && (blue1>=leb_ama_1-des && blue1<=leb_ama_1+des)){
        enc_ama_1=1;  
      }
   if ((red1>=ler_vde_1-des && red1<=ler_vde_1+des) && (green1>=leg_vde_1-des && green1<=leg_vde_1+des) && (blue1>=leb_vde_1-des && blue1<=leb_vde_1+des)){
        enc_vde_1=1;  
      }
   if ((red1>=ler_azu_1-des && red1<=ler_azu_1+des) && (green1>=leg_azu_1-des && green1<=leg_azu_1+des) && (blue1>=leb_azu_1-des && blue1<=leb_azu_1+des)){
        enc_azu_1=1;  
      }
   if ((red1>=ler_roj_1-des && red1<=ler_roj_1+des) && (green1>=leg_roj_1-des && green1<=leg_roj_1+des) && (blue1>=leb_roj_1-des && blue1<=leb_roj_1+des)){
        enc_roj_1=1;  
      }

    // colores en sensor 2
    if ((red2>=ler_bco_2-des && red2<=ler_bco_2+des) && (green2>=leg_bco_2-des && green2<=leg_bco_2+des) && (blue2>=leb_bco_2-des && blue2<=leb_bco_2+des)){
        enc_bco_2=1;  
      }
    if ((red2>=ler_ngo_2-des && red2<=ler_ngo_2+des) && (green2>=leg_ngo_2-des && green2<=leg_ngo_2+des) && (blue2>=leb_ngo_2-des && blue2<=leb_ngo_2+des)){
        enc_ngo_2=1;  
      }
   if ((red2>=ler_ama_2-des && red2<=ler_ama_2+des) && (green2>=leg_ama_2-des && green2<=leg_ama_2+des) && (blue2>=leb_ama_2-des && blue2<=leb_ama_2+des)){
        enc_ama_2=1;  
      }
   if ((red2>=ler_vde_2-des && red2<=ler_vde_2+des) && (green2>=leg_vde_2-des && green2<=leg_vde_2+des) && (blue2>=leb_vde_2-des && blue2<=leb_vde_2+des)){
        enc_vde_2=1;  
      }
   if ((red2>=ler_azu_2-des && red2<=ler_azu_2+des) && (green2>=leg_azu_2-des && green2<=leg_azu_2+des) && (blue2>=leb_azu_2-des && blue2<=leb_azu_2+des)){
        enc_azu_2=1;  
      }
   if ((red2>=ler_roj_2-des && red2<=ler_roj_2+des) && (green2>=leg_roj_2-des && green2<=leg_roj_2+des) && (blue2>=leb_roj_2-des && blue2<=leb_roj_2+des)){
        enc_roj_2=1;  
      }

      
}

//Incluimos la libreria SD.
#include <SD.h>
#include <QTRSensors.h>
#include <AFMotor.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//define motores por cada puerto
AF_DCMotor motori_D(4); //motor izquierdo delantero
AF_DCMotor motori_T(1); //motor izquierdo trasero
AF_DCMotor motord_D(2);   //motor derecho
AF_DCMotor motord_T(3);   //motor izquierdo

//Declaracion de Variables para sensores
  // SD
      const int chipSelect = 44;
  //Ultrasonicos 
     //Delantero
       const int trigPin_D = 46;
       const int echoPin_D = 48;
     //Derecho
       const int trigPin_R = 23;
       const int echoPin_R = 25;
     //Izquierdo
       const int trigPin_L= 26; // Pin disparador. Se puede usar otro pin digital
       const int echoPin_L= 28; // Pin eco. Se puede usar otro pin digital
     //Trasero      
       const int trigPin_A= 30; // Pin disparador. Se puede usar otro pin digital
       const int echoPin_A= 32; // Pin eco. Se puede usar otro pin digital
//variables de medicion de sensores
    //Sensores ultrasonicos 
       long duration;
       long inches;
       long cm_D; 
       long cm_R; 
       long cm_L; 
       long cm_A; 
       long dif_cm=0;
       

//Variables de control
    // distancia para encontrar las paredes (centimetros)
       int d_enc=20; 
       int d_fte=6;
    //encuentro con las paredes del laberinto (0) libre, (1) encuentra la pared 
       int adelante=0;
       int derecha=0;
       int izquierda=0;
       int atras=0;
    //velocidad de ruedas
       int ade_ordi=200;
       int medioi=100;
       int ade_ordd=200;
       int mediod=100;
       //long dif_cm=0;
       
    //Control de ultimo giro 
       String ul_giro="FR"; 
    // espara para los giros
       int t_giro=1700;      //tiempo para los giros de 90°
       int t_u=800;
       int ine=800;         //
       int esp_giro=2000;    //avanza despues de girar 180°
       int t_giro_u=5000;   // tiempo para giros de 180°
       int tr=40;           // tiempo de retorno a la recta 
       int giro=0;  
       float dif_temp=0;
       float temp1=0;
       float temp2=0;
       //led de victima
       int vic=22;

void setup() {

  
   //Puerto serial 
   Serial.begin(9600); 
   mlx.begin(); 
   pinMode(vic,OUTPUT);
   // Sensor ultrasonico Delantero
      pinMode(trigPin_D, OUTPUT); // Establece pin como salida
      pinMode(echoPin_D, INPUT); // Establece pin como entrada
      digitalWrite(trigPin_D, LOW); // Pone el pin a un estado logico bajo
   
   // Sensor ultrasonico derecho
      pinMode(trigPin_R, OUTPUT); // Establece pin como salida
      pinMode(echoPin_R, INPUT); // Establece pin como entrada
      digitalWrite(trigPin_R, LOW); // Pone el pin a un estado logico bajo

   // Sensor ultrasonico izquierdo
      pinMode(trigPin_L, OUTPUT); // Establece pin como salida
      pinMode(echoPin_L, INPUT); // Establece pin como entrada 
      digitalWrite(trigPin_L, LOW); // Pone el pin a un estado logico bajo

   // Sensor ultrasonico izquierdo
      pinMode(trigPin_A, OUTPUT); // Establece pin como salida
      pinMode(echoPin_A, INPUT); // Establece pin como entrada 
      digitalWrite(trigPin_A, LOW); // Pone el pin a un estado logico bajo


   // El pin CS por defecto de la placa arduino debe ser configurado como salida
   // aunque no se use (10 en la mayoria de las placas, 53 en Arduino Mega).
   pinMode(53, OUTPUT);
   // Si ha habido error al leer la tarjeta informamos por el puerto serie.
   if (!SD.begin(chipSelect)){
      Serial.println("Error al leer la tarjeta.");
      return;
   }
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
   delay(100);
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
   //delay(900);
}


void loop() {



  //delay(1000);
   // Abrimos el fichero donde vamos a guardar los datos (Si no existe se crea automaticamente).
   File dataFile = SD.open("valores.txt", FILE_WRITE);

   // determina el tiempo de lectura para cada color (rojo, azul, verde
   
   //------------------------------------------------------------------------------
   digitalWrite(vic,LOW);
   temp1=mlx.readAmbientTempC();
   temp2=mlx.readObjectTempC();
   Serial.print("Ambiente = ");
   Serial.print(temp1); 
   Serial.print("  ºC\tObjeto = "); 
   Serial.print(temp2); 
   Serial.println(" ºC");
   dataFile.print("Ambiente = ");
   dataFile.print(temp1);
   dataFile.print("  ºC\tObjeto = ");
   dataFile.print(temp2);
   dataFile.println(" ºC");
   dif_temp=temp2-temp1;
   if (dif_temp>3){
     digitalWrite(vic,HIGH);
     alto();
     Serial.println(" Victima");
     delay(10000);
  }

   // Lectura de sensores ultrasonicos 
   
   
   ultra_D();
   ultra_R();
   ultra_L();
   ultra_A();
   //Detremina si encontro la pared Delantera
   if (cm_D<d_fte) {
      adelante=0;
   }else {
      adelante=1;
   }
   //Detremina si encontro la pared Derecha
   if (cm_R<d_enc) {
      derecha=0;
   }else {
       derecha=1;
   }
   //Detremina si encontro la pared Izquierda
   if (cm_L<d_enc) {
       izquierda=0;
   }else {
       izquierda=1;
   }
   if (cm_A<d_fte) {
       atras=0;
   }else {
       atras=1;
   }
   
   Serial.print(millis());
   Serial.print("    cm_D->");
   Serial.print(cm_D);
   Serial.print("-");
   Serial.print(adelante);
   
   Serial.print("  cm_R->");
   Serial.print(cm_R);
   Serial.print("-");
   Serial.print(derecha);
   
   Serial.print("   cm_L->");
   Serial.print(cm_L);
   Serial.print("-");
   Serial.print(izquierda);

   Serial.print("   cm_A->");
   Serial.print(cm_A);
   Serial.print("-");
   Serial.println(atras);
   
   if (dataFile){
      dataFile.print(millis());
      dataFile.print("    cm_D->");
      dataFile.print(cm_D);
      dataFile.print("-");
      dataFile.print(adelante);
   
      dataFile.print("  cm_R->");
      dataFile.print(cm_R);
      dataFile.print("-");
      dataFile.print(derecha);
   
      dataFile.print("   cm_L->");
      dataFile.print(cm_L);
      dataFile.print("-");
      dataFile.print(izquierda);

      dataFile.print("   cm_A->");
      dataFile.print(cm_A);
      dataFile.print("-");
      dataFile.print(atras);

      
  dataFile.print("Ambiente = ");
  dataFile.print(temp1);
  dataFile.print("   ºC\tObjeto = ");
  dataFile.print(temp2);
  dataFile.println("  ºC");

   
   }
    // pared frontal 
   /*if ((adelante==0)){
       alto();
       dataFile.print("   ----alto----");
   } */
   // Campo abierto avanza de frente 
   /*if ((adelante==1) && (atras==1) && (derecha==1) && (izquierda==1)){
       //avanza_l();
       motori_D.setSpeed(ade_ordi-(dif_cm*10));  //velocidad de motor izquierdo
       motori_D.run(FORWARD);        //polaridad de motor izquierdo
       motord_D.setSpeed(ade_ordd+(dif_cm*10));  //velocidad de motor derecho
       motord_D.run(FORWARD);        //polaridad de motor  derecho
       motori_T.setSpeed(ade_ordi-(dif_cm*10));  //velocidad de motor izquierdo
       motori_T.run(FORWARD);        //polaridad de motor izquierdo
       motord_T.setSpeed(ade_ordd+(dif_cm*10));  //velocidad de motor derecho
       motord_T.run(FORWARD);        //polaridad de motor  derecho
       dataFile.print("   ----avanza_l----");
   }*/
   //antre dos paredes avanza de frente
   //if ((adelante==1) && (atras==1)  && (izquierda==0) && (derecha==0)){
   if ((adelante==1) && (izquierda==0) && (derecha==0)){
       motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
       motori_D.run(FORWARD);        //polaridad de motor izquierdo
       motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
       motord_D.run(FORWARD);        //polaridad de motor  derecho
       motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
       motori_T.run(FORWARD);        //polaridad de motor izquierdo
       motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
       motord_T.run(FORWARD);        //polaridad de motor  derecho
       //avanza_l();
       dataFile.print("   ----avanza ---derecho -");
       //algoritmo para centrar
       if(cm_L<7 && cm_R<20){
             dataFile.print("   cm_L<7   ");
             motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
             motori_D.run(FORWARD); //polaridad de motor izquierdo
             motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
             motord_D.run(BACKWARD);//polaridad de motor  derecho
             motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
             motori_T.run(FORWARD); //polaridad de motor izquierdo
             motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
             motord_T.run(BACKWARD);//polaridad de motor  derecho
             delay(500);
             motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
             motori_D.run(FORWARD);        //polaridad de motor izquierdo
             motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
             motord_D.run(FORWARD);        //polaridad de motor  derecho
             motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
             motori_T.run(FORWARD);        //polaridad de motor izquierdo
             motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
             motord_T.run(FORWARD);        //polaridad de motor  derecho
             delay(500);
             motori_D.setSpeed(medioi);//velocidad de motor izquierdo
             motori_D.run(BACKWARD); //polaridad de motor izquierdo
             motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
             motord_D.run(FORWARD);//polaridad de motor  derecho
             motori_T.setSpeed(medioi);//velocidad de motor izquierdo
             motori_T.run(BACKWARD); //polaridad de motor izquierdo
             motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
             motord_T.run(FORWARD);//polaridad de motor  derecho
             delay(300);
  
          }
          if(cm_R<7 && cm_L<20){
               dataFile.print("   cm_R<7   ");
               //gira hacia el centro 
               motori_D.setSpeed(medioi);//velocidad de motor izquierdo
               motori_D.run(BACKWARD); //polaridad de motor izquierdo
               motord_D.setSpeed(mediod);//velocidad de motor derecho
               motord_D.run(FORWARD);//polaridad de motor  derecho
               motori_T.setSpeed(medioi);//velocidad de motor izquierdo
               motori_T.run(BACKWARD); //polaridad de motor izquierdo
               motord_T.setSpeed(mediod);//velocidad de motor derecho
               motord_T.run(FORWARD);//polaridad de motor  derecho
               delay(500);
               //avanza hacia el centro
               motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
               motori_D.run(FORWARD);        //polaridad de motor izquierdo
               motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
               motord_D.run(FORWARD);        //polaridad de motor  derecho
               motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
               motori_T.run(FORWARD);        //polaridad de motor izquierdo
               motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
               motord_T.run(FORWARD);        //polaridad de motor  derecho
               delay(500);
               //gira para enderesar
               motori_D.setSpeed(medioi);//velocidad de motor izquierdo
               motori_D.run(FORWARD); //polaridad de motor izquierdo
               motord_D.setSpeed(mediod);//velocidad de motor derecho
               motord_D.run(BACKWARD);//polaridad de motor  derecho
               motori_T.setSpeed(medioi);//velocidad de motor izquierdo
               motori_T.run(FORWARD); //polaridad de motor izquierdo
               motord_T.setSpeed(mediod);//velocidad de motor derecho
               motord_T.run(BACKWARD);//polaridad de motor  derecho
               delay(300);
          }
          //ul_giro="FT";
   }
   
   //Pared izquierda gira a la derecha
   //if ((adelante==0) && (atras==1)  && (izquierda==0) && (derecha==1)){
   if (((adelante==0)   && (izquierda==0) && (derecha==1)) || ((adelante==1)   && (izquierda==0) && (derecha==1)) ){
       //v_derecha();
       delay(ine); //avanza para centrar el giro
       motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
       motori_D.run(FORWARD); //polaridad de motor izquierdo
       motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
       motord_D.run(BACKWARD);//polaridad de motor  derecho
       motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
       motori_T.run(FORWARD); //polaridad de motor izquierdo
       motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
       motord_T.run(BACKWARD);//polaridad de motor  derecho
       delay(t_giro);
       motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
       motori_D.run(FORWARD);        //polaridad de motor izquierdo
       motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
       motord_D.run(FORWARD);        //polaridad de motor  derecho
       motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
       motori_T.run(FORWARD);        //polaridad de motor izquierdo
       motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
       motord_T.run(FORWARD);        //polaridad de motor  derecho
       delay(esp_giro);
       alto();
       motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
       motori_D.run(FORWARD);        //polaridad de motor izquierdo
       motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
       motord_D.run(FORWARD);        //polaridad de motor  derecho
       motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
       motori_T.run(FORWARD);        //polaridad de motor izquierdo
       motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
       motord_T.run(FORWARD);        //polaridad de motor  derecho
       ul_giro="DE";
       dataFile.print("   ----gira derecha----");
       
   }
   
   //Pared derecha gira a la izquierda
   //if ((adelante==0) && (atras==1) && (izquierda==1) && (derecha==0) ){
   if (((adelante==0) && (izquierda==1) && (derecha==0)) || ((adelante==1) && (izquierda==1) && (derecha==0))){
       //v_izquierda();
       //gira izquierda
           delay(ine); //avanza para centrar el giro
           motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
           motori_D.run(BACKWARD); //polaridad de motor izquierdo
           motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
           motord_D.run(FORWARD);//polaridad de motor  derecho
           motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
           motori_T.run(BACKWARD); //polaridad de motor izquierdo
           motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
           motord_T.run(FORWARD);//polaridad de motor  derecho
           delay(t_giro);
           motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
           motori_D.run(FORWARD);        //polaridad de motor izquierdo
           motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
           motord_D.run(FORWARD);        //polaridad de motor  derecho
           motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
           motori_T.run(FORWARD);        //polaridad de motor izquierdo
           motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
           motord_T.run(FORWARD);        //polaridad de motor  derecho
           delay(esp_giro);
           alto();
           motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
           motori_D.run(FORWARD);        //polaridad de motor izquierdo
           motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
           motord_D.run(FORWARD);        //polaridad de motor  derecho
           motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
           motori_T.run(FORWARD);        //polaridad de motor izquierdo
           motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
           motord_T.run(FORWARD);        //polaridad de motor  derecho
           ul_giro="IZ";
           dataFile.print("   ---- giro izquierda----");
           
   }


   //Pared izquierda gira a la derecha
   //if ((adelante==0) && (atras==1)  && (izquierda==0) && (derecha==1)){
   if (((adelante==0)   && (izquierda==1) && (derecha==1)) || ((adelante==1)   && (izquierda==1) && (derecha==1)) ){
       //v_derecha();
       delay(ine); //avanza para centrar el giro
       if (ul_giro=="IZ"){
          //derecha
          motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
          motori_D.run(FORWARD); //polaridad de motor izquierdo
          motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
          motord_D.run(BACKWARD);//polaridad de motor  derecho
          motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
          motori_T.run(FORWARD); //polaridad de motor izquierdo
          motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
          motord_T.run(BACKWARD);//polaridad de motor  derecho
          delay(t_giro); 
       }else{
           motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
           motori_D.run(BACKWARD); //polaridad de motor izquierdo
           motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
           motord_D.run(FORWARD);//polaridad de motor  derecho
           motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
           motori_T.run(BACKWARD); //polaridad de motor izquierdo
           motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
           motord_T.run(FORWARD);//polaridad de motor  derecho
           delay(t_giro);

          
       }
       motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
       motori_D.run(FORWARD);        //polaridad de motor izquierdo
       motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
       motord_D.run(FORWARD);        //polaridad de motor  derecho
       motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
       motori_T.run(FORWARD);        //polaridad de motor izquierdo
       motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
       motord_T.run(FORWARD);        //polaridad de motor  derecho
       delay(esp_giro);
       alto();
       motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
       motori_D.run(FORWARD);        //polaridad de motor izquierdo
       motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
       motord_D.run(FORWARD);        //polaridad de motor  derecho
       motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
       motori_T.run(FORWARD);        //polaridad de motor izquierdo
       motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
       motord_T.run(FORWARD);        //polaridad de motor  derecho
       ul_giro="DE";
       dataFile.print("   ----gira derecha----");
       
   }

   

    //sin pared atras
    //if ((adelante==0) && (atras==1) && (derecha==0) && (izquierda==0)){
    if ((adelante==0) && (derecha==0) && (izquierda==0)){
    //giro_u();
         motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
         motori_D.run(BACKWARD); //polaridad de motor izquierdo
         motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
         motord_D.run(FORWARD);//polaridad de motor  derecho
         motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
         motori_T.run(BACKWARD); //polaridad de motor izquierdo
         motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
         motord_T.run(FORWARD);//polaridad de motor  derecho
         delay(t_u);
    
    dataFile.print("   ----giro U----");
   }

   dataFile.print("   ul_giro->");
   dataFile.println(ul_giro);        
   
   dataFile.close();
}
   

void ultra_D(){
  digitalWrite(trigPin_D, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin_D, LOW);
  duration = pulseIn(echoPin_D, HIGH); //Devuelve la longitud del pulso del pin Echo en us
  // Imprime valores por el puerto serie:
  // Convierte el tiempo de recepción del eco en distancia:
  inches = microsecondsToInches(duration);
  cm_D = microsecondsToCentimeters(duration);
}

void ultra_R(){
  digitalWrite(trigPin_R, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin_R, LOW);
  duration = pulseIn(echoPin_R, HIGH); //Devuelve la longitud del pulso del pin Echo en us
  // Imprime valores por el puerto serie:
  // Convierte el tiempo de recepción del eco en distancia:
  inches = microsecondsToInches(duration);
  cm_R = microsecondsToCentimeters(duration);
  //cm_R=10;
}

void ultra_L(){
  digitalWrite(trigPin_L, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin_L, LOW);
  duration = pulseIn(echoPin_L, HIGH); //Devuelve la longitud del pulso del pin Echo en us
  // Imprime valores por el puerto serie:
  // Convierte el tiempo de recepción del eco en distancia:
  inches = microsecondsToInches(duration);
  cm_L = microsecondsToCentimeters(duration);
}
void ultra_A(){
  digitalWrite(trigPin_A, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin_A, LOW);
  duration = pulseIn(echoPin_A, HIGH); //Devuelve la longitud del pulso del pin Echo en us
  // Imprime valores por el puerto serie:
  // Convierte el tiempo de recepción del eco en distancia:
  inches = microsecondsToInches(duration);
    cm_A = microsecondsToCentimeters(duration);
}



// Calcula la distancia en pulgadas
long microsecondsToInches(long microseconds) {
    return microseconds/148;
}
// Calcula la distancia en cm
long microsecondsToCentimeters(long microseconds) {
    return microseconds/58;
} 

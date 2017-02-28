//Incluimos la libreria SD.
#include <SD.h>
#include <QTRSensors.h>
#include <AFMotor.h>

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
       const int trigPin_D = 24;
       const int echoPin_D = 22;
     //Derecho
       const int trigPin_R = 49;
       const int echoPin_R = 48;
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
       int d_enc=15;
       int d_fte=10;
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
       int t_giro=1800;
    //Control de ultimo giro 
       String ul_giro="FR"; 
    // espara para los giros
       int ine=1000;
       int esp_giro=1500;
       

void setup() {
   //Puerto serial 
      Serial.begin(9600); 
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



void avanza(){
     long dif_cm=cm_R-cm_L;
     motori_D.setSpeed(ade_ordi-(dif_cm*7));  //velocidad de motor izquierdo
     motori_D.run(FORWARD);        //polaridad de motor izquierdo
     motord_D.setSpeed(ade_ordd+(dif_cm*7));  //velocidad de motor derecho
     motord_D.run(FORWARD);        //polaridad de motor  derecho
     motori_T.setSpeed(ade_ordi-(dif_cm*7));  //velocidad de motor izquierdo
     motori_T.run(FORWARD);        //polaridad de motor izquierdo
     motord_T.setSpeed(ade_ordd+(dif_cm*7));  //velocidad de motor derecho
     motord_T.run(FORWARD);        //polaridad de motor  derecho
 }


void avanza_l(){
     motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
     motori_D.run(FORWARD);        //polaridad de motor izquierdo
     motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
     motord_D.run(FORWARD);        //polaridad de motor  derecho
     motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
     motori_T.run(FORWARD);        //polaridad de motor izquierdo
     motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
     motord_T.run(FORWARD);        //polaridad de motor  derecho
 }
void giro_u(){
     motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
     motori_D.run(BACKWARD); //polaridad de motor izquierdo
     motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
     motord_D.run(FORWARD);//polaridad de motor  derecho
     motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
     motori_T.run(BACKWARD); //polaridad de motor izquierdo
     motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
     motord_T.run(FORWARD);//polaridad de motor  derecho
     delay(7000);
}


 void v_izquierda(){
     //gira izquierda
     motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
     motori_D.run(BACKWARD); //polaridad de motor izquierdo
     motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
     motord_D.run(FORWARD);//polaridad de motor  derecho
     motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
     motori_T.run(BACKWARD); //polaridad de motor izquierdo
     motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
     motord_T.run(FORWARD);//polaridad de motor  derecho
     delay(t_giro);
     //avanza
     motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
     motori_D.run(FORWARD);        //polaridad de motor izquierdo
     motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
     motord_D.run(FORWARD);        //polaridad de motor  derecho
     motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
     motori_T.run(FORWARD);        //polaridad de motor izquierdo
     motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
     motord_T.run(FORWARD);        //polaridad de motor  derecho
     delay(esp_giro);
 }

 void v_derecha(){
     //gira derecha
     motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
     motori_D.run(FORWARD); //polaridad de motor izquierdo
     motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
     motord_D.run(BACKWARD);//polaridad de motor  derecho
     motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
     motori_T.run(FORWARD); //polaridad de motor izquierdo
     motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
     motord_T.run(BACKWARD);//polaridad de motor  derecho
     delay(t_giro);
     //avanza
     motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
     motori_D.run(FORWARD);        //polaridad de motor izquierdo
     motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
     motord_D.run(FORWARD);        //polaridad de motor  derecho
     motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
     motori_T.run(FORWARD);        //polaridad de motor izquierdo
     motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
     motord_T.run(FORWARD);        //polaridad de motor  derecho
     delay(esp_giro);
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
   //delay(2000);
   // Abrimos el fichero donde vamos a guardar los datos (Si no existe se crea automaticamente).
   File dataFile = SD.open("valores.txt", FILE_WRITE);

   // determina el tiempo de lectura para cada color (rojo, azul, verde
   
   //------------------------------------------------------------------------------
     
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
   
   Serial.println(millis());
   Serial.print("DELANTERO   ");
   Serial.print(cm_D);
   Serial.print(" - ");
   Serial.println(adelante);
   
   Serial.print("DERECHO   ");
   Serial.print(cm_R);
   Serial.print(" - ");
   Serial.println(derecha);
   
   Serial.print("IZQUIERDO   ");
   Serial.print(cm_L);
   Serial.print(" - ");
   Serial.println(izquierda);

   Serial.print("TRASERO   ");
   Serial.print(cm_A);
   Serial.print(" - ");
   Serial.println(atras);
   
   if (dataFile) {
      dataFile.println(millis());
      dataFile.print("DELANTERO   ");
      dataFile.print(cm_D);
      dataFile.print(" - ");
      dataFile.println(adelante);
   
      dataFile.print("DERECHO   ");
      dataFile.print(cm_R);
      dataFile.print(" - ");
      dataFile.println(derecha);
   
      dataFile.print("IZQUIERDO   ");
      dataFile.print(cm_L);
      dataFile.print(" - ");
      dataFile.println(izquierda);
   }

    // pared frontal 
   if ((adelante==0)){
       alto();
       dataFile.println("alto");
   } 
   // Campo abierto avanza de frente 
   if ((adelante==1) && (atras==1) && (derecha==1) && (izquierda==1)){
       avanza_l();
       dataFile.println("avanza_l");
   }
   //antre dos paredes avanza de frente
   if ((adelante==1) && (atras==1)  && (izquierda==0) && (derecha==0)){
       avanza();
       dataFile.println("avanza_l");
   }
   //Pared izquierda gira a la derecha
   if ((adelante==0) && (atras==1)  && (izquierda==0) && (derecha==1)){
       v_derecha();
       ul_giro="DE";
       dataFile.println("derecha");
   }
   //Pared izquierda gira a la derecha
   if ((adelante==1) && (atras==1)  && (izquierda==0) && (derecha==1)){
       delay(ine);
       v_derecha();
       ul_giro="DE";
       dataFile.println("derecha");
   }
   //Pared derecha gira a la izquierda
   if ((adelante==0) && (atras==1) && (izquierda==1) && (derecha==0) ){
       v_izquierda();
       ul_giro="IZ";
       dataFile.println("izquierda");
   }

     //Pared derecha gira a la izquierda
   if ((adelante==1) && (atras==1) && (izquierda==1) && (derecha==0) ){
       delay(ine);
       v_izquierda();
       ul_giro="IZ";
       dataFile.println("izquierda");
   }

   //Pared derecha gira a la izquierda
   if ((adelante==0) && (atras==1) && (izquierda==1) && (derecha==1) ){
       if (ul_giro="DE"){
          v_izquierda();
          ul_giro="IZ";
          dataFile.println("izquierda");
       }else{ 
          v_derecha();
          ul_giro="DE";
          dataFile.println("derecha");
       }
   }
   
   //sin pared atras
   if ((adelante==0) && (atras==1) && (derecha==0) && (izquierda==0)){
    giro_u();
   }

      //algoritmo para centrar
   /*if(cm_L<5){
           motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
           motori_D.run(FORWARD); //polaridad de motor izquierdo
           motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
           motord_D.run(BACKWARD);//polaridad de motor  derecho
           motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
           motori_T.run(FORWARD); //polaridad de motor izquierdo
           motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
           motord_T.run(BACKWARD);//polaridad de motor  derecho
         delay(100);
           motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
           motori_D.run(FORWARD);        //polaridad de motor izquierdo
           motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
           motord_D.run(FORWARD);        //polaridad de motor  derecho
           motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
           motori_T.run(FORWARD);        //polaridad de motor izquierdo
           motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
           motord_T.run(FORWARD);        //polaridad de motor  derecho
         delay(200);
         }
      if(cm_R<5){
             motori_D.setSpeed(ade_ordi);//velocidad de motor izquierdo
             motori_D.run(BACKWARD); //polaridad de motor izquierdo
             motord_D.setSpeed(ade_ordd);//velocidad de motor derecho
             motord_D.run(FORWARD);//polaridad de motor  derecho
             motori_T.setSpeed(ade_ordi);//velocidad de motor izquierdo
             motori_T.run(BACKWARD); //polaridad de motor izquierdo
             motord_T.setSpeed(ade_ordd);//velocidad de motor derecho
             motord_T.run(FORWARD);//polaridad de motor  derecho
           delay(100);
             motori_D.setSpeed(ade_ordi);  //velocidad de motor izquierdo
             motori_D.run(FORWARD);        //polaridad de motor izquierdo
             motord_D.setSpeed(ade_ordd);  //velocidad de motor derecho
             motord_D.run(FORWARD);        //polaridad de motor  derecho
             motori_T.setSpeed(ade_ordi);  //velocidad de motor izquierdo
             motori_T.run(FORWARD);        //polaridad de motor izquierdo
             motord_T.setSpeed(ade_ordd);  //velocidad de motor derecho
             motord_T.run(FORWARD);        //polaridad de motor  derecho
          delay(200);
         }*/
    
   
   
   /*
   v_izquierda();
   alto();
   v_derecha();
   alto();
   regresa();
   delay(500);
   alto();
   delay(30000);
   */
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

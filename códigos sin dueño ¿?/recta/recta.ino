//Incluimos la libreria SD.
#include <SD.h>
//#include <QTRSensors.h>
#include <AFMotor.h>
//define tipo de variable motor y puerto
AF_DCMotor motori(2); //motor izquierdo
AF_DCMotor motord(4);//motor derecho



//s1
int izq_1=49;
//s2
int izq_2=47;
//s3
int izq_3=45;
//s4
int izq_centro=43;
//s5
int der_centro=41;
//s6
int der_6=39;
//s7
int der_7=37;
//s8
int der_8=35;
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
////////////////////////tiempo para ezquinas
int tezquina=600;
int reg=400; 
//////////Potencias
int ade_ordi=160;
int medioi=130;
int ade_ordd=180;
int mediod=150;
int dife=2;
// dirección y tiempo de regreso
int tr=40;
int rl=100;
int al=60;
String dire="";



// Guardamos en que entrada de Arduino esta conectado el pin CS del modulo.
const int chipSelect = 44;

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
  motori.setSpeed(10);//velocidad de motor izquierdo
  motori.run(BACKWARD); //polaridad de motor izquierdo
  motord.setSpeed(10);//velocidad de motor derecho          
  motord.run(BACKWARD);//polaridad de motor  derecho
  motori.setSpeed(0);//velocidad de motor izquierdo
  motori.run(RELEASE); //polaridad de motor izquierdo
  motord.setSpeed(0);//velocidad de motor derecho          
  motord.run(RELEASE);//polaridad de motor  derecho
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
   /*Serial.println("____Sensores de Izq. a Derecha_____");
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
   Serial.println(l8);*/
   
   // Abrimos el fichero donde vamos a guardar los datos (Si no existe se crea automaticamente).
   File dataFile = SD.open("valores.txt", FILE_WRITE);
     
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
      // Avisamos de que se ha podido escribir correctamente.
      //Serial.println("impresion correcta");
      // Si no pudimos escribir en el fichero avisamos por el puerto serie.
   }else{
      //Serial.println("Error al escribir en valorpot.txt");
   }
   
   //delay(4000);
   
   suma=(l1+l2+l3+l4+l5+l6+l7+l8);
   if (suma<=2){  
   ///////////////////////////////////// RECTA
   if (l1==bco && l2==bco && l3==bco && l4==bco && l5==bco && l6==bco && l7==bco  && l8==bco){
     dire="C0";
     dataFile.print(",C0,");
     dataFile.print(ade_ordi);
     dataFile.print(",");
     dataFile.print(ade_ordd);
     motori.setSpeed(ade_ordi);//velocidad de motor izquierdo
     motori.run(FORWARD); //polaridad de motor izquierdo
     motord.setSpeed(ade_ordd);//velocidad de motor derecho
     motord.run(FORWARD);//polaridad de motor  derecho
   }else{
     if (l1==bco && l2==bco && l3==bco && l4==neg && l5==neg && l6==bco && l7==bco  && l8==bco){ 
        if (dire=="C2" || dire=="C3" || dire=="C4"){
           dataFile.print(",R1,");
           dataFile.print(ade_ordi);
           dataFile.print(",");
           dataFile.print(mediod);
           motori.setSpeed(ade_ordi);//velocidad de motor izquierdo
           motori.run(FORWARD); //polaridad de motor izquierdo
           motord.setSpeed(mediod);//velocidad de motor derecho          
           motord.run(FORWARD);//polaridad de motor  derecho
           delay(tr);
        }
        if (dire=="C5" || dire=="C6" || dire=="C7"){
           dataFile.print(",R2,");
           dataFile.print(medioi);
           dataFile.print(",");
           dataFile.print(ade_ordd);
           motori.setSpeed(medioi);//velocidad de motor izquierdo
           motori.run(FORWARD); //polaridad de motor izquierdo
           motord.setSpeed(ade_ordd);//velocidad de motor derecho          
           motord.run(FORWARD);//polaridad de motor  derecho
           delay(tr);
        }
        dire="C1";
        dataFile.print(",C1,");
        dataFile.print(ade_ordi);
        dataFile.print(",");
        dataFile.print(ade_ordd);
        motori.setSpeed(ade_ordi);//velocidad de motor izquierdo
        motori.run(FORWARD); //polaridad de motor izquierdo
        motord.setSpeed(ade_ordd);//velocidad de motor derecho
        motord.run(FORWARD);//polaridad de motor  derecho
     } else {
         // desviado a la derecha gira acelerando motor derecho
         if ((l1==bco && l2==bco) && (l3==neg || l4==neg) && (l5==bco && l6==bco && l7==bco  && l8==bco)){
            dire="C2";
            dataFile.print(",C2,");
            dataFile.print(medioi);
            dataFile.print(",");
            dataFile.print(ade_ordd);
            motori.setSpeed(medioi);//velocidad de motor izquierdo
            motori.run(FORWARD); //polaridad de motor izquierdo
            motord.setSpeed(ade_ordd);//velocidad de motor derecho          
            motord.run(FORWARD);//polaridad de motor derecho
         } else {
            if ((l1==bco) && (l2==neg || l3==neg) && (l4==bco && l5==bco && l6==bco && l7==bco  && l8==bco)){
               //Serial.println("C3");
               dire="C3";
               dataFile.print(",C3,");
               dataFile.print(medioi-(dife));
               dataFile.print(",");
               dataFile.print(ade_ordd+(dife));
               motori.setSpeed(medioi-(dife));//velocidad de motor izquierdo
               motori.run(FORWARD); //polaridad de motor izquierdo
               motord.setSpeed(ade_ordd+(dife));//velocidad de motor derecho          
               motord.run(FORWARD);//polaridad de motor derecho
            } else {
              if ((l1==neg || l2==neg) && (l3==bco && l4==bco && l5==bco && l6==bco && l7==bco  && l8==bco)){
                  //if (l7==bco && l8==neg){
                     ///////////////////////////////////////////////////
                     dataFile.print("------------- sale por derecha");
                     //alto();
                     motori.setSpeed(100);//velocidad de motor izquierdo
                     motori.run(BACKWARD); //polaridad de motor izquierdo
                     motord.setSpeed(100);//velocidad de motor derecho
                     motord.run(FORWARD);//polaridad de motor  derecho
                     delay(rl);
                     motori.setSpeed(100);//velocidad de motor izquierdo
                     motori.run(FORWARD); //polaridad de motor izquierdo
                     motord.setSpeed(100);//velocidad de motor derecho
                     motord.run(FORWARD);//polaridad de motor  derecho
                     delay(al);
                     //////////////////////////////////////////////////
                  //}
                        
                  dire="C4";
                  dataFile.print(",C4,");
                  dataFile.print(medioi-(dife*3));
                  dataFile.print(",");
                  dataFile.print(ade_ordd+(dife*3));
                  motori.setSpeed(medioi-(dife*3));//velocidad de motor izquierdo
                  motori.run(FORWARD); //polaridad de motor izquierdo
                  motord.setSpeed(ade_ordd+(dife*3));//velocidad de motor derecho          
                  motord.run(FORWARD);//polaridad de motor derecho
               } else {
                  if ((l1==bco && l2==bco && l3==bco && l4==bco) && (l5==neg || l6==neg) && (l7==bco  && l8==bco)){
                     dire="C5";
                     dataFile.print(",C5,");
                     dataFile.print(ade_ordi);
                     dataFile.print(",");
                     dataFile.print(mediod);
                     motori.setSpeed(ade_ordi);//velocidad de motor izquierdo
                     motori.run(FORWARD); //polaridad de motor izquierdo
                     motord.setSpeed(mediod);//velocidad de motor derecho          
                     motord.run(FORWARD);//polaridad de motor  derecho
                     //delay(200);*/
                  } else {
                     if ((l1==bco && l2==bco && l3==bco && l4==bco && l5==bco) && (l6==neg || l7==neg)  && (l8==bco)){
                        
                        dire="C6";
                        dataFile.print(",C6,");
                        dataFile.print(ade_ordi+(dife));
                        dataFile.print(",");
                        dataFile.print(mediod-(dife));
                        motori.setSpeed(ade_ordi+(dife));//velocidad de motor izquierdo
                        motori.run(FORWARD); //polaridad de motor izquierdo
                        motord.setSpeed(mediod-(dife));//velocidad de motor derecho          
                        motord.run(FORWARD);//polaridad de motor  derecho*/
                     } else {
                        if ((l1==bco && l2==bco && l3==bco && l4==bco && l5==bco && l6==bco) && (l7==neg  || l8==neg)){
                           //if (l7==bco && l8==neg){
                              ///////////////////////////////////////////////////
                              dataFile.print("------------- sale por izquierda");
                              //alto();
                              motori.setSpeed(100);//velocidad de motor izquierdo
                              motori.run(FORWARD); //polaridad de motor izquierdo
                              motord.setSpeed(100);//velocidad de motor derecho
                              motord.run(BACKWARD);//polaridad de motor  derecho
                              delay(rl);
                              motori.setSpeed(100);//velocidad de motor izquierdo
                              motori.run(FORWARD); //polaridad de motor izquierdo
                              motord.setSpeed(100);//velocidad de motor derecho
                              motord.run(FORWARD);//polaridad de motor  derecho
                              delay(al);
                              //////////////////////////////////////////////////
                           //}
                           dire="C7";
                           dataFile.print(",C7,");
                           dataFile.print(ade_ordi+(dife*3));
                           dataFile.print(",");
                           dataFile.print(mediod-(dife*3));
                           motori.setSpeed(ade_ordi+(dife*3));//velocidad de motor izquierdo
                           motori.run(FORWARD); //polaridad de motor izquierdo
                           motord.setSpeed(mediod-(dife*3));//velocidad de motor derecho          
                           motord.run(FORWARD);//polaridad de motor  derecho*/
                           //delay(300);
                        } 
                          
                     }
                  }
               }
            }
         }
     }
   } 
    /////////////////////////////////////    

   }else{
      if (suma<=5){
         // a la izquierda
         int sum_izq=l1+l2+l3+l4;
         int sum_der=l5+l6+l7+l8;
         
         if ((sum_izq>sum_der) || (dire=="C5" || dire=="C6" || dire=="C7")){
           //Serial.println("C8");
           dataFile.print("------------- izquierda ");
           dataFile.print(" tezquina ");
           dataFile.print(tezquina);
           dataFile.print(" reg ");
           dataFile.print(reg);
           dataFile.print(" ai ");
           dataFile.println(ade_ordi);
           dataFile.print(" mi ");
           dataFile.print(medioi);
           dataFile.print(" ad ");
           dataFile.print(ade_ordd);
           dataFile.print(" md ");
           dataFile.println(mediod);
           
           alto();
           motori.setSpeed(150);//velocidad de motor izquierdo
           motori.run(BACKWARD); //polaridad de motor izquierdo
           motord.setSpeed(150);//velocidad de motor derecho
           motord.run(BACKWARD);//polaridad de motor  derecho
           delay(reg);
           dataFile.print(",C8,");
           dataFile.print(-ade_ordi);
           dataFile.print(",");
           dataFile.print(ade_ordd);
           motori.setSpeed(ade_ordi);//velocidad de motor izquierdo
           motori.run(BACKWARD); //polaridad de motor izquierdo
           motord.setSpeed(ade_ordd);//velocidad de motor derecho
           motord.run(FORWARD);//polaridad de motor  derecho
           delay(tezquina);
         }else{
           //if (((l4==neg && l5==neg && l6==neg) || (l5==neg && l6==neg && l7==neg) || (l6==neg && l7==neg && l8==neg))){ 
           if ((sum_der>sum_izq) || (dire=="C2" || dire=="C3" || dire=="C4")) {
              //Serial.println("C9");
              dataFile.println("------------- derecha");
              alto();
              motori.setSpeed(150);//velocidad de motor izquierdo
              motori.run(BACKWARD); //polaridad de motor izquierdo
              motord.setSpeed(150);//velocidad de motor derecho
              motord.run(BACKWARD);//polaridad de motor  derecho
              delay(reg);
              dataFile.print(",C9,");
              dataFile.print(ade_ordi);
              dataFile.print(",");
              dataFile.print(-ade_ordd);
              motori.setSpeed(ade_ordi);//velocidad de motor izquierdo
              motori.run(FORWARD); //polaridad de motor izquierdo
              motord.setSpeed(ade_ordd);//velocidad de motor derecho
              motord.run(BACKWARD);//polaridad de motor  derecho
              delay(tezquina);
           }else {
              alto();
           }
            
         }
      } else {
          alto(); 
      }
       
   }
   // Cerramos el archivo.
   dataFile.println(".");
   dataFile.close();   
}
   


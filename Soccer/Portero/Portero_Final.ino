#include <AFMotor.h>
AF_DCMotor motord(1);
AF_DCMotor motort(2);

//////ULTRASONICO
const int trigPin_D=31;   //Sensor ultrasónico derecho
const int echoPin_D=30;
const int trigPin_I=53;   //Sensor ultrasónico izquierdo
const int echoPin_I=33;
long duration;     //Declarar variables
int cm_d,cm_i;     //Distancia en centímetros del sensor derecho e izquierdo
int pared=52;      //Distnacia a la pared
int p_inf=19;

//////RECEPTORES
const int sd_ext=A11;     //Se declara el pin del sensor infrarrojo derecho exterior(lateral)
//const int sd_int=A12;     //Sensor Infrarrojo derecho interior
const int centro=A13;     //Sensor Infrarrojo Centro 
const int si_int=A15;     //Sensor Infrarrojo izquierdo interior
const int si_ext=A14;     //Sensor Infrarrojo izquiero exterior(lateral)
int ls1=0;    //sensor Infrarrojo derecho exterior
int ls2=0;    //Sensor Infrarrojo derecha interior
int ls3=0;    //Sensor infrarrojo centro 
//int ls4=0;    //Sensor Infrarrojo izquierdo interior
int ls5=0;    //Sensor Infrarrojo izquierdo exterior

void setup() {
  Serial.begin(9600);
/////ULTASÖNICOS  
  pinMode(trigPin_D, OUTPUT);
  pinMode(echoPin_D, INPUT);
  digitalWrite(trigPin_D, LOW);
  pinMode(trigPin_I, OUTPUT);
  pinMode(echoPin_I, INPUT);
  digitalWrite(trigPin_I, LOW);
  
/////RECEPTORES
  pinMode(sd_ext,INPUT);//Declara las variables como entrada 
  //pinMode(sd_int,INPUT);
  pinMode(centro,INPUT);
  pinMode(si_int,INPUT);
  pinMode(si_ext,INPUT);  

}

void loop() {
  ls5=analogRead(sd_ext);
  //ls4=analogRead(sd_int);
  ls3=analogRead(centro);
  ls2=analogRead(si_int);
  ls1=analogRead(si_ext);

  //Inicia ulstrasónicos
    ult_D();
    ult_I();

  if(ls1<920 && ls2>1020 && ls3<920 && ls5>3){      //Si ninguno de los receptores detecta nada 
    //El robot se centra
    Cent();
  }

  if(ls1>920 || ls2<965){     //Si alguno de los sensores izquierdos detecta la pelota
      //EL robot evita salirse del área
    Cent_inf();
      //Avanza hacia la izquierda
    motord.setSpeed(190);
    motord.run(FORWARD);
    motort.setSpeed(178);
    motort.run(FORWARD);
  }

  if(ls3>920){     //Si el sensor del centro detecta la pelota
    //No se mueve
    motord.setSpeed(0);
    motord.run(FORWARD);
    motort.setSpeed(0);
    motort.run(FORWARD);
  }

  if( ls5<3){     //Si alguno de los sensores derechos detecta la pelota
    //EL robot evita salirse del área
    Cent_inf();
    //Avanza hacia la derecha
    motord.setSpeed(190);
    motord.run(BACKWARD);
    motort.setSpeed(178);
    motort.run(BACKWARD);
  }
}

//Centrar robot con receptores
void Cent_inf(){
  if(cm_i>p_inf && cm_d<p_inf){  //Si la distancia del sensor izquierdo a la pared es mayor a 52, avanza hacia la izquierda
    motord.setSpeed(190);
    motord.run(FORWARD);
    motort.setSpeed(178);
    motort.run(FORWARD);
  }
  if(cm_d>p_inf && cm_i<p_inf){  //Si la distancia del sensor derecho a la pared es mayor a 52, avanza hacia la derecha
    motord.setSpeed(190);
    motord.run(BACKWARD);
    motort.setSpeed(178);
    motort.run(BACKWARD);
  }
}

//Centrar robot sin receptores
void Cent(){
  if(cm_i>pared && cm_d<pared){  //Si la distancia del sensor izquierdo a la pared es mayor a 52, avanza hacia la izquierda
    motord.setSpeed(190);
    motord.run(FORWARD);
    motort.setSpeed(178);
    motort.run(FORWARD);
  }
  if(cm_d>pared && cm_i<pared){  //Si la distancia del sensor derecho a la pared es mayor a 52, avanza hacia la derecha
    motord.setSpeed(190);
    motord.run(BACKWARD);
    motort.setSpeed(178);
    motort.run(BACKWARD);
  }
}


//Distancia de ultrasónico derecho
void ult_D(){
  // Pulso de 10us para inicial el modulo
  digitalWrite(trigPin_D, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_D, LOW);
  duration = pulseIn(echoPin_D, HIGH);      //Devuelve la longitud del pulso del pin Echo en us
  cm_d = microsecondsToCentimeters(duration);     //Convierte la duración en cm

}


//Distancia de ultrasónico izquierdo
void ult_I(){
  // Pulso de 10us para inicial el modulo
  digitalWrite(trigPin_I, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_I, LOW);
  duration = pulseIn(echoPin_I, HIGH);      //Devuelve la longitud del pulso del pin Echo en us
  cm_i = microsecondsToCentimeters(duration);     //Convierte la duración en cm
}


//Calcula distancia en centímetros
long microsecondsToCentimeters(long microseconds){
  return microseconds/58;
 }

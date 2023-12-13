#include <SoftwareSerial.h>
#include <Servo.h>
//CONEXIONES PARA EL BLUETOOTH

int bluetoothTx = 2;
int bluetoothRx = 3;

//SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

//MOTOR 1

int Motor1A = 9;
int Motor1B = 10;

//MOTOR 2

int Motor2A = 11;
int Motor2B = 12;

//CONEXIONES DEL SENSOR

const int Trigger = 5;   //Pin digital 2 para el Trigger del sensor
const int Echo = 6;   //Pin digital 3 para el echo del sensor

int u;

class Auto{
  
  private:
    char toSend;
    int flag1=-1;
    int flag2=-1;
  
  public:
    char asignatoSend();
    void detenerse();
    void avanza();
    void retrocede();
    void derecha();
    void izquierda();
    void otro();
};
void setup() {

  //para inicializar el modulo
  //bluetooth.begin(115200);
  Serial.begin(9600);//para comunicarse con precessing
  //bluetooth.print("$$$");
  delay(10);
  //bluetooth.println("U.9600.N");
  

  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT); 
  digitalWrite(Trigger, LOW);
  
  pinMode( Motor1A, OUTPUT );
  pinMode( Motor2A, OUTPUT );
  pinMode( Motor1B, OUTPUT );
  pinMode( Motor2B, OUTPUT );

  digitalWrite( Motor1A, LOW );
  digitalWrite( Motor2A, LOW );
  digitalWrite( Motor1B, LOW );
  digitalWrite( Motor2B, LOW );
}

Auto MyCar;

void loop() {

  long t; //timepo que demora en llegar el eco
  long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t/59; //escalamos el tiempo a una distancia en cm

 /* if (d<10){
    u = d;
  }else{
    u=0;
  }  */          
  
 // Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
 // Serial.print("cm");
  Serial.println();
  delay(100);

  if (Serial.available()){
    char toSend=MyCar.asignatoSend();
     if(toSend == 'S'){
      MyCar.detenerse();
     }
     if(toSend == 'F' || toSend == 'G' || toSend == 'I'){
      MyCar.avanza();
      }
      if(toSend == 'B' || toSend == 'H' || toSend == 'J'){
        MyCar.retrocede();
        }
      if(toSend == 'L' || toSend == 'G' || toSend == 'I'){
       MyCar.izquierda();
        }
      else if(toSend == 'R' || toSend == 'I' || toSend == 'J'){
      MyCar.derecha();
      }
    }else{
      MyCar.otro();
    }
    
  }

  char Auto::asignatoSend(){
    toSend = (char)Serial.read();
    return toSend;
  }
  void Auto::detenerse(){
     flag1 = 0;
     flag2 = 0;
      digitalWrite(Motor1A, LOW);
      analogWrite(Motor1B, LOW);
      digitalWrite(Motor2A, LOW);
      analogWrite(Motor2B, LOW);   
  }
  
  void Auto::avanza(){
    
      if(flag1 != 1){ //hace que se mueva hacia adelante
        flag1 = 1;
        digitalWrite(Motor1A, HIGH);
        analogWrite(Motor1B, 0);
        digitalWrite(Motor2A, HIGH);
        analogWrite(Motor2B, 0);
      }
    }
    
  void Auto::retrocede(){     
    
    if(flag1 != 2){ //hace que se mueva hacia atras
        flag1 = 2;
        digitalWrite(Motor1B, HIGH);
        analogWrite(Motor1A, 0);
        digitalWrite(Motor2B, HIGH);
        analogWrite(Motor2A, 0);
     }
    
  }
  
  void Auto::izquierda(){
  
    if(flag2 != 2){ //hace que gire hacia la izquierda
        flag2 = 2;
        digitalWrite(Motor1B, HIGH);
        analogWrite(Motor1A, 0);
        digitalWrite(Motor2A, HIGH);
        analogWrite(Motor2B, 0);
      
       }
     }
  void Auto::derecha(){
    
    if(flag2 != 1){ //hace que gire hacia la derecha
        flag2 = 1;
        digitalWrite(Motor2B, HIGH);
        analogWrite(Motor2A, 0);
        digitalWrite(Motor1A, HIGH);
        analogWrite(Motor1B, 0);
    }
  }
        
  void Auto::otro(){
      
    if(flag2 != 3){
        flag2 = 3;
        digitalWrite(Motor2A, LOW);
        analogWrite(Motor2B, LOW);
        digitalWrite(Motor2A, LOW);
        analogWrite(Motor2B, LOW);
    }
  }

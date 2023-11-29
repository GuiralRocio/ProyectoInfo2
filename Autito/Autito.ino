#include <SoftwareSerial.h>
#include <Servo.h>

//CONEXIONES PARA EL BLUETOOTH

int bluetoothTx = 2;
int bluetoothRx = 3;

//CONEXIONES SENSOR

const int Trigger = 5;   //Pin digital 5 para el Trigger del sensor
const int Echo = 6;   //Pin digital 6 para el echo del sensor

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

//MOTOR 1

int Motor1A = 9;
int Motor1B = 10;

//MOTOR 2

int Motor2A = 11;
int Motor2B = 12;

void setup() {

  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U.9600.N");
  bluetooth.begin(9600);

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

int flag1 = -1;
int flag2 = -1;

void loop() {

  if (bluetooth.available()){
    long t; //timepo que demora en llegar el eco
    long d; //distancia en centimetros

    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10);          //Enviamos un pulso de 10us
    digitalWrite(Trigger, LOW);
  
    t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
    d = t/59;             //escalamos el tiempo a una distancia en cm
    // el 59 sale de :v=d/t y se que vel del sonido 340m/s,el tiempo fue medido en us y para obtener la dist en centimetros hay ue hacer regl de 3
    bluetooth.print(u);
    delay(100);
  }
  
  if (bluetooth.available()){
    char toSend = (char)bluetooth.read();
    if(toSend == 'S'){
      flag1 = 0;
      flag2 = 0;
      digitalWrite(Motor1A, LOW);
      analogWrite(Motor1B, LOW);
      digitalWrite(Motor2A, LOW);
      analogWrite(Motor2B, LOW);
      }
    if(toSend == 'F' || toSend == 'G' || toSend == 'I'){
      if(flag1 != 1){ //hace que se mueva hacia adelante
        flag1 = 1;
        digitalWrite(Motor1A, HIGH);
        analogWrite(Motor1B, 0);
        digitalWrite(Motor2A, HIGH);
        analogWrite(Motor2B, 0);
      }
    }
    
    if(toSend == 'B' || toSend == 'H' || toSend == 'J'){
      if(flag1 != 2){ //hace que se mueva hacia atras
        flag1 = 2;
        digitalWrite(Motor1B, HIGH);
        analogWrite(Motor1A, 0);
        digitalWrite(Motor2B, HIGH);
        analogWrite(Motor2A, 0);
      }
    }

    if(toSend == 'L' || toSend == 'G' || toSend == 'I'){
      if(flag2 != 1){ //hace que gire hacia la izquierda
        flag2 = 1;
        digitalWrite(Motor2B, HIGH);
        analogWrite(Motor2A, 0);
        digitalWrite(Motor1A, HIGH);
        analogWrite(Motor1B, 0);
      }
    }

    else if(toSend == 'R' || toSend == 'I' || toSend == 'J'){
      if(flag2 != 2){ //hace que gire hacia la derecha
        flag2 = 2;
        digitalWrite(Motor1B, HIGH);
        analogWrite(Motor1A, 0);
        digitalWrite(Motor2A, HIGH);
        analogWrite(Motor2B, 0);
      }
    }
    else{
      if(flag2 != 3){
        flag2 = 3;
        digitalWrite(Motor2A, LOW);
        analogWrite(Motor2B, LOW);
        digitalWrite(Motor2A, LOW);
        analogWrite(Motor2B, LOW);
      }
    }
  }
}

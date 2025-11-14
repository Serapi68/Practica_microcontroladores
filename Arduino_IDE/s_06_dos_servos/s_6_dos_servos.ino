#include <Servo.h>

const int pinPulsador = 3;
const int pinPot = A0;
const int pinServo1 = 9;
const int pinServo2 = 11;
const int pinLed = 2;

bool activo = false;
int pulsoAnterior = HIGH;
Servo miServo1;
Servo miServo2;

//Funciones
//Activar y desactivar
bool leerpulsador(){
  int estadopulsador = digitalRead(pinPulsador);
  bool cambioEstado = false;
  if(estadopulsador == LOW && pulsoAnterior == HIGH){
    cambioEstado = true;
    delay(50);
  }
  pulsoAnterior = estadopulsador;
  return cambioEstado;
}

//Lectura de potenciometro:
int leerPot(){
  int valor = analogRead(pinPot);
  return valor;
}

//Control del servomotor de 180 grador por el monitor en serie:

void controlServo1(){
  if (Serial.available() > 0){
    int angulo = Serial.parseInt();
    
    if(angulo >= 0 && angulo <= 180){
      miServo1.write(angulo);
      Serial.print("Angulo de mirada: ");
      Serial.println(angulo);
    }else{
      Serial.println("Ingrese valor valido: ");
    }
    while (Serial.available() > 0){
      Serial.read();
    }
  }
}

//Control de velocidad del servo de 360 grados:

void controlServo2(int valor){
  int velocidad = map(valor, 0, 1023, 0, 180);
  if (valor >= 450 && valor <= 600){
    miServo2.write(90);
  }else{
    miServo2.write(velocidad);
  }
}

//bloque donde se apga el sistema:

void sistemaoff(){
  digitalWrite(pinLed,LOW);
  miServo1.write(0);
  miServo2.write(90);
  Serial.println("Sistema Apagado");
}

void setup() {
  miServo1.attach(pinServo1);
  miServo2.attach(pinServo2);
  pinMode(pinLed, OUTPUT);
  pinMode(pinPulsador, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Ingresa un angulo para el servo de 180");
}

void loop() {
  if (leerpulsador()){
    activo = !activo;
    Serial.print("Estado: ");
    Serial.println(activo ? "Activo" : "Inactivo");
  }

  if (activo){
    digitalWrite(pinLed, HIGH);
    int valor = leerPot();
    controlServo1();
    controlServo2(valor);

  }else{
    sistemaoff();
  }
  delay(100);
}

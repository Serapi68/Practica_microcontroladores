#include <Servo.h>

const int pinPotenciometro = A0;
const int Servo1 = 9;
const int Servo2 = 11;
const int pinPulsador = 3;
const int pinLed = 2;
const int pinLed2 = 4;

bool activo = false;
int pulsoAnterior = HIGH;

Servo miServo1;
Servo miServo2;

void setup() {
  
  miServo1.attach(Servo1); // Servo de 180 grados
  miServo2.attach(Servo2); // Servo de 360 grados continuo
  pinMode(pinLed2, OUTPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinPulsador, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {

  int estadoPulsador = digitalRead(pinPulsador);

  if (estadoPulsador == HIGH && pulsoAnterior == LOW){

    activo = !activo;
    delay(50);
  } 

  pulsoAnterior = estadoPulsador;

  if (activo){
    int valor = analogRead(pinPotenciometro); // Lectura de señal analoga
    int angulo = map(valor, 0, 1023, 0, 180); //Angulo de movimiento
    digitalWrite(pinLed, HIGH); //prende luz    
    miServo1.write(angulo);
    
    if (valor > 500 && valor < 600 && activo){
      miServo2.write(90);
      Serial.println("Estacionado");
      digitalWrite(pinLed2, LOW);

    }else{

    int velocidad = map(valor, 0, 1023, 0, 180); // 0 velocidad inversa, 90 = parado, 180 = maxima velocidad de verdad
    digitalWrite(pinLed2, HIGH);
    miServo2.write(velocidad);
    Serial.print("Velocidad: ");
    Serial.println(velocidad);

    
   }
   
    Serial.print("Valor de potenciometro: ");
    Serial.println(valor);
    Serial.print("Angulo de movimiento: ");
    Serial.println(angulo);

  }else{
    
    digitalWrite(pinLed, LOW);
    digitalWrite(pinLed2, LOW);
    miServo1.write(0);
    miServo2.write(90);
    Serial.print("Estado: ");
    Serial.println(activo);

  }
  delay(100);

}

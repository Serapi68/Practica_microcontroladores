#include <NewPing.h>

const int ejeX = A0;
const int pulsador = 3;
const int LedRojo = 5;
const int LedVerde = 6;
const int LedAzul = 7;
const int Trigg = 9;
const int Echo = 10;

NewPing sonar(Trigg, Echo, 100); 

bool activo = true;
int pulsadorAnterior = HIGH;

bool leerpulsador(){
  int estadopulsador = digitalRead(pulsador);
  bool cambioestado = false;
  if(estadopulsador == LOW && pulsadorAnterior == HIGH){
    cambioestado = true;
    delay(50);
  }
  pulsadorAnterior = estadopulsador;
  return cambioestado;
}

int leerumbral(){
  int valorx = analogRead(ejeX);
  int umbral = map(valorx, 0, 1023, 10, 50);
  return umbral;
}

float leerdistancia(){
  float distancia = sonar.ping_cm();
  if (distancia == 0){
    distancia = 100;
  }
  return distancia;
}

void controlLed(float distancia, int umbral){
  if (distancia < 5){
    digitalWrite(LedRojo, HIGH);
    digitalWrite(LedVerde, LOW);
    digitalWrite(LedAzul,LOW);
  }else if(distancia <= umbral){
    digitalWrite(LedRojo,HIGH);
    digitalWrite(LedVerde, HIGH);
    digitalWrite(LedAzul, LOW);
  }else{
    digitalWrite(LedRojo,LOW);
    digitalWrite(LedVerde, HIGH);
    digitalWrite(LedAzul, LOW);
  }
}

void mostrarDatos(float distancia, int umbral){
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println("cm");
  Serial.print("Umbral: ");
  Serial.print(umbral);
  Serial.println("cm");
}

void setup() {
  pinMode(LedRojo, OUTPUT);
  pinMode(LedVerde, OUTPUT);
  pinMode(LedAzul, OUTPUT);
  pinMode(pulsador, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if(leerpulsador()){
    activo = !activo;
  }

  if(activo){
    int umbral = leerumbral();
    float distancia = leerdistancia();
    controlLed(distancia, umbral);
    mostrarDatos(distancia, umbral);
  }else{
    digitalWrite(LedRojo, LOW);
    digitalWrite(LedVerde, LOW);
    digitalWrite(LedAzul, HIGH);
  }
  delay(100);
}

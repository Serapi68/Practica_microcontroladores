#include <OneWire.h>
#include <DallasTemperature.h>

const int ejeX = A0;
const int pinFoto = A1;
const int pinSwitch = 3;
const int pinRojo = 5;
const int pinVerde = 6;
const int pinAzul = 11;
const int pinTemperatura = 8;
const int pinBuzzer = 10;

// Creamos una estructura para comparar y guardar los datos de los sensores

struct SensorData{
  int joystickX;
  int fotocelda;
  float temperatura;
};

// Variables para activacion y desactivacion
bool activo = false;
int pulsoAnterior = HIGH;
OneWire oneWire(pinTemperatura);
DallasTemperature sensors(&oneWire);


//Bloque de funciones:

bool leerpulsador(){                             //Activar o desactivar
  int estadoPulsador = digitalRead(pinSwitch);
  bool cambioestado = false;
  if (estadoPulsador == LOW && pulsoAnterior == HIGH){
    cambioestado = true;
    delay(50);
  }
  pulsoAnterior = estadoPulsador;
  return cambioestado;
}

void leerSensores(SensorData &datos, int valores[]){  //Lectura y pineado de una libreria con los valores de los sensores
  valores[0] = analogRead(ejeX);
  valores[1] = analogRead(pinFoto);
  sensors.requestTemperatures();
  datos.joystickX = valores[0];
  datos.fotocelda = valores[1];
  datos.temperatura = sensors.getTempCByIndex(0);
  if (datos.temperatura == DEVICE_DISCONNECTED_C){
    datos.temperatura = 25.0;
    Serial.println("Sensor de temperatura desconectado ");
  }
}

void mostrarDatos(SensorData datos, int valores[]){ //Muestra de los valores de los sesnores
  Serial.print("Joystick X: ");
  Serial.println(datos.joystickX);
  Serial.print("Luz: ");
  Serial.println(datos.fotocelda);
  Serial.print("Temperatura: ");
  Serial.print(datos.temperatura);
  Serial.println(" °C");
}

void controlarLED(SensorData datos, int valores[]){
  if (datos.temperatura > 30){
    digitalWrite(pinRojo, HIGH);
    digitalWrite(pinVerde, LOW);
    analogWrite(pinAzul, map(valores[0], 0, 1023, 0, 255));
  }else{
    digitalWrite(pinRojo, LOW);
    analogWrite(pinVerde, map(valores[1], 1023, 0, 0, 255));
    analogWrite(pinAzul, map(valores[0], 0, 1023, 0, 255));
  }
}

void controlBuzzer(int valores[]){
  int promedio = (valores[0] + valores[1]) / 2;
  int frecuencia = map(promedio, 0, 1023, 200, 2000);
  tone(pinBuzzer, frecuencia);

}

void apagarSistema(){
  digitalWrite(pinRojo, LOW);
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAzul, LOW);
  noTone(pinBuzzer);
}


void setup() {
  pinMode(pinRojo, OUTPUT);
  pinMode(pinFoto, INPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
  pinMode(pinSwitch, INPUT_PULLUP);
  pinMode(pinBuzzer, OUTPUT);
  sensors.begin();
  Serial.begin(9600);
  Serial.println("Sistema iniciado. Presiona el pulsador del joystick para activar/desactivar.");
}

void loop() {
  if (leerpulsador()){
    activo = !activo;

  }
  if (activo) {
    int valores[2];
    SensorData datos;
    leerSensores(datos, valores);
    mostrarDatos(datos, valores);
    controlarLED(datos, valores);
    controlBuzzer(valores);
  }else{
    apagarSistema();
  }
  delay(50);

}

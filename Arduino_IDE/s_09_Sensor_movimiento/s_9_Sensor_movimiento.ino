const int pinPIR = 8;
const int pinBuzzer = 2;
const int pinRojo = 5;
const int pinVerde = 6;
const int pinAzul = 7;

unsigned long tiempoInicio = 0;
const unsigned long duracionAlerta = 5000;
bool enAlerta = false;

bool detectarMovimiento(){
  return digitalRead(pinPIR) == HIGH;
}

void activarAlerta(){
  enAlerta = true;
  tiempoInicio = millis();
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAzul, LOW);
}

void parpadearRojo() {
  static unsigned long ultimaAlternanciaRojo = 0;
  static bool estadoRojo = false;
  const unsigned long intervaloParpadeo = 200;

  if (enAlerta && millis() - tiempoInicio < duracionAlerta) {
    if (millis() - ultimaAlternanciaRojo >= intervaloParpadeo) {
      ultimaAlternanciaRojo = millis();
      estadoRojo = !estadoRojo;
      digitalWrite(pinRojo, estadoRojo ? HIGH : LOW);
    }
  } else {
    digitalWrite(pinRojo, LOW);
  }
}

void controlBuzzer(){
  static unsigned long ultimoSonido = 0;
  static bool estadobuzzer = false;
  const unsigned long intervaloSonido = 200;
  if(enAlerta && millis() - tiempoInicio < duracionAlerta){
    if(millis() - ultimoSonido >= intervaloSonido){
      ultimoSonido = millis();
      estadobuzzer = !estadobuzzer;
      if(estadobuzzer){
      tone(pinBuzzer, 440);
      }else{
      noTone(pinBuzzer);
      }
    }
  }else{
    noTone(pinBuzzer);
  }
}

void apagarAlerta(){
  enAlerta = false;
  digitalWrite(pinRojo, LOW);
  digitalWrite(pinVerde, HIGH);
  digitalWrite(pinAzul, LOW);
  noTone(pinBuzzer);
  Serial.println("Alerta desactivada");
}

void mostrarDatos(){
  if(enAlerta){
    unsigned long tiempoRestante = duracionAlerta -(millis() - tiempoInicio);
    Serial.print("Alerta activada, Tiempo restante: ");
    Serial.print(tiempoRestante /  1000.0);
    Serial.println("segundos");
  }else{
    Serial.println("Movimiento no detectado");
    delay(200);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(pinPIR, INPUT);
  pinMode(pinAzul, OUTPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  delay(3000);
}

void loop() {
  if(detectarMovimiento() && !enAlerta){
    activarAlerta();

  }
  if(enAlerta){
    if(millis() - tiempoInicio < duracionAlerta){
      controlBuzzer();
      parpadearRojo();
    }else{
      apagarAlerta();
    }
  }
  mostrarDatos();
  delay(200);
}  


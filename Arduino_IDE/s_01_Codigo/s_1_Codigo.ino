
const int pinPulsador = 6;
const int pinLed = 13;
const int pinBuzzer = 10;
const int pinLed2 = 3;
bool secuenciaActiva = false;
int ultimoEstado = LOW;

void setup() {
  pinMode(pinPulsador, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  int estadoPulsador = digitalRead(pinPulsador); //Esta leyendo la entrada de pinPulsador
  if (estadoPulsador == HIGH && ultimoEstado == LOW) { //el INPUT_PULLUP invierte la logica
    
    secuenciaActiva = !secuenciaActiva;

    Serial.println("Secuencia Activada");

    digitalWrite(pinLed, HIGH);

    tone(pinBuzzer, 523);
    delay(1000);

    noTone(pinBuzzer);
    digitalWrite(pinLed,LOW);
    delay(200);

    tone(pinBuzzer, 587);
    digitalWrite(pinLed2, HIGH);
    delay(1000);

    noTone(pinBuzzer);
    digitalWrite(pinLed2, LOW);
    delay(200);

    tone(pinBuzzer, 659);
    digitalWrite(pinLed, HIGH);
    delay(1000);

    noTone(pinBuzzer);
    digitalWrite(pinLed,LOW);
    delay(200);

    tone(pinBuzzer, 698);
    digitalWrite(pinLed2, HIGH);
    delay(1000);

    noTone(pinBuzzer);
    digitalWrite(pinLed2, LOW);
    delay(200);

    tone(pinBuzzer, 783);
    digitalWrite(pinLed, HIGH);
    delay(1000);

    noTone(pinBuzzer);
    digitalWrite(pinLed, LOW);
    delay(200);

    tone(pinBuzzer, 880);
    digitalWrite(pinLed2, HIGH);
    delay(1000);

    noTone(pinBuzzer);
    digitalWrite(pinLed2, LOW);
    delay(200);

    tone(pinBuzzer, 987);
    digitalWrite(pinLed, HIGH);
    delay(1000);

    noTone(pinBuzzer);
    digitalWrite(pinLed, LOW);
    delay(200);

    tone(pinBuzzer, 1046);
    digitalWrite(pinLed2, HIGH);
    delay(1000);

    noTone(pinBuzzer);
    digitalWrite(pinLed2, LOW);
    delay(200);



  }else{
    Serial.println("Alarma Desactivada");
    digitalWrite(pinLed, LOW);
    noTone(pinBuzzer);
  }
}


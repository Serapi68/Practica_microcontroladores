
const int pinBuzzer = 2;
const int pinRojo = 5;
const int pinVerde = 6;
const int pinAzul = 7;
const int pinTrig = 10;
const int pinEcho = 11;

float leerdistancia(){
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  
  long duracion = pulseIn(pinEcho, HIGH);
  float distancia = duracion * 0.034 / 2;
  
  if (distancia < 2 || distancia > 50){
    distancia = -1;
  }
  return distancia;
}

float promediarDistancia(int numLecturas){
  float suma = 0;
  int lecturasValidas = 0;

  for ( int  i = 0; i < numLecturas; i++){
    float distancia = leerdistancia();
    if ( distancia != -1){
      suma += distancia;
      lecturasValidas++;
    }
    delay(50);
  }

  if(lecturasValidas > 0){
    return suma / lecturasValidas;
  }else{
    return -1;
  }
}

void controlLed(float distancia){
  if (distancia == -1){
    digitalWrite(pinRojo, HIGH);
    digitalWrite(pinVerde,LOW);
    tone(pinBuzzer,440);
    while(distancia ==- 1){
      digitalWrite(pinAzul,HIGH);
      delay(200);
      digitalWrite(pinAzul,LOW);
      delay(200);
      distancia = leerdistancia();
    }

  }else if (distancia < 5){
    digitalWrite(pinRojo, HIGH);
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAzul, LOW);
  }else if (distancia < 15){
    analogWrite(pinRojo, 128);
    analogWrite(pinVerde, 100);
    digitalWrite(pinAzul, LOW);
  }else{
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinVerde, HIGH);
    digitalWrite(pinAzul, LOW);
  }
}

void controlBuzzer(float distancia){
  if (distancia < 5){
    tone(pinBuzzer, 329.628);
  }else if (distancia >= 5 && distancia <= 15){
    tone(pinBuzzer, 277.183);
  }else if (distancia > 15){
    tone(pinBuzzer, 220);
  }else{
    noTone(pinBuzzer);
  }
  
}
void mostrarDatos(float distancia){
  if(distancia == -1){
    Serial.print("Error distancia fuera de rango");
  }
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println("cm");
}


void setup() {
  pinMode(pinEcho, INPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinAzul, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float distancia = promediarDistancia(5);
  mostrarDatos(distancia);
  controlLed(distancia);
  controlBuzzer(distancia);
  delay(200);

}

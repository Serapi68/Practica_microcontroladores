const int pinejeX = A0;
const int pinejeY = A1;
const int pinPulsador = 3;
const int pinVerde = 5;
const int pinRojo = 6;
const int pinAzul = 7;
const int pinBocina = 11;

bool activo = false;
int pulsoAnterior = HIGH;

bool leerpulsador(){
  int estadoPulsador = digitalRead(pinPulsador);
  bool cambioEstado = false;
  if(estadoPulsador == LOW && pulsoAnterior == HIGH){
    cambioEstado = true;
    delay(50);
  }
  pulsoAnterior = estadoPulsador;
  return cambioEstado;
}

void leerJoystick(int &x, int &y){
  x = analogRead(pinejeX);
  y = analogRead(pinejeY);
  Serial.print("Joystick X: ");
  Serial.println(x);
  Serial.print("Joystick Y: ");
  Serial.println(y);
}

void controlLED(int x, int y){
  if(x >= 450 && x <= 550 && y >= 450 && y <= 550){
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinVerde, LOW);
    digitalWrite(pinAzul, HIGH);
  } else if(abs( x - 512) > abs(y - 512)){
    analogWrite(pinRojo, map(abs(x-512), 0, 512, 0, 255));
    digitalWrite(pinVerde,LOW);
    digitalWrite(pinAzul, LOW);
  }else{
    analogWrite(pinVerde, map(abs(y-512), 0, 512, 0, 255));
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinAzul, LOW);
  }
}

void controlBocina(int x, int y){
  if(x >= 450 && x <= 550 && y >= 450 && y <= 550){
    noTone(pinBocina);
  } else if( x >= 551){
    tone(pinBocina, 261);
  } else if( x <= 449){
    tone(pinBocina, 440);
  } else if ( y >= 551){
    tone(pinBocina, 349);
  }else{
    tone(pinBocina, 466);
  }
}

void apagarSistema(){
  digitalWrite(pinRojo, LOW);
  digitalWrite(pinVerde, LOW);
  digitalWrite(pinAzul, LOW);
  noTone(pinBocina);
  Serial.println("Estado : Inactivo");
}

void setup() {
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
  pinMode(pinBocina, OUTPUT);
  pinMode(pinPulsador,INPUT_PULLUP);
  Serial.begin(9600); 
} 

void loop() {
  if (leerpulsador()){
    activo = !activo;
    Serial.print("Estado: ");
    Serial.println(activo ? "Activo" : "Inactivo" );
  }

  if(activo){
    int x, y;
    leerJoystick(x,y);
    controlLED(x,y);
    controlBocina(x,y);
  }else{
    apagarSistema();
  }
  delay(100);
}

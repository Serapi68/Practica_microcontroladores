const int pinPotenciometro = A0;
const int pinLed = 5;
const int pinBuzzer = 10;
const int pinBoton = 3;

int frecuenciaAnterior = 0;
int pulsoAnterior = HIGH   ;
bool activo = false;

void setup() {
  pinMode (pinLed, OUTPUT);
  pinMode (pinBuzzer, OUTPUT);
  pinMode (pinBoton, INPUT_PULLUP);
  Serial.begin(9600);


}

void loop() {

  int estadoPulsador = digitalRead(pinBoton); 

  if (estadoPulsador == LOW && pulsoAnterior == HIGH){

    activo = !activo;
    delay(50); 
  }

  pulsoAnterior = estadoPulsador;


  if (activo) {
    int valor = analogRead(pinPotenciometro);
    int brillo = map(valor, 0, 1023, 0 , 200); //Conversion de analogo a PWM
    int frecuencia = map(valor, 0, 1023, 440, 880); // Convierte a HZ   
    
    analogWrite(pinLed, brillo); //Brillo de led


    if (frecuencia != frecuenciaAnterior){
      tone(pinBuzzer, frecuencia);
      frecuenciaAnterior = frecuencia;
    }  
    
    Serial.print("Valor potenciometro: ");
    Serial.println(valor);
    Serial.print("Brillo: ");
    Serial.println(brillo);
    Serial.print("Frecuencia: ");
    Serial.println(frecuencia);

    
  }else {
    analogWrite(pinLed, 0);
    noTone(pinBuzzer);
    Serial.println("Sistema Desactivado...");
  }

  delay(100);
}

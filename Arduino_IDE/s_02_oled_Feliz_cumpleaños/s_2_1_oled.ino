#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int pinBuzzer = 10;
const int pinLed = 2;
const int pinLed2 = 3;
const int pinLed3 = 4;
const int pinPulsador = 6;

int Do   = 261;
int DoS  = 277;
int Re   = 293;
int ReS  = 311;
int Mi   = 329;
int Fa   = 349;
int FaS  = 370; 
int Sol  = 392;
int SolS = 415; 
int La   = 440;
int LaS  = 466; 
int Si   = 493;
int Do8  = 523;
int DoS8 = 554;
int Re8  = 587;
int ReS8 = 622;
int Mi8  = 659;
int Fa8  = 698;
int FaS8 = 739;
int Sol8 = 783;

int corchea = 100;
int negra = 200;
int blanca = 400;
int retardo = 3000;

void setup() {
  pinMode(pinPulsador, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinLed3, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinLed2, OUTPUT); 

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  
    for(;;);
  }
  display.clearDisplay();
  display.display();
}

void nota(int nota, int duracion){
  tone(pinBuzzer, nota, duracion);
  delay(duracion);
  noTone(pinBuzzer);
  delay(duracion);
}

void mostrarMensaje() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  
  // Divido el mensaje en 3 líneas
  String lines[3] = {"FELIZ,", "DIA", "MAMAA!!!!"};
  int y_positions[3] = {8, 28, 48};  // Posiciones verticales
  
  // Imprimo cada línea centrada
  for(int i = 0; i < 3; i++) {
    String line = lines[i];
    int width = line.length() * 12;  // Ancho en píxeles
    int x = (SCREEN_WIDTH - width) / 2;  // Centrado horizontal
    display.setCursor(x, y_positions[i]);
    display.println(line);
  }
  
  display.display();
}

void loop() {
  int estadoPulsador = digitalRead(pinPulsador);
  if (estadoPulsador == HIGH){
    mostrarMensaje();
    
    digitalWrite(pinLed,HIGH);
    nota(Sol, corchea);
    digitalWrite(pinLed, LOW);

    digitalWrite(pinLed3, HIGH);
    nota(Sol, corchea);
    digitalWrite(pinLed3, LOW);

    digitalWrite(pinLed2, HIGH);
    nota(La, negra);
    digitalWrite(pinLed2, LOW);

    digitalWrite(pinLed3, HIGH);
    nota(Sol, negra);
    digitalWrite(pinLed3, LOW);

    digitalWrite(pinLed2,HIGH);
    nota(Do8, negra);
    digitalWrite(pinLed2, LOW);

    digitalWrite(pinLed, HIGH);
    nota(Si, blanca);
    digitalWrite(pinLed, LOW);

    digitalWrite(pinLed,HIGH);
    nota(Sol, corchea);
    digitalWrite(pinLed, LOW);
    
    digitalWrite(pinLed3, HIGH);
    nota(Sol, corchea);
    digitalWrite(pinLed3, LOW);

    digitalWrite(pinLed2, HIGH);
    nota(La, negra);
    digitalWrite(pinLed2, LOW);

    digitalWrite(pinLed3, HIGH);
    nota(Sol, negra);
    digitalWrite(pinLed3, LOW);

    digitalWrite(pinLed2,HIGH);
    nota(Re8, negra);
    digitalWrite(pinLed2, LOW);

    digitalWrite(pinLed, HIGH);
    nota(Do8, blanca);
    digitalWrite(pinLed, LOW);

    digitalWrite(pinLed,HIGH);
    nota(Sol, corchea);
    digitalWrite(pinLed, LOW);
    
    digitalWrite(pinLed3, HIGH);
    nota(Sol, corchea);
    digitalWrite(pinLed3, LOW);

    digitalWrite(pinLed2, HIGH);
    nota(Sol8, negra);
    digitalWrite(pinLed2, LOW);

    digitalWrite(pinLed, HIGH);
    nota(Mi8, negra);
    digitalWrite(pinLed, LOW);

    digitalWrite(pinLed2, HIGH);
    nota(Do8, negra);
    digitalWrite(pinLed2, LOW);

    digitalWrite(pinLed3, HIGH);
    nota(Si, negra);
    digitalWrite(pinLed3, LOW);
    
    digitalWrite(pinLed2, HIGH);
    nota(La, negra);
    digitalWrite(pinLed2, LOW);

    digitalWrite(pinLed, HIGH);
    nota(Fa8, corchea);
    digitalWrite(pinLed, LOW);

    digitalWrite(pinLed2, HIGH);
    nota(Fa8, corchea);
    digitalWrite(pinLed2, LOW);

    digitalWrite(pinLed3, HIGH);
    nota(Mi8, negra);
    digitalWrite(pinLed3, LOW);    

    digitalWrite(pinLed2, HIGH);
    nota(Do8, negra);
    digitalWrite(pinLed2, LOW);

    digitalWrite(pinLed, HIGH);
    nota(Re8, negra);

    digitalWrite(pinLed2, HIGH);
    delay(500);
    digitalWrite(pinLed3, HIGH);
    nota(Do8, retardo);

    digitalWrite(pinLed, LOW);
    delay(500);
    digitalWrite(pinLed2, LOW);
    delay(500);
    digitalWrite(pinLed3, LOW);

    display.clearDisplay(); 
    display.display();
  }


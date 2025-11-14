const int pinFotocelda = A0;
const int pinLed = 5;




void setup() {
  
  pinMode(pinLed, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {

  int fotocelda = analogRead(pinFotocelda);
  int brillo = map(fotocelda, 0, 1023, 0, 255);

  if(fotocelda > 100){
    analogWrite(pinLed,brillo);
  }else{
    brillo = 0;
    analogWrite(pinLed, brillo);
  }


  Serial.print("Fotocelda: ");
  Serial.println(fotocelda);
  Serial.print("Brillo: ");
  Serial.println(brillo);

  delay(100);


}

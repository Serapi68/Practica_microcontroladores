#include <Servo.h>

const int Servo1 = 9;

int ultimoAngulo= 0;

Servo miServo;


void setup() {

  miServo.attach(Servo1);
  Serial.begin(9600);

}

void loop() {
  
  if(Serial.available() > 0){
    int servoPos = Serial.parseInt(); 
  

    if(servoPos >= 0 && servoPos <= 180){
      ultimoAngulo = servoPos;
      Serial.print("Moviendo a: ");
      Serial.println(ultimoAngulo);
    }else{
      Serial.println("Angulo fuera de rango");
    }


    while (Serial.available() > 0){
    Serial.read();

    }
  
    miServo.write(ultimoAngulo); 
  }
  
  delay(10);
}

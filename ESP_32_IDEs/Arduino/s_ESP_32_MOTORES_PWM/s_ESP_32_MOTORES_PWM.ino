// Pines
const int MotorIzq_Avz = 12;
const int MotorIzq_Atr = 13;
const int Ena_Velocidad = 14;
const int Joystick = 34;

// PWM
const int PWM_CHANNEL = 0;
const int PWM_FREQ = 5000;
const int PWM_RESOLUTION = 8;

// DEADZONE
const int Deadzone = 200;

void setup() {
  pinMode(MotorIzq_Avz, OUTPUT);
  pinMode(MotorIzq_Atr, OUTPUT);
  pinMode(Ena_Velocidad, OUTPUT);
  pinMode(Joystick, INPUT);

  // Configurar PWM con LEDC (ESP32)
  ledcSetup (PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin (Ena_Velocidad, PWM_CHANNEL);

  Serial.begin(115200);
  Serial.println("ESP32 + L298N + Joystick INICIADO");
  stopMotor();
}

void patras(int velocidad) {
  digitalWrite(MotorIzq_Avz, LOW);
  digitalWrite(MotorIzq_Atr, HIGH);
  ledcWrite(PWM_CHANNEL, velocidad);
}

void palante(int velocidad) {
  digitalWrite(MotorIzq_Atr, LOW);
  digitalWrite(MotorIzq_Avz, HIGH);
  ledcWrite(PWM_CHANNEL, velocidad);
}

void stopMotor() {
  digitalWrite(MotorIzq_Avz, LOW);
  digitalWrite(MotorIzq_Atr, LOW);
  ledcWrite(PWM_CHANNEL, 0);
}

void loop() {
  int lectura_joy = analogRead(Joystick);
  int centro = 2048;
  int lugar = lectura_joy - centro;  // ← FALTABA EL PUNTO Y COMA

  if (abs(lugar) < Deadzone) {
    stopMotor();
    Serial.println("Parado (zona muerta)");
  } else {
    int velocidad = map(abs(lugar), Deadzone, centro, 0, 255);  // ← center → centro
    velocidad = constrain(velocidad, 0, 255);

    if (lugar > 0) {
      palante(velocidad);
      Serial.print("Adelante - Vel: ");
    } else {
      patras(velocidad);
      Serial.print("Atrás - Vel: ");
    }
    Serial.println(velocidad);
  }

  delay(50);
}
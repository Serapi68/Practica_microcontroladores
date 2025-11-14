import machine
import time
from machine import Pin, ADC, PWM

Adelante = Pin(2, Pin.OUT)
Atras = Pin(4, Pin.OUT)
pwm_Motor = PWM(Pin(5))
pwm_Motor.freq(10000)  # Cambiado a 10 kHz

potenciometro = ADC(Pin(34))
potenciometro.atten(ADC.ATTN_11DB)
potenciometro.width(ADC.WIDTH_12BIT)

while True:
    lectura = potenciometro.read()
    mapeo = int((lectura / 4095) * 65535)
    print("Lectura ADC:", lectura, "PWM:", mapeo)  # Para depuración
    if mapeo > 1310:
        Adelante.value(1)
        Atras.value(0)
        pwm_Motor.duty_u16(mapeo)
    else:
        Adelante.value(0)
        Atras.value(0)
        pwm_Motor.duty_u16(0)
    time.sleep(0.1)

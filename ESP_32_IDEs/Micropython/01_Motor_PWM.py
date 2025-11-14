import machine
import time
from machine import Pin, ADC, PWM

Adelante = Pin(2, Pin.OUT)
Atras = Pin(4, Pin.OUT)
pwm_Motor = PWM(Pin(5))
pwm_Motor.freq(1000)  # Cambiado a 10 kHz

potenciometro = ADC(Pin(34))
potenciometro.atten(ADC.ATTN_11DB)
potenciometro.width(ADC.WIDTH_12BIT)

while True:
    Adelante.value(1)

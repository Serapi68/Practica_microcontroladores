import machine
from machine import Pin, PWM, ADC
import time

led = PWM(Pin(2))
bocina = PWM(Pin(17))
led.freq(1000)
led_rojo = Pin(4, Pin.OUT)
led_verde = Pin(16, Pin.OUT)

potenciometro = ADC(Pin(34))
potenciometro.atten(ADC.ATTN_11DB) #Rango de 0-3.3 Voltios

while True:
    lectura = potenciometro.read()
    mapeo = int((lectura / 4095) * 100) #Rango de 0 a 100%
    lectura_pwm = int(mapeo *10.35)

    if lectura_pwm > 1023:
        lectura_pwm = 1023
    elif lectura_pwm > 500 and lectura_pwm < 700:
        led.duty(lectura_pwm)
        bocina.duty(lectura_pwm)
        led_rojo.value(1)
    elif lectura_pwm > 800 and lectura_pwm < 1000:
        led_verde.value(1)
        led.duty(lectura_pwm)
        bocina.duty(lectura_pwm)
    else:
        bocina.duty(lectura_pwm)
        led_verde.value(0)
        led_rojo.value(0)
        led.duty(lectura_pwm)
    led.duty(lectura_pwm)
    bocina.duty(lectura_pwm)

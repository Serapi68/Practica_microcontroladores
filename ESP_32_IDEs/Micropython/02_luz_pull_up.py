# Escribe tu código aquí :-)
import machine
import time
contador = 0
led = machine.Pin(2, machine.Pin.OUT)
boton = machine.Pin(4, machine.Pin.IN, machine.Pin.PULL_UP)

while True:
    # La lectura de presiona es igual a 0, ya que el PULL_UP es logica negativa
    lectura = boton.value()
    time.sleep(0.2)

    if lectura == 0:
        contador += 1

        if (contador == 1):
            led.value(1)

        else:
            led.value(0)
            contador = 0

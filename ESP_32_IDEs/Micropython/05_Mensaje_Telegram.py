from machine import Pin
import network
import time
import onewire
import ds18x20
import urequests

# Configuración del Wifi

SSID = 'NOMBRE DE RED'
PASSWORD = 'CONTRASEÑA'

#Configuración de sensor:

sensor = Pin(4)

#Dato de bus del protocolo OneWire
ow = onewire.OneWire(sensor)
ds = ds18x20.DS18X20(ow)
#Encuentra el sensor
roms = ds.scan()

#Conecta a wifi
print("Iniciando conexion")
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(SSID, PASSWORD)

timeout = 10

while not wlan.isconnected() and timeout > 0:
    print("Conectando...", timeout, "seg")
    time.sleep(1)
    timeout -= 1

if wlan.isconnected():
    print("¡Conectado! IP:", wlan.ifconfig()[0])
else:
    print("Error: No se conectó. Revisa SSID/clave.")

#Token de telegram
TOKEN = "***************************" #Reemplazar con tu token
CHAT_ID = [*********************, *********************] #Reemplazar con tus chat_id
URL = f"https://api.telegram.org/bot{TOKEN}/sendMessage"


while True:
    ds.convert_temp()       # Solicita lectura
    time.sleep_ms(750)      # Espera conversión
    for rom in roms:
        temp = ds.read_temp(rom)
        print('Temperatura:', temp, '°C')
    #Enviar a telegram
    mensaje = f"Temperatura actual en Alcorcon: {temp:.2f} °C "
    #mensaje = 'Hola desde españa'
    for chat_id in CHAT_ID:
        try:
            respuesta = urequests.post(URL, json={'chat_id': chat_id, 'text' : mensaje})
            respuesta.close()
            print('Mensaje enviado a telegram')
        except Exception as e:
            print('Error al enviar:', e)
    time.sleep(10)

import pygame
import serial

# Inicializar Pygame y el joystick
pygame.init()
pygame.joystick.init()

# Conectar con el HC-05 (ajusta el puerto según corresponda)
ser = serial.Serial('COM3', 9600)

# Inicializar el primer joystick conectado
joystick = pygame.joystick.Joystick(0)
joystick.init()

print(f"Conectado al joystick: {joystick.get_name()}")

while True:
    # Escuchar eventos de pygame
    for event in pygame.event.get():
        if event.type == pygame.JOYAXISMOTION:
            # Capturar los valores de los ejes
            eje_x = joystick.get_axis(0)  # Eje X del joystick
            eje_y = joystick.get_axis(1)  # Eje Y del joystick

            # Determinar la dirección en base a los valores del joystick
            if eje_y < -0.5:
                direccion = "arriba"
            elif eje_y > 0.5:
                direccion = "abajo"
            elif eje_x < -0.5:
                direccion = "izquierda"
            elif eje_x > 0.5:
                direccion = "derecha"
            else:
                direccion = "centro"

            # Imprimir dirección en la consola para depuración
            print(f"Dirección: {direccion}, Eje X: {eje_x:.2f}, Eje Y: {eje_y:.2f}")

            # Enviar el comando correspondiente al Arduino
            #ser.write(direccion.encode())

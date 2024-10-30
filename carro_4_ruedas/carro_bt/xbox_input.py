import pygame
import serial
import time

# Inicializar Pygame y el joystick
pygame.init()
pygame.joystick.init()

# Conectar con el HC-05 (ajusta el puerto según corresponda)
ser = serial.Serial('COM9', 9600)

# Inicializar el primer joystick conectado
joystick = pygame.joystick.Joystick(0)
joystick.init()

print(f"Conectado al joystick: {joystick.get_name()}")

while True:
    con=0
    # Escuchar eventos de pygame
    for event in pygame.event.get():
        if event.type == pygame.JOYAXISMOTION:
            con=con+1
            # Capturar los valores de los ejes
            eje_x = joystick.get_axis(0)  # Eje X del joystick
            eje_y = joystick.get_axis(1)  # Eje Y del joystick
            valor = 0
            # Determinar la dirección en base a los valores del joystick
            if eje_y < -0.5:
                direccion = "w"
                valor=eje_y
            elif eje_y > 0.5:
                direccion = "s"
                valor=eje_y
            elif eje_x < -0.5:
                direccion = "a"
                valor=eje_x
            elif eje_x > 0.5:
                direccion = "d"
                valor=eje_x
            else:
                direccion = "c"
                valor=eje_x
                
            # Imprimir dirección en la consola para depuración
            print(f"{con} Direccion: {direccion}, Eje X: {eje_x:.2f}, Eje Y: {eje_y:.2f}")

            # Enviar el comando correspondiente al Arduino
            #ser.write(direccion.encode())
            
            
            direccion+="-"
            
            # Using the % operator to round to 2 decimal places
            formatted_number = "%.2f" % abs(valor)
            direccion+=formatted_number
            print(formatted_number)
            direccion += "#"
            ser.write(direccion.encode())
            time.sleep(0.150)
            
            

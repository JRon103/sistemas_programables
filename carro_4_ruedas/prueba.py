import tkinter as tk
from tkinter import ttk
import pygame
import time
import serial
import math
import serial.tools.list_ports

# Configuración de puerto serial y velocidad de baudios
velocidad_baudios = 9600
ser = None  # Inicializamos ser como None
reconectando = False  # Variable para verificar si se está reconectando

# Inicializar Pygame y el joystick
pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()
print(f"Conectado al joystick: {joystick.get_name()}")

def obtener_puertos_com():
    puertos = serial.tools.list_ports.comports()
    return [port.device for port in puertos]

def actualizar_puertos():
    nuevos_puertos = obtener_puertos_com()
    puerto_seleccionado.set("")  # Limpiar la selección actual
    puerto_combobox['values'] = nuevos_puertos  # Actualizar los valores del combobox

# Función para intentar la conexión al puerto serial
def conectar_al_puerto():
    global ser, reconectando
    try:
        # Si ya hay una conexión activa, ciérrala
        if ser and ser.is_open:
            ser.close()
            print("Puerto cerrado antes de intentar una nueva conexión.")

        estado_label.config(text="Conectando...")
        print(f"Intentando conectarse al puerto {puerto_seleccionado.get()} con baudrate {velocidad_baudios}")
        ser = serial.Serial(puerto_seleccionado.get(), velocidad_baudios, timeout=2)
        print(f"Conectado al puerto serial: {puerto_seleccionado.get()}")
        estado_label.config(text="Conectado")
        reconectando = False  # Reiniciar la variable de reconexión

    except serial.SerialException as e:
        estado_label.config(text="Error de conexión")
        print(f"Error de conexión: {str(e)}")
        reconectando = True  # Indicar que estamos en modo de reconexión

# Función para manejar la actualización del joystick
def manejar_joystick():
    global ser, reconectando
    if ser and ser.is_open:
        for event in pygame.event.get():
            if event.type == pygame.JOYAXISMOTION:
                valor = 0
                eje_x = joystick.get_axis(0)
                eje_y = joystick.get_axis(1)

                magnitud = math.sqrt(eje_x**2 + eje_y**2)
                if magnitud > 1:
                    eje_x /= magnitud
                    eje_y /= magnitud

                x = centro_x + int(eje_x * radio)
                y = centro_y + int(eje_y * radio)

                canvas.delete("joystick")
                canvas.create_oval(x - 5, y - 5, x + 5, y + 5, fill="red", tag="joystick")

                if abs(eje_x) < 0.2 and abs(eje_y) < 0.2:
                    direccion = "c"
                elif abs(eje_x) > abs(eje_y):
                    direccion = "a" if eje_x < 0 else "d"
                    valor = eje_x
                else:
                    direccion = "w" if eje_y < 0 else "s"
                    valor = eje_y

                direccion += "-" + "%.2f" % abs(valor) + "#"
                ser.write(direccion.encode())
                label_comando.config(text=f"Comando: {direccion}")

    else:
        if ser and not ser.is_open:
            ser.close()
            estado_label.config(text="Perdió conexión")
            print("Conexión cerrada.")
            ser = None  # Reiniciar ser

            # Intentar reconectar
            if not reconectando:  # Solo intentamos reconectar si no estamos ya en ese proceso
                reconectando = True
                while reconectando:  # Mantener el bucle hasta que se reconecte
                    conectar_al_puerto()  # Intenta conectar
                    time.sleep(1)  # Esperar antes de intentar de nuevo

# Crear la ventana principal
ventana = tk.Tk()
ventana.title("Driver Station")

# Crear un combobox para seleccionar el puerto COM
puertos_disponibles = obtener_puertos_com()
puerto_seleccionado = tk.StringVar()
puerto_combobox = ttk.Combobox(ventana, textvariable=puerto_seleccionado, values=puertos_disponibles)
puerto_combobox.set(puertos_disponibles[0] if puertos_disponibles else "")
puerto_combobox.pack()

# Crear un botón para iniciar la conexión
boton_conectar = tk.Button(ventana, text="Conectar", command=conectar_al_puerto)
boton_conectar.pack()

# Crear un botón para actualizar los puertos
boton_actualizar = tk.Button(ventana, text="Actualizar Puertos", command=actualizar_puertos)
boton_actualizar.pack()

# Crear un canvas para dibujar el círculo y el joystick
canvas = tk.Canvas(ventana, width=300, height=300, bg='white')
canvas.pack()

# Crear un label para mostrar el comando
label_comando = tk.Label(ventana, text="Comando:")
label_comando.pack()

# Crear un label para mostrar el estado de conexión
estado_label = tk.Label(ventana, text="Desconectado")
estado_label.pack()

# Dibujar el círculo
centro_x = 150
centro_y = 150
radio = 100
canvas.create_oval(centro_x - radio, centro_y - radio, centro_y + radio, centro_x + radio)

# Actualizar el joystick cada 150ms
def actualizar():
    manejar_joystick()
    ventana.after(150, actualizar)

# Iniciar el mainloop de la ventana y el loop de actualización
ventana.after(150, actualizar)
ventana.mainloop()

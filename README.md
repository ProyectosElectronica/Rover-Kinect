# Rover-Kinect
Archivos fuente del proyecto de un vehículo autónomo utilizando el sensor Kinect de Microsoft

El archivo principal es el Piloto.py, este archivo debe estar en una carpeta llamada rover con archivos de texto (que usted debe crear) titulados:

overrideon.txt
overrideoff.txt
override.txt
accion.txt
ade.txt
atr.txt
izq.txt
der.txt
freno.txt

Estos archivos son para el uso manual del vehículo, los cuales son utilizados por el servidor web, el archivo llamado ServidorRover.c, el ejecutable de este código en C debe estar en la carpeta que contiene la carpeta de rover. 

IMPORTANTE: En el código de ServidorRover.c deben sustituirse todas las líneas que posean GET /rover/ade.txt por
GET [ruta absoluta a la carpeta del servidor]/rover/ade.txt

La explicación de esta aplicación se encuentra en https://electr0nicablog.wordpress.com/?p=37, esta es una aplicación desarrollada en Raspbian para una Raspberry Pi 3.



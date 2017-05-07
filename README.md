# sed-raspduino
Proyecto que comunica dos Arduinos y una Raspberry para implementar un sistema de doble autenticación usando un lector RFID y contraseñas. Fue realizado para la asignatura Sistemas Empotrados Distribuidos. En el repo hay una serie de códigos base y luego los archivos que juntaran varias librerias para usar en las diferentes arduinos-

## Componentes usados:

Usamos los siguientes componentes:

- 1x Raspberry 2.
- 2x Arduino Uno rev. 2.
- LCD comunicado por I2C para ahorrar pines.
- Teclado matricial.
- Sensor RFID.
- LEDs.
- Zumbador.


## Librerias necesarias:

- LCD, se encuentra comprimida en el directorio de LCD_I2C/. [enlace?]:https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library/blob/master/examples/HelloWorld/HelloWorld.ino
- RFID, [liberia de KOOKYE (fabricante)]:http://osoyoo.com/driver/ArduinoRFID.rar
- Teclado Matricial, [liberia de KOOKYE (fabricante)]:http://osoyoo.com/wp-content/uploads/2016/07/Keypad.rar

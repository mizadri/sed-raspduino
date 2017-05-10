# Comportamiento Rasberry


La Raspberry será el servidor central del sistema, encargada de validar los usuarios en la base de datos, así como de realizar la coordinación de los dos Arduinos para que comportamiendo del sistema sea adecuado. el Arduino actuador estará siempre a la escucha por su conexión mediante el puerto serie, y tratará cada orden recibida de la manera adecuada.
Recibirá mensajes del estado de las entradas del sistema recogidas por el ArduinoReceptor y enviará órdenes al Arduino Actuador.

En concreto, responderá a las siguientes situaciones:

- Realizará la conexión con los dos Arduinos, quedando a la espera de mensajes recibidos del ArduinoReceptor.

- Cuando reciba un mensaje del ArduinoReceptor con un RFID UID, comprobará su presencia en la base de datos y enviará un mensaje al ArduinoActuador de vuelta informándole de si el usuario ha sido reconocido (enviando su clave de acceso) o no.
Además, enviará un mensaje 'd' al ArduinoActuador para que pase al modo de esperar que se introduzcan los dígitos de la clave en caso de ser reconocido o que se muestre un mensaje de error si no lo es, enviando el mensaje 'n'.

- Cuando reciba la señal de que el usuario ha pulsado una tecla "normal", informará al ArduinoActuador con un mensaje 'k' para que lo muestre en su pantalla LCD.

- Cuando reciba una señal de que el usuario quiere borrar su intento de clave con la tecla '#', enviará un mensaje 'r' al ArduinoActuador para que lo elimine del LCD.

- Cuando reciba una señal de que el usuario ha introducido una clave válida, enviará un mensaje 'u' al ArduinoActuador para que lo indique en el LCD y abra la puerta del sistema.
En caso de ser una señal incorrecta, enviará al ArduinoActuador un mensaje 'm' si se han alcanzado el número máximo de intentos de introducir la clave o un mensaje 'w' si aún dispone de intentos para introducir la clave.




#Comportamiento Arduino actuador


El Arduino actuador será el encargado de recibir las órdenes de la Raspberry Pi, que a su vez recibirá información de los sensores del Arduino sensor.

En concreto, el Arduino actuador estará siempre a la escucha por su conexión mediante el puerto serie, y tratará cada orden recibida de la manera adecuada.

En concreto, responderá a las siguientes órdenes:

- Mostrar el estado inicial del sistema, indicando que se encuentra a la espera de que se acerque una tarjeta RFID.
Mensaje: "Waiting cards..."

- Mostrar un mensaje cuando la tarjeta RFID no corresponda con un usuario conocido, de manera que se le denegará el acceso al sistema y éste volverá a su estado inicial. Se acompañará con una señal sonora.
Mensaje: "Unknown user. U shall not pass"

- Mostrar un mensaje cuando la tarjeta RFID se reconozca de un usuario conocido, pidiendole que introduzca su clave personal.
Se acompañará con una señal sonora.
Mensaje: "Type your key"

- Mostrar '*' cuando un usuario vaya introduciendo los dígitos de su clave.
Se acompañará con una señal sonora.

- Eliminar los dígitos de la pantalla si un usuario decide borrar alguno.
Se acompañará con una señal sonora.

- Mostrar un mensaje cuando la contraseña introducida por el usuario sea incorrecta.
Tras un lapso de tiempo, podrá volver a introducir la contraseña.
Se acompañará con una señal sonora.
Mensaje: "Wrong password. Try again..."

- Mostrar un mensaje cuando la contraseña sea correcta, abriendo la puerta girando el servomotor. Tras unos segundos, el sistema avisará de que se va a cerrar la puerta. En otro breve instante de tiempo, el sistema volverá al estado inicial con la puerta cerrada.
Se acompañará con una señal sonora.
Mensaje: "Hello user! Unlocked door"
Mensaje: "Attention! Locking door..."



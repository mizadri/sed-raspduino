# Comportamiento Arduino receptor

El Arduino receptor será el encargado de leer el código RFID que se encuentra en los chips o tarjetas RFID de los usuarios. Una vez ha leído un código, inciará la comunicación con la Raspberry para validar la autenticidad del usuario. 

La Raspberry utilizará la respuesta para enviar la contraseña del usuario (en caso de ser válido) o un mensaje de error en caso de no existir. Una vez lo ha recibido, procederá a leer la contraseña que el usuario introduzca a través del teclado matricial y enviará un mensaje de control a la Raspberry que podrá ser uno de los siguientes:

* '''max_attemps''': se enviará en caso de que el usuario introduzca tres contraseñas incorrectas.
* '''correct''': se enviará en caso de que se introduzca una contraseña correcta.
* '''incorrect''': se enviará en caso de que se introduzca una contraseña incorrecta.

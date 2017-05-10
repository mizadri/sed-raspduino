import serial
import os
 
#Arduino con RFID y Teclado
arduinoSensor = serial.Serial('/dev/ttyACM0', 9600)
#Arduino con LCD, servo y zumbador
# arduinoActuador = serial.Serial('/dev/ttyACM1', 9600)
 
print("System ON. Waiting for inputs...")
 
continuar = True
while continuar:
	mensaje = arduinoSensor.readline()
	print(mensaje)
	# arduinoSensor.write('d')	
	# if mensaje.
	''' if reconocido_usuario_rfid:
		comando = "d"
	elif !reconocido_usuario_rfid:
		comando = "n"
	elif type_digit:
		comando = "k"
	elif remove_digit: 
		comando = "r"
	elif !correct_pass:
		comando = "w"
	elsif correct_pass:
		comando = "u"
 	'''
        # arduinoActuador.write(comando) #Mandar un comando hacia Arduino actuador

# arduinoActuador.close() #Finalizamos la comunicacion
arduinoSensor.close()

import serial
import os
import MySQLdb

# Información base de datos 
DB_HOST = 'localhost' 
DB_USER = 'root' 
DB_PASS = '' # Completar!!
DB_NAME = 'sed'
 
#Arduino con RFID y Teclado
arduinoSensor = serial.Serial('/dev/ttyACM0', 9600)
#Arduino con LCD, servo y zumbador
arduinoActuador = serial.Serial('/dev/ttyACM1', 9600)
 
print("System ON. Waiting for inputs...")
 
continuar = True
while continuar:
	mensaje = arduinoSensor.readline()
	# print(mensaje)

	if mensaje.split(':')[0] == "UID : ":
                rfid_uid =  mensaje.split(':')[1]
                res = consultaUsuario(rfid_uid)
                arduinoSensor.write(res)
                if res == False: # Usuario desconocido 
                        arduinoActuador.write('n')
                else: # Usuario conocido
                        arduinoActuador.write('d')
        elif mensaje == "key": # Pulsa tecla normal
                arduinoActuador.write('k')
        elif mensaje == "remove": # Pulsa tecla de borrado de clave
                arduinoActuador.write('r')
        elif mensaje == "correct": # La contraseña era correcta
                arduinoActuador.write('u')
        elif mensaje == "incorrect": # La contraseña no era correcta
                arduinoActuador.write('w')
        elif mensaje == "max_attempts":
                arduinoActuador.write('m')
	

arduinoActuador.close() #Finalizamos la comunicacion
arduinoSensor.close()

def run_query(query): 
    datos = [DB_HOST, DB_USER, DB_PASS, DB_NAME] 
    conn = MySQLdb.connect(*datos) # Conectar a la base de datos 
    cursor = conn.cursor()         # Crear un cursor 
    cursor.execute(query)          # Ejecutar una consulta 
 
    query.upper().startswith('SELECT'): 
    data = cursor.fetchall()   # Traer los resultados de un select 
 
    cursor.close()                 # Cerrar el cursor 
    conn.close()                   # Cerrar la conexion 
 
    return data

def consultaUsuario(rfid):
     result = run_query('SELECT * FROM usuarios')
     if result == blablabla:
             
     else:

     return result        

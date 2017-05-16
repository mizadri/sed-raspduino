import serial
import os
import MySQLdb

def run_query(query): 
    datos = [DB_HOST, DB_USER, DB_PASS, DB_NAME] 
    conn = MySQLdb.connect(*datos) # Conectar a la base de datos 
    cursor = conn.cursor()         # Crear un cursor 
    cursor.execute(query)          # Ejecutar una consulta 
 
    query.upper().startswith('SELECT') 
    data = cursor.fetchall()   # Traer los resultados de un select
        
    result = False     
    for row in data:
         result = row[0]

    cursor.close()                 # Cerrar el cursor 
    conn.close()                   # Cerrar la conexion 
    return result    
 
def consultaUsuario(rfid):
     print(rfid)   
     val = rfid.strip()
     #print(val)
     msg = "SELECT codAcceso FROM usuarios WHERE codRFID LIKE '%s'" % val
     print(msg)
     result = run_query(msg)
     
     if result == False:
             result = "FALSE"
        
     return result        


# Informacion base de datos 
DB_HOST = 'localhost' 
DB_USER = 'root' 
DB_PASS = 'VillerKulla1993' # Completar!!
DB_NAME = 'sed'
 
#Arduino con RFID y Teclado
arduinoSensor = serial.Serial('/dev/ttyACM0', 9600)
#Arduino con LCD, servo y zumbador
# arduinoActuador = serial.Serial('/dev/ttyACM1', 9600)
 
print("System ON. Waiting for inputs...")
 
continuar = True
while continuar:
	mensaje = arduinoSensor.readline()
	print(mensaje)
	if mensaje.split(':')[0] == "UID":
                rfid_uid =  mensaje.split(':')[1]
                res = consultaUsuario(rfid_uid)
                print(res)
                arduinoSensor.write(str(res))
                """
                if res == False:
                        #arduinoActuador.write('n')
                else:
                        #arduinoActuador.write('d')
                """
        elif mensaje.strip() == "key": # Pulsa tecla normal
               #arduinoActuador.write('k')
                print('k')
        elif mensaje.strip() == "remove": # Pulsa tecla de borrado de clave
               #arduinoActuador.write('r')
                print('r')
        elif mensaje.strip() == "correct": # La contrasena era correcta
               #arduinoActuador.write('u')
                print('u')
        elif mensaje.strip() == "incorrect": # La contrasena no era correcta
               #arduinoActuador.write('w')
                print('w')
        elif mensaje.strip() == "max_attempts":
               #arduinoActuador.write('m')
                print('m')
	

#arduinoActuador.close() #Finalizamos la comunicacion
arduinoSensor.close()


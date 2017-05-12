#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9

const char CLAVE[4] = {'1','9','9','3'};
char INTENTO[4] = {'X', 'X', 'X', 'X'};
int pos = 0;
int maxIntentos = 3;
int nIntentos = 0;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2, 0}; //connect to the column pinouts of the keypad
bool autorizado = false;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad
 
void setup(){
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println();

}

void borraClave(){
  for(int i = 0; i < 4; i++){
     INTENTO[i] = 'X';
  }  
}

void loop() 
{
    // Solo entra a comprobar la password si se ha reconocido un RFID valido
    if (autorizado){
    char customKey = customKeypad.getKey();
  
    if (customKey){
      
      if(customKey == '#'){ // Borrar intento de clave actual
           borraClave();
	   pos = 0;
	   // Mandar a Raspy una señal de que se ha borrado la clave
	   Serial.println("remove");
      }
      else if(customKey == '*'){ // Comprobar clave 
        
          int correcto = 1;  
          for(int i = 0; i < 4; i++){
            if(INTENTO[i] != CLAVE[i]){
              correcto = 0;
            }
          }
          
          if (correcto){
              autorizado = false;
              nIntentos = 0;
              // Hacer cosas de abrir cajas
              Serial.println("correct");
          }else{
              // Si falla muchas veces o timer quitar la autorizacion a RFID
              nIntentos++;
              if (nIntentos == maxIntentos){
					// mandar aviso a Raspy de que ha superado intentos
					Serial.println("max_attempts");
					nIntentos = 0;
					autorizado = false;
				  }
			  else{
					// mandar aviso a Raspy de clave erronea	
				   Serial.println("incorrect");

			  }
			}
	  pos = 0; 
	  borraClave();
       /*
          for(int i = 0; i < 4; i++){
                  Serial.print(INTENTO[i]);
          }
          Serial.println();
  	*/     
      }
      else{
		 // Enviar mensaje a Raspy de que se ha pulsado tecla "normal"
		 Serial.println("key");
		 if (pos < 3){
			  INTENTO[pos] = customKey;
			  pos = (pos + 1)% 4;
		 }
      }
      delay(100);
    }

  }
  else{
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()){
      return;
    }
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()){
      return;
    }
    //Show UID on serial monitor
    Serial.print("UID :");
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++){
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);
       content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
     Serial.println();
     content.toUpperCase();
     // Enviar mensaje a Raspy con el RFID UID a comprobar
     
     // Recibir la respuesta de la Raspy, con un "false" o la clave del usuario si es conocido  
    String mensaje = Serial.readString();
    if (mensaje != "FALSE"){
		// Guardar la clave para comprobar con lo que introduzca el usuario por teclado
		autorizado = true;
        delay(3000);
        delay(3000);
    }
    else{
		autorizado = false;
        delay(3000); 
    }
    
    /*
    if (content.substring(1) == "30 13 D2 7E" || content.substring(1) == "E0 DD 5F 7E"){
      Serial.println();
      autorizado = true;
      delay(3000);
    }
   
   else{
      autorizado = false;
      delay(3000);
    }
    */
  }
  

} 



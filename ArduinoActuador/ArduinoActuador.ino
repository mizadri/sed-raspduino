#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"
#include <Servo.h>

// Notas en la melodía
int melodyWin[] = {
  NOTE_G4, NOTE_G4, NOTE_B4, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_D5};
int noteDurationsWin[] = { 
  8, 4, 4, 2, 8, 8, 8, 8, 8, 2};

// Servo y su angulo
Servo myServo;
int servoValue;

// LCD y posiciones
LiquidCrystal_I2C lcd(0x27, 16,2); 
int posCol,posRow;

// Pines servo y buzzer
int PIN_SERVO = 9, PIN_BUZZER = 8;


void setup(){
  Serial.begin(9600); //Inicializo el puerto serial a 9600 baudios
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  servoValue = 0;
  myServo.attach(PIN_SERVO);
  myServo.write(servoValue); // posicion inicial 0 grados
  initLCD();
}

void loop(){  

  if (Serial.available()) { //Si está disponible
    char c = Serial.read(); //Guardamos la lectura en una variable char

    switch(c){
    case 'd': // Se ha reconocido la tarjeta RFID, se pide clave
      limpiaLCD();
      enterKey();
      break;
    case 'n': // La tarjeta RFID no esta reconocida
      limpiaLCD();
      lcd.print("Unknown user");
      lcd.setCursor(0, 1);
      lcd.print("U shall not pass!");   
      wrong_tone();       
      posRow++;
      delay(2000);
      initLCD();
      break;
    case 'm': // Se ha alcanzado el máximo número de intentos para introducir la clave
      limpiaLCD();
      lcd.print("Max attempts");
      lcd.setCursor(0, 1);
      lcd.print("reached");   
      wrong_tone();       
      posRow++;
      delay(2000);
      initLCD();
      break;
    case 'k': // El usuario escribe un digito
      if(posCol < 4) {
        lcd.setCursor(posCol, posRow);
        lcd.print("*");
        posCol++;
      }
      writing_tone();            
      break;
    case 'r': // El usuario borra un digito
      if(posCol > 0){
        posCol = 0;
        borrarDigitos();
      }
      remove_tone(); 
      break;
    case 'w': // La contraseña es incorrecta, a los 2 segundos se pide de nuevo
      limpiaLCD();
      lcd.print("Wrong password");
      lcd.setCursor(0, 1);
      lcd.print("Try again...");
      wrong_tone(); 
      delay(2000);
      limpiaLCD();
      enterKey();
      break;
    case 'u': // La contraseña es correcta, se abre la puerta, a los 5 segundos se cierra y pasados 2 segundos el sistema vuelve al estado inicial
      limpiaLCD();
      lcd.print("Hello user!");
      lcd.setCursor(0, 1);
      lcd.print("Unlocked door :)");
      servoValue = 90;
      myServo.write(servoValue);
      granted_tone();              
      delay(5000);
      lockSystem();
      delay(2000);
      initLCD();
      break;
    }
  } 
}


// ------------------------------------ METODOS ESCRITURA LCD -------------------------

void limpiaLCD(){
  lcd.clear();
  posCol = 0;
  posRow = 0;
  lcd.setCursor(posCol, posRow);
}

void borrarDigitos(){
  lcd.setCursor(posCol,posRow);
  lcd.print("          ");
}

void initLCD(){
  limpiaLCD();
  lcd.print("Waiting cards...");
}

void enterKey(){
  lcd.print("Enter your key:");
  posRow++;
  typing_tone();
}

void lockSystem(){
  limpiaLCD();
  lcd.print("Attention!");
  lcd.setCursor(0, 1);
  lcd.print("Locking door...");
  servoValue = 0;
  myServo.write(servoValue);
  closing_tone();
}


// ------------------------------------ METODOS TONOS BUZZER -------------------------

void wrong_tone(){
  tone(PIN_BUZZER,NOTE_A3 ,200 );
  delay(300);
  noTone(PIN_BUZZER); 
}

void granted_tone(){
  for (int thisNote = 0; thisNote < 10; thisNote++) {
    int noteDurationWin = 1000/noteDurationsWin[thisNote];
    tone(PIN_BUZZER, melodyWin[thisNote],noteDurationWin);
    int pauseBetweenNotes = noteDurationWin * 1.30;
    delay(pauseBetweenNotes);
    noTone(PIN_BUZZER);
  }
}

void typing_tone(){
  tone(PIN_BUZZER,NOTE_G4,35);
  delay(35);
  tone(PIN_BUZZER,NOTE_G5,35);
  delay(35);
  tone(PIN_BUZZER,NOTE_G6,35);
  delay(35);
  noTone(PIN_BUZZER);
}

void writing_tone(){
  tone(PIN_BUZZER,NOTE_D8 ,8 );
  delay(8);
  noTone(PIN_BUZZER);
}

void remove_tone(){
  tone(PIN_BUZZER,NOTE_D6 ,8 );
  delay(8);
  noTone(PIN_BUZZER);    
}

void closing_tone(){
  tone(PIN_BUZZER,NOTE_A3 ,200 );
  delay(500);
  tone(PIN_BUZZER,NOTE_A3 ,200 );
  delay(500);
  tone(PIN_BUZZER,NOTE_A3 ,200 );
  delay(500);
  noTone(PIN_BUZZER); 
}


                                     

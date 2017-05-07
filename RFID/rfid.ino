/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/    
 * www.osoyoo.com water drop sensor
 * program tutorial : http://osoyoo.com/2016/07/04/arduino-rfid/
 *  Copyright John Yu
 */


// libraries
#include <SPI.h>
#include <RFID.h>
#include <Servo.h>
#include "pitches.h"
#include <Wire.h>

// RFID definition
RFID rfid(10,9);

// 5 data bytes from cards
// you can read these bytes on the Serial console
byte userC[5] = {0x30,0x13,0xD2,0x7E,0x8F}; // user C     
byte userB[5] = {0xE5,0x60,0xD8,0x65,0x38}; // User B
byte userA[5] = {0x01,0x9A,0x92,0x2b,0x23}; // User A
// Add allowed card IDs here

// // LCD address and type declaration

byte serNum[5];
byte data[5];
int cardRead;  // card read 1 = good 0 = bad for playTune function
String Name;   // used for user name displayMsg function

// Melodies definition: access, welcome and rejection
int access_melody[] = {NOTE_G4,0, NOTE_A4,0, NOTE_B4,0, NOTE_A4,0, NOTE_B4,0, NOTE_C5,0};
int access_noteDurations[] = {8,8,8,8,8,4,8,8,8,8,8,4};
int fail_melody[] = {NOTE_G2,0, NOTE_F2,0, NOTE_D2,0};
int fail_noteDurations[] = {8,8,8,8,8,4};

// pins definition - LED, Buzzer and Servo-motor
int LED_access =2;
int LED_intruder =3;
int speaker_pin = 8;
int servoPin = 9;

// servo motor definition
Servo doorLock;


void setup(){
  Serial.begin(9600);           // Serial communication initialization                // Clears the LCD display
  SPI.begin();                  // SPI communication initialization
  rfid.init();                  // RFID module initialization
  Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  Serial.println("+ project tutorial: http://osoyoo.com/2016/07/04/arduino-rfid/                                             +"); 
  Serial.println("+ Arduino RFID Security System using MFRC522-AN                                       +");
  Serial.println("+ The RFID module is initiate in the automatic read mode, waiting for a valid card... +");
  Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  delay(3000);

}
 
void loop(){
 
  // Here you can create a variable for each user
  // NAME_card ou KEY_card
  boolean userC_card = true; // that is user C
  boolean userB_card = true; // that is user B
  boolean userA_card = true; // that is user A
  //put another users here
  
  if (rfid.isCard()){ // valid card found
    if (rfid.readCardSerial()){ // reads the card
      delay(1000);
      data[0] = rfid.serNum[0]; // stores the serial number
      data[1] = rfid.serNum[1];
      data[2] = rfid.serNum[2];
      data[3] = rfid.serNum[3];
      data[4] = rfid.serNum[4];
    }
  rfid.halt(); // RFID module to standby
  cardRead = 0;
  displayID_Console(); // used for testing purposes only. Prints the Card ID at the serial console 
  for(int i=0; i<5; i++){
    if(data[i] != userC[i]) userC_card = false; // if it is not a valid card, put false to this user
    if (data[i] != userB[i]) userB_card = false;
    if (data[i] != userA[i]) userA_card = false;
    // Here you can check the another allowed users, just put lines like above with the user name
  }
  
  Serial.println(); // used for testing purposes  only
  if (userC_card){ // if a valid card was found
    cardRead = 1;
    Serial.println("C");  }
  else if(userB_card){
    cardRead = 1;
    Serial.println("B");  }
  else if(userA_card){
    cardRead = 1;
    Serial.println("A"); // used for testing purposes  only
  }
  // another cards analysis, put many blocks like this 
  // as many users you have
  
  else{ // if a card is not recognized
    Serial.println("Card not recognized!  contact administration!"); // used for testing purposes  only
    delay(1000);
  }
  if (userC_card || userB_card || userA_card){// add another user using an logical or condition || 
    Serial.println("Access Granted!... Welcome to Osoyoo.com!"); // used for testing purposes  only
    delay(3000); // wait 5 senconds
  }
  Serial.println(); // used for testing purposes  only
  delay(1000);
  rfid.halt(); // wait till sense a card over the reader
  }
}

  

 // lcd.print(rfid.serNum[0],HEX);
  



void displayID_Console(){
  Serial.print("Card found - code:");
  if(rfid.serNum[0] < 16){
    Serial.print("0");
  }
  Serial.print(rfid.serNum[0],HEX);
  Serial.print(" ");
  if(rfid.serNum[1] < 16){
    Serial.print("0");
  }
  Serial.print(rfid.serNum[1],HEX);
   Serial.print(" ");
  if(rfid.serNum[2] < 16){
    Serial.print("0");
  }
  Serial.print(rfid.serNum[2],HEX);
   Serial.print(" ");
  if(rfid.serNum[3] < 16){
    Serial.print("0");
  }
  Serial.print(rfid.serNum[3],HEX);
   Serial.print(" ");
  if(rfid.serNum[4] < 16){
    Serial.print("0");
  }
  Serial.print(rfid.serNum[4],HEX);
   Serial.print(" ");
}

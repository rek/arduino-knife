#include <stdint.h>
#include "Arduino.h" // for serial
#include "headers.h"
//#include "pitches.h"

const int buzzerPin = 19;

void beep(int note, int duration){
  //tone(buzzerPin, note, duration);

  note_t noteToPlay = NOTE_C;
  
  if (note == 100) {
    noteToPlay = NOTE_Cs;
  }

//typedef enum {
//    NOTE_C, NOTE_Cs, NOTE_D, NOTE_Eb, NOTE_E, NOTE_F, NOTE_Fs, NOTE_G, NOTE_Gs, NOTE_A, NOTE_Bb, NOTE_B, NOTE_MAX
//} note_t;
  Serial.println("Sound");  
  Serial.println(duration);  
  Serial.println(noteToPlay);  

  ledcAttachPin(buzzerPin, 0);
  ledcWriteNote(buzzerPin, noteToPlay, 4);
 
  delay(duration);

  ledcDetachPin(buzzerPin);
}

void onSound() {
  Serial.println("Playing on sound");  
  beep(NOTE_C, 300); 
  beep(NOTE_Cs, 200); 
}
//void playShutdown() {
//  beep(NOTE_F4, 300);    
//  beep(NOTE_D4, 200);       
//  beep(NOTE_A3, 200);   
//}

void playScale(uint8_t pin, uint8_t channel) {
//  ledcSetup(0, 2000, 8); // setup beeper

//  ledcAttachPin(buzzerPin, channel);
//  ledcWriteNote(buzzerPin, NOTE_C, 4);
//  delay(500);
//  ledcWriteNote(buzzerPin, NOTE_D, 4);
//  delay(500);
//  ledcWriteNote(buzzerPin, NOTE_E, 4);
//  delay(500);
//  ledcWriteNote(buzzerPin, NOTE_F, 4);
//  delay(500);
//  ledcWriteNote(buzzerPin, NOTE_G, 4);
//  delay(500);
//  ledcWriteNote(buzzerPin, NOTE_A, 4);
//  delay(500);
//  ledcWriteNote(buzzerPin, NOTE_B, 4);
//  delay(500);
//  ledcDetachPin(buzzerPin)
}

#include <stdint.h>

#include "headers.h"
#include "pitches.h"

const int buzzerPin = 8;

void beep(int note, int duration){
//  tone(buzzerPin, note, duration);

//  ledcAttachPin(buzzerPin, 0);
//  ledcWriteNote(buzzerPin, note, 4);
// 
//  delay(duration);
//
//  ledcDetachPin(buzzerPin)
}

void onSound() {
  beep(NOTE_A4, 300); 
  beep(NOTE_A5, 200); 
}
void playShutdown() {
  beep(NOTE_F4, 300);    
  beep(NOTE_D4, 200);       
  beep(NOTE_A3, 200);   
}

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

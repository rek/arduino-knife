#include <stdint.h>
#include "Arduino.h" // for serial
#include "headers.h"

#define BUZZER_PIN         19
// use first channel of 16 channels (started from zero)
#define LEDC_CHANNEL_0     0
// use 13 bit precission for LEDC timer
#define LEDC_TIMER_13_BIT  13
// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ     3000

void buzzerSetup() {
  Serial.println("Doing buzzer setup");  
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
  ledcAttachPin(BUZZER_PIN, 0);
}

void beep(int note, int duration){
//typedef enum {
//    NOTE_C, NOTE_Cs, NOTE_D, NOTE_Eb, NOTE_E, NOTE_F, NOTE_Fs, NOTE_G, NOTE_Gs, NOTE_A, NOTE_Bb, NOTE_B, NOTE_MAX
//} note_t;

//  Serial.print("Sound duration: ");  
//  Serial.println(duration);  
//  Serial.print("Sound note: ");  
//  Serial.println(note);  

  if (note == 0) {
    return;
  }

  if (note < 0) {
    note = note * -1;
  }

  if (note <= 0){
    Serial.print("Bad note: ");  
    Serial.println(note);  
    return;
  }
  if (note > 7000){
    Serial.print("Bad note: ");  
    Serial.println(note);  
    return;
  }

  
  ledcWriteTone(LEDC_CHANNEL_0, note);
 
  delay(duration);
  
  ledcWriteTone(LEDC_CHANNEL_0, 0); // stop the tone playing:
  // ledcDetachPin(BUZZER_PIN);
}

void playOnSound() {
  Serial.println("Playing on sound");  
  beep(2000, 300); 
  beep(2200, 200); 
}

void playOffSound() {
  Serial.println("Playing off sound");  
  beep(2000, 300);    
  beep(1500, 200);       
  beep(1000, 200);   
}

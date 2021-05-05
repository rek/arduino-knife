#pragma once

//typedef enum {
//    NOTE_C, NOTE_Cs, NOTE_D, NOTE_Eb, NOTE_E, NOTE_F, NOTE_Fs, NOTE_G, NOTE_Gs, NOTE_A, NOTE_Bb, NOTE_B, NOTE_MAX
//} note_t;

void beep(int note, int duration);
void onSound();

void playScale(uint8_t pin, uint8_t channel);
void playMusic();
void playShutdown();

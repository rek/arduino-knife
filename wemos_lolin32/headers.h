#pragma once

void beep(int note, int duration);
void onSound();

void playScale(uint8_t pin, uint8_t channel);
void playMusic();
void playShutdown();

void wifiLoopAction();

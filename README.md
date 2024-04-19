# Knife Sharpening - Digital trainer

## Dev

Install the board pack in Arduino IDE: esp32 from espressif

Set the board to: WEMOS LOLIN 32
Baud rate: 115200

## Usage

Connect to the wifi: 'Knife Sharpner'

Browse to: 192.168.1.1

## Features


[x] - make app not sleep
[x] - move beep down 200 db
[x] - stop beep after round of sharpening, eg: raised X by x amound - add a sensor stop of 500ms after this detection. since this is only triggered from x accel, which is only the start of the return movement.
[X] - make main page number reset to 0 after hitting TARE (eg: show only deviation on main page)
[X] - level table button - TARE
[ ] - preset angles
[ ] - web server to see angles.
[ ] - history of set angles

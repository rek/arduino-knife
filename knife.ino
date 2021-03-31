#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "pitches.h"

/* 

   Connections
   ===========

   XYZ:
   SCL to analog 5
   SDA to analog 4
   VDD to 3.3-5V DC
   GROUND to common ground

   Buzzer:
   S to digital 8
   - to GND

   Button:
   either to digital 12
   either to GND

*/
const int button = 12;

/* Set the delay between fresh samples */
uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;

const int buzzerPin = 8;

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

bool setupComplete = false;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");

  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  // setup initial button state
  pinMode(button, INPUT_PULLUP);

  delay(500); // needs time to startup

  // beep to indicate ready to start
  beep(NOTE_A4, 300); 
}

void beep(int note, int duration){
  tone(buzzerPin, note, duration);
  delay(duration);
}

int buzzerNote = 2500;
int goodLevel = -1;

void setInitialPosition(int z) {
  Serial.print("Set base level at:");
  Serial.println(z);
  goodLevel = z;
  beep(NOTE_A4, 300); 
  beep(NOTE_A5, 200);    
}

int getReading() {
  // read from sensors:
  sensors_event_t orientationData , angVelocityData , linearAccelData, magnetometerData, accelerometerData, gravityData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  // printEvent(&orientationData);

  uint8_t system, gyro, accel, mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);

  delay(BNO055_SAMPLERATE_DELAY_MS);

  return orientationData.orientation.z;
}

void loop(void)
{
  // for fun and testing:
  // playMusic(); return;

  int z = getReading();

  if (!setupComplete) {
    //Serial.print("Button state: ");
    //Serial.println(digitalRead(button));

    // button is pressed
    if (digitalRead(button) == 0) {     
      // so save angle
      setInitialPosition(z);
      setupComplete = true;
      Serial.print("Reset angle to: ");
      Serial.println(goodLevel) ;
      delay(1000);
    }

  } else {
    amountFromLevel(z);
    
    if (digitalRead(button) == 0) {
      Serial.println("Stopped reading");
      setupComplete = false;
      beep(NOTE_F4, 300);    
      beep(NOTE_D4, 200);       
      beep(NOTE_A3, 200);       
    }
  }
}

void amountFromLevel(int currentLevel) {
  const int okDeviation = 3;

  Serial.print("Current: ");
  Serial.println(currentLevel);

  if (goodLevel == currentLevel) {
    return 0;
  }

  if (goodLevel > currentLevel) {
    int deviation = goodLevel - currentLevel ;

    if (deviation < okDeviation) {
      return 0;
    }

    if (deviation > 90) {
      playMusic();
    }

    Serial.print("Below ");
    Serial.println(deviation);    
    int speedOfSound = 100;
    if (deviation > 20) {
      speedOfSound = 300;
    } else {
      speedOfSound = 100;
    }
    beep(deviation * 100, speedOfSound);  
  } else {
    int deviation = currentLevel - goodLevel ;

    if (deviation < okDeviation) {
      return 0;
    }

    Serial.print("Above ");
    Serial.println(deviation);   
    int speedOfSound = 100;
    if (deviation > 20) {
      speedOfSound = 300;
    } else {
      speedOfSound = 100;
    }
     
    beep(deviation * 100, speedOfSound);  
  }
}

void printEvent(sensors_event_t* event) {
  double x = -1000000, y = -1000000 , z = -1000000; //dumb values, easy to spot problem
  if (event->type == SENSOR_TYPE_ORIENTATION) {
    Serial.print("Orient:");
    x = event->orientation.x;
    y = event->orientation.y;
    z = event->orientation.z;
  }
  Serial.print("\tx= ");
  Serial.print(x);
  Serial.print(" |\ty= ");
  Serial.print(y);
  Serial.print(" |\tz= ");
  Serial.println(z);
}

void playMusic() {
  beep(NOTE_A4, 500);
  beep(NOTE_A4, 500);    
  beep(NOTE_A4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);  
  beep(NOTE_A4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 650);
 
  delay(500);
 
  beep(NOTE_E5, 500);
  beep(NOTE_E5, 500);
  beep(NOTE_E5, 500);  
  beep(NOTE_F5, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_GS4, 500);
  beep(NOTE_F4, 350);
  beep(NOTE_C5, 150);
  beep(NOTE_A4, 650);
 
  delay(500);
 
  beep(NOTE_A5, 500);
  beep(NOTE_A4, 300);
  beep(NOTE_A4, 150);
  beep(NOTE_A5, 500);
  beep(NOTE_GS5, 325);
  beep(NOTE_G5, 175);
  beep(NOTE_FS5, 125);
  beep(NOTE_F5, 125);    
  beep(NOTE_FS5, 250);
 
  delay(325);
 
  beep(NOTE_AS4, 250);
  beep(NOTE_DS5, 500);
  beep(NOTE_D5, 325);  
  beep(NOTE_CS5, 175);  
  beep(NOTE_C5, 125);  
  beep(NOTE_AS4, 125);  
  beep(NOTE_C5, 250); 
   
  delay(350);
}

#include <Wire.h>

#include "headers.h"
#include "xyz.h"
#include "wifiBroadcast.h"

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

class MainSystem
{
public:
  MainSystem();
  void setup();
  XYZ xyz;
  WifiBroadcast wifiBroadcast;
  
  int getDeviationFromBase(int currentLevel);
  bool setupComplete;
  int baseAngle;

private:
};

MainSystem::MainSystem()
{
}
// doing this stuff here, because the constructor
// is called before Serial is initialized
void MainSystem::setup()
{
  setupComplete = false;

  baseAngle = 0;

  wifiBroadcast.setup();
//  wifiBroadcast.addRoute("/test", wifiBroadcast.getHTMLWrapper)
  wifiBroadcast.start();

  return;

  xyz.setup();

  // setup initial button state
  pinMode(button, INPUT_PULLUP);

  delay(500); // needs time to startup  
}

int MainSystem::getDeviationFromBase(int currentLevel) {
  const int okDeviation = 3;

  Serial.print("Current: ");
  Serial.println(currentLevel);

  if (baseAngle == currentLevel) {
    return 0;
  }

  if (baseAngle > currentLevel) {
    int deviation = baseAngle - currentLevel ;

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
    int deviation = currentLevel - baseAngle;

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

MainSystem mainSystem;

void setup(void)
{
  Serial.begin(115200);
  mainSystem.setup();
}

void setInitialPosition(int z) {
  Serial.print("Set base level at:");
  Serial.println(z);
  mainSystem.baseAngle = z;
  onSound();
}

void loop(void)
{
  // for fun and testing:
  // playMusic(); return;

  wifiLoopAction();
  return;

//  int z = getReading();
  int z = 0;

  if (!mainSystem.setupComplete) {
    //Serial.print("Button state: ");
    //Serial.println(digitalRead(button));

    // button is pressed
    if (digitalRead(button) == 0) {     
      // so save angle
      setInitialPosition(z);
      mainSystem.setupComplete = true;
      Serial.print("Reset angle to: ");
      Serial.println(mainSystem.baseAngle);
      delay(1000);
    }

  } else {
    mainSystem.getDeviationFromBase(z);
    
    if (digitalRead(button) == 0) {
      Serial.println("Stopped reading");
      mainSystem.setupComplete = false;
      playShutdown();
    }
  }
}

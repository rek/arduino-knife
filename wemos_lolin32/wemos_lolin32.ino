#include <Wire.h>
#include <WebServer.h>

#include "headers.h"
#include "xyz.h"
#include "wifiBroadcast.h"
#include "html.h"

/* 
 *  Knife sharpner v2
 *  
 *  Features:
 *  
 *   - web interface to control setup
 *   - buzzer for angle change feedback
 *  
 *  Setup info:

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
*
*/
const int button = 12;

boolean setupComplete = false;
boolean buzzerState = false;

int baseAngle = 0;
  
int getDeviationFromBase(int currentLevel) {
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

//server.on("/update", MainSystem_handleUpdate_wrapper);

WebServer server(80);

void handleSendAll() {
  server.send(200, "text/html", getHTML()); 
}

void toggleAngleSet() {
  baseAngle += 1;
  server.send(200, "text/html", (String) baseAngle); 
}

void handleToggleBuzzer() {
  buzzerState = !buzzerState;
  server.send(200, "text/html", buzzerState ? "ON" : "OFF"); 
}

void setup(void)
{
  Serial.begin(115200);
  
  WifiBroadcast wifiBroadcast;
  
  wifiBroadcast.setup();
  
  server.on("/", handleSendAll);
  server.on("/toggleAngleSet", toggleAngleSet);
  server.on("/toggleBuzzer", handleToggleBuzzer);  
  
  server.begin();

  // xyz.setup();

  // setup initial button state
  // pinMode(button, INPUT_PULLUP);

  delay(500); // needs time to startup  
  Serial.println("HTTP server started");
}

void setInitialPosition(int z) {
  Serial.print("Set base level at:");
  Serial.println(z);
  baseAngle = z;
  onSound();
}

void loop(void)
{
  // for fun and testing:
  // playMusic(); return;
  server.handleClient();
  // wifiLoopAction();
  return;

//  int z = getReading();
  int z = 0;

  if (!setupComplete) {
    //Serial.print("Button state: ");
    //Serial.println(digitalRead(button));

    // button is pressed
    if (digitalRead(button) == 0) {     
      // so save angle
      setInitialPosition(z);
      setupComplete = true;
      Serial.print("Reset angle to: ");
      Serial.println(baseAngle);
      delay(1000);
    }

  } else {
    getDeviationFromBase(z);
    
    if (digitalRead(button) == 0) {
      Serial.println("Stopped reading");
      setupComplete = false;
      playShutdown();
    }
  }
}

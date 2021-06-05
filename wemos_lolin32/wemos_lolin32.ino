#include <Wire.h>
#include <WebServer.h>

#include "headers.h"
#include "xyz.h"
#include "wifiBroadcast.h"
#include "html.h"

/*
    Knife sharpner v2 - lolin32 Wemos

    Features:

     - web interface to control setup
     - buzzer for angle change feedback

    Setup info:

   Connections
   ===========

   XYZ:
   SCL to 22
   SDA to 21
   VDD to 3.3-5V DC
   GROUND to common ground

   Buzzer:
   S to 19  
   - to GND

*/

boolean buzzerState = true;

int baseAngle = 0;
int currentAngle;
int okDeviation = 3;

int convertDeviationToNote(int deviation) {
  return (deviation * 100);
//  return (deviation * 100) - 500;
}

int getDeviationFromBase() {
  int deviation;
  int speedOfSound = 100;

  Serial.print("Base,SetDeviation,Current,Deviation: ");
  Serial.print(baseAngle);
  Serial.print(", ");
  Serial.print(okDeviation);
  Serial.print(", ");
  Serial.print(currentAngle);
  Serial.print(", ");

  if (baseAngle == currentAngle) {
    Serial.println("");
    return 0;
  }

  if (baseAngle > currentAngle) {
    deviation = baseAngle - currentAngle;

    Serial.print(deviation);
    Serial.println(" (Below)");

    if (deviation <= okDeviation) {
      return 0;
    }

//    if (deviation > 90) {
//      playMusic();
//    }

//    Serial.print("Below ");
//    Serial.println(deviation);

    if (deviation > 20) {
      speedOfSound = 300;
    } else {
      speedOfSound = 100;
    }
  } else {
    deviation = currentAngle - baseAngle;

    Serial.print(deviation);
    Serial.println(" (Above)");

    if (deviation <= okDeviation) {
      return 0;
    }

//    Serial.print("Above ");
//    Serial.println(deviation);

    if (deviation > 20) {
      speedOfSound = 300;
    } else {
      speedOfSound = 100;
    }
  }

  beep(convertDeviationToNote(deviation), speedOfSound);
}

XYZ xyz;
WebServer server(80);

void handleSendAll() {
  server.send(200, "text/html", getHTML());
}

void setAngle() {
  baseAngle = currentAngle;
  server.send(200, "text/html", (String) baseAngle);
}

void getCurrentAngle() {
  server.send(200, "text/html", (String) currentAngle);
}

void handleToggleBuzzer() {
  buzzerState = !buzzerState;
  if (buzzerState) {
    playOnSound();
  } else {
    playOffSound();
  }
  server.send(200, "text/html", buzzerState ? "ON" : "OFF");
}

void checkforErrors() {
  Serial.println("Error state:");  
  Serial.println(xyz.error);  
  
  server.send(200, "text/html", xyz.error ? "Error during startup" : "");
}

void decrementDeviation() {
  okDeviation -= 1;
  server.send(200, "text/html", (String) okDeviation);
}
void incrementDeviation() {
  okDeviation += 1;
  server.send(200, "text/html", (String) okDeviation);
}

void setup(void)
{
  Serial.begin(115200);

  WifiBroadcast wifiBroadcast;

  wifiBroadcast.setup();

  delay(500); // needs time to startup

  server.on("/", handleSendAll);
  server.on("/setAngle", setAngle);
  server.on("/getCurrentAngle", getCurrentAngle);
  server.on("/toggleBuzzer", handleToggleBuzzer);
  server.on("/decrementDeviation", decrementDeviation);
  server.on("/incrementDeviation", incrementDeviation);
  server.on("/checkforErrors", checkforErrors); 

  server.begin();

  buzzerSetup();
    
  playOnSound();
  
  xyz.setup();

  delay(500); // needs time to startup
  Serial.println("HTTP server started (setup complete)");
  Serial.println("");  
}

void loop(void)
{
  // for fun and testing:
  // playMusic(); return;
  
  server.handleClient();

  currentAngle = xyz.getZReading();

  // delay(200);

  if (buzzerState && !xyz.error) {
    getDeviationFromBase();
  }
}

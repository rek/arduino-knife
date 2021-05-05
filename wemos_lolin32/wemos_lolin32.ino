#include <Wire.h>
#include <WebServer.h>

#include "headers.h"
#include "xyz.h"
#include "wifiBroadcast.h"
#include "html.h"

/*
    Knife sharpner v2

    Features:

     - web interface to control setup
     - buzzer for angle change feedback

    Setup info:

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

*/

boolean setupComplete = false;
boolean buzzerState = false;

int baseAngle = 0;
int currentAngle;
int okDeviation = 3;

int getDeviationFromBase() {


  Serial.print("Current: ");
  Serial.println(currentAngle);

  if (baseAngle == currentAngle) {
    return 0;
  }

  if (baseAngle > currentAngle) {
    int deviation = baseAngle - currentAngle;

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
    int deviation = currentAngle - baseAngle;

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
  server.send(200, "text/html", buzzerState ? "ON" : "OFF");
}

void decrementDeviation() {
  okDeviation -= 1;
  server.send(200, "text/html", (String) okDeviation);
}
void incrementDeviation() {
  okDeviation += 1;
  server.send(200, "text/html", (String) okDeviation);
}

XYZ xyz;

void setup(void)
{
  Serial.begin(115200);

  WifiBroadcast wifiBroadcast;

  wifiBroadcast.setup();

  server.on("/", handleSendAll);
  server.on("/setAngle", setAngle);
  server.on("/getCurrentAngle", getCurrentAngle);
  server.on("/toggleBuzzer", handleToggleBuzzer);
  server.on("/decrementDeviation", decrementDeviation);
  server.on("/incrementDeviation", incrementDeviation);

  server.begin();

  ledcSetup(0, 500, 13);
  ledcAttachPin(19, 0);
    
  onSound();
  
  xyz.setup();

  delay(500); // needs time to startup
  Serial.println("HTTP server started");
}

void loop(void)
{
  // for fun and testing:
  // playMusic(); return;
  
  server.handleClient();

  currentAngle = xyz.getZReading();

  delay(200);

  if (buzzerState) {
    getDeviationFromBase();
  }
}

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

boolean buzzerState = false;
boolean activeState = false;

// set the base angle of the table and stone
int baseAngleZ = 0;
int baseAngleX = 0;
// set the desired angle
int desiredAngleZ = 0;

int currentAngleZ;
int currentAngleX;

int okDeviationZ = 3;
int okDeviationX = 3;

/* Set the delay between fresh samples */
uint16_t delayTimeMillis = 100;

int convertDeviationToNote(int deviation)
{
  return (deviation * 100) - 200;
  //  return (deviation * 100) - 500;
}

int processCurrentAngle()
{
  int deviation;
  int speedOfSound = 100;

  // make sure we have not moved the thing off the sharpening plain
  // eg: bringing it back:
  int hasMovedUpAmount = baseAngleX - currentAngleX - okDeviationX;
  Serial.print("XDeviation: ");
  Serial.println(hasMovedUpAmount);
  if (hasMovedUpAmount > okDeviationX)
  {
    Serial.print("Detected X elevation, skipping checks.");
    return 0;
  }

  Serial.print("Base,SetDeviation,Current,Deviation: ");
  Serial.print(baseAngleZ);
  Serial.print(", ");
  Serial.print(okDeviationZ);
  Serial.print(", ");
  Serial.print(currentAngleZ);
  Serial.print(", ");

  if (baseAngleZ == currentAngleZ)
  {
    Serial.println("");
    return 0;
  }

  if (baseAngleZ > currentAngleZ)
  {
    deviation = baseAngleZ - currentAngleZ;

    Serial.print(deviation);
    Serial.println(" (Below)");

    if (deviation <= okDeviationZ)
    {
      return 0;
    }

    //    Serial.print("Below ");
    //    Serial.println(deviation);

    if (deviation > 20)
    {
      speedOfSound = 300;
    }
    else
    {
      speedOfSound = 100;
    }
  }
  else
  {
    deviation = currentAngleZ - baseAngleZ;

    Serial.print(deviation);
    Serial.println(" (Above)");

    if (deviation <= okDeviationZ)
    {
      return 0;
    }

    //    Serial.print("Above ");
    //    Serial.println(deviation);

    if (deviation > 20)
    {
      speedOfSound = 300;
    }
    else
    {
      speedOfSound = 100;
    }
  }

  if (buzzerState) {
    beep(convertDeviationToNote(deviation), speedOfSound);
  }
}

XYZ xyz;
WebServer server(80);

void handleSendAll()
{
  server.send(200, "text/html", getHTML());
}

void setBaseAngle()
{
  baseAngleX = currentAngleX;
  baseAngleZ = currentAngleZ;
  server.send(200, "text/html", (String)baseAngleX);
}

void setDesiredAngleZ()
{
  desiredAngleZ = currentAngleZ;
  server.send(200, "text/html", (String)desiredAngleZ);
}

void getCurrentAngleZ()
{
  server.send(200, "text/html", (String)currentAngleZ);
}
void getCurrentAngleX()
{
  server.send(200, "text/html", (String)currentAngleX);
}

void handleToggleActive()
{
  activeState = !activeState;
  server.send(200, "text/html", activeState ? "ON" : "OFF");
}
void handleToggleBuzzer()
{
  buzzerState = !buzzerState;  
  if (buzzerState)
  {
    playOnSound();
  }
  else
  {
    playOffSound();
  }
  server.send(200, "text/html", buzzerState ? "ON" : "OFF");
}

void checkforErrors()
{
  Serial.println("Error state:");
  Serial.println(xyz.error);

  server.send(200, "text/html", xyz.error ? "Error during startup" : "");
}

void decrementDeviationZ()
{
  okDeviationZ -= 1;
  server.send(200, "text/html", (String)okDeviationZ);
}
void incrementDeviationZ()
{
  okDeviationZ += 1;
  server.send(200, "text/html", (String)okDeviationZ);
}
void decrementDeviationX()
{
  okDeviationX -= 1;
  server.send(200, "text/html", (String)okDeviationX);
}
void incrementDeviationX()
{
  okDeviationX += 1;
  server.send(200, "text/html", (String)okDeviationX);
}

void setup(void)
{
  Serial.begin(115200);

  WifiBroadcast wifiBroadcast;

  wifiBroadcast.setup();

  delay(500); // needs time to startup

  server.on("/", handleSendAll);
  server.on("/setBaseAngle", setBaseAngle);
  server.on("/setDesiredAngleZ", setDesiredAngleZ);
  server.on("/getCurrentAngleZ", getCurrentAngleZ);
  server.on("/getCurrentAngleX", getCurrentAngleX);
  server.on("/decrementDeviationZ", decrementDeviationZ);
  server.on("/decrementDeviationX", decrementDeviationX);
  server.on("/incrementDeviationZ", incrementDeviationZ);
  server.on("/incrementDeviationX", incrementDeviationX);
  server.on("/handleToggleBuzzer", handleToggleBuzzer);
  server.on("/handleToggleActive", handleToggleActive);
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

  if (!activeState || xyz.error) {
    delay(delayTimeMillis);
    return;  
  }

  currentAngleZ = xyz.getZReading();
  currentAngleX = xyz.getXReading();

  if (activeState)
  {
    processCurrentAngle();
  }

  delay(delayTimeMillis);
}

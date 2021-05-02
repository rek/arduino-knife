#include "xyz.h"

#include <Adafruit_Sensor.h> // ?
#include <Adafruit_BNO055.h> // main xyz sensor
#include <utility/imumaths.h> // ?

/* Set the delay between fresh samples */
uint16_t BNO055_SAMPLERATE_DELAY_MS = 100;

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

void XYZ::setup()
{
  Serial.println("");
  Serial.println("Orientation Sensor Test"); 
  Serial.println("");


  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
 
}

int XYZ::getZReading()
{
  sensors_event_t orientationData;
//  sensors_event_t angVelocityData;
//  sensors_event_t linearAccelData;
//  sensors_event_t magnetometerData;
//  sensors_event_t accelerometerData;
//  sensors_event_t gravityData;
  
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  // printEvent(&orientationData);

  uint8_t system = 0;
  uint8_t gyro = 0;
  uint8_t accel = 0;
  uint8_t mag = 0;
  
  bno.getCalibration(&system, &gyro, &accel, &mag);

  delay(BNO055_SAMPLERATE_DELAY_MS);

  return orientationData.orientation.z;
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

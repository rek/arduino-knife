#include <WiFi.h>

#include "wifiBroadcast.h"

#define WIFI_SSID "Knife sharpner"
#define WIFI_PASS NULL

/* IP Address details */
IPAddress Ip(192, 168, 1, 1);
IPAddress NMask(255, 255, 255, 0);

void WifiBroadcast::setup()
{
  Serial.print("Initializing Wi-Fi... ");
  
  WiFi.mode(WIFI_AP);
  
  WiFi.softAP(WIFI_SSID, WIFI_PASS);
  delay(100);
  WiFi.softAPConfig(Ip, Ip, NMask);

  Serial.println(" complete!");
  //  WiFi.disconnect();

  IPAddress IP = WiFi.softAPIP();
  Serial.print("IP address: ");
  Serial.println(IP);
}

#include <WiFi.h>
#include <WebServer.h>

#include "wifiBroadcast.h"

#define WIFI_SSID "Knife sharpner"
#define WIFI_PASS NULL

/* IP Address details */
IPAddress Ip(192, 168, 1, 1);
IPAddress NMask(255, 255, 255, 0);

WebServer server(80);


String SendHTML(uint8_t led1stat, String runningTime){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Knife System</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  
  ptr +="<script>\n";
  ptr +="// setInterval(loadDoc,1000);\n";
  ptr +="function loadDoc() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState === 4 && this.status === 200) {\n";
  ptr +="document.body.innerHTML = this.responseText}\n";
  ptr +="};\n";
  ptr +="xhttp.open(\"GET\", \"/update\", true);\n";
  ptr +="xhttp.send();\n";
  ptr +="}\n";
  ptr +="</script>\n";  

  
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Knife Sharpner</h1>\n";
  ptr +="<h3>This is awesome!</h3>\n";

  
  
  if (runningTime) {
    ptr +="<p>Running time: " + runningTime + "</p>\n";
  }
//  ptr +="<p>Angle set: " + goodLevel + "</p>\n";

  ptr +="<p>Mode: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";
  ptr +="<a id='angleButton' class=\"button button-off\">Start</a>\n";

  ptr +="<p id='angle'>Set angle: none</p>\n";

//  if(led2stat)
//  {ptr +="<p>Mode: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
//  else
//  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}


  ptr +="<script>\n";
  ptr +="const setAngle = function() {\n";
  ptr +="  console.log('Clicked set angle button');\n";
  ptr +="  var xhttp = new XMLHttpRequest();\n";
  ptr +="  xhttp.onreadystatechange = function() {\n";
  ptr +="    console.log('Intial response', this);\n";
  ptr +="    if (this.readyState === 4 && this.status === 200) {\n";
  ptr +="      console.log('Response:', this.responseText)\n";
  ptr +="      document.getElementById('angle').innerHTML = this.responseText;\n";
  ptr +="    }\n";
  ptr +="  }\n";
  ptr +="  xhttp.open(\"GET\", \"/update\", true);\n";
  ptr +="  xhttp.send();\n";
  ptr +="}\n";
  ptr +="document.getElementById('angleButton').onclick = setAngle;\n";  
  ptr +="</script>\n";  
  
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(true, (String) (millis() / 1000))); 
}

void handle_getNewServerValues() {
  server.send(200, "text/html", SendHTML(true, "")); 
}

void handleUpdateAngle() {
  server.send(200, "text/html", "JUST SOME AWESOME TEXT"); 
}

void wifiLoopAction() {
  server.handleClient();
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

//void WifiBroadcast::handleUpdateAngle() {}
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
    
  server.on("/", handle_OnConnect);
//  server.on("/start", handle_led1on);
  server.on("/update", handleUpdateAngle);
  
  server.onNotFound(handle_NotFound);
  
}

void WifiBroadcast::addRoute(char * routeName, void * action) 
{
//  void aaa() {
//    Serial.println("GPIO4 Status: ON");
//    server.send(200, "text/html", SendHTML(true, "")); 
//  }
//
//  server.on(routeName, aaa);
}

void WifiBroadcast::start()
{
  server.begin(); 
  Serial.println("HTTP server started");
}


String WifiBroadcast::getHTMLWrapper(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Knife System</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="<script>\n";
  ptr +="setInterval(loadDoc,1000);\n";
  ptr +="function loadDoc() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState === 4 && this.status === 200) {\n";
  ptr +="document.body.innerHTML = this.responseText}\n";
  ptr +="};\n";
  ptr +="xhttp.open(\"GET\", \"/\", true);\n";
  ptr +="xhttp.send();\n";
  ptr +="}\n";
  ptr +="</script>\n";  
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Knife Sharpner</h1>\n";
  ptr +="<h3>This is awesome!</h3>\n";

  ptr +="<p>Mode: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

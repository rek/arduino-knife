#include <Arduino.h>

String getHTML() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Knife System</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".wrapper {display: flex;padding: 20px;justify-content: center;}\n";
  ptr +=".wrapperButton {padding: 0 20px;}\n";
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
  // ptr +="<h3>This is awesome!</h3>\n";
  ptr +="<h3>Set angle: <span id='displayBaseAngle'>0</span></h3>\n";
  
  ptr +="<div class='wrapper'>\n";
  ptr +="  <div class='wrapperButton'>\n";
  ptr +="    <p>Buzzer</p><a id='buzzerState' class=\"button button-off\">OFF</a>\n";
  ptr +="  </div>\n";
  ptr +="  <div class='wrapperButton'>\n";
  ptr +="    <p>Reset angle</p><a id='angleResetState' class=\"button button-off\">OFF</a>\n";
  ptr +="  </div>\n";
  ptr +="</div>\n";
  
  ptr +="<a id='angleButton' class=\"button button-off\">Start</a>\n";

  ptr +="<p id='angle'>Set angle: none</p>\n";


  ptr +="<script>\n";
  ptr +="const setAngle = function() {\n";
  ptr +="  console.log('Clicked set angle button');\n";
  ptr +="  var xhttp = new XMLHttpRequest();\n";
  ptr +="  xhttp.onreadystatechange = function() {\n";
  ptr +="    // console.log('Initial response', this);\n";
  ptr +="    if (this.readyState === 4 && this.status === 200) {\n";
  ptr +="      console.log('Response:', this.responseText)\n";
  ptr +="      document.getElementById('displayBaseAngle').innerHTML = this.responseText;\n";
  ptr +="      document.getElementById('angleResetState').innerHTML = document.getElementById('angleResetState').innerHTML === 'OFF' ? 'ON' : 'OFF';\n";
  ptr +="    }\n";
  ptr +="  }\n";
  ptr +="  xhttp.open(\"GET\", \"/toggleAngleSet\", true);\n";
  ptr +="  xhttp.send();\n";
  ptr +="}\n";
  ptr +="document.getElementById('angleResetState').onclick = setAngle;\n";  

  ptr +="const setBuzzer = function() {\n";
  ptr +="  console.log('Clicked buzzer toggle button');\n";
  ptr +="  var xhttp = new XMLHttpRequest();\n";
  ptr +="  xhttp.onreadystatechange = function() {\n";
  ptr +="    // console.log('Intial response', this);\n";
  ptr +="    if (this.readyState === 4 && this.status === 200) {\n";
  ptr +="      console.log('Response:', this.responseText)\n";
  ptr +="      document.getElementById('buzzerState').innerHTML = this.responseText;\n";
  ptr +="    }\n";
  ptr +="  }\n";
  ptr +="  xhttp.open(\"GET\", \"/toggleBuzzer\", true);\n";
  ptr +="  xhttp.send();\n";
  ptr +="}\n";
  ptr +="document.getElementById('buzzerState').onclick = setBuzzer;\n";  
  
  ptr +="</script>\n";  
  
  ptr +="</body>\n";
  ptr +="</html>\n";
  
  return ptr;
}

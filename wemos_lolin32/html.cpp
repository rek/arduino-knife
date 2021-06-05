#include <Arduino.h>

String getHTML() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Knife System</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 30px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +="#setupError {color: darkorange;}\n";
  ptr +=".wrapper {display: flex;justify-content: center;}\n";
  ptr +=".wrapperButton {padding: 0 20px;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +=".big-text {font-size: 229px; margin: 0; color: #444444}\n";
  ptr +="#deviation {padding-top: 60px;}\n";
    
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Knife Sharpner</h1>\n";
  // ptr +="<h3>This is awesome!</h3>\n";
  ptr +="<h2><span id='setupError'></span></h2>\n";
  ptr +="<h3>Set angle: <span id='displayBaseAngle'>0</span></h3>\n";
  
  ptr +="<div class='wrapper'>\n";
  ptr +="  <div class='wrapperButton'>\n";
  ptr +="    <p>Buzzer</p><a id='buzzerState' class=\"button button-off\">OFF</a>\n";
  ptr +="  </div>\n";
  ptr +="  <div id='middle_gap'>\n";
  ptr +="  &nbsp;\n";
  ptr +="  </div>\n";  
  ptr +="  <div class='wrapperButton'>\n";
  ptr +="    <p>Reset angle</p><a id='angleResetState' class=\"button button-off\">SET</a>\n";
  ptr +="  </div>\n";
  ptr +="</div>\n";

  ptr +="<div class='wrapper'>\n";
  ptr +="  <div class='wrapperButton'>\n";
  ptr +="    <p>Deviation</p><a id='decrementDeviation' class=\"button button-off\">-</a>\n";
  ptr +="  </div>\n";
  ptr +="  <div id='deviation'>\n";
  ptr +="  3\n";
  ptr +="  </div>\n";
  ptr +="  <div class='wrapperButton'>\n";
  ptr +="    <p>&nbsp;</p><a id='incrementDeviation' class=\"button button-off\">+</a>\n";
  ptr +="  </div>\n";
  ptr +="</div>\n";

  ptr +="<p class='big-text' id='angle'>0</p>\n";


  ptr +="<script>\n";
  ptr +="const incrementDeviation = function() {\n";
  ptr +="  var xhttp = new XMLHttpRequest();\n";
  ptr +="  xhttp.onreadystatechange = function() {\n";
  ptr +="    if (this.readyState === 4 && this.status === 200) {\n";
  ptr +="      document.getElementById('deviation').innerHTML = this.responseText;\n";
  ptr +="    }\n";
  ptr +="  }\n";
  ptr +="  xhttp.open(\"GET\", \"/incrementDeviation\", true);\n";
  ptr +="  xhttp.send();\n";
  ptr +="}\n";
  ptr +="document.getElementById('incrementDeviation').onclick = incrementDeviation;\n";  

  ptr +="const decrementDeviation = function() {\n";
  ptr +="  var xhttp = new XMLHttpRequest();\n";
  ptr +="  xhttp.onreadystatechange = function() {\n";
  ptr +="    if (this.readyState === 4 && this.status === 200) {\n";
  ptr +="      document.getElementById('deviation').innerHTML = this.responseText;\n";
  ptr +="    }\n";
  ptr +="  }\n";
  ptr +="  xhttp.open(\"GET\", \"/decrementDeviation\", true);\n";
  ptr +="  xhttp.send();\n";
  ptr +="}\n";
  ptr +="document.getElementById('decrementDeviation').onclick = decrementDeviation;\n";  
  
  ptr +="const setAngle = function() {\n";
  ptr +="  console.log('Clicked set angle button');\n";
  ptr +="  var xhttp = new XMLHttpRequest();\n";
  ptr +="  xhttp.onreadystatechange = function() {\n";
  ptr +="    // console.log('Initial response', this);\n";
  ptr +="    if (this.readyState === 4 && this.status === 200) {\n";
  ptr +="      console.log('Response:', this.responseText)\n";
  ptr +="      document.getElementById('displayBaseAngle').innerHTML = this.responseText;\n";
  ptr +="    }\n";
  ptr +="  }\n";
  ptr +="  xhttp.open(\"GET\", \"/setAngle\", true);\n";
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
  
  ptr +="function updateAngleDisplay() {\n";
  ptr +="  var xhttp = new XMLHttpRequest();\n";
  ptr +="  xhttp.onreadystatechange = function() {\n";
  ptr +="    if (this.readyState === 4 && this.status === 200) {\n";
  ptr +="      document.getElementById('angle').innerHTML = this.responseText;\n";
  ptr +="    }\n";
  ptr +="  }\n";
  ptr +="  xhttp.open(\"GET\", \"/getCurrentAngle\", true);\n";
  ptr +="  xhttp.send();\n";
  ptr +="}\n";
  ptr +="setInterval(updateAngleDisplay, 300);\n";

  ptr +="function checkforErrors() {\n";
  ptr +="  var xhttp = new XMLHttpRequest();\n";
  ptr +="  xhttp.onreadystatechange = function() {\n";
  ptr +="    if (this.readyState === 4 && this.status === 200) {\n";
  ptr +="      document.getElementById('setupError').innerHTML = this.responseText;\n";
  ptr +="    }\n";
  ptr +="  }\n";
  ptr +="  xhttp.open(\"GET\", \"/checkforErrors\", true);\n";
  ptr +="  xhttp.send();\n";
  ptr +="}\n";
  ptr +="checkforErrors();\n";
  
  ptr +="</script>\n";  
  ptr +="</body>\n";
  ptr +="</html>\n";
  
  return ptr;
}

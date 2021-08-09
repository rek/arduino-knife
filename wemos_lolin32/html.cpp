#include <Arduino.h>

String getHTML()
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Knife System</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 40px auto 30px;} h3 {color: #444444;margin-bottom: 30px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += "#setupError {color: darkorange;}\n";
  ptr += ".wrapper {display: flex;justify-content: center;}\n";
  ptr += ".wrapperButton {padding: 0 8px;}\n";
  ptr += ".wrapperButton p {margin-bottom: 0px;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += ".big-text {font-size: 229px; margin: 0; color: #444444}\n";
  ptr += ".wrapper-text {padding-top: 50px;}\n";

  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>Knife Sharpner</h1>\n";
  // ptr +="<h3>This is awesome!</h3>\n";
  ptr += "<h2><span id='setupError'></span></h2>\n";
  ptr += "<h3>Sharpening angle: <span id='displayBaseAngle'>0</span></h3>\n";

  ptr += "<div class='wrapper'>\n";
  ptr += "  <div class='wrapperButton'>\n";
  ptr += "    <p>Buzzer</p><a id='handleToggleBuzzer' class=\"button button-off\">OFF</a>\n";
  ptr += "  </div>\n";
  ptr += "  <div class='middle_gap'>\n";
  ptr += "  &nbsp;\n";
  ptr += "  </div>\n";
  ptr += "  <div class='wrapperButton'>\n";
  ptr += "    <p>Active</p><a id='handleToggleActive' class=\"button button-off\">OFF</a>\n";
  ptr += "  </div>\n";
  ptr += "</div>\n";

  ptr += "<div class='wrapper'>\n";
  ptr += "  <div class='wrapperButton'>\n";
  ptr += "    <p>&nbsp;</p><a id='setBaseAngle' class=\"button button-off\">TARE</a>\n";
  ptr += "  </div>\n";
  ptr += "  <div class='middle_gap'>\n";
  ptr += "  &nbsp;\n";
  ptr += "  </div>\n";
  ptr += "  <div class='wrapperButton'>\n";
  ptr += "    <p>Set Angle</p><a id='setDesiredAngleZ' class=\"button button-off\">SET</a>\n";
  ptr += "  </div>\n";
  ptr += "</div>\n";

  ptr += "<div class='wrapper'>\n";
  ptr += "  <div class='wrapperButton'>\n";
  ptr += "    <p>Deviation</p><a id='decrementDeviationZ' class=\"button button-off\">-</a>\n";
  ptr += "  </div>\n";
  ptr += "  <div class='wrapper-text' id='deviation'>\n";
  ptr += "  3\n";
  ptr += "  </div>\n";
  ptr += "  <div class='wrapperButton'>\n";
  ptr += "    <p>&nbsp;</p><a id='incrementDeviationZ' class=\"button button-off\">+</a>\n";
  ptr += "  </div>\n";
  ptr += "</div>\n";

  ptr += "<div class='wrapper'>\n";
  ptr += "  <div class='wrapperButton'>\n";
  ptr += "    <p>Deviation X</p><a id='decrementDeviationX' class=\"button button-off\">-</a>\n";
  ptr += "  </div>\n";
  ptr += "  <div class='wrapper-text' id='deviationX'>\n";
  ptr += "  3\n";
  ptr += "  </div>\n";
  ptr += "  <div class='wrapperButton'>\n";
  ptr += "    <p>&nbsp;</p><a id='incrementDeviationX' class=\"button button-off\">+</a>\n";
  ptr += "  </div>\n";
  ptr += "</div>\n";

  ptr += "<p class='big-text' id='angle'>0</p>\n";

  ptr += "<script>\n";

  // eventName - endpoint to call (also updates element if no updateId is set)
  // updateId  - string - id of element to update with result (optional)
  //             false - do not perform any update
  ptr += "const generateCallback = function(eventName, updateId) {\n";
  ptr += "  return function() {\n";
  ptr += "    var xhttp = new XMLHttpRequest();\n";
  ptr += "    if (updateId !== false) {\n";
  ptr += "      xhttp.onreadystatechange = function() {\n";
  ptr += "        if (this.readyState === 4 && this.status === 200) {\n";
  ptr += "          document.getElementById(updateId || eventName).innerHTML = this.responseText;\n";
  ptr += "        }\n";
  ptr += "      }\n";
  ptr += "    }\n";
  ptr += "    xhttp.open(\"GET\", `/${eventName}`, true);\n";
  ptr += "    xhttp.send();\n";
  ptr += "  }\n";
  ptr += "}\n";

  ptr += "const attachClickEvent = function(eventName, updateId) {\n";
  ptr += "  document.getElementById(eventName).onclick = generateCallback(eventName, updateId);\n";
  ptr += "}\n";

  ptr += "attachClickEvent('incrementDeviationX', 'deviationX')\n";
  ptr += "attachClickEvent('decrementDeviationX', 'deviationX')\n";
  ptr += "attachClickEvent('incrementDeviationZ', 'deviation')\n";
  ptr += "attachClickEvent('decrementDeviationZ', 'deviation')\n";

  ptr += "attachClickEvent('handleToggleBuzzer')\n";
  ptr += "attachClickEvent('setDesiredAngleZ', 'displayBaseAngle')\n";
  ptr += "attachClickEvent('setBaseAngle', false)\n";

  ptr += "const handleToggleActive = generateCallback('handleToggleActive')\n";
  ptr += "let checkLoop;\n";
  ptr += "const getTaredAngleZ = generateCallback('getTaredAngleZ', 'angle');\n";
  ptr += "const attachClickToggleActiveEvent = function(eventName, updateId) {\n";
  ptr += "  document.getElementById('handleToggleActive').onclick = () => {\n";
  ptr += "    handleToggleActive();\n";
  ptr += "    const isInOffstatus = document.getElementById('handleToggleActive').innerHTML === 'OFF';\n";
  ptr += "    if (isInOffstatus) {\n";
  ptr += "      checkLoop = setInterval(getTaredAngleZ, 150);\n";
  ptr += "    } else {\n";
  ptr += "      clearInterval(checkLoop);";
  ptr += "    }\n";
  ptr += "  }\n";
  ptr += "}\n";
  ptr += "attachClickToggleActiveEvent();\n";

  ptr += "const checkforErrors = generateCallback('checkforErrors', 'setupError');\n";
  ptr += "checkforErrors();\n";

  // stop the screen from going to sleep.
  ptr += "const requestWakeLock = async () => {\n";
  ptr += "  try {\n";
  ptr += "    const wakeLock = await navigator.wakeLock.request('screen');\n";
  ptr += "  } catch (err) {\n";
  ptr += "    console.log(`${err.name}, ${err.message}`);\n";
  ptr += "  }\n";
  ptr += "}\n";
  ptr += "requestWakeLock();\n";

  ptr += "</script>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";

  return ptr;
}

#pragma once

class WifiBroadcast
{
public:
  
  void setup();
  void start();
  void addRoute(char * routeName);
  void addRoute(char * routeName, void * action);
  String getHTMLWrapper();
//  int getZReading();

private:
//  void handle_NotFound();
//  void handleUpdateAngle();
};

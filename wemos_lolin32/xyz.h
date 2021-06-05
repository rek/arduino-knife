#pragma once

class XYZ
{
public:
  void setup();
  int getZReading();
  bool error;
  int setupAttempts = 0;
};

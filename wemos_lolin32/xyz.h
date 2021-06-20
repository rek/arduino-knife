#pragma once

class XYZ
{
public:
  void setup();
  int getZReading();
  int getXReading();
  bool error;
  int setupAttempts = 0;
};

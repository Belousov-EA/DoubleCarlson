#ifndef ATR_MOTORS_H
#define AIR_MOTORS_H

#include "Actuator.h"

class AirData;

class AirMotors : public Actuator
{
  public:
    void init(int RightPin, int LeftPin)
    {
      rightPin = RightPin;
      leftPin = LeftPin;
    }
    
    void setAirData(AirData* ad)
    {
      airData = ad;
    }

    void call()
    {
      if(airData->getDifference()<0.00)
      {
        analogWrite(leftPin, int(abs(255*airData->getDifference())));
        analogWrite(rightPin, 0);
      }else
      {
        analogWrite(leftPin, 0);
        analogWrite(rightPin, int(abs(255* airData->getDifference())));
      }
    }
    
  private:
    int rightPin;
    int leftPin;
    AirData *airData;
};

#endif

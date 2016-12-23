#ifndef AIR_SPEED_ALGORITHM_H
#define AIR_SPEED_ALGORITHM_H

#include "Algorithm.h"
#include "Union2.h"
#include "ClassFactory.h"
#include "SpeedData.h"
#include "AirData.h"

class ExcData;

class AirSpeedAlgorithm : public Algorithm, public ClassFactory<Union2<SpeedData, AirData>>
{
  public:
    void init(float P, float D, float MidSpeed, unsigned long VozvratTime, float AirThreshold, float AP, float AD, unsigned long StopTime)
    {
      p = P;
      d = D;
      midSpeed = MidSpeed;
      vozvratTime = VozvratTime;
      airThreshold = AirThreshold;
      aP = AP;
      aD = AD;
      stopTime = StopTime;
    }
    
    void call()
    {
      if(excData->getDarks()!=0)
      {
        data.first ->setDifference ( excData -> getExc()*p+(excData -> getExc()-lastExc)*d/(excData->getExcTime() - lastTime));
    
        lastTime = excData->getExcTime();
        lastExc = excData->getExc();
        data.first -> setAvgSpeed(midSpeed);
        if(excData -> getExc()<airThreshold)
        {
          data.second -> setDifference(0.00);
        }else
        {
          data.second -> setDifference(excData -> getExc()*aP+(excData -> getExc() -lastExc)*aD/(excData -> getExcTime() -lastTime));
        }
      }else
      {
        vozvrat();
      }      
      
    }

    void vozvrat()
    {
      if(excData->getExcTime()-excData->getLastTime()>vozvratTime)
      {
        data.first-> setAvgSpeed(midSpeed);
        if(excData->getValid()>0)
        {
          data.first ->setDifference(p);
          data.second ->setDifference(1.00);
          lastExc = 1.00;
        }else
        {
          data.first ->setDifference(-p);
          data.second -> setDifference(-1.00);
          lastExc = -1.00;
        }
        if(excData -> getExcTime() - excData -> getLastTime()> stopTime)
        {
          stopMotors();
        }
      }
    }

    void stopMotors()
    {
      data.first -> setAvgSpeed(0.00);
      data.first -> setDifference(0.00);
      data.second -> setDifference(0.00);
    }
    void setExcDataPtr(ExcData* ed)
    {
      this -> excData = ed;
    }
  private:
    float p;
    float d;
    float aP;
    float aD;
    float midSpeed;
    float airThreshold;
    unsigned long vozvratTime;
    ExcData* excData;
    float lastExc;
    unsigned long lastTime;
    unsigned long stopTime;
};
#endif

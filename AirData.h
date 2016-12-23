#ifndef AIR_DATA_H
#define AIR_DATA_H

#include "DataObject.h"

class AirData : public DataObject
{
  public:
    void setDifference(float dif)
    {
      difference = dif;
    }
    
    float getDifference()
    {
      return difference;
    }
    
  private:
    float difference;
};

#endif

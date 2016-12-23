#include "SensorData.h"
#include "ExcData.h"
#include "SpeedData.h"
#include "AirData.h"
#include "Sensor.h"
#include "ExcAlgorithm.h"
#include "SpeedAlgorithm.h"
#include "Motors.h"
#include "ClassFactory.h"
#include "AirMotors.h"
#include "AirSpeedAlgorithm.h"


#define SENSOR_COUNT 8
#//define DEBUG
#define SENSOR_DEBUG
#define EXC_DEBUG
#define SPEED_DEBUG


//initialization
  Sensor<int, 8> sensor;
  ExcAlgorithm<8> excAlgorithm;
  AirSpeedAlgorithm speedAlgorithm;
  Motors motors;
  AirMotors airMotors;

#ifdef DEBUG
  SensorData<int, 8> *sensorData;
  ExcData *excData;
  SpeedData* speedData;
#endif

int sensors[SENSOR_COUNT] = {7, 6, 5, 4, 3, 2, 1, 0};
int white[SENSOR_COUNT]= {77,  72,  71,  77,  68,  70,  76,  296 }; 
int black[SENSOR_COUNT]= {513,  423, 433, 556, 398, 441, 518, 640};

float p = 1;
float d = 20;
float midSpeed = 0.5;


void setup()
{
  //get references
    airMotors.setAirData(speedAlgorithm.getData()->second);
    motors.setSpeedData(speedAlgorithm.getData()-> first);
    speedAlgorithm.setExcDataPtr(excAlgorithm.getData());
    excAlgorithm.setSensorDataPtr(sensor.getData());
    
    

  //debug
  #ifdef DEBUG
    sensorData = sensor.getData();
    excData = excAlgorithm.getData();
    speedData = speedAlgorithm.getData();
    Serial.begin(115200);
  #endif

  //init
    sensor.init(sensors);
    excAlgorithm.init(white, black);
    speedAlgorithm.init(p, d, midSpeed, 10, 0.5, 1, 1, 500);
    motors.init(4, 5, 7, 6);
    airMotors.init(11, 10);
}

void loop() 
{
  sensor.call();
  excAlgorithm.call();
  speedAlgorithm.call();
  motors.call();
  airMotors.call();

  #ifdef DEBUG
    #ifdef SENSOR_DEBUG
      for(int i = 0; i<sensorData->getSensorCount(); i++)
      {
        Serial.print(sensorData -> getValue(i));
        Serial.print('\t');
      }
      Serial.println();
    #endif
    #ifdef EXC_DEBUG
      Serial.print(excData ->getExc());
      Serial.print('\t');
      Serial.print(excData -> getDarks());
      Serial.print('\t');
      Serial.print(excData -> getValid());
      Serial.print('\t');
      Serial.print(excData -> getExcTime());
      Serial.print('\t');
      Serial.println(excData -> getLastTime());
    #endif
    #ifdef SPEED_DEBUG
      Serial.print(speedData -> getAvgSpeed());
      Serial.print('\t');
      Serial.println(speedData -> getDifference());
    #endif
  #endif
}



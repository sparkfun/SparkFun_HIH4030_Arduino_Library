/*
Sparkfun's HIH-4030 Humidity Sensor Library Main Header File
SparkFun_HIH4030.h

E.Robert @ SparkFun Electronics
Created: Nov 2, 2016
Updated: Nov 2, 2016

Hardware Resources:
- Arduino Development Board: SparkFun RedBoard
- SparkFun Humidity Sensor Breakout - HIH-4030

Development Environment Specifics:
Arduino 1.6.8
SparkFun Humidity Sensor Breakout - HIH-4030
SparkFun RedBoard
*/

#ifndef HIH4030_h
#define HIH4030_h

#include <Arduino.h>

class HIH4030 {

public:
	HIH4030(uint8_t analogPin, float supplyVoltage);
	float getSensorRH();
	float getTrueRH(float temperature);
	float vout();

private:
	uint8_t pin;    // SparkFun RedBoard/Arduino Board Analog IO Pin connected to HIH-4030 Breakout OUT Pin
	float supply;   // Supply Voltage for HIH-4030 Sensor Breakout
};

#endif
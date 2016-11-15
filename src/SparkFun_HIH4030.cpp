/*
Sparkfun's HIH-4030 Humidity Sensor Library Main Source File
SparkFun_HIH4030.cpp

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

#include <SparkFun_HIH4030.h>

HIH4030::HIH4030(uint8_t analogPin, float supplyVoltage) {
	pin = analogPin;				// SparkFun RedBoard/Arduino Board Analog IO Pin connected to HIH-4030 Breakout OUT Pin
	supply = supplyVoltage;			// Voltage Supplying HIH-4030 Breakout [Typically 5V]
	pinMode(pin, INPUT);
}

// Convert sensor reading into Relative Humidity (RH%) using equation from Datasheet
// VOUT = (VSUPPLY)(0.0062(SENSOR RH) + 0.16), typical at 25 degrees Celsius
float HIH4030::getSensorRH() {
	return ((vout() / (.0062 * supply)) - 25.81);
}

// Get True Relative Humidity (RH%) compensated with Static Temperature or Measured Temperature
// TRUE RH = (SENSOR RH)/(1.0546 - 0.00216T), T in degrees Celsius
float HIH4030::getTrueRH(float temperature) {
	return getSensorRH() / (1.0546 - (0.00216 * temperature));
}

// Read value from the sensor and convert to voltage value
float HIH4030::vout() {
	return (float)(analogRead(pin)) * supply / 1023;
}
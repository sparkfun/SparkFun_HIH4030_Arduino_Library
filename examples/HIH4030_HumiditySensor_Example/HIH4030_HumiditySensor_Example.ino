/* **************************************************************************************
 * HIH4030_HumiditySensor_Example.ino
 * E.Robert @ SparkFun Electronics
 * original creation date: November 5, 2016
 * https://github.com/sparkfun/SparkFun_HIH4030_Arduino_Library
 * 
 * Functions: Allows you to set supply voltage, define whether or not a temperature 
 *            sensor is being used, define static temperature value in absense of a 
 *            temperature sensor, and utilize the equations supplied by the manufacturer 
 *            to acquire accurate measurements of Relative Humidity (RH%).
 *            
 *            https://learn.sparkfun.com/tutorials/hih-4030-humidity-sensor-hookup-guide
 *            
 *            Note: TMP102 Sensor is being used in this example as part of the
 *                  SparkFun HIH-4030 Humidity Sensor Hookup Guide. However, other 
 *                  temperature sensors can also be used in this sketch by replacing
 *                  the necessary code inside the getTemperature() function.
 * 
 * Resources:
 * Wire.h - Arduino I2C Library
 * SparkFun_HIH4030.h - Arduino Library for SparkFun Humidity Sensor Breakout - HIH-4030
 * 
 * Development environment specifics:
 * Arduino 1.6.8
 * SparkFun RedBoard
 * SparkFun Real Time Clock Module (v14)
 ************************************************************************************** */

// Library Inclusions
#include <SparkFun_HIH4030.h>
#include <Wire.h>

// Example Variables
int tempAddress = 0x48;             // I2C: TMP102 Slave Address with ADD0 Grounded
float temp = 0;                     // Temperature Value either Static or Sensor Reading

// Are You Using a Temperature Sensor? 1 = YES / 0 = NO
int tempSensor = 0;

// Analog IO Pin Connected to OUT
#define HIH4030_OUT A0

// Supply Voltage - Typically 5 V
#define HIH4030_SUPPLY 5

// Library Variables
HIH4030 sensorSpecs(HIH4030_OUT, HIH4030_SUPPLY);

void setup(void){
  
  Serial.begin(9600);               // Serial Port
  Wire.begin();                     // I2C: Utilized by TMP102 Temperature Sensor
  
}

/* Serial Output of Temperature C, Sensor Voltage V, SensorRH %, and TrueRH % */
void printData(HIH4030 sensor, float temperature){
  
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.print(" C ("); Serial.print((temperature * 9/5) + 32); Serial.println(" F)");
  Serial.print("Sensor Voltage = ");
  Serial.print(sensor.vout());
  Serial.println(" V");
  Serial.print("Relative Humidity = ");
  Serial.print(sensor.getSensorRH());
  Serial.println(" %");
  Serial.print("True Relative Humidity = ");
  Serial.print(sensor.getTrueRH(temperature));
  Serial.println(" %");
  
}

void loop(void){
  
  /*  IF tempSensor = 1 Utilizing a Temperature Sensor             */
  /*  IF tempSensor = 0 Utilizing a Static Value for Temperature   */
  if (tempSensor == 1) {
    temp = getTemperature();        // Get Temperature Sensor Reading
  } else if (tempSensor == 0) {
    temp = 25;                      // Static Temperature Value in C
                                    // Set by User to Desired Temperature                            
  } else {
    while (tempSensor != 1 || tempSensor != 0){
      Serial.println("ERROR: tempSensor Value Out of Range");
    }
  }

  printData(sensorSpecs, temp);     // Print Sensor Readings
  Serial.println("");               // Return Space Between Readings
  delay(100);                       // Slow Down Serial Output
  
}

/* Only Called IF Temperature Sensor is Being Used */
float getTemperature(){

  /*  IF Temperature Sensor is different from the TMP102 and not   */      
  /*    utilizing I2C via the Wire.h library, replace the code     */ 
  /*    within the getTemperature() function.                      */ 
  
  Wire.requestFrom(tempAddress,2);  // Wire.requestFrom(address, # of bytes to request)

  byte MSB = Wire.read();           // Receive byte as MSB or left-most bit
  byte LSB = Wire.read();           // Receive byte as LSB or right-most bit

  /*  TMP102 Temperature Register 12-bit, read-only, two's compliment for negative */
  /*  << is bit shift left ; >> is bit shift right ; | is bitwise OR               */
  /*  Syntax:   variable << number_of_bits                                         */
  /*            variable >> number_of_bits                                         */
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;  //One LSB equals 0.0625 C
  return celsius;
  
}

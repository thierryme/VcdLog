/*
  Serial Logging in VCD format
 Language: Wiring/Arduino

 This program sends analog values trough the serial
 connection in the VCD format

   The circuit:
 * potentiometers attached to analog inputs 0 

 Created 18 Jun. 2016
 by Thierry Meister
 */

#include "VcdLog.h"

#define POT '+'
#define PRINT_TIME '"'

#define ANALOG 1
#define DIGITAL 0

VcdLog logger;

float firstSensor = 0.0;    // first analog sensor
unsigned long time1, time2, new_time1;
bool printing = false;

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  logger.addSignal(POT, "val_pot", ANALOG);
  logger.addSignal(PRINT_TIME, "t_serial_print", DIGITAL);

  delay(1000);
  Serial.print(logger.getHeader()); //Print the header of the VCD file
  delay(1000);
  time1 = millis();
  time2 = millis();
}

void loop() {
  // if we get a valid byte, read analog ins:

  // read first analog input
  firstSensor = (float)analogRead(A0);
  // delay 10ms to let the ADC recover:
  delay(10);

  new_time1 = millis(); 
  printing = true;
  // send sensor values: 
  Serial.print(logger.toVcdTime(time1));
  Serial.print(logger.toVcdVal(POT,firstSensor));
  Serial.print(logger.toVcdVal(PRINT_TIME, printing));

  Serial.print(logger.toVcdTime(time2));
  printing = false;
  Serial.print(logger.toVcdVal(PRINT_TIME, printing));

  time2 = millis();
  time1 = new_time1;
}

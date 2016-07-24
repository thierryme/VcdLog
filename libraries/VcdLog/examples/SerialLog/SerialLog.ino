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



VcdLog logger(&Serial);

float first_sensor = 0.0;    // first analog sensor
unsigned long time1, time2, new_time1;
bool printing = false;

int pot_val, print_time;

void setup() {
  // start serial port at 115200 bps:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pot_val = logger.addSignal('+', "val_pot", VL_REAL);
  print_time = logger.addSignal('"', "t_serial_print", VL_BOOL);

  delay(1000);
  //Serial.print(logger.getHeader()); //Print the header of the VCD file
  logger.printHeader();
  delay(1000);
  time1 = millis();
  time2 = millis();
}

void loop() {
  // if we get a valid byte, read analog ins:

  // read first analog input
  first_sensor = (float)analogRead(A0);
  // delay 10ms to let the ADC recover:
  delay(10);

  new_time1 = millis(); 
  printing = true;
  // send sensor values: 
  // Serial.print(logger.toVcdTime(time1));
  // Serial.print(logger.toVcdVal(POT,first_sensor));
  // Serial.print(logger.toVcdVal(PRINT_TIME, printing));

  logger.printSignal(pot_val, first_sensor, time1);
  logger.printSignal(print_time, printing, time1);

  // Serial.print(logger.toVcdTime(time2));
  printing = false;
  // Serial.print(logger.toVcdVal(PRINT_TIME, printing));

  logger.printSignal(print_time, printing, time2);

  time2 = millis();
  time1 = new_time1;
}

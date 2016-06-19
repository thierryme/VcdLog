
#ifndef _VCD_LOG_H_
#define _VCD_LOG_H_

#include <Arduino.h>


/**
 * @brief   Helps formating values into vcd file format
 * @details The constructor and each call of the addSignal method construct 
 *          the vcd file header
 * @note    This class doesn't provided control on given values.
 *          VCD files are intressting for visualysing signals trough progams
 *          like GTKwave.
 *          For more information on VCD files, 
 *          see: https://en.wikipedia.org/wiki/Value_change_dump
 *          and IEEE Std 1364-2001: 
 *          http://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=954909&tag=1
 */
class VcdLog
{
public:

/**
 * @brief   Construct a VcdLog object
 * @details Helps construct VCD header and helps formating value
 * @note    Default header (before $var declarations):
 *          $date THE_COMPILATION_DATE_AND_TIME $end
 *          $version Tsukinomi Proto V0.1 $end
 *          $timescale 1 ms $end
 *
 */
  VcdLog();

/**
 * @brief   Overloaded constructor
 * @details Specifiy the headers value
 *
 * @param[in] date        defines the date of the vcd file 
 *                        (ex: "July 09 2016 12:00:05")
 * @param[in] version     defines the version of the vcd file 
 *                        (ex: "Tsukinomi Proto V0.1")
 * @param[in] timescale   defines the timescale of each time value
 *                        (ex: "1 ns")
 *
 */
  VcdLog(String date, String version, String timescale);


/**
 * @brief   Add a $var declaration into the VCD header
 *
 * @param[in] id            the character from wich the signal will be refered
 * 
 * @param[in] signal_name   a name representing the content of the signal
 *
 * @param[in] type          0: digital signal, 1: analog signal
 */
  void addSignal(char id, String signal_name, int type);

/**
 * @brief   Get the VCD header
 * 
 * @note    This function is intended to be called only once, 
 *          to finish the construction of the header and get it
 */
  String getHeader();

/**
 * @brief   Use this fuction to print the time
 * @note    Use it before printing the signals
 * 
 * @param[in] time    Put here the time of the capture
 */
  String toVcdTime(unsigned long time);
  //String toVcdVal(char id, int val);

/**
 * @brief   Use this fuction to print digital signal
 * @note    Use it after printing the time of the capture
 * 
 * @param[in] id      Put here the id of the signal
 * 
 * @param[in] val     Put here the value of the signal
 */
  String toVcdVal(char id, bool val);
  
  /**
 * @brief   Use this fuction to print analog signal
 * @note    Use it after printing the time of the capture
 * 
 * @param[in] id      Put here the id of the signal
 * 
 * @param[in] val     Put here the value of the signal
 */
  String toVcdVal(char id, float val);

private:
  const String date;
  const String version;
  const String timescale;

  String vcd_file_header;
};

#endif
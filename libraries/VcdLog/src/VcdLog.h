
#ifndef _VCD_LOG_H_
#define _VCD_LOG_H_

#include <Arduino.h>


enum VcdLogType {VL_BOOL, VL_CHAR, VL_INT, VL_REAL};

class VcdLogSignal
{
public:
  char* name;
  char id;
  VcdLogType type;
};


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
 * @brief   Construct a VcdLog object
 * @details Helps construct VCD header and helps formating value
 * @note    Default header (before $var declarations):
 *          $date THE_COMPILATION_DATE_AND_TIME $end
 *          $version Tsukinomi Proto V0.1 $end
 *          $timescale 1 ms $end
 *
 */
  VcdLog(Print* print_dst);

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
  VcdLog(char* date, char* version, char* timescale);

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
  VcdLog(char* date, char* version, char* timescale, Print* print_dst);


/**
 * @brief   
 *
 * @param[in] id            the character from wich the signal will be refered
 * 
 * @param[in] signal_name   a name representing the content of the signal
 *
 * @param[in] type          0: digital signal, 1: analog signal
 */
  int addSignal(char id, char* signal_name, VcdLogType type);


  void printHeader();

/**
 * @brief   Use this fuction to print the time
 * @note    Use it before printing the signals
 * 
 * @param[in] time    Put here the time of the capture
 */
  void printSignal(int signal_index, bool val, uint32_t signal_time);
  void printSignal(int signal_index, int val, uint32_t signal_time);
  void printSignal(int signal_index, float val, uint32_t signal_time);

private:
  const char* date;
  const char* version;
  const char* timescale;

  Print* print_dst;

  VcdLogSignal signals[30];
  int signals_index;
  uint32_t last_printed_time;
};

#endif
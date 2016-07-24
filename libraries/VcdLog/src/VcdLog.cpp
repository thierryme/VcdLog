
#include "VcdLog.h"
#include <Arduino.h>


VcdLog::VcdLog()
  :date(__DATE__ " " __TIME__), version("VcdLog V0.1"), timescale("1 ms"), print_dst(&Serial), signals_index(0), last_printed_time(0)
{
  // vcd_file_header[0] = '\0';

  // strcat(vcd_file_header, "$date ");
  // strcat(vcd_file_header, date);
  // strcat(vcd_file_header, " $end\n");
  // strcat(vcd_file_header, "$version ");
  // strcat(vcd_file_header, version);
  // strcat(vcd_file_header, " $end\n");
  // strcat(vcd_file_header, "$timescale ");
  // strcat(vcd_file_header, timescale);
  // strcat(vcd_file_header, " $end\n");
}

VcdLog::VcdLog(Print* print_dst)
  :date(__DATE__ " " __TIME__), version("VcdLog V0.1"), timescale("1 ms"), print_dst(print_dst), signals_index(0), last_printed_time(0)
{
  // vcd_file_header[0] = '\0';
}

VcdLog::VcdLog(char* date, char* version, char* timescale)
  :date(date), version(version), timescale(timescale), print_dst(&Serial), signals_index(0), last_printed_time(0)
{
  // vcd_file_header[0] = '\0';

}

VcdLog::VcdLog(char* date, char* version, char* timescale, Print* print_dst)
  :date(date), version(version), timescale(timescale), print_dst(print_dst), signals_index(0), last_printed_time(0)
{
  // vcd_file_header[0] = '\0';

}


int VcdLog::addSignal(char id, char* signal_name, VcdLogType type)
{
  // if(type == 0) //digital
  // {
  //   vcd_file_header += "$scope module digital $end\n"\
  //     + char* "$var wire 1 ") + id + " " + signal_name + " $end\n"\
  //     + char* "$upscope $end\n");
  // }
  // else if(type == 1) //analog
  // {
  //   vcd_file_header += "$scope module analog $end\n"\
  //     + char* "$var real 32 ") + id + " " + signal_name + " $end\n"\
  //     + char* "$upscope $end\n");
  // }
  signals[signals_index].id = id;
  signals[signals_index].name = signal_name;
  signals[signals_index].type = type;

  return signals_index++;
}

void VcdLog::printHeader()
{
  // vcd_file_header += "$enddefinitions $end\n";

  // return vcd_file_header;

  print_dst->print("$date ");
  print_dst->print(date);
  print_dst->print(" $end\n");
  print_dst->print("$version ");
  print_dst->print(version);
  print_dst->print(" $end\n");
  print_dst->print("$timescale ");
  print_dst->print(timescale);
  print_dst->print(" $end\n");

  for(int i = 0;i<signals_index;i++)
  {
    switch(signals[signals_index].type)
    {
      case VL_BOOL:
        print_dst->println("$scope module bool $end");
        print_dst->print("$var wire 1 ");
        print_dst->print(signals[i].id);
        print_dst->print(" ");
        print_dst->print(signals[i].name);
        print_dst->println(" $end");
        print_dst->println("$upscope $end");
      break;
      case VL_CHAR:
        print_dst->println("$scope module char $end");
        print_dst->print("$var wire 8 ");
        print_dst->print(signals[i].id);
        print_dst->print(" ");
        print_dst->print(signals[i].name);
        print_dst->println(" $end");
        print_dst->println("$upscope $end");
      break;
      case VL_INT:
        print_dst->println("$scope module int $end");
        print_dst->print("$var wire 32 ");
        print_dst->print(signals[i].id);
        print_dst->print(" ");
        print_dst->print(signals[i].name);
        print_dst->println(" $end");
        print_dst->println("$upscope $end");
      break;
      case VL_REAL:
        print_dst->println("$scope module real $end");
        print_dst->print("$var real 32 ");
        print_dst->print(signals[i].id);
        print_dst->print(" ");
        print_dst->print(signals[i].name);
        print_dst->println(" $end");
        print_dst->println("$upscope $end");
      break;
    }

  }
  print_dst->println("$enddefinitions $end");
  print_dst->println("#0");
}

void VcdLog::printSignal(int signal_index, bool val, uint32_t signal_time)
{
  if(signal_time>last_printed_time)
  {
    print_dst->print("#");
    print_dst->println(signal_time);
    last_printed_time = signal_time;
  }

  switch(signals[signal_index].type)
  {
    case VL_BOOL:
      print_dst->print((bool)val);
      print_dst->println(signals[signal_index].id);
    break;
    case VL_REAL:
      print_dst->print("r");
      print_dst->print(val);
      print_dst->print(" ");
      print_dst->println(signals[signal_index].id);
    break;
    case VL_INT:
      print_dst->print("b");
      print_dst->print(val, BIN);
      print_dst->print(" ");
      print_dst->println(signals[signal_index].id);
    break;
    case VL_CHAR:
      print_dst->print("b");
      print_dst->print(val, BIN);
      print_dst->print(" ");
      print_dst->println(signals[signal_index].id);
    break;
  }
}

void VcdLog::printSignal(int signal_index, int val, uint32_t signal_time)
{
  if(signal_time>last_printed_time)
  {
    print_dst->print("#");
    print_dst->println(signal_time);
    last_printed_time = signal_time;
  }

  switch(signals[signal_index].type)
  {
    case VL_BOOL:
      print_dst->print((bool)val);
      print_dst->println(signals[signal_index].id);
    break;
    case VL_REAL:
      print_dst->print("r");
      print_dst->print((float)val);
      print_dst->print(" ");
      print_dst->println(signals[signal_index].id);
    break;
    case VL_INT:
      print_dst->print("b");
      print_dst->print(val, BIN);
      print_dst->print(" ");
      print_dst->println(signals[signal_index].id);
    break;
    case VL_CHAR:
      print_dst->print("b");
      print_dst->print((char)val, BIN);
      print_dst->print(" ");
      print_dst->println(signals[signal_index].id);
    break;
  }
}

void VcdLog::printSignal(int signal_index, float val, uint32_t signal_time)
{
  if(signal_time>last_printed_time)
  {
    print_dst->print("#");
    print_dst->println(signal_time);
    last_printed_time = signal_time;
  }

  switch(signals[signal_index].type)
  {
    case VL_BOOL:
      print_dst->print((bool)val);
      print_dst->println(signals[signal_index].id);
    break;
    case VL_REAL:
      print_dst->print("r");
      print_dst->print(val);
      print_dst->print(" ");
      print_dst->println(signals[signal_index].id);
    break;
  }
}

void VcdLog::printSignal(int signal_index, char val, uint32_t signal_time)
{
  if(signal_time>last_printed_time)
  {
    print_dst->print("#");
    print_dst->println(signal_time);
    last_printed_time = signal_time;
  }

  switch(signals[signal_index].type)
  {
    case VL_BOOL:
      print_dst->print((bool)val);
      print_dst->println(signals[signal_index].id);
    break;
    case VL_REAL:
      print_dst->print("r");
      print_dst->print((float)val);
      print_dst->print(" ");
      print_dst->println(signals[signal_index].id);
    break;
    case VL_INT:
      print_dst->print("b");
      print_dst->print(val, BIN);
      print_dst->print(" ");
      print_dst->println(signals[signal_index].id);
    break;
    case VL_CHAR:
      print_dst->print("b");
      print_dst->print((char)val, BIN);
      print_dst->print(" ");
      print_dst->println(signals[signal_index].id);
    break;
  }
}
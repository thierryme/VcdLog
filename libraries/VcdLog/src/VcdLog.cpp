
#include "VcdLog.h"
#include <Arduino.h>



VcdLog::VcdLog()
{
  VcdLog(__DATE__ " " __TIME__, "Tsukinomi Proto V0.1", "1 ms");
}

VcdLog::VcdLog(String date, String version, String timescale)
  :date(date), version(version), timescale(timescale)
{
  vcd_file_header = "";

  vcd_file_header += "$date " + date + " $end\n"\
    + "$version " + version + " $end\n"\
    + "$timescale " + timescale + " $end\n";
}


void VcdLog::addSignal(char id, String signal_name, int type)
{
  if(type == 0) //digital
  {
    vcd_file_header += "$scope module digital $end\n"\
      + "$var wire 1 " + id + " " + signal_name + " $end\n"\
      + "$upscope $end\n";
  }
  else if(type == 1) //analog
  {
    vcd_file_header += "$scope module analog $end\n"\
      + "$var real 32 " + id + " " + signal_name + " $end\n"\
      + "$upscope $end\n";
  }
}

String VcdLog::getHeader()
{
  vcd_file_header += "$enddefinitions $end\n";

  return vcd_file_header;
}

String VcdLog::toVcdTime(unsigned long time)
{
  String time_entry = "#";

  return time_entry+time+"\n";
}
//String toVcdVal(char id, int val);
String VcdLog::toVcdVal(char id, bool val)
{
  String signal_id = id;

  return val + signal_id + "\n";
}

String toVcdVal(char id, float val)
{
  String signal_id = " "+id;
  String real_id = "r";

  return real_id+val+signal_id+"\n";
}

#include "VcdLog.h"
#include <Arduino.h>



VcdLog::VcdLog()
  :date(__DATE__ " " __TIME__), version("VcdLog V0.1"), timescale("1 ms")
{
  vcd_file_header = "";

  vcd_file_header += "$date " + date + " $end\n"\
    + "$version " + version + " $end\n"\
    + "$timescale " + timescale + " $end\n";
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
      + String("$var wire 1 ") + id + " " + signal_name + " $end\n"\
      + String("$upscope $end\n");
  }
  else if(type == 1) //analog
  {
    vcd_file_header += "$scope module analog $end\n"\
      + String("$var real 32 ") + id + " " + signal_name + " $end\n"\
      + String("$upscope $end\n");
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
  String signal_id = String(id);

  return val + signal_id + "\n";
}

String VcdLog::toVcdVal(char id, float val)
{
  String signal_id = String(id);
  String real_id = "r";

  return real_id+val+" "+signal_id+"\n";
}
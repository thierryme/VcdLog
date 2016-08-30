# VcdLog

Basic library for logging certain type of data into the VCD format. See the  IEEE Standard 1364-1995.

Use the TCL script with Gtkwave to have automatic coloring and format selection.

Syntax (Gtkwave must be compiled with TCL script support)
  ./gtkwave file.vcd --script gtkwave_init2.tcl


The python script retrieves VCD datas from a Serial connection and writes them to the computer.
  ./VCDSerialToFile.py -p /dev/my_tty_port -b baudrate > filename.vcd

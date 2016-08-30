# VcdLog

Basic Arduino library for logging certain type of data into the VCD format. See the  IEEE Standard 1364-1995.


## TCL script
Use the TCL script with Gtkwave to have automatic coloring and format selection.

### Syntax 
> note: Gtkwave must be compiled with TCL script support

```bash
./gtkwave_file.vcd --script gtkwave_init2.tcl
```

## Python script
The python script retrieves VCD datas from a serial connection and writes them on the standard output.

```bash
./VCDSerialToFile.py -p /dev/my_tty_port -b baudrate > filename.vcd
```

#!/usr/bin/python

# -*- coding: utf-8 -*-
# @Author: Meister Thierry
# @Date:   2016-06-10 14:10:54
# @Last Modified by:   Meister Thierry
# @Last Modified time: 2016-06-19 14:14:09


import serial
import time
import sys
import argparse


if __name__ == '__main__':
    # Arguments parser
    parser = argparse.ArgumentParser(description='Receive VCD format trough Serial port')
    parser.add_argument('-d', '--device', metavar='DEVICE',
                        help='Serial device ex: /dev/xxx', required=True)
    parser.add_argument('-b', '--baud', metavar='BAUD', type=int,
                        help='Baud used for the serial device',
                        default=115200)
    args = parser.parse_args()

    while True:
        try:
            ser = serial.Serial(args.device, serial.baud)                     # open serial port
            ser_connected = ser.name
            print("{} connected".format(ser_connected), file=sys.stderr)    # check the used port

            try:
                #Clear garabage before header
                line = ser.readline()
                while(line.find("$date") == -1):
                    print(line, file=sys.stderr)
                    line = ser.readline();

                start_index = line.find("$date")

                print("Start of file detected", file=sys.stderr)
                print(line[start_index:-1])

                while True:
                    line = ser.readline().decode('ascii')



                    if line[0] in '#01xXzZbBrR$': #basic filtering of entry, drops if incorrect
                        print(line[:-1])
                    else:
                        print("error:{}".format(line[:-2]), file=sys.stderr)

            finally:
                ser.close()
                print("{} disconnected".format(ser_connected), file=sys.stderr)

        except serial.serialutil.SerialException:
            time.sleep(1)
            print("try reconnect", file=sys.stderr)

else:
    parser.print_help(file=sys.stderr)

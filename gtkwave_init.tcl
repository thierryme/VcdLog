###################################################################
# This TCL script automaticly load every signals into GTKwave
# the signals that are into the analog scope are displayed in step
# mode and with colors (other than green)
# -----------------------------------------------------------------
# Usage: 
# $ gtkwave file.vcd --script gtkwave_init.tcl
###################################################################
# 14.06.2016                  #  Thierry Meister
###################################################################

set nfacs [ gtkwave::getNumFacs ]
set dumpname [ gtkwave::getDumpFileName ]
set dmt [ gtkwave::getDumpType ]

set analog_colors {Red Yellow Blue Orange Indigo}

puts "number of signals in dumpfile '$dumpname' of type $dmt: $nfacs"
puts "special formating for signals in analog scope module"


gtkwave::/Edit/Insert_Analog_Height_Extension

set color_choice 0

for {set i 0} {$i < $nfacs } {incr i} {
    set facname [ gtkwave::getFacName $i ]
   
    puts "add signal '$facname'"
    set num_added [ gtkwave::addSignalsFromList $facname ]

    if { [string match {*analog.*} $facname] } {
        puts "put it in analog format"
        gtkwave::/Edit/Data_Format/Analog/Step
        gtkwave::/Edit/Color_Format/[lindex $analog_colors $color_choice]
        gtkwave::/Edit/Insert_Analog_Height_Extension
        gtkwave::/Edit/Insert_Analog_Height_Extension

    } 

    if {$color_choice == [llength $analog_colors]} {
        set color_choice 0
    } else {
        incr color_choice
    }
}

gtkwave::/Edit/UnHighlight_All
gtkwave::/Time/Zoom/Zoom_Full

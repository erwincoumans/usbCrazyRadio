#!/bin/sh
gcc   main.cpp TimeUtils.cpp ofxCrazyradio.cpp -lusb-1.0 -framework IOKit -framework Cocoa -lstdc++ -ousbCrazyRadio

printf "Use ./usbCrazyRadio and a remote nRF24L01+ transceiver\n"


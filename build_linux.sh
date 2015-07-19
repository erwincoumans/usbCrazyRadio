#!/bin/sh
gcc main.cpp TimeUtils.cpp ofxCrazyradio.cpp  -lusb-1.0 -lstdc++ -lm -ousbCrazyRadio

printf "Use sudo ./usbCrazyRadio and a remote nRF24L01+ transceiver\n"


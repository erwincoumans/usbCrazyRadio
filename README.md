== usbCrazyRadio ==

Send and receive to nRF24L01+ from Mac and Linux using libusb and the CrazyRadio dongle with nRF24LU1+
Tested with an Arduino with nRF24L01+ transceiver and the ping-pong sketch (in arduino/crazyradio_pingping_with_ack.ino)

Uses code from ofxCrazyFlie, see https://github.com/Saqoosha/ofxCrazyflie

== Build ==

Install libusb-1.0

Mac OSX:
```
./build_mac.sh
```
Linux:
```
./build_linux.sh
```
== Run ==

Make sure the receiver nRF24L01+ is running some ping-pong script with acknowledge and dynamic payload enabled.
```
./usbCrazyRadio
```
== Example output ==
```
[~/develop/network/crazyradio2nrf24l01/tmp/usbCrazyRadio]$ ./usbCrazyRadio 
usleep(500) test took 522105 nano seconds (or 0.00052s seconds)
Wait searching and initializing USB device
libusb_init: 0
libusb_get_device_list: 9
libusb_open: 0
version: 52
libusb_get_string_descriptor_ascii: 8
Bitcraze
config: 1
bNumInterfaces: 1
  num_altsetting: 1
    Interface number: 0
    number of endpoint: 2
     desc type: 5
     ep address: 129
     attributes: 2
     desc type: 5
     ep address: 1
     attributes: 2
libusb_kernel_driver_active: 0
libusb_claim_interface: 0
ok initialized
nRF24 radio initialized.
Now sending 2000 packets, please wait
Successfull send packets: 2000, failed packets:0
Roundtrip of 2000 packets took 2307673899 nano seconds (or 2.3s seconds)
```


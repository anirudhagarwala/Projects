#/bin/bash

#set baudrate for MySmartUSB: 19200
stty 19200 -F /dev/ttyUSB_MySmartUSB

#send command to set to UART mode
echo -en '\x00\xE6\xB5\xBA\xB9\xB2\xB3\xA9\x70' > /dev/ttyUSB_MySmartUSB

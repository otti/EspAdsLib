# Simple ESP library for Beckhoff ADS

## Features
* Base functions
  * Ads Read
  * Ads Write
  * Ads ReadWrite
* Convenience functions which are based on the functions above
  * Ads WritePlcVarByName
  * Ads ReadPlcVarByName
  * Ads ReadCoe (with and without complete access)
  * Ads WriteCoe (with and without complete access)

## How to install
Download this repository as zip file and import it to the Arduino libraries.  
(Sketch -> Include Library -> Add .ZIP Library)

## Usage
* Set WiFi SSID and password in the example .ino file
* Set the SrcAmsAddr to the IP address of your ESP followed by `1.1`.  
* In the TwinCAT "Add Route Dialog" of the target machine you have to add the IP of this ESP.
Make sure, that you have set the "Remote Route" to "None"
<img src="https://github.com/otti/EspAdsLib/blob/main/pics/AddRoute.png" width="500">

### Writing CoE Values
Set the DestAmsAddr and the port in the code to the AmsAddr of the slave you want to access.
<img src="https://github.com/otti/EspAdsLib/blob/main/pics/AmsNetId_CoE.png" width="450">

### Writing PLC variables
Set the DestAmsAddr in the code to the AmsAddr of the target. This usually ends with `.1.1`
<img src="https://github.com/otti/EspAdsLib/blob/main/pics/AmsNetId_Target.png" width="450">
Set the port to the port of your PLC. The first PLC usually has port 851 on TwinCAT3 and 801 on TwinCAT2.
The port is also available as define. (`AMSPORT_R0_PLC_TC3`)

## Limitations
To save some memory, the lib can read and write a maximum ammount auf 64 bytes. 
This value can be increased by overwriting the `#define ADS_MAX_DATA_SIZE` in ads.h

## Current status/To Do
* The Lib is tested insufficiently
* Should work with ESP8266, but not tested
* The ADS Read, Write and ReadWrite function are mostly identical. With some affort this three functions can share the same code.

## Debugging
* For some debug outputs on the serial console set `#define ADS_DEBUG_PRINT_ENABLE = 1`
* DebugPrintHex() can be used to print a hex dump in a format like a hex editor

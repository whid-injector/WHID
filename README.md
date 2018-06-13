# WHID Injector #


[![Black Hat Arsenal Europe](https://github.com/toolswatch/badges/blob/master/arsenal/europe/2017.svg)](http://www.toolswatch.org/2018/01/black-hat-arsenal-top-10-security-tools/) [![ToolsWatch Best Tools](https://github.com/toolswatch/badges/blob/master/toptools/2017.svg)](http://www.toolswatch.org/2018/01/black-hat-arsenal-top-10-security-tools/)


WiFi HID Injector for Fun & Profit

Hardware Design Author: Luca Bongiorni - https://twitter.com/lucabongiorni

Initial sw based on ESPloit by Corey Harding of www.LegacySecurityGroup.com

Available at**:

* [Aliexpress Shop](https://www.aliexpress.com/item/Cactus-Micro-compatible-board-plus-WIFI-chip-esp8266-for-atmega32u4/32318391529.html)
* [Tindie Shop](https://www.tindie.com/products/aprbrother/cactus-whid-wifi-hid-injector-usb-rubberducky)
* [eBay Shop](https://www.ebay.com/sch/camealone/m.html)
* [Manufacturer Online Shop](https://blog.aprbrother.com/product/cactus-whid)

**The Author has no profit out of the Cactus WHID sales.

## HOW TO START [Newbies Edition] ##

Since July 2017 all Cactus WHID are delivered with pre-loaded ESPloitV2 and are ready to Plug-n-Hack ✌

Thus, even if you are not an Arduino expert, you can immediately have fun!

Just plug it in an USB port and connect to the WiFi network:

SSID "Exploit" 

Password "DotAgency"

Open a web browser pointed to "http://192.168.1.1"

The default administration username is "admin" and password "hacktheplanet".

https://youtu.be/5WTrKvQbK9o

For cool payloads or more info check the Wiki or the Payloads directory.

## The Hardware ##

<img src="https://raw.githubusercontent.com/whid-injector/WHID/master/tools/images/collage.jpg" width="300">


## USB Pinouts ##

In order to make easier the process of weaponizing USB gadgets, you can solder the USB wires to the dedicated pinouts.

The pin closer to USB-A is GND. The pins are:

* GND 
* D+ 
* D-  
* VCC 

<img src="https://raw.githubusercontent.com/whid-injector/WHID/master/tools/hardware/p2-usb-pinout.png" width="300">

[ If also an USB HUB is needed (i.e. to weaponize a wired mouse), usually, I do use this one https://www.tindie.com/products/mux/nanohub-tiny-usb-hub-for-hacking-projects ]

## Documentation WIKI ##

I HEAVILY RECOMMEND TO READ IT ALL!
https://github.com/whid-injector/WHID/wiki

## Third-Party Softwares Compatible with WHID's Hardware ##

https://github.com/exploitagency/ESPloitV2  An improved version of WHID GUI

https://github.com/sensepost/USaBUSe

https://github.com/spacehuhn/wifi_ducky

https://github.com/basic4/WiDucky


## Possible Applications ##

- Classic: Remote Keystrokes Injection Over WiFi

Deploy WHID on Victim's machine and remotely control it by  accessing its WiFi AP SSID. (eventually you can also setup WHID to connect to an existing WiFi network)

<img src="https://raw.githubusercontent.com/whid-injector/WHID/master/tools/images/WHID_GUI.png" width="300">

- Social Engineering: Deploy WHID inside an USB-enable gadget

The main idea behind it is to test for Social Engineering weaknesses within your target organization (e.g. DLP policy violations) and to bypass physical access restrictions to Target's device.
Usually, I create a fancy brochure (sample template https://github.com/whid-injector/WHID/tree/master/tools/Social_Engineering_Lures ) attached with a weaponized USB gadget and then use a common delivery carrier (e.g. UPS, DHL, FedEx).

<img src="https://raw.githubusercontent.com/whid-injector/WHID/master/tools/images/Weaponized_PlasmaBall.png" width="300">

<img src="https://raw.githubusercontent.com/whid-injector/WHID/master/tools/images/Brochure_front.jpg" width="300">

## Video Tutorials ##

[![WHID's Attack Simulation](https://raw.githubusercontent.com/whid-injector/WHID/master/tools/images/snapshot_youtube_2.jpg)](https://www.youtube.com/watch?v=U-TtobZXJcw)

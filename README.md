# WHID Injector #

WiFi HID Injector for Fun & Profit

Available at:

* https://www.aliexpress.com/item/Cactus-Micro-compatible-board-plus-WIFI-chip-esp8266-for-atmega32u4/32318391529.html
* https://blog.aprbrother.com/product/cactus-whid
* http://www.ebay.com/itm/Cactus-WHID-WiFi-HID-InjectorAn-USB-Rubberducky-On-Steroids-for-hackers-pentests-/252927790606


Hardware Design Author: Luca Bongiorni - <info@whid.ninja> - http://whid.ninja

Initial sw based on ESPloit by Corey Harding of www.LegacySecurityGroup.com

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

https://github.com/whid-injector/WHID/wiki

## Third-Party Softwares Compatible with WHID's Hardware ##

https://github.com/exploitagency/ESPloitV2  An improved version of WHID GUI software!

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


Please keep in mind that the following Video is for installing WHID Software into Cactus Micro (which has 512K/64K Flash). If you wanna install on Cactus WHID hardware, select 4M/3M option in Arduino's settings.


[![How To Install WHID Software](https://raw.githubusercontent.com/whid-injector/WHID/master/tools/images/snapshot_youtube_1.jpg)](https://www.youtube.com/watch?v=MRGUSPW-Cr0)

## More to come... ##

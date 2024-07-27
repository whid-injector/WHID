# WHID Injector #


[![Black Hat Arsenal Europe](https://github.com/toolswatch/badges/blob/master/arsenal/europe/2017.svg)](http://www.toolswatch.org/2018/01/black-hat-arsenal-top-10-security-tools/) [![Black Hat Arsenal USA](https://github.com/toolswatch/badges/blob/master/arsenal/usa/2018.svg)](https://www.blackhat.com/us-18/arsenal/schedule/index.html#whid-injector-and-whid-elite-a-new-generation-of-hid-offensive-devices-10459) [![ToolsWatch Best Tools](https://github.com/toolswatch/badges/blob/master/toptools/2017.svg)](http://www.toolswatch.org/2018/01/black-hat-arsenal-top-10-security-tools/)

**WiFi HID Injector for Fun & Profit**<br>
Hardware Design Author: Luca Bongiorni - https://twitter.com/lucabongiorni<br>
Initial sw based on ESPloit by Corey Harding of www.LegacySecurityGroup.com<br>
WHID Mobile Connector by Paul https://twitter.com/paulwebsec<br>

**For Sale at:****

* [Aliexpress Shop](https://www.aliexpress.com/item/Cactus-Micro-compatible-board-plus-WIFI-chip-esp8266-for-atmega32u4/32318391529.html)
* [Tindie Shop](https://www.tindie.com/products/aprbrother/cactus-whid-wifi-hid-injector-usb-rubberducky)
* [eBay Shop](https://www.ebay.com/sch/camealone/m.html)
* [Manufacturer Online Shop](https://blog.aprbrother.com/product/cactus-whid)



## WHID's Trainings
The 𝙊𝙛𝙛𝙚𝙣𝙨𝙞𝙫𝙚 𝙃𝙖𝙧𝙙𝙬𝙖𝙧𝙚 𝙃𝙖𝙘𝙠𝙞𝙣𝙜 𝙏𝙧𝙖𝙞𝙣𝙞𝙣𝙜 is a Self-Paced training including Videos, a printed Workbook and a cool Hardware Hackit Kit. And... you get everything shipped home Worldwide! 🌍🔥😎<br>
For more info... ➡ https://www.whid.ninja/store <br><br>
[![WHID's Trainings](https://files.gandi.ws/64/2e/642e05f6-84e1-48fe-8a59-d678c7d635e3.PNG)](https://www.youtube.com/watch?v=zbUuBZJIHkE)



** **The Author has no profit out of the Cactus WHID sales. But you can always buy him an Italian Coffee** :) <a href='https://ko-fi.com/X7X6L82L' target='_blank'><img height='36' style='border:0px;height:36px;' src='https://az743702.vo.msecnd.net/cdn/kofi4.png?v=0' border='0' alt='Buy Me a Coffee at ko-fi.com' /></a>

# Generic Overwiev #

[![WHID's Talk @ HackInParis 2018](https://raw.githubusercontent.com/whid-injector/WHID/master/tools/images/HiP_2k18.png)](https://www.youtube.com/watch?v=ADqMCKtufNY)

Here the Video: [HiP 2018 Video](https://www.youtube.com/watch?v=ADqMCKtufNY)

Here its slides: [HiP 2018 Slides](https://hackinparis.com/data/slides/2018/talks/HIP2018_Luca_Bongiorni_How_To_Bring_HID_Attacks_To_The_Next_Level.pdf) (dead url, see  [webarchive Nov 2021](https://web.archive.org/web/20211119231320/https://www.hackinparis.com/data/slides/2018/talks/HIP2018_Luca_Bongiorni_How_To_Bring_HID_Attacks_To_The_Next_Level.pdf))

**<br> WHID Injector has an Official Android App https://apkpure.com/whid-mobile-connector/whid.usb.injector and guess what, we open sourced it.
WHID Mobile Connector is Open/Source! Wanna contribute?<br>Look at https://github.com/whid-injector/WHID-Mobile-Connector**

## READ FIRST ALL THIS README OR DON'T YOU DARE TO OPEN ISSUES. I AM SERIOUS!<br/>













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

[ In case an USB HUB is needed (i.e. to weaponize some USB gadget or mouse), usually, I do use this one https://www.smart-prototyping.com/NanoHub-tiny-USB-hub-for-hacking-projects or https://www.tindie.com/products/mux/nanohub-tiny-usb-hub-for-hacking-projects or this https://www.aliexpress.com/item/Random-Color-Redbud-High-Speed-USB-2-0-4-Port-HUB-Fashion-Design-HUB-Computer-Accessories/32788390064.html]

## Documentation WIKI ##

I HEAVILY RECOMMEND TO READ IT ALL!
https://github.com/whid-injector/WHID/wiki

## Third-Party Softwares Compatible with WHID's Hardware ##

https://github.com/whid-injector/WHID/tree/master/ESPloitV2_whid  (Improved version of WHID GUI, installed by default on Cactus WHID hardware)

https://github.com/sensepost/USaBUSe (Dedicated software for AirGap bypass Vs Windows)

https://github.com/spacehuhn/wifi_ducky (old software similar to ESPloitV2)


## Possible Applications ##

- Classic: Remote Keystrokes Injection Over WiFi

Deploy WHID on Victim's machine and remotely control it by  accessing its WiFi AP SSID. (eventually you can also setup WHID to connect to an existing WiFi network)

<img src="https://raw.githubusercontent.com/whid-injector/WHID/master/tools/images/WHID_GUI.png" width="300">

- Social Engineering: Deploy WHID inside an USB gadget

The main idea behind it is to test for Social Engineering weaknesses within your target organization (e.g. DLP policy violations) and to bypass physical access restrictions to Target's device.
Usually, I create a fancy brochure (sample template https://github.com/whid-injector/WHID/tree/master/tools/Social_Engineering_Lures ) attached with a weaponized USB gadget and then use a common delivery carrier (e.g. UPS, DHL, FedEx).

<img src="https://raw.githubusercontent.com/whid-injector/WHID/master/tools/images/Weaponized_PlasmaBall.png" width="300">

<img src="https://raw.githubusercontent.com/whid-injector/WHID/master/tools/images/Brochure_front.jpg" width="300">

## Video Tutorials ##

[![WHID's Attack Simulation](https://raw.githubusercontent.com/whid-injector/WHID/master/tools/images/snapshot_youtube_2.jpg)](https://www.youtube.com/watch?v=U-TtobZXJcw)

More Video on WHID's Youtube Channel:

https://www.youtube.com/channel/UCzh8wlTSYbdZCs__Djym5UQ/videos


## Blogposts about WHID ##

https://www.x90x90.net/hardware/2021/03/26/HID-Implants-for-the-electrically-challenged.html

https://blog.rootshell.be/2018/05/22/evil-mouse-project/

https://medium.com/@LucaBongiorni/whid-injector-how-to-bring-hid-attacks-to-the-next-level-b06a40b7df22

## Forensics Analysis of HID Offensive Implants from Societe Generale's CERT ##

https://github.com/certsocietegenerale/Publications/blob/master/DFRWS%20EU19%20-%20The%20Rise%20Of%20HID%20Devices.pdf

# How to report bugs:
I won't spend time explaining in depth how to report issues, since I am pretty sure you have done it tons of times. 
The main idea can be summed up in the following points:
1. Expected Behavior
2. Unexpected Behavior
3. which OS you using?
4. Which Arduino IDE version you using?
5. Is the target computer an Apple Product?
6. Is the target USB port an USB3.0?
7. Eventual Explanation Notes, Screenshots, Videos, etc.


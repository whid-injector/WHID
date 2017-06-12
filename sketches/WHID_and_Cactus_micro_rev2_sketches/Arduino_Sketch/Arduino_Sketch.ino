/*
 * WHID Injector - Arduino Sketch
 * http://whid.ninja
 * Forked by Luca Bongiorni
 * Based on ESPloit by Corey Harding of www.LegacySecurityGroup.com
*/

/*
For individual keypresses or combinations of key presses send the following via software serial:
-"Press:X" or "Press:X+Y" or "Press:X+Y+Z" and so forth
--Expects DECIMAL Values for X,Y,Z,etc
--Sending the following via software serial "Press:131+114" with the Arduino's USB plugged into a Windows machine would output KEY_LEFT_GUI(Windows_Key)+r thus launching the run prompt
--List of modifier keys(GUI,ALT,CTRL,ETC) at https://www.arduino.cc/en/Reference/KeyboardModifiers
--ASCII table lookup at http://www.asciitable.com/

To type out strings of text send via software serial:
-"Print:XYZ" Types out "XYZ"
--Sending the following via software serial "Print:www.Exploit.Agency" would type out "www.Exploit.Agency" on the machine connected via USB

To type out strings of text send via software serial:
-"PrintLine:XYZ" Types out "XYZ" then presses enter
--Sending the following via software serial "PrintLine:www.Exploit.Agency" would type out "www.Exploit.Agency" on the machine connected via USB and press enter

To make a delay:
-"Delay"
--Sending the following via software serial "Delay" would wait for X seconds(length of delay set in esp8266 sketch) on the machine connected via USB before proceeding to next item in payload
*/

#include <Keyboard.h>
#include <SoftwareSerial.h>
//#include <HID-Project.h>
//#include <HID-Settings.h>

//Used later for determining if we are ready to release a key press or a combination of key presses
int keypressdone=0;

void setup() { 
  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
  Serial1.begin(4800);
  Keyboard.begin();
}

void loop() {  
  while (Serial1.available()) {
    String cmd = Serial1.readStringUntil(':');
    //If command equals "Press:X" or "Press:X+Y+ETC"
    if(cmd == "Press"){
      keypressdone=1;
      String fullkeys = Serial1.readString();
      int str_len = fullkeys.length()+1; 
      char keyarray[str_len];
      fullkeys.toCharArray(keyarray, str_len);
      char delimiter[] = "+";
      char *keypart;
      keypart = strtok(keyarray, delimiter);
      while(keypart != NULL) {
        int key = atoi(keypart);
        delay(25);
        Keyboard.press(key);
        keypart = strtok(NULL, delimiter);
      }
      
      if(keypressdone==1) {
        delay(25);
        Keyboard.releaseAll();
        keypressdone=0;
      }
    }
  
    //If command equals "Print:X"
    else if(cmd == "Print") {
      String keycode = Serial1.readString();
      delay(25);
      Keyboard.print(keycode);
    }

    //If command equals "PrintLine:X"
    else if(cmd == "PrintLine") {
      String keycode = Serial1.readString();
      delay(25);
      Keyboard.print(keycode);
      delay(25);
      Keyboard.press(KEY_RETURN);
      delay(25);
      Keyboard.release(KEY_RETURN);
    }
  }
}

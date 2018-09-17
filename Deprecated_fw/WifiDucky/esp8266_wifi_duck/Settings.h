#pragma once

#include "Arduino.h"
#include <EEPROM.h>
#define ssidLenAdr 0
#define ssidAdr 1
#define passwordLenAdr 33
#define passwordAdr 34
#define channelAdr 66
#define hiddenAdr 67
#define autoExecAdr 68
#define autostartLenAdr 69
#define autostartAdr 70

#define debug false

class Settings{
public:
	Settings();
	void load();
	void save();
	void reset();
	void print();

	int ssidLen;
	char ssid[32];

	int passwordLen;
	char password[32];

	int autostartLen;
	char autostart[32];

	uint8_t channel;
	uint8_t hidden;
	uint8_t autoExec;
	
};


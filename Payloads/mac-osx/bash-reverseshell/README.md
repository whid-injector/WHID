# Bash One-liner

* Author: Phish
* Version: Version 0.1
* Target: Mac-OSX

# Description

A simple bash reverse shell. Opens the terminal app and issues a command to connect back to the attacker's host. Change the Attacker IP address and port number as required.

# Notes

## Start listener first

Use a netcat listener such as; `nc -lv <port>` on mac.

## No control flow

You cannot background or foreground processes in this reverse shell.

## Keys Used

The following keys presses are emulated:

| Key | In English | What it does |
| --- | ------------ | ---------- |
| 131+32 | Command (⌘) + Spacebar | Opens spotlight |
| 176 | Enter | Press enter |
| 131+81 | Command (⌘) + Q | Quit app |

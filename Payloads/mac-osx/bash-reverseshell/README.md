# Bash One-liner

* Author: [dunderhay](https://github.com/dunderhay)
* Version: Version 0.2
* Target: Mac-OSX

# Description

A simple bash reverse shell for Mac OSX. The script will open the terminal app and send through a bash one-liner to create a reverse shell to the attacker. Finally the terminal window is closed. _Note:_ Sigint (Ctrl-C) will kill the shell.

# Notes

Change the Attacker IP address and port number as required.

## Start listener first

Use a netcat listener such as; `nc -lv <port>` on mac.

## No Job Control

You cannot background or foreground processes in this reverse shell.

## Keys Used

The following keys presses are emulated:

| Key | In English | What it does |
| --- | ------------ | ---------- |
| 131+32 | Command (⌘) + Spacebar | Opens spotlight |
| 131+113 | Command (⌘) + q | Quit app |

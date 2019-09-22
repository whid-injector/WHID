# Bash One-liner Alternative

* Author: [dunderhay](https://github.com/dunderhay)
* Version: Version 0.1
* Target: Mac-OSX

# Description

Variation of the bash reverse shell for Mac OSX. However, the command is not run in the background and the terminal window is minimized / hidden using `(⌘) + h` not closed. This allows Job Control to manage Foreground and Background Processes. _Note:_ Sigint (Ctrl-C) will kill the shell.

# Notes

Change the Attacker IP address and port number as required.

## Start listener first

Use a netcat listener such as; `nc -lv <port>` on mac.

## Keys Used

The following keys presses are emulated:

| Key | In English | What it does |
| --- | ------------ | ---------- |
| 131+32 | Command (⌘) + Spacebar | Opens spotlight |
| 131+104 | Command (⌘) + h | Hide terminal app window |

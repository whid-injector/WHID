# RickRoll prank for WHID Injector

* Author: Phish
* Version: Version 0.1
* Target: Mac-OSX

# Description

A simple rickroll script to prank the victim. Opens the terminal app and issues a command to open Rick Astley in a browser.

# Notes

## `nohup`

Runs a command with hangup signals (SIGHUP) ignored, so that the command can continue running in the background after you log out. _Note:_ `nohup` does not automatically background the command, so you need to end the command with an `&` to run it in the background.

## Keys Used

The following keys presses are emulated:

| Key | In English | What it does |
| --- | ------------ | ---------- |
| 131+32 | Command (⌘) + Spacebar | Opens spotlight |
| 176 | Enter | Press enter |

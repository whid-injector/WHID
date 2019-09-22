# PoC to exfil data using wget

* Author: [dunderhay](https://github.com/dunderhay)
* Version: Version 0.1
* Target: Mac-OSX

# Description

Basic Proof on Concept to exfil data from terminal app using wget.

# Notes

Change the Attacker IP address and port number as required.

## Start listener first

You can use whatever web server you want or just use python:

`python -m SimpleHTTPServer <port>`

## Keys Used

The following keys presses are emulated:

| Key | In English | What it does |
| --- | ------------ | ---------- |
| 131+32 | Command (⌘) + Spacebar | Opens spotlight |
| 131+113 | Command (⌘) + q | Quit app |

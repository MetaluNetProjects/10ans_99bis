# Chimere
2017

-----------------------
## Description

4 x Fraise8X2A with (for each) :

- DC-motor + encoder + hall-endswitch
- 3 PWMdriven-leds 12V/1A
- 2 servomotors for pan-tilt-LED

host: raspberryPi3 with start button on GPIO-0 (pin 11 of 40-pins header)

network remote Pd patch:

- set LEDs/motors   
- record/save-to-file/replay from/to OSC

## Installation
### Machine:

Install Pure Data (v >= 0.47-1)  
Install Fraise  
Install Pd externals:

- maxlib
- ggee

Download project zipfile (from github's page), extract.  
Open with Pd : 0main.pd

Configure the rPi: (optionnal)

- set hostname : Chimere
- autostart "pd 0main.pd"
- read-only file-system
- WIFI access point:
	- network name: AP-Chimere
	- password: raspberry
- static eth0 IP: 192.168.1.71

### Remote client:

Install Pure Data (v >= 0.47-1)

Download project zipfile (from github's page), extract.

Connect to the raspberryPi either through ethernet or to WIFI access point:

- network name: AP-Chimere
- password: raspberry

Open with Pd : 0remote.pd  


#### If the client doesn't connect to the machine:
  
In 0client.pd, open sub-patch named `pd guts`; locate the object:  
`PdClient CLIENT CLIENT Chimere.local`

In edit mode, change `Chimere.local` to the IP address you can ping the machine host. Try `192.168.3.1` if WIFI connected, or `192.168.1.71` if ethernet. 
Connection should be established almost instantly. Save the patch when working.


## OSC names:

lyre 1: 

- 1R:rotation
- 1X:pan(in radians -100°/+100°)
- 1Y:tilt(in radians -60°/+140°)
- 1L1:LED1(0-10)
- 1L2:LED2(0-10)
- 1L3:LED3(0-10)

lyre2: 2R 2X 2Y 2L1 2L2 2L3

...

## Credits

Copyright (c) Antoine Rousseau <antoine@metalu.net> 2017  
GNU GENERAL PUBLIC LICENSE  
For information on usage and redistribution, and for a DISCLAIMER OF ALL WARRANTIES, see the file "LICENSE.txt" in this distribution.



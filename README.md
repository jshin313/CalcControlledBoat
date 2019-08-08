# Calculator Controlled Boat

## Description:
I'm able to control an RC boat using my TI-84+ Calculator!
Originally posted in 2017 at https://www.cemetech.net/forum/viewtopic.php?t=13876

## Turning Left:
![](left.gif)

## Moving Forward:
![](forward.gif)

## In a Pond:
![](pond.gif)

I used a library called ArTICL to interface between an Arduino and TI-84+ Calculator: https://github.com/KermMartian/ArTICL

## Instructions:

To start the boat forward, press the UP arrow. 
To stop the boat, press the DOWN arrow. 
To make the boat turn left, press the LEFT arrow. 
To turn the boat right, press the RIGHT arrow.


## Pinouts:

### Transmitter:
#### nrf24l01:

GND -> GND
vcc -> 3.3V
CE  -> 9
CSN -> 10
SCK -> 13
MOSI-> 11
MISO-> 12

RED  -> 7
WHITE-> 6


### Receiver:
#### nrf24l01:

GND -> GND
vcc -> 3.3V
CE  -> 9
CSN -> 10
SCK -> 13
MOSI-> 11
MISO-> 12




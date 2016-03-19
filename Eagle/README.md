# Hardware (Drivers and Monitors)
The hardware is each splitted into two modules (Driver and Monitor).
The two modules where connected by a ribbon cable which should not be too long.


## Driver 1 (Program Counter) -> Monitor 12
Driver 1 is for the Program Counter and have to be placed between the Signal Decoder- and the Program Counter-Board.

You have to remove IC44 and IC46 from the Program-Counter-Board and place it on the Driver 1-Board and use IC socket extensions to connect the ICs again to the Programm Counter-Board like the Memory-Base-, and the Memory-Extension-Board.

You can connect the Monitor 12-Board to display the Programm Counter value.


## Driver 2 (Address Bus) -> Monitor 12, AddressHold
Driver 2 is for the Address Bus and have to be placed between the Program Counter- and the Bus Interface-Board

You can connect the Monitor 12-Board to display the Address Bus value and with the AddressHold-Board you can select an address with dip-switches to hold the CPU on a specific point.


## Driver 3 (Accu, X, Y, SP, OP, AR1, AR2, ALU, O-, V-, C-Flag) -> Monitor 3
Driver 3 is for the various internal CPU register and have to be placed between the Microcode Control- and the Signal Decoder-Board.

You can connect the Monitor 3-Board to display all the registers and flags.

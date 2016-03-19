# MyCPU_HDW_RegMonV2
A hardware expansion for for the MyCPU from Dennis Kuschel (http://www.mycpu.eu) to display the various CPU internal registers.

#### Attention: 
**This project especially the layout are not yet finished and have _never been tested!_
So be careful if you connect this to your MyCPU!**

## Features
- Values display in Hex using an EPROM to convert Binary to 7-segment
- Hold CPU on a specific address using DIP-Switches
- You dont have to build the whole Monitor - Its split into 3x Driver and 2x Monitor modules

## Registers
- Accu
- X-Reg
- Y-Reg
- Stackpointer
- OP-Code
- ALU-Reg 1
- ALU-Reg 2
- ALU-OUT
- Sign-, Zero-, Carry-Flag
- Program Counter
- Addressregister

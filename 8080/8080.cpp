#include <iostream>
#include "c8080.h"

int main()
{
    c8080 my8080;
    
    //load program into memory
    my8080.mem[0x00] = 0x01; //LXI B, D16
    my8080.mem[0x01] = 0x23; //value 23H
    my8080.mem[0x02] = 0x55; //value 55H
    //0x01 and 0x02 represent the 16 bit address 0x5523

    //set registers
   // my8080.C.data = 0x48;
   // my8080.H.data = 0x40;
   // my8080.L.data = 0x05;

    //program cycles until it finds an opcode it cant deal with
    while (my8080.cycle() != -1) {
        //while loop
    }
}
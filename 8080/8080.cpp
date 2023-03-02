#include <iostream>
#include "c8080.h"

int main()
{
    c8080 my8080;
    
    //load program into memory
    my8080.mem[0x00] = 0x40; //mov b,b
    my8080.mem[0x01] = 0x46; //mov b, m(HL)

    //set registers
    my8080.H = 0x40;
    my8080.L = 0x05;

    //program cycles until it finds an opcode it cant deal with
    while (my8080.cycle() != -1) {
        //while loop
    }
}
#include <iostream>
#include "c8080.h"

int main()
{
    c8080 my8080;
    
    //load program into memory
    //my8080.mem[0x00] = 0x06; //mvi b
    //my8080.mem[0x01] = 22; //value 29H

    //my8080.mem[0x02] = 0x16; // mvi d
    //my8080.mem[0x03] = 22; //value 22H

    //my8080.mem[0x04] = 0x5e; //mov e, M(HL)

    //my8080.mem[0x05] = 0x36; //mvi m, d8
    //my8080.mem[0x06] = 5;

    my8080.mem[0x00] = 0x06;
    my8080.mem[0x01] = 0x82;
    my8080.mem[0x02] = 0x3e;
    my8080.mem[0x03] = 0x05;
    my8080.mem[0x04] = 0x80;

    //set registers
  //  my8080.H.data = 0x00;
  //  my8080.L.data = 0x03;

    //Expected output: 
    // B = 0x29
    // D = 22H
    // E = value at 0x0003 -> 0x22
    // H = 0x00
    // L = 0x02
    //program cycles until it finds an opcode it cant deal with
    while (my8080.cycle() != -1) {
        //while loop
    }
}
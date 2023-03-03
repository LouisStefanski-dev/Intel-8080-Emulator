#include <iostream>
#include "c8080.h"

int main()
{
    c8080 my8080;
    
    //load program into memory

    ////test add with carry
    //my8080.mem[0x00] = 0x3e;
    //my8080.mem[0x01] = 0xf0;

    //my8080.mem[0x02] = 0x06;
    //my8080.mem[0x03] = 0xf0;

    //my8080.mem[0x04] = 0x80;

    //my8080.mem[0x05] = 0x3e;
    //my8080.mem[0x06] = 0x00;

    //my8080.mem[0x07] = 0x88;

    //test subtract
    //my8080.mem[0x00] = 0x3e;
    //my8080.mem[0x01] = 0x20;

    //my8080.mem[0x02] = 0x06;
    //my8080.mem[0x03] = 0x05;

    //my8080.mem[0x04] = 0x90;

   //test sub with carry
    my8080.mem[0x00] = 0x3e;
    my8080.mem[0x01] = 0xf0;

    my8080.mem[0x02] = 0x06;
    my8080.mem[0x03] = 0xd2;

    my8080.mem[0x04] = 0x80;

    my8080.mem[0x05] = 0x3e;
    my8080.mem[0x06] = 0x00;

    my8080.mem[0x07] = 0x98;

    //program cycles until it finds an opcode it cant deal with
    while (my8080.cycle() != -1) {
        //while loop
    }
}
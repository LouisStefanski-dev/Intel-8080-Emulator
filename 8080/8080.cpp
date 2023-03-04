#include <iostream>
#include <string>
#include "c8080.h"

//TODO: 
//      1. turn inx into a function that takes a 16 bit value
//      2. Implement all LXI instructions
//      3. Fix AC flag
//      4. fix 0x77 and similar mov instructions which mov a value into M
//      5. set carry flag 0x07
int main()
{
    c8080 my8080;
    std::string program = "3E19060AA076";
    //load program into memory
    my8080.loadProgram(0x0000, program);
    my8080.stepMode = false;
    //program cycles until it finds an opcode it cant deal with
    while (my8080.cycle() != -1) {
        //while loop
    }
}
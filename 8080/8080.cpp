#include <iostream>
#include <string>
#include "c8080.h"

int main()
{
    c8080 my8080;
    std::string program = "3EF00614803E009876";
    //load program into memory
    my8080.loadProgram(0x0000, program);
    my8080.stepMode = false;
    //program cycles until it finds an opcode it cant deal with
    while (my8080.cycle() != -1) {
        //while loop
    }
}
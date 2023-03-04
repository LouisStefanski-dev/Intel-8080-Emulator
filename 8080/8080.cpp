#include <iostream>
#include <string>
#include "c8080.h"

//TODO: 
//      2. Look into when carry flag is (actually) set
//      3. Fix AC flag
//      4. fix 0x77 and similar mov instructions which mov a value into M
int main()
{
    c8080 my8080;
    std::string program = "3E19060AA0AE317C0106F080B6070776";
    //load program into memory
    my8080.loadProgram(0x0000, program);
    my8080.stepMode = false;
    //program cycles until it finds an opcode it cant deal with
    while (my8080.cycle() != -1) {
        //while loop
    }
}
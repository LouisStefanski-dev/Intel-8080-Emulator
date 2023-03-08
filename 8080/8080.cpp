#include <iostream>
#include <string>
#include <chrono>
#include "c8080.h"
#include "DebuggerC8080.h"

#include "c8080commandLine.h"
#include "c8080ioHandler.h"

//Ways to improve performance:
//  1. Remove calls to pow and replace with constant values

//TODO: 
//      *Make switch statement look nicer
//      2. Look into when carry flag is (actually) set
//      3. Fix AC flag
//      4. fix 0x77 and similar mov instructions which mov a value into M
//      5. Technically and, or, and xor set the carry and ac flags to zero. Maybe implement setting of flags rather than
//          relying on them being cleared before
//      6. work on carry flag and ac flag
//      7. work on removing overloaded version of setCarryFlag(supports dad)
//      8. Currently using a hack around for when sp wraps from (sp - 1) for sp = 0, since 65535 is not a valid
//          memory address
//results in a carry flag when a number is subtracted from itself, maybe do a check for it with an if statement

#define showPerformance false

int main()
{
    c8080 my8080;
    DebuggerC8080 debugger;
    c8080ioHandler handler;

    handler.addDevice(new c8080commandLine(HEX), 0x00); //used for hex output
    handler.addDevice(new c8080commandLine(ASCII), 0x01); //used for string output


   // std::string program = "2123000E0ECD09007679FE00CA22007EFE61DA1D00FE7BD21D00D62077230DC30900C96865"; //capitalize
   // std::string program = "110E0021130006000E05CD1D007611223344550000000000000000000078B1C81A7713230B78B1C22000C9"; //memcpy
    //std::string program = "3E41D30076"; //output test
   // std::string program = "3E1EDB0047DB0080D30076"; //test i/o add function
   // std::string program = "DB004F79D3000DFE00CA0F00C3030076"; //test loop output
    std::string program = "1120000E161AD301130DCA1000C30500DB004F79D3000DFE00CA1F00C3130076456E746572206E756D626572206F66206C6F6F70733A20";
    //load program into memory
    my8080.loadProgram(0x0000, program);

    //debug options
    bool debugMode = false;
    bool stepMode = false;

    //program cycles until it finds an opcode it cant deal with or a hlt instruction is called
    auto start = std::chrono::high_resolution_clock::now();
    while (my8080.cycle() != -1) {
        if (debugMode) {
            debugger.debugCycle(my8080, stepMode);
        }
        if (my8080.out) { //read value from c8080 into i/o handler
            handler.handleIO(c8080ioHandler::WRITE, my8080.output >> 8, my8080.output);
            my8080.out = false; //disable output
        }
        if (my8080.in) { //read value from i/o handler into c8080
            my8080.A.data = handler.handleIO(c8080ioHandler::READ,  my8080.input >> 8);
            my8080.in = false; //disable input
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    //print final status of register and memory
    debugger.debugCycle(my8080, true);

    //statistics about performance
    if (showPerformance) {
        auto timeElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "Program took " << timeElapsed << "ns to run." << std::endl;
        std::cout << "Time Elapsed(ms): " << (timeElapsed / pow(10, 6)) << std::endl;
        std::cout << std::setprecision(12) << "Instructions Per Second: " << (1 / (timeElapsed / pow(10, 9))) * my8080.cycles << std::endl;
    }
}
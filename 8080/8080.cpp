#include <iostream>
#include <string>
#include <chrono>
#include "c8080.h"
#include "DebuggerC8080.h"

//Ways to improve performance:
//  1. Remove calls to pow and replace with constant values
//  
//
//


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
int main()
{
    c8080 my8080;
    DebuggerC8080 debugger;

    std::string program = "2123000E0ECD09007679FE00CA22007EFE61DA1D00FE7BD21D00D62077230DC30900C96865"; //capitalize
    //std::string program = "110E0021130006000E05CD1D007611223344550000000000000000000078B1C81A7713230B78B1C22000C9"; //memcpy
  
    //load program into memory
    my8080.loadProgram(0x0000, program);

    bool debugMode = true;
    bool stepMode = true;
    //program cycles until it finds an opcode it cant deal with
    auto start = std::chrono::high_resolution_clock::now();
    while (my8080.cycle() != -1) {
        //while loop
        if (debugMode) {
            debugger.debugCycle(my8080, stepMode);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    //print final status of register and memory
    debugger.debugCycle(my8080, true);

    //statistics about performance 
    auto timeElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Program took " << timeElapsed << "ns to run." << std::endl;
    std::cout << "Time Elapsed(ms): " << (timeElapsed / pow(10, 6)) << std::endl;
    std::cout << std::setprecision(12) << "Instructions Per Second: " << (1/(timeElapsed / pow(10, 9))) * my8080.cycles << std::endl;
}
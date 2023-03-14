#include "DebuggerC8080.h"

//Print out the state of all registers, sp, pc, and instruction
void DebuggerC8080::stateUpdate(c8080& cpu)
{
    std::cout << "----------------------------------------------------------------------------------------" << std::endl;
    std::cout <<
        "A: " << std::format("{:#x}", cpu.A.data) << " B: " << std::format("{:#x}", cpu.B.data) <<
        " C: " << std::format("{:#x}", cpu.C.data) << " D: " << std::format("{:#x}", cpu.D.data) << " E: " << std::format("{:#x}", cpu.E.data) <<
        " H: " << std::format("{:#x}", cpu.H.data) << " L: " << std::format("{:#x}", cpu.L.data)
        << std::endl;
    std::cout <<
        "FLAGS: S: " << std::format("{:#x}", cpu.getFlagStatus(7)) <<
        " Z: " << std::format("{:#x}", cpu.getFlagStatus(6)) <<
        " AC: " << std::format("{:#x}", cpu.getFlagStatus(4)) <<
        " P: " << std::format("{:#x}", cpu.getFlagStatus(2)) <<
        " C: " << std::format("{:#x}", cpu.getFlagStatus(0)) << std::endl;
    std::cout <<
        "Current Instruction: " << std::format("{:#x}", cpu.mem[cpu.pc]) << "   " <<
        "Current Stack Pointer: " << std::format("{:#x}", cpu.sp)
        << std::endl;
    std::cout << "Current Cycle: " << cpu.cycles << " Current PC: " << std::format("{:#x}", cpu.pc) << std::endl;
    std::cout << "----------------------------------------------------------------------------------------" << std::endl;
}

//Print out a 16 x 16 block of memory 
void DebuggerC8080::printMemory(c8080& cpu)
{
    std::cout << "Memory View   0x00-0xFF" << std::endl;

    //format border top
    for (int i = 0; i < 120; i++) {
        std::cout << "_";
    }
    std::cout << std::endl;

    //format top row(index)
    std::cout << " R/C|" << "  ";
    for (int i = 0; i < 16; i++) {
        std::cout << std::format("{:#04x}", i) << "   ";
    }
    std::cout << "|\n" << std::endl;

    //output memory data
    for (int i = 0; i < 16; i++) {
        std::cout << std::format("{:#04x}", i) << "|  ";
        for (int j = 0; j < 16; j++) {
            std::cout << std::format("{:#04x}", cpu.mem[(i * 16) + j]) << "   ";
        }
        std::cout << "|" << std::endl;
    }

    //format border bottom
    for (int i = 0; i < 120; i++) {
        std::cout << "_";
    }
    std::cout << std::endl;
}

//Takes the cpu it will be operating on and a boolean stepMode that determines if memory is printed
//for that particular cycle. It then calls cin.get() to pause the program.
void DebuggerC8080::debugCycle(c8080& cpu, bool stepMode) {
    stateUpdate(cpu);
    if (stepMode) {
        printMemory(cpu);
        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get(); //pause until input
    }
}

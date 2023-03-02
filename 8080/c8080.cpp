#include "c8080.h"

//Performs the following operations:
//  1. Grab opcode from mem[pc]
//  2. Switch over opcode to perform function
//      2.1. Fetch additional addresses from memory
//  3. Increment pc
//  4. Output status of all registers for debugging 
int c8080::cycle()
{
    uint8_t opcode = mem[pc];
    //switch through moves 0x40 - 0x4f
    switch (opcode) {
    case 0x40: //mov b,b
        B = B;
        break;
    case 0x41: //mov b, c
        B = C;
        break;
    case 0x42: //mov b, d
        B = D;
        break;
    case 0x43: //mov b, e
        B = E;
        break;
    case 0x44: //mov b, h
        B = H;
        break;
    case 0x45: //mov b, l
        B = L;
        break;
    case 0x46: //mov b, m(HL)
        B = ((H << 8) | L) ;
        break;
    case 0x47: //mov b, a
        B = A;
        break;
    case 0x48: //mov c, b
        C = B;
        break;
    case 0x49: //mov c,c
        C = C;
        break;
    case 0x4a: //mov c,d
        C = D;
        break;
    case 0x4b: //mov c, e
        C = E;
        break;
    case 0x4c: //mov c, h
        C = H;
        break;
    case 0x4d: //mov c, l
        C = L;
        break;
    case 0x4e: //mov c, m(HL)
        C = ((H << 8) | L);
        break;
    case 0x4f: //mov c , a
        C = A;
        break;
    default:
        return -1;
        break;
    }
    pc++;
    stateUpdate();
    return 0;
}

//move register into register
void c8080::mov(uint8_t* f, uint8_t* s)
{
    *f = *s;
    //increase cycle by one
}

//outputs the status of all registers 
void c8080::stateUpdate() {
    std::cout << "----------------------------------------------------------------------------------------" << std::endl;
    std::cout <<
        "A: " << std::format("{:#x}", A) << " B: " << std::format("{:#x}", B) <<
        " C: " << std::format("{:#x}", C) << " D: " << std::format("{:#x}", D) << " E: " << std::format("{:#x}", E) <<
        " H: " << std::format("{:#x}", H) << " L: " << std::format("{:#x}", L)
        << std::endl;
    std::cout << "FLAGS: " << std::format("{:#x}", FLAGS) << std::endl;
    std::cout <<
        "Current Instruction: " << std::format("{:#x}", mem[pc]) << "   " <<
        "Current Stack: " << std::format("{:#x}", mem[sp])
        << std::endl;
    std::cout << "----------------------------------------------------------------------------------------" << std::endl;
}

#include "c8080.h"

//Performs the following operations:
//  1. Grab opcode from mem[pc]
//  2. Switch over opcode to perform function
//      2.1. Fetch additional addresses from memory
//  3. Increment pc
//  4. Output status of all registers for debugging 
//NOTE: Each case must increment PC as needed.
int c8080::cycle()
{
    uint8_t opcode = mem[pc];
    switch (opcode) {
    //case 0x00:
    //   break;
    case 0x01: //LXI B, D16
        //loads byte 2[pc + 1] into C and byte 3[pc + 2] into B
        //Increments pc by 2
        C.data = mem[pc + 1];
        B.data = mem[pc + 2];
        pc += 2;
        break;
    case 0x02:
        break;
    case 0x03:
        break;
    case 0x04:
        break;
    case 0x05:
        break;
    case 0x06: //MVI B, D8
        mov(B, mem[pc + 1]);
        break;
    case 0x07:
        break;
    case 0x08:
        break;
    case 0x09:
        break;
    case 0x0a:
        break;
    case 0x0b:
        break;
    case 0x0c:
        break;
    case 0x0d:
        break;
    case 0x0e: //mvi c, D8
        mov(C, mem[pc + 1]);
        break;
    case 0x0f:
        break;

    //0x10 - 0x1f
    case 0x10:
        break;
    case 0x11:
        break;
    case 0x12:
        break;
    case 0x13:
        break;
    case 0x14:
        break;
    case 0x15:
        break;
    case 0x16: //MVI D, D8
        mov(D, mem[pc + 1]);
        break;
    case 0x17:
        break;
    case 0x18:
        break;
    case 0x19:
        break;
    case 0x1a:
        break;
    case 0x1b:
        break;
    case 0x1c:
        break;
    case 0x1d:
        break;
    case 0x1e: //mvi E, D8
        mov(E, mem[pc + 1]);
        break;
    case 0x1f:
        break;

    //0x20 - 0x2f
    case 0x20:
        break;
    case 0x21:
        break;
    case 0x22:
        break;
    case 0x23:
        break;
    case 0x24:
        break;
    case 0x25:
        break;
    case 0x26: //mvi H, D8
        mov(H, mem[pc + 1]);
        break;
    case 0x27:
        break;
    case 0x28:
        break;
    case 0x29:
        break;
    case 0x2a:
        break;
    case 0x2b:
        break;
    case 0x2c:
        break;
    case 0x2d:
        break;
    case 0x2e: //mvi L, D8
        mov(L, mem[pc + 1]);
        break;
    case 0x2f:
        break;

    //0x30 - 0x3f
    case 0x30:
        break;
    case 0x31:
        break;
    case 0x32:
        break;
    case 0x33:
        break;
    case 0x34:
        break;
    case 0x35:
        break;
    case 0x36: //mvi m, D8
        mem[getM()] = mem[pc + 1];
        pc += 2;
        break;
    case 0x37:
        break;
    case 0x38:
        break;
    case 0x39:
        break;
    case 0x3a:
        break;
    case 0x3b:
        break;
    case 0x3c:
        break;
    case 0x3d:
        break;
    case 0x3e: //mvi A, D8
        mov(A, mem[pc + 1]);
        break;
    case 0x3f:
        break;
    //switch through moves 0x40 - 0x4f
    case 0x40: //mov b,b
        mov(B, B);
        break;
    case 0x41: //mov b, c
        mov(B, C);
        break;
    case 0x42: //mov b, d
        mov(B, D);
        break;
    case 0x43: //mov b, e
        mov(B, E);
        break;
    case 0x44: //mov b, h
        mov(B, H);
        break;
    case 0x45: //mov b, l
        mov(B, L);
        break;
    case 0x46: //mov b, m(HL)
        B.data = mem[((H.data << 8) | L.data)];
        pc++;
        break;
    case 0x47: //mov b, a
        mov(B, A);
        break;
    case 0x48: //mov c, b
        mov(C, B);
        break;
    case 0x49: //mov c,c
        mov(C, C);
        break;
    case 0x4a: //mov c,d
        mov(C, D);
        break;
    case 0x4b: //mov c, e
        mov(C, E);
        break;
    case 0x4c: //mov c, h
        mov(C, H);
        break;
    case 0x4d: //mov c, l
        mov(C, L);
        break;
    case 0x4e: //mov c, m(HL)
        C.data = mem[((H.data << 8) | L.data)];
        pc++;
        break;
    case 0x4f: //mov c , a
        mov(C, A);
        break;

    //switches 0x50 - 0x5f
    case 0x50: //mov D,b
        mov(D, B);
        break;
    case 0x51: //mov D, c
        mov(D, C);
        break;
    case 0x52: //mov d, d
        mov(D, D);
        break;
    case 0x53: //mov d, e
        mov(D, E);
        break;
    case 0x54: //mov d, h
        mov(D, H);
        break;
    case 0x55: //mov d, l
        mov(D, L);
        break;
    case 0x56: //mov d, m(HL)
        D.data = mem[((H.data << 8) | L.data)];
        pc++;
        break;
    case 0x57: //mov d, a
        mov(D, A);
        break;
    case 0x58: //mov e, b
        mov(E, B);
        break;
    case 0x59: //mov e,c
        mov(E, C);
        break;
    case 0x5a: //mov e,d
        mov(E, D);
        break;
    case 0x5b: //mov e, e
        mov(E, E);
        break;
    case 0x5c: //mov e, h
        mov(E, H);
        break;
    case 0x5d: //mov e, l
        mov(E, L);
        break;
    case 0x5e: //mov e, m(HL)
        E.data = mem[((H.data << 8) | L.data)];
        pc++;
        break;
    case 0x5f: //mov e , a
        mov(E, A);
        break;

    //switches 0x60 - 0x6f
    case 0x60: //mov h,b
        mov(H, B);
        break;
    case 0x61: //mov h, c
        mov(H, C);
        break;
    case 0x62: //mov h, d
        mov(H, D);
        break;
    case 0x63: //mov h, e
        mov(H, E);
        break;
    case 0x64: //mov h, h
        mov(H, H);
        break;
    case 0x65: //mov h, l
        mov(H, L);
        break;
    case 0x66: //mov h, m(HL)
        H.data = mem[((H.data << 8) | L.data)];
        pc++;
        break;
    case 0x67: //mov h, a
        mov(H, A);
        break;
    case 0x68: //mov l, b
        mov(L, B);
        break;
    case 0x69: //mov l,c
        mov(L, C);
        break;
    case 0x6a: //mov l,d
        mov(L, D);
        break;
    case 0x6b: //mov l, e
        mov(L, E);
        break;
    case 0x6c: //mov l, h
        mov(L, H);
        break;
    case 0x6d: //mov l, l
        mov(L, L);
        break;
    case 0x6e: //mov l, m(HL)
        L.data = mem[((H.data << 8) | L.data)];
        pc++;
        break;
    case 0x6f: //mov l , a
        mov(L, A);
        break;

    //switches 0x70 - 0x7f
    //TODO:  Look into the logic used for 0x70-0x77 as I am assuming the 8 bit registers can only fit the L(low) register 
    //M register is the same as (H << 8) | L 
    case 0x70: //mov M,b
        mov(L, B);
        break;
    case 0x71: //mov M, c
        mov(L, C);
        break;
    case 0x72: //mov M, d
        mov(L, D);
        break;
    case 0x73: //mov M, e
        mov(L, E);
        break;
    case 0x74: //mov M, h
        mov(L, H);
        break;
    case 0x75: //mov M, l
        mov(L, L);
        break;
    case 0x76: //HLT
        //TODO: Code Hlt functionality 
        break;
    case 0x77: //mov M, a
        mov(L, A);
        break;
    case 0x78: //mov a, b
        mov(A, B);
        break;
    case 0x79: //mov a,c
        mov(A, C);
        break;
    case 0x7a: //mov a,d
        mov(A, D);
        break;
    case 0x7b: //mov a, e
        mov(A, E);
        break;
    case 0x7c: //mov a, h
        mov(A, H);
        break;
    case 0x7d: //mov a, l
        mov(A, L);
        break;
    case 0x7e: //mov a, m(HL)
        A.data = mem[((H.data << 8) | L.data)];
        pc++;
        break;
    case 0x7f: //mov a , a
        mov(A, A);
        break;

    //0x80 - 0x8f
    case 0x80:
        add(A, B);
        break;
    case 0x81:
        add(A, C);
        break;
    case 0x82:
        add(A, D);
        break;
    case 0x83:
        add(A, E);
        break;
    case 0x84:
        add(A, H);
        break;
    case 0x85:
        add(A, L);
        break;
    case 0x86: //TODO: test this function
        add(A, mem[getM()]);
        break;
    case 0x87:
        add(A, A);
        break;
    case 0x88:
        adc(A, B);
        break;
    case 0x89:
        adc(A, C);
        break;
    case 0x8a:
        adc(A, D);
        break;
    case 0x8b:
        adc(A, E);
        break;
    case 0x8c:
        adc(A, H);
        break;
    case 0x8d:
        adc(A, L);
        break;
    case 0x8e://TODO: test this one functionality 
        adc(A, mem[getM()]);
        break;
    case 0x8f:
        adc(A, A);
        break;

    //0x90 - 0x9f
    case 0x90:
        sub(A, B);
        break;
    case 0x91:
        sub(A, C);
        break;
    case 0x92:
        sub(A, D);
        break;
    case 0x93:
        sub(A, E);
        break;
    case 0x94:
        sub(A, H);
        break;
    case 0x95:
        sub(A, L);
        break;
    case 0x96: //TODO: look into why this set a carry in other emulator but not mine
        sub(A, mem[getM()]);
        break;
    case 0x97:
        sub(A, A);
        break;
    case 0x98:
        sbb(A, B);
        break;
    case 0x99:
        sbb(A, C);
        break;
    case 0x9a:
        sbb(A, D);
        break;
    case 0x9b:
        sbb(A, E);
        break;
    case 0x9c:
        sbb(A, H);
        break;
    case 0x9d:
        sbb(A, L);
        break;
    case 0x9e: //TODO: look into why this set a carry in other emulator but not mine
        sbb(A, mem[getM()]);
        break;
    case 0x9f:
        sbb(A, A);
        break;
    default:
        return -1;
        break;
    }
    stateUpdate();
    cycles++;
    return 0;
}

//move register into register
void c8080::mov(reg& f, reg& s)
{
    f.data = s.data;
    pc++;
    //increase cycle by one
}

//move immediate into register
//uses [pc + 1], then increments pc by 2
void c8080::mov(reg& f, uint8_t s)
{
    f.data = s;
    pc += 2;
    //TODO: increase cycle by one
}

//Adds two registers together, setting appropriate flags 
//TODO: check on if ac flag is correct
void c8080::add(reg& f, reg& s)
{
    //Method to set bit: or the flags register with 2^i where i is the bits position(from 0 to 7)
    FLAGS.data = 0x00;  //clear flags

    setCarryFlag(f.data, s.data);
    setACFlag(f.data, s.data);

    f.data += s.data; //add numbers

    setSignFlag(f.data);
    setZeroFlag(f.data);
    setParityFlag(f.data);
    pc++;
}

void c8080::add(reg& f, uint8_t s)
{
    //Method to set bit: or the flags register with 2^i where i is the bits position(from 0 to 7)
    FLAGS.data = 0x00;  //clear flags

    setCarryFlag(f.data, s);
    setACFlag(f.data, s);

    f.data += s; //add numbers

    setSignFlag(f.data);
    setZeroFlag(f.data);
    setParityFlag(f.data);
    pc++;
}

void c8080::adc(reg& f, reg& s)
{
    //Method to set bit: or the flags register with 2^i where i is the bits position(from 0 to 7)
    uint8_t carryData = getFlagStatus(7); //store carry data

    FLAGS.data = 0x00; //clear flags

    setCarryFlag(f.data, s.data, carryData);
    setACFlag(f.data, s.data, carryData);

    f.data += s.data + carryData; //add numbers

    setSignFlag(f.data);
    setZeroFlag(f.data);
    setParityFlag(f.data);
    pc++;
}

void c8080::adc(reg& f, uint8_t s)
{
    //Method to set bit: or the flags register with 2^i where i is the bits position(from 0 to 7)
    uint8_t carryData = getFlagStatus(7); //store carry data

    FLAGS.data = 0x00; //clear flags

    setCarryFlag(f.data, s, carryData);
    setACFlag(f.data, s, carryData);

    f.data += s + carryData; //add numbers

    setSignFlag(f.data);
    setZeroFlag(f.data);
    setParityFlag(f.data);
    pc++;
}

void c8080::sub(reg& f, reg& s)
{
    //Method to set bit: or the flags register with 2^i where i is the bits position(from 0 to 7)
    FLAGS.data = 0x00;  //clear flags

    setCarryFlag(f.data, s.data, 0, SUB);
    setACFlag(f.data, s.data, 0, SUB);

    f.data -= s.data; //add numbers

    setSignFlag(f.data);
    setZeroFlag(f.data);
    setParityFlag(f.data);
    pc++;
}

void c8080::sub(reg& f, uint8_t s)
{
    //Method to set bit: or the flags register with 2^i where i is the bits position(from 0 to 7)
    FLAGS.data = 0x00;  //clear flags

    setCarryFlag(f.data, s, 0, SUB);
    setACFlag(f.data, s, 0, SUB);

    f.data -= s; //add numbers

    setSignFlag(f.data);
    setZeroFlag(f.data);
    setParityFlag(f.data);
    pc++;
}

void c8080::sbb(reg& f, reg& s)
{
    //Method to set bit: or the flags register with 2^i where i is the bits position(from 0 to 7)
    uint8_t carryData = getFlagStatus(7); //store carry data

    FLAGS.data = 0x00; //clear flags 

    setCarryFlag(f.data, s.data, carryData, SUB);
    setACFlag(f.data, s.data, carryData, SUB);

    f.data -= (s.data + carryData); //add numbers

    setSignFlag(f.data);
    setZeroFlag(f.data);
    setParityFlag(f.data);
    pc++;
}

void c8080::sbb(reg& f, uint8_t s)
{
    //Method to set bit: or the flags register with 2^i where i is the bits position(from 0 to 7)
    uint8_t carryData = getFlagStatus(7); //store carry data

    FLAGS.data = 0x00; //clear flags 

    setCarryFlag(f.data, s, carryData, SUB);
    setACFlag(f.data, s, carryData, SUB);

    f.data -= (s + carryData); //add numbers

    setSignFlag(f.data);
    setZeroFlag(f.data);
    setParityFlag(f.data);
    pc++;
}

//returns the value of a flag(denoted by i)
//Below are the values i for certain flags
//  0. sign
//  1. zero
//  3. AC
//  5. Parity
//  7. Carry
int c8080::getFlagStatus(int i)
{
    return (FLAGS.data & (0x00 | (uint8_t)pow(2, i))) >> i;
}

//returns 1 for even parity, 0 for odd parity
int c8080::calculateParity(uint8_t f)
{
    int onBits = 0;
    for (int i = 0; i < 8; i++) {
        if ((f >> i) & 0x01) {
            onBits++;
        }
    }
    return (onBits % 2) == 0 ? 1 : 0;
}

//takes a uint8_t and sets appropiate bit in flag if it is zero
void c8080::setZeroFlag(uint8_t f)
{
    if (f == 0) {
        FLAGS.data |= (uint8_t)pow(2, 1);
    }
}

//takes two uint8_t variables, f and s, and sets appropiate bit in flag if their is a carry from low nibble to high nibble in the result
//of their sum
//The op argument is used to signify if this function is checking for AC flag with subtraction or addition
void c8080::setACFlag(uint8_t f, uint8_t s, uint8_t c, operation op)
{
    if (op == ADD) {
        if (((f - s - c) > pow(2, 4) - 1) && (f < pow(2, 4) - 1)) {
            FLAGS.data |= (uint8_t)pow(2, 3);
        }
        return;
    }
    if (((f - s - c) > pow(2, 4) - 1) && (f < pow(2, 4) - 1)) {
        FLAGS.data |= (uint8_t)pow(2, 3);
    }
}

//takes a uint8_t and sets appropiate bit in flag if the first bit is a sign bit
void c8080::setSignFlag(uint8_t f)
{
    if (f >> 7) {
        FLAGS.data |= (uint8_t)pow(2, 0);
    }
}

//takes two uint8_t, f and s, and sets appropriate bit in flag if their sum produces a carry
//The op argument is used to signify if this function is checking for AC flag with subtraction or addition
void c8080::setCarryFlag(uint8_t f, uint8_t s, uint8_t c, operation op)
{
    if (op == ADD) {
        if (f + s + c > UINT8_MAX) {
            FLAGS.data |= (uint8_t)pow(2, 7);
        }
        return;
    }
    if (f - s - c > UINT8_MAX) {
        FLAGS.data |= (uint8_t)pow(2, 7);
    }
}

//takes a uint8_t and sets appropriate bit in flag to 1 if the parity of f is even, 0 otherwise
void c8080::setParityFlag(uint8_t f)
{
    if (calculateParity(f)) {
        FLAGS.data |= (uint8_t)pow(2, 5);
    }
}

//returns the value given by H << 8 | L 
uint16_t c8080::getM()
{
    return ((H.data << 8) | L.data);
}


//outputs the status of all registers 
void c8080::stateUpdate() {
    std::cout << "----------------------------------------------------------------------------------------" << std::endl;
    std::cout <<
        "A: " << std::format("{:#x}", A.data) << " B: " << std::format("{:#x}", B.data) <<
        " C: " << std::format("{:#x}", C.data) << " D: " << std::format("{:#x}", D.data) << " E: " << std::format("{:#x}", E.data) <<
        " H: " << std::format("{:#x}", H.data) << " L: " << std::format("{:#x}", L.data)
        << std::endl;
    std::cout << 
                "FLAGS: S: " << std::format("{:#x}", getFlagStatus(0)) <<
                " Z: " << std::format("{:#x}", getFlagStatus(1)) <<
                " AC: " << std::format("{:#x}", getFlagStatus(3)) << 
                " P: " << std::format("{:#x}", getFlagStatus(5)) <<
                " C: " << std::format("{:#x}", getFlagStatus(7)) << std::endl;
    std::cout <<
        "Current Instruction: " << std::format("{:#x}", mem[pc]) << "   " <<
        "Current Stack: " << std::format("{:#x}", mem[sp])
        << std::endl;
    std::cout << "Current Cycle: " << cycles  << " Current PC: " << std::format("{:#x}", pc) << std::endl;
    std::cout << "----------------------------------------------------------------------------------------" << std::endl;
}

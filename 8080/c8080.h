#pragma once
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <format>

//		FLAGS register order
// -------------------------------+
//	7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
//	S | Z | 0 | A | 0 | P | 1 | C |
//--------------------------------+

//NOTE on flags register: The current get[flag] functions assume the flags register is reset using
//	resetFlags() before being called. As such when the function would normally clear a flag bit
//	it instead ignores it and returns without changing any flag bits.

enum operation{ ADD, SUB, AND, OR, XOR};

struct reg {
	uint8_t data;
};

//For this implementation of the 8080 the following is assumed to be true:
//	1. Program memory begins at 0x00
//	2. The stack pointer (can) be placed in program memory, to do this is a fatal mistake. The stack pointer (should) be placed after program
//		memory. This particular implementation makes use of a varialbe, programEnd, which denotes the value in memory that contains the last
//		program instruction. As such, a logical statck pointer placement is anywhere in the range [programEnd + 1, 0xFF]
class c8080
{
public:
	//Registers
	reg A, B, C, D, E, H, L, FLAGS;

	//Memory
	//uint8_t mem[0xFFFF] = { 0x0000 }; //64KB of memory
	uint8_t* mem = (uint8_t*)malloc(0xFFFF);
	//Stack pointer
	uint16_t sp;

	//program counter
	uint16_t pc;

	//program end tells the emulator where the last program instruction is, this is set by loadProgram
	uint16_t programEnd; 

	//cycle counter
	uint16_t cycles = 0x00;

	//i/o devices
	uint8_t ioDevices[0xFF] = { 0x00 };

	//if stepMode is true the program will allow the user to step through it instruction by instruction
	//if false the program runs without intervention unless a hlt instruction is reached
	bool stepMode = false;

	c8080() {
		sp = 0x00;
		pc = 0x00;
		A.data = 0x00;
		B.data = 0x00;
		C.data = 0x00;
		D.data = 0x00;
		E.data = 0x00;
		H.data = 0x00;
		L.data = 0x00;
		FLAGS.data = 0x00;
	}

	int cycle();

	void mov(reg& f, reg& s);
	void mov(reg& f, uint8_t s);

	void add(reg& f, reg& s);
	void add(reg& f, uint8_t s);

	void adc(reg& f, reg& s);
	void adc(reg& f, uint8_t s);

	void sub(reg& f, reg& s);
	void sub(reg& f, uint8_t s);

	void sbb(reg& f, reg& s);
	void sbb(reg& f, uint8_t s);

	void ana(reg& f, reg& s);
	void ana(reg& f, uint8_t s);

	void xra(reg& f, reg& s);
	void xra(reg& f, uint8_t s);

	void ora(reg& f, reg& s);
	void ora(reg& f, uint8_t s);

	void inr(reg& f);
	void dcr(reg& f);

	void ret();
	void jmp();
	void call();

	void nop();

	int getFlagStatus(int i);
	int calculateParity(uint8_t f);

	void loadProgram(uint16_t startAddr, std::string program);

	//flag set functions
	//All flags that are affected by carry support the inclusion of a carry bit by the uint8_t value c
	void setZeroFlag(uint8_t f);
	void setACFlag(uint8_t f, uint8_t s, uint8_t c = 0, operation op = ADD);
	void setSignFlag(uint8_t f);
	void setCarryFlag(uint8_t f, uint8_t s, uint8_t c = 0, operation op = ADD);
	void setParityFlag(uint8_t f);

	void resetFlags();

	uint16_t getM();

	//prints out all registers and current instruction
	void stateUpdate();
};


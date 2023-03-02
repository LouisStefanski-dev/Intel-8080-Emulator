#pragma once
#include <stdint.h>
#include <iostream>
#include <format>

struct reg {
	uint8_t data;
};

class c8080
{
public:
	//Registers
	reg A, B, C, D, E, H, L, FLAGS;

	//Memory
	uint8_t mem[0xFFFF] = { 0x0000 }; //64KB of memory

	//Stack pointer
	uint16_t sp;

	//program counter
	uint16_t pc;

	//cycle counter
	uint16_t cycles = 0x00;

	//i/o devices
	uint8_t inputDevices[0xFF] = { 0x00 };
	uint8_t outputDevices[0xFF] = { 0x00 };

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

	//prints out all registers and current instruction
	void stateUpdate();
};


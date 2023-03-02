#pragma once
#include <stdint.h>
#include <iostream>
#include <format>


class c8080
{
public:
	//Registers
	uint8_t A = 0x00; //Accumulator 
	uint8_t B = 0x00;
	uint8_t C = 0x00;
	uint8_t D = 0x00;
	uint8_t E = 0x00;
	uint8_t H = 0x00;
	uint8_t L = 0x00;
	uint8_t FLAGS = 0x00;

	//Memory
	uint8_t mem[0xFFFF] = { 0x0000 }; //64KB of memory

	//Stack pointer
	uint16_t sp;

	//program counter
	uint16_t pc;

	//instruction pointer
	uint16_t ip;

	//i/o devices
	uint8_t inputDevices[0xFF] = { 0x00 };
	uint8_t outputDevices[0xFF] = { 0x00 };

	c8080() {
		sp = 0x00;
		pc = 0x00;
		ip = 0x00;
	}

	int cycle();
	void mov(uint8_t* f, uint8_t* s);

	//prints out all registers and current instruction
	void stateUpdate();
};


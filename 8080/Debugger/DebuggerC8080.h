#pragma once
#include "..\CPU\c8080.h"
#include <iostream>
#include <format>

//A debugger to be used with the c8080 emulator. 
//This debugger allows the user to print state(registers,pc, sp, current instruction),
//memory, or both with debugCycle.

class DebuggerC8080
{
public:
	static void stateUpdate(c8080& cpu);
	static void printMemory(c8080& cpu);
	static void debugCycle(c8080& cpu, bool stepMode);
};


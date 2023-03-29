#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "CPU\c8080.h"
#include "Debugger\DebuggerC8080.h"

#include "IO\c8080commandLine.h"
#include "IO\c8080ioHandler.h"


#define OLC_PGE_APPLICATION
#include "Include\olcPixelGameEngine.h"

// PGEX Require the presence of olc::PixelGameEngine
#define OLC_PGEX_QUICKGUI
#include "Include\olcPGEX_QuickGUI.h"


//Ways to improve performance:
//  1. Remove calls to pow and replace with constant values

//TODO: 
//      *Make switch statement look nicer
//      2. Look into when carry flag is (actually) set
//      3. Fix AC flag
//      8. Currently using a hack around for when sp wraps from (sp - 1) for sp = 0, since 65535 is not a valid
//          memory address
//results in a carry flag when a number is subtracted from itself, maybe do a check for it with an if statement

#define showPerformance false

c8080 my8080;
std::string program = "C30D001AD30113FE00C8C30300112900CD0300DB004F114100CD030079D3000DFE00CA2800C31C0076456E746572206E756D626572206F66206C6F6F70733A2000546865206F75747075742069733A2000";

bool startCPU = false;
bool debugMode = false;
bool stepMode = false;

struct memoryField {
	olc::vu2d pos;
	olc::vu2d size;
	std::vector<olc::QuickGUI::Label*> memElements;
};

//this is what runs the processor each cycle
void processorCycle() {
	while (true) {
		if (debugMode) {
			//debugger->debugCycle(my8080, stepMode);
		}
		if (!my8080.in && !my8080.out && startCPU) {
			my8080.cycle();
			(my8080.mem[my8080.pc] == 0x76) ? (startCPU = false) : (startCPU = startCPU); //check for hlt
		}
	}
}

class olcDemo_QuickGUI : public olc::PixelGameEngine
{
public:
	olcDemo_QuickGUI()
	{
		sAppName = "c8080 Emulator";
	}

protected:
	//c8080 my8080;
	DebuggerC8080* debugger = nullptr;
	c8080ioHandler* chandler;
	bool showMemory = false;

	olc::QuickGUI::Manager guiManager;
	olc::QuickGUI::Manager showMemManager;

	olc::QuickGUI::TextBox* gui = nullptr;
	olc::QuickGUI::TextBox* flagsBox = nullptr;
	olc::QuickGUI::TextBox* currentStateBox = nullptr;

	olc::QuickGUI::Label* registerBoxLabel = nullptr; //holds registers A-L
	olc::QuickGUI::Label* flagsBoxLabel = nullptr;
	olc::QuickGUI::Label* currentStateBoxLabel = nullptr;

	olc::QuickGUI::Button* runButton = nullptr;
	olc::QuickGUI::Button* stopButton = nullptr;
	olc::QuickGUI::Button* resetButton = nullptr;
	olc::QuickGUI::Button* showMemoryButton = nullptr;

	//command line
	std::vector<std::string> commandLine; //holds the items written to the command line
	olc::QuickGUI::ListBox* commandLineListBox = nullptr;

	olc::QuickGUI::TextBox* commandPromptEntry = nullptr;
	olc::QuickGUI::Button* commandPromptEnterButton = nullptr;

	//memory view
	memoryField memoryF;

	std::string output = "";
public:
	bool OnUserCreate() override
	{
		//create c8080
		chandler = new c8080ioHandler;
		debugger = new DebuggerC8080;

		gui = new olc::QuickGUI::TextBox(guiManager, 
			"A: \nB: \nC: \nD: \nE: \nH: \nL:",
			{ 600.0f, 45.0f }, { 160.0f, 80.0f });
		flagsBox = new olc::QuickGUI::TextBox(guiManager, 
			"S: \nZ: \nAC: \nP: \nC: \n",
			{ 600.0f, 170.0f }, { 160.0f, 70.0f });

		currentStateBox = new olc::QuickGUI::TextBox(guiManager, "Current Instruction: \nStack Pointer: ", { 600.0f, 285.0f }, { 160.0f, 30.0f });


		registerBoxLabel = new olc::QuickGUI::Label(guiManager, "Registers", { 640.0f, 25.0f }, { 50.0f, 23.0f });
		flagsBoxLabel = new olc::QuickGUI::Label(guiManager, "Flags", { 640.0f, 150.0f }, { 50.0f, 23.0f });
		currentStateBoxLabel = new olc::QuickGUI::Label(guiManager, "State", { 640.0f, 265.0f }, { 50.0f, 23.0f });

		runButton = new olc::QuickGUI::Button(guiManager, "Run", { 640.0f, 320.0f }, { 80.0f, 40.0f });
		stopButton = new olc::QuickGUI::Button(guiManager, "Stop", { 640.0f, 360.0f }, { 80.0f, 40.0f });
		resetButton = new olc::QuickGUI::Button(guiManager, "Reset", { 640.0f, 400.0f }, { 80.0f, 40.0f });

		showMemoryButton = new olc::QuickGUI::Button(guiManager, "Show Memory", { 640.0f, 450.0f }, { 80.0f, 40.0f });

		commandLineListBox = new olc::QuickGUI::ListBox(guiManager, commandLine, { 25.0f, 25.0f }, { 550.0f, 500.0f }, true);

		commandPromptEntry = new olc::QuickGUI::TextBox(guiManager, "", { 40.0f, 525.0f }, { 475.0f, 25.0f });
		commandPromptEnterButton = new olc::QuickGUI::Button(guiManager, "->", { 515.0f, 525.0f }, { 25.0f, 25.0f });

		initMemElements(16 * 16);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		guiManager.Update(this);
		showMemManager.Update(this);

		//c8080 i/o
		if (my8080.out) {
			switch (my8080.output >> 8) {
			case 0x01: //ASCII
			{
				if (my8080.A.data == 0x00) {
					commandLine.push_back(output);
					output = "";
				}
				else {
					std::stringstream ss;
					ss << my8080.A.data;
					output += ss.str();
				}
				my8080.out = false;
				break;
			}
			case 0x00: //HEX
			{
				std::string s = ": " + std::format("{:#x}", my8080.A.data);
				commandLine.push_back(s);
				my8080.out = false;
				break;
			}
			}
		}

		//show memory
		if (showMemory) {
			getMemoryText();
		}

		//buttons
		if (runButton->bPressed) {
			//run the script
			my8080.loadProgram(0x00, program);
			startCPU = true;
		}

		if (stopButton->bPressed)
			startCPU = false;

		if (resetButton->bPressed)
			my8080.reset();

		if (showMemoryButton->bPressed) {
			if (showMemory) {
				showMemory = false;
			}
			else {
				showMemory = true;
			}
		}

		if (commandPromptEnterButton->bPressed) {
			if (my8080.in) {
				switch (my8080.input >> 8) {
					case 0x01: //ASCII
					{
						std::string s = commandPromptEntry->sText;
						uint16_t val = std::stoi(s);
						my8080.A.data = val;
						my8080.in = false;
						break;
					}
					case 0x00: //HEX
					{
						std::string s = commandPromptEntry->sText;
						uint16_t val = std::stoi(s, 0, 16);
						my8080.A.data = val;
						my8080.in = false;
						break;
					}
					default:
						break;
				}
			}
			commandLine.push_back("$ " + commandPromptEntry->sText);
			commandPromptEntry->sText = "";
		}

		//update register views
		gui->sText = std::format("A: {:#x}\nB: {:#x}\nC: {:#x}\nD: {:#x}\nE: {:#x}\nH: {:#x}\n L: {:#x}",
					my8080.A.data, my8080.B.data, my8080.C.data, my8080.D.data, my8080.E.data, my8080.L.data, my8080.H.data);
		flagsBox->sText = std::format("S: {:#x}\nZ: {:#x}\nAC: {:#x}\nP: {:#x}\nC: {:#x}",
					my8080.getFlagStatus(7), my8080.getFlagStatus(6), my8080.getFlagStatus(4), my8080.getFlagStatus(2), my8080.getFlagStatus(0));
		currentStateBox->sText = std::format("Curr. Instruction: {:#x}\nPC: {:#x}", my8080.mem[my8080.pc], my8080.pc);

		//Drawing area
		Clear(olc::DARK_GREY);
		guiManager.Draw(this);
		if (showMemory) {
			olc::PixelGameEngine::FillRectDecal(memoryF.pos, memoryF.size, olc::DARK_CYAN);
			showMemManager.Draw(this);
		}
		return true;
	}


	//experimental

	//call before getMemoryText to init the memElements vector
	void initMemElements(int size) {
		for (int i = 0; i < size; i++) {
			memoryF.memElements.push_back(new olc::QuickGUI::Label(showMemManager, "", { 0.0f, 0.0f }, { 0.0f, 0.0f }));
		}
	}

	void getMemoryText() {
		int index = 0;
		int numberOfElements = 16;

		olc::vu2d size = { 35, 35 };
		olc::vu2d pos = { 25, 25 };
		olc::vu2d rectSize = { numberOfElements * size.x, numberOfElements * size.y };
		memoryF.pos = pos;
		memoryF.size = rectSize;

		olc::vu2d elemPos = { 0, 0 };
		std::string s = "";
		for (int i = 0; i < numberOfElements; i++) {
			for (int j = 0; j < numberOfElements; j++) {
				elemPos.x = pos.x + (size.x * j);
				elemPos.y = pos.y + (size.y * i);
				s = std::format("{:#04x}", my8080.mem[index]);

				memoryF.memElements.at(index)->sText = s;
				memoryF.memElements.at(index)->vPos = elemPos;
				memoryF.memElements.at(index)->vSize = size;
				index++;
			}
		}
		int x = 5;
	} //end getMemoryText

};

//fix mouse in gui for the listbox 

int main()
{
	olcDemo_QuickGUI  c8080viewWindow;
	bool windowCreated = c8080viewWindow.Construct(800, 600, 1, 1);
	std::thread t1(&processorCycle);
	c8080viewWindow.Start();
}
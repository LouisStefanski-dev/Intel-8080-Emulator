#pragma once
#include "c8080ioDevice.h"
#include <iostream>
#include <format>

/// <summary>
/// This class is meant to represent a simple command line for use in the c8080 
/// This commandLine supports reading of values from cin.get and outputting via std::cout(ASCII)
/// 
/// + onWrite takes a value byte by byte. I.e. only one char at a time, or one number at a time
/// + Currently onRead supports inputs of only one byte
/// </summary>

enum mode { HEX, ASCII, DEC };

class c8080commandLine :
    public c8080ioDevice
{
private:
    uint32_t storageValue = 0x00; //stores value to be read/written
    mode ioMode = HEX;

public:
    c8080commandLine(mode ioMode = HEX) { this->ioMode = ioMode; };

    uint8_t onRead() override { //automatically takes hex input, any values over 8 bits will be truncated
        std::cout << "$ ";
        switch (ioMode) {
            case HEX:
                std::cin >> std::hex >> storageValue;
                break;
            case ASCII:
                std::cin >> storageValue;
                break;
            default:
                std::cout << "Invalid input mode..." << std::endl;
                break;
        }
        return storageValue;
    }

    void onWrite(uint8_t val) override { //outputs val formatted in hex
        this->storageValue = val;
        switch (ioMode) {
            case HEX:
                std::cout << ": " << std::format("{:#x}", val) << std::endl;
                break;
            case ASCII: //ASCII mode does not put in a space or line-end it is the programmers responsiblity to do it in
                        //their code
                std::cout << val;
                break;
            default:
                std::cout << "Invalid output mode..." << std::endl;
        }
    }
};


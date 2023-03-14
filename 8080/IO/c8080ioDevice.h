#pragma once
#include <cstdint>
//this class is the abstract class for i/o devices. All emulated i/o devices will inherite this class
class c8080ioDevice
{
public:
	virtual uint8_t onRead() { return 0x00; };
	virtual void onWrite(uint8_t val) {};
	c8080ioDevice() {};
};


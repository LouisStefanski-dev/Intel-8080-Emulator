#pragma once
#include <unordered_map>
#include <cstdint>

#include "c8080commandLine.h"
#include "c8080ioDevice.h"

//TODO: change vector to map

class c8080ioHandler
{
	std::unordered_map<uint8_t, c8080ioDevice*> ioDevices;
public:
	enum ioTypes { READ, WRITE };

	uint8_t addDevice(c8080ioDevice* device, uint8_t deviceID);

	uint8_t handleIO(ioTypes type, uint8_t deviceID, uint8_t val = 0x00);
};


#include "c8080ioHandler.h"

uint8_t c8080ioHandler::addDevice(c8080ioDevice* device, uint8_t deviceID)
{
	ioDevices.insert(std::make_pair(deviceID, device));
	return (ioDevices.size() - 1);
}

uint8_t c8080ioHandler::handleIO(ioTypes type, uint8_t deviceID, uint8_t val)
{
	switch (type) {
		case READ:
			return ioDevices[deviceID]->onRead();
			break;
		case WRITE:
			ioDevices[deviceID]->onWrite(val);
			break;
		default:
			std::cout << "handleIO error..." << std::endl;
			break;
	}
	return 0x00;
}

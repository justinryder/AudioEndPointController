// EndPointController.cpp : Defines the entry point for the console application.
//

#include "SoundDeviceController.h"

// EndPointController.exe [NewDefaultDeviceID]
int _tmain(int argc, LPCWSTR argv[])
{
	SoundDeviceController* pSoundDeviceController = new SoundDeviceController();
	//std::vector<SoundDevice*> devices = pSoundDeviceController->getAllDevices();
	std::vector<SoundDevice*> devices = pSoundDeviceController->getActiveDevices();
	//std::vector<SoundDevice*> devices = pSoundDeviceController->getDisabledDevices();
	//std::vector<SoundDevice*> devices = pSoundDeviceController->getNotPresentDevices();
	//std::vector<SoundDevice*> devices = pSoundDeviceController->getUnpluggedDevices();
	pSoundDeviceController->printSoundDevices();
	system("pause");
	devices[1]->setAsDefaultPlaybackDevice();
	pSoundDeviceController->printSoundDevices();
	system("pause");
	devices[2]->setAsDefaultPlaybackDevice();
	pSoundDeviceController->printSoundDevices();
	system("pause");
	return 0;
}
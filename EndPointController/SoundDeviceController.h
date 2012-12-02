

#pragma once

#include <vector>
#include "SoundDevice.h"

class SoundDevice;

class SoundDeviceController
{
public:
	SoundDeviceController();
	~SoundDeviceController();

	// Creates and returns a list of new SoundDevices
	// This destroys the old list first
	std::vector<SoundDevice*> createSoundDevices(int deviceStateFilter);
	// Destroys the SoundDevice list
	void destroySoundDevices();

	inline std::vector<SoundDevice*> createActiveDevices() { return createSoundDevices(DEVICE_STATE_ACTIVE); }
	inline std::vector<SoundDevice*> createDisabledDevices() { return createSoundDevices(DEVICE_STATE_DISABLED); }
	inline std::vector<SoundDevice*> createNotPresentDevices() { return createSoundDevices(DEVICE_STATE_NOTPRESENT); }
	inline std::vector<SoundDevice*> createUnpluggedDevices() { return createSoundDevices(DEVICE_STATE_UNPLUGGED); }
	inline std::vector<SoundDevice*> createAllDevices() { return createSoundDevices(DEVICE_STATEMASK_ALL); }

	inline std::vector<SoundDevice*> getDeviceList() { return devices; }
	inline int getDeviceCount() { return (int)devices.size(); }

	inline SoundDevice* getDefaultDevice() { return pDefaultSoundDevice; }

	HRESULT setDefaultSoundDevice(SoundDevice* pDevice);
	HRESULT setDefaultSoundDevice(int i);

	void printDevice(SoundDevice* pDevice);
	void printDevice(int i);
	void printSoundDevices();

private:
	std::vector<SoundDevice*> devices;
	SoundDevice* pDefaultSoundDevice;
};


#pragma once

#include <vector>
#include "SoundDevice.h"

class SoundDevice;

class SoundDeviceController
{
public:
	SoundDeviceController();
	~SoundDeviceController();

	void printSoundDevices();
	void printDevice(SoundDevice* pDevice);
	HRESULT setDefaultSoundDevice(SoundDevice* pDevice);

	inline std::vector<SoundDevice*> getActiveDevices() { return getSoundDevices(DEVICE_STATE_ACTIVE); }
	inline std::vector<SoundDevice*> getDisabledDevices() { return getSoundDevices(DEVICE_STATE_DISABLED); }
	inline std::vector<SoundDevice*> getNotPresentDevices() { return getSoundDevices(DEVICE_STATE_NOTPRESENT); }
	inline std::vector<SoundDevice*> getUnpluggedDevices() { return getSoundDevices(DEVICE_STATE_UNPLUGGED); }
	inline std::vector<SoundDevice*> getAllDevices() { return getSoundDevices(DEVICE_STATEMASK_ALL); }

	std::vector<SoundDevice*> getSoundDevices(int deviceStateFilter);

	inline SoundDevice* getDefaultDevice() { return pDefaultSoundDevice; }

private:
	std::vector<SoundDevice*> createSoundDevices(int deviceStateFilter);
	void destroySoundDevices();

	std::vector<SoundDevice*> devices;
	SoundDevice* pDefaultSoundDevice;
};
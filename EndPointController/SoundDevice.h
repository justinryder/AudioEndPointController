

#pragma once

#include <stdio.h>
#include <wchar.h>
#include <tchar.h>
#include <string>
#include <iostream>
#include "windows.h"
#include "Mmdeviceapi.h"
#include "PolicyConfig.h"
#include "Propidl.h"
#include "Functiondiscoverykeys_devpkey.h"
#include "Functions.h"
#include "SoundDeviceController.h"

class SoundDeviceController;

class SoundDevice
{
public:
	SoundDevice(SoundDeviceController* pDeviceController, IMMDevice* pDevice, int index);
	~SoundDevice();

	HRESULT setAsDefaultPlaybackDevice();
	
	bool isDefaultPlaybackDevice();

	inline bool isStateActive() { return state == DEVICE_STATE_ACTIVE; }
	inline bool isStateDisabled() { return state == DEVICE_STATE_DISABLED; }
	inline bool isStateNotPresent() { return state == DEVICE_STATE_NOTPRESENT; }
	inline bool isStateUnplugged() { return state == DEVICE_STATE_UNPLUGGED; }

	inline DWORD getState() { return state; }
	std::string getStateStr();

	inline int getIndex() { return index; }

	inline LPWSTR getIdPtr() { return id; }
	inline std::string getIdStr() { return wstring_to_string(id); }

	inline std::string getFriendlyNameStr() { return wstring_to_string(friendlyName); }
	inline std::wstring getFriendlyNameWStr() { return friendlyName; }

	inline std::string getInterfaceFriendlyNameStr() { return wstring_to_string(interfaceFriendlyName); }
	inline std::wstring getInterfaceFriendlyNameWStr() { return interfaceFriendlyName; }

	inline std::string getDescriptionStr() { return wstring_to_string(description); }
	inline std::wstring getDescriptionWStr() { return description; }

private:
	std::wstring getDeviceProperty(IPropertyStore* pStore, const PROPERTYKEY key);

	// The index of this device SoundDeviceController's list of SoundDevices
	int index;

	// WCHAR pointer id; (std::wstring in wchar pointer array form)
	// use getIdStr() to convert to a std::string
	LPWSTR id;

	// The current state of the device.
	// See MSDN Device State Constants explanation below.
	DWORD state;

	// A combination of the description and interfaceFriendlyName.
	// friendlyName = description + " (" + intefaceFriendlyName + ")"
	std::wstring friendlyName;
	
	// The user defined name.
	// This can be changed in the Playback devices window, by right-clicking and selecting Properties on any device.
	std::wstring description;

	// The manufacturer defined name.
	// This is the device description as defined by the device's drivers.
	std::wstring interfaceFriendlyName;

	// Pointer to the SoundDeviceController that created this.
	SoundDeviceController* pSoundDeviceController;
};

// MSDN Device State Constants
// http://msdn.microsoft.com/en-us/library/windows/desktop/dd370823(v=vs.85).aspx
//
// DEVICE_STATE_ACTIVE = 0x00000001 = 1
// The audio endpoint device is active.
// That is, the audio adapter that connects to the endpoint device is present and enabled.
// In addition, if the endpoint device plugs into a jack on the adapter, then the endpoint device is plugged in.
//
// DEVICE_STATE_DISABLED = 0x00000002 = 2
// The audio endpoint device is disabled.
// The user has disabled the device in the Windows multimedia control panel, Mmsys.cpl.
// 
// DEVICE_STATE_NOTPRESENT = 0x00000004 = 4
// The audio endpoint device is not present because the audio adapter that connects to the endpoint device has been removed from the system, or the user has disabled the adapter device in Device Manager.
// 
// DEVICE_STATE_UNPLUGGED = 0x00000008 = 8
// The audio endpoint device is unplugged.
// The audio adapter that contains the jack for the endpoint device is present and enabled, but the endpoint device is not plugged into the jack.
// Only a device with jack-presence detection can be in this state.
// 
// DEVICE_STATEMASK_ALL = 0x0000000F = 15
// Includes audio endpoint devices in all states—active, disabled, not present, and unplugged.
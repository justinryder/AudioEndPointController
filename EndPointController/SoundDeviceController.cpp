

#include "SoundDeviceController.h"

using namespace std;

SoundDeviceController::SoundDeviceController()
{
	
}

SoundDeviceController::~SoundDeviceController()
{
	destroySoundDevices();
}

void SoundDeviceController::destroySoundDevices()
{
	while (devices.size() > 0)
	{
		delete devices[devices.size() - 1];
		devices.pop_back();
	}
}

std::vector<SoundDevice*> SoundDeviceController::createSoundDevices(int deviceStateFilter)
{
	if (devices.size() > 0)
		destroySoundDevices();

	HRESULT hr;
	IMMDeviceEnumerator *pEnum;
	IMMDeviceCollection *pDevices;
	LPWSTR strDefaultDeviceID;
	IMMDevice *pCurrentDevice;

	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	pEnum = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnum);
	if (SUCCEEDED(hr))
	{
		hr = pEnum->EnumAudioEndpoints(eRender, deviceStateFilter, &pDevices);
		if SUCCEEDED(hr)
		{
			UINT count;
			pDevices->GetCount(&count);

			// Get default device
			IMMDevice* pDefaultDevice;
			hr = pEnum->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDefaultDevice);
			if (SUCCEEDED(hr))
			{
			
				hr = pDefaultDevice->GetId(&strDefaultDeviceID);

				// Iterate all devices
				for (int i = 0; i < (int)count; i++)
				{
					hr = pDevices->Item(i, &pCurrentDevice);
					if (SUCCEEDED(hr))
					{
						SoundDevice* pSoundDevice = new SoundDevice(this, pCurrentDevice, (int)devices.size());
						devices.push_back(pSoundDevice);
						if (pSoundDevice->getIdStr() == wstring_to_string(strDefaultDeviceID))
							pDefaultSoundDevice = pSoundDevice;
						pCurrentDevice->Release();
					}
				}
			}
			pDevices->Release();
		}
		pEnum->Release();
	}
	return devices;
}

void SoundDeviceController::printSoundDevices()
{
	for (unsigned int i = 0; i < devices.size(); i++)
	{
		SoundDevice* pDevice = devices[i];
		printDevice(pDevice);
		cout << endl;
	}
}

void SoundDeviceController::printDevice(SoundDevice* pDevice)
{
	// We add 1 so that the user sees the devices being numbered starting at 1.
	// This is because _wtoi will return 0 in the case of an error and we do not want to interpret that as a command to set the default device.
	cout << "Device# " << pDevice->getIndex() + 1 << endl;
	cout << "Name: " << pDevice->getFriendlyNameStr() << endl;
	cout << "State: " << pDevice->getStateStr() << endl;
	if (pDevice->isDefaultPlaybackDevice())
		cout << "Default: Yes" << endl;
	else
		cout << "Default: No" << endl;
}

void SoundDeviceController::printDevice(int i)
{
	if ((int)devices.size() > i && i > -1)
		printDevice(devices[i]);
}

HRESULT SoundDeviceController::setDefaultSoundDevice(SoundDevice* pDevice)
{
	IPolicyConfigVista *pPolicyConfig;
	ERole reserved = eConsole;

    HRESULT hr = CoCreateInstance(__uuidof(CPolicyConfigVistaClient), 
		NULL, CLSCTX_ALL, __uuidof(IPolicyConfigVista), (LPVOID *)&pPolicyConfig);
	if (SUCCEEDED(hr))
	{
		hr = pPolicyConfig->SetDefaultEndpoint(pDevice->getIdPtr(), reserved);
		if (SUCCEEDED(hr))
		{
			pDefaultSoundDevice = pDevice;
		}
		pPolicyConfig->Release();
	}
	return hr;
}

HRESULT SoundDeviceController::setDefaultSoundDevice(int i)
{
	if ((int)devices.size() > i && i > -1)
		return setDefaultSoundDevice(devices[i]);
	return -1;
}
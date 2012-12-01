

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

std::vector<SoundDevice*> SoundDeviceController::getSoundDevices(int deviceStateFilter)
{
	if (devices.size() > 0)
		destroySoundDevices();
	return createSoundDevices(deviceStateFilter);
}

std::vector<SoundDevice*> SoundDeviceController::createSoundDevices(int deviceStateFilter)
{
	HRESULT hr;
	int option;
	IMMDeviceEnumerator *pEnum;
	IMMDeviceCollection *pDevices;
	LPWSTR strDefaultDeviceID;
	IMMDevice *pCurrentDevice;
	LPCWSTR pDeviceFormatStr;

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

void SoundDeviceController::printDevice(SoundDevice* pDevice)
{
	cout << "Device# " << pDevice->getIndex() << endl;
	cout << "Name: " << pDevice->getFriendlyNameStr() << endl;
	cout << "State: " << pDevice->getStateStr() << endl;
	if (pDevice->isDefaultPlaybackDevice())
		cout << "Default: Yes" << endl;
	else
		cout << "Default: No" << endl;
}
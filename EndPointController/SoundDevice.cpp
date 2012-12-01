

#include "SoundDevice.h"

SoundDevice::SoundDevice(SoundDeviceController* pDeviceController, IMMDevice* pDevice, int index)
	:pSoundDeviceController(pDeviceController)
{
	this->index = index;

	HRESULT hr = pDevice->GetId(&id);
	if (!SUCCEEDED(hr))
	{
		printf("Error getting id");
		system("pause");
	}
	hr = pDevice->GetState(&state);
	if (!SUCCEEDED(hr))
	{
		printf("Error getting state");
		system("pause");
	}

	IPropertyStore *pStore;
	hr = pDevice->OpenPropertyStore(STGM_READ, &pStore);
	if (SUCCEEDED(hr))
	{
		friendlyName = getDeviceProperty(pStore, PKEY_Device_FriendlyName);
		description = getDeviceProperty(pStore, PKEY_Device_DeviceDesc);
		interfaceFriendlyName = getDeviceProperty(pStore, PKEY_DeviceInterface_FriendlyName);

		pStore->Release();
	}
	else
	{
		printf("Error opening property store");
		system("pause");
	}
}

SoundDevice::~SoundDevice()
{

}

bool SoundDevice::isDefaultPlaybackDevice()
{
	return pSoundDeviceController->getDefaultDevice() == this;
}

HRESULT SoundDevice::setAsDefaultPlaybackDevice()
{
	return pSoundDeviceController->setDefaultSoundDevice(this);

	IPolicyConfigVista *pPolicyConfig;
	ERole reserved = eConsole;

    HRESULT hr = CoCreateInstance(__uuidof(CPolicyConfigVistaClient), 
		NULL, CLSCTX_ALL, __uuidof(IPolicyConfigVista), (LPVOID *)&pPolicyConfig);
	if (SUCCEEDED(hr))
	{
		hr = pPolicyConfig->SetDefaultEndpoint(id, reserved);
		pPolicyConfig->Release();
	}
	return hr;
}

std::wstring SoundDevice::getDeviceProperty(IPropertyStore* pStore, const PROPERTYKEY key)
{
	PROPVARIANT prop;
	PropVariantInit(&prop);
	HRESULT hr = pStore->GetValue(key, &prop);
	if (SUCCEEDED(hr))
	{
		std::wstring result (prop.pwszVal);
		PropVariantClear(&prop);
		return result;
	}
	else
	{
		return std::wstring (L"");
	}
}

std::string SoundDevice::getStateStr()
{
	switch (state)
	{
	case DEVICE_STATE_ACTIVE:
		return "Active";
	case DEVICE_STATE_DISABLED:
		return "Disabled";
	case DEVICE_STATE_NOTPRESENT:
		return "Not Present";
	case DEVICE_STATE_UNPLUGGED:
		return "Unplugged";
	default:
		return "STATE_TO_STRING_ERROR";
	}
}
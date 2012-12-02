// EndPointController.cpp : Defines the entry point for the console application.
//

#include "SoundDeviceController.h"

using namespace std;

// EndPointController.exe [NewDefaultDeviceID]
int _tmain(int argc, LPCWSTR argv[])
{
	SoundDeviceController* pSoundDeviceController = new SoundDeviceController();

	if (argc > 1)
	{
		if (wcscmp(argv[1], _T("-help")) == 0 ||
			wcscmp(argv[1], _T("--help")) == 0 ||
			wcscmp(argv[1], _T("/help")) == 0 ||
			wcscmp(argv[1], _T("/?")) == 0 ||
			wcscmp(argv[1], _T("-?")) == 0)
		{
			printHelp();
		}
		else if (wcscmp(argv[1], _T("-all")) == 0 ||
				wcscmp(argv[1], _T("-a")) == 0 ||
				wcscmp(argv[1], _T("/a")) == 0 ||
				wcscmp(argv[1], _T("/all")) == 0)
		{
			pSoundDeviceController->createAllDevices();
			cout << "\n";
			pSoundDeviceController->printSoundDevices();
		}
		else if (wcscmp(argv[1], _T("-active")) == 0 ||
				wcscmp(argv[1], _T("/active")) == 0)
		{
			pSoundDeviceController->createActiveDevices();
			cout << "\n";
			pSoundDeviceController->printSoundDevices();
		}
		else if (wcscmp(argv[1], _T("-disabled")) == 0 ||
				wcscmp(argv[1], _T("-d")) == 0 ||
				wcscmp(argv[1], _T("/disabled")) == 0 ||
				wcscmp(argv[1], _T("/d")) == 0)
		{
			pSoundDeviceController->createDisabledDevices();
			cout << "\n";
			pSoundDeviceController->printSoundDevices();
		}
		else if (wcscmp(argv[1], _T("-notpresent")) == 0 ||
				wcscmp(argv[1], _T("-n")) == 0 ||
				wcscmp(argv[1], _T("/notpresent")) == 0 ||
				wcscmp(argv[1], _T("/n")) == 0)
		{
			pSoundDeviceController->createNotPresentDevices();
			cout << "\n";
			pSoundDeviceController->printSoundDevices();
		}
		else if (wcscmp(argv[1], _T("-unplugged")) == 0 ||
				wcscmp(argv[1], _T("-u")) == 0 ||
				wcscmp(argv[1], _T("/unplugged")) == 0 ||
				wcscmp(argv[1], _T("/u")) == 0)
		{
			pSoundDeviceController->createUnpluggedDevices();
			cout << "\n";
			pSoundDeviceController->printSoundDevices();
		}
		else
		{
			// _wtoi returns 0 in the case of an error, so we number the devices starting at 1, but we want to set the default based on the index so we subtract 1.
			// setDefaultSoundDevice will check if the passed index is in range, so we don't have to worry about an error from _wtoi accidentally setting the wrong default.
			int deviceIndex = _wtoi(argv[1]) - 1;
			pSoundDeviceController->createActiveDevices();
			if (pSoundDeviceController->getDeviceCount() > deviceIndex && deviceIndex > -1)
			{
				cout << "\nINITIAL DEFAULT DEVICE:\n\n";
				pSoundDeviceController->printDevice(pSoundDeviceController->getDefaultDevice());
				cout << "\nCHANGING DEFAULT DEVICE TO:\n\n";
				pSoundDeviceController->printDevice(deviceIndex);
				system("pause");
				HRESULT result = pSoundDeviceController->setDefaultSoundDevice(deviceIndex);
				pSoundDeviceController->destroySoundDevices();//dont forget to clean up!
				return result;
			}
		}
	}
	else
	{
		pSoundDeviceController->createActiveDevices();
		cout << "\n";
		pSoundDeviceController->printSoundDevices();
	}

	pSoundDeviceController->destroySoundDevices();//dont forget to clean up!

	return 0;
}


#include "Functions.h"

#include <algorithm>
#include <iostream>

using namespace std;

wstring string_to_wstring(const string& src)
{
	wstring tmp;
	tmp.resize(src.size());
	transform(src.begin(), src.end(), tmp.begin(), btowc);
	return tmp;
}

string wstring_to_string(const wstring& src)
{
	string tmp;
	tmp.resize(src.size());
	transform(src.begin(), src.end(), tmp.begin(), wctob);
	return tmp;
}

void printHelp()
{
	cout << "Lists active audio playback devices or sets default audio playback device." << endl;
	cout << endl;
	cout << "USAGE" << endl;
	cout << "  EndPointController.exe" << endl;
	cout << "                                       Displays devices that are active." << endl;
	cout << "  EndPointController.exe [OPTIONS]" << endl;
	cout << "                                       Displays devices that are active." << endl;
	cout << "  EndPointController.exe [#]" << endl;
	cout << "                                       Sets the default device." << endl;
	cout << "                                       (uses active device numbering)" << endl;
	cout << "OPTIONS" << endl;
	cout << "  [NONE]                               Display devices that are active." << endl;
	cout << "  -all, /all, -a, /a                   Display all devices." << endl;
	cout << "  -active, /active                     Display devices that are active." << endl;
	cout << "  -disabled, /disabled, -d, /d         Display devices that are diabled." << endl;
	cout << "  -notpresent, /notpresent, -n, /n     Display devices that are not present." << endl;
	cout << "  -unplugged, /unplugged, -u, /u       Display devices that are unplugged." << endl;
	cout << "  -help, --help, /help, -?, /?         Display this message." << endl;
	cout << "  [#]                                  Set default device to active device" << endl;
	cout << "                                       with given number." << endl;
	cout << "EXAMPLES" << endl;
	cout << "  EndPointController.exe /disabled" << endl;
	cout << "                                       Displays the disabled devices" << endl;
	cout << "  EndPointController.exe 2" << endl;
	cout << "                                       Sets the default device to active" << endl;
	cout << "                                       device # 2." << endl;

}
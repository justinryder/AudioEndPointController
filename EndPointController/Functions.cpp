

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
	cout <<
"Lists active audio playback devices or sets default audio playback device.\n\
\n\
USAGE\n\
  EndPointController.exe\n\
                                       Displays devices that are active.\n\
  EndPointController.exe [OPTIONS]\n\
                                       Displays devices that are active.\n\
  EndPointController.exe [#]\n\
                                       Sets the default device.\n\
                                       (uses active device numbering)\n\
OPTIONS\n\
  [NONE]                               Display devices that are active.\n\
  -all, /all, -a, /a                   Display all devices.\n\
  -active, /active                     Display devices that are active.\n\
  -disabled, /disabled, -d, /d         Display devices that are diabled.\n\
  -notpresent, /notpresent, -n, /n     Display devices that are not present.\n\
  -unplugged, /unplugged, -u, /u       Display devices that are unplugged.\n\
  -help, --help, /help, -?, /?         Display this message.\n\
  [#]                                  Set default device to active device\n\
                                       with given number.\n\
EXAMPLES\n\
  EndPointController.exe /disabled\n\
                                       Displays the disabled devices\n\
  EndPointController.exe 2\n\
                                       Sets the default device to active\n\
                                       device # 2.\n";
}
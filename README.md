AudioEndPointController
=======================

A Windows command-line program for listing audio end-points and setting the default

	>EndPointController.exe --help
	Lists active audio playback devices or sets default audio playback device.
	
	USAGE
	  EndPointController.exe" << endl;
	                                       Displays devices that are active.
	  EndPointController.exe [OPTIONS]" << endl;
	                                       Displays devices that are active.
	  EndPointController.exe [#]" << endl;
	                                       Sets the default device.
	                                       (uses active device numbering)
	OPTIONS
	  [NONE]                               Display devices that are active.
	  -all, /all, -a, /a                   Display all devices.
	  -active, /active                     Display devices that are active.
	  -disabled, /disabled, -d, /d         Display devices that are diabled.
	  -notpresent, /notpresent, -n, /n     Display devices that are not present.
	  -unplugged, /unplugged, -u, /u       Display devices that are unplugged.
	  -help, --help, /help, -?, /?         Display this message.
	  [#]                                  Set default device to active device
	                                       with given number.
	EXAMPLES
	  EndPointController.exe /disabled
	                                       Displays the disabled devices
	  EndPointController.exe 2
	                                       Sets the default device to active
	                                       device # 2.
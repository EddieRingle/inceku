/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include "header.h"
#include "webserver.h"

Console *console = NULL;
Server *inst = NULL;

int init(string arg)
{
	if(arg == "start")
	{
		console->WriteLine("Start web server");
		inst = new Server(80);	
	} else if(arg == "stop")
	{
		console->WriteLine("Stop web server");
	
	} else if(arg == "help")
	{
		console->WriteLine("Usage: WebServer start | stop | help");
	}
	
	return 0;
}

int RunApplication ( int argc, char **argv )
{
	console = new Console ();

	// Start your application here
	if (argc <= 1)
	{
		string usage = "Usage: WebServer start | stop | help";
		console->WriteLine(usage);
		inst = new Server(8080); // This is here simply for debugging purposes
	}
	else{
	init(argv[1]);
	}
	// End your application here.

#ifdef TARGET_OS_WINDOWS
	system ( "pause" );
#endif

	delete console;
	return 0;
}

#include "config.h"
#include "header.h"
#include "StringTokenizer.h"

Config::Config()
{
	std::string l;
	std::string delimiter = " ";
	FileReader *f = new FileReader();
	
	f->Open("inceku.conf");
	
	while (!f->EndOfFile()) {
		f->ReadLine(l);
		if (l.compare(0,1,"#") != 0) {
		    cout << l << endl;
			StringTokenizer strtok(l,delimiter);
			if (strtok.nextToken() == "port") {
				port = strtok.nextIntToken();
				cout << "Setting port to " << port << endl;
			}
		}
	}
}

Config::~Config()
{
	// nothing to see here
}
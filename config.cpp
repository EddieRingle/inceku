/*
 *   Inceku
 *   A portable HTTP server.
 *
 *   (c) 2008 Eddie Ringle.
 *   Licensed under the
 *   Creative Commons Attribution-Noncommercial-Share Alike 3.0 License.
 *   To view a copy of this license,
 *   visit http://creativecommons.org/licenses/by-nc-sa/3.0/us/.
 */

#include "config.h"
#include "header.h"

Config::Config()
{
    // nothing to do here
}

int Config::LoadnParse()
{
	int line = 0;
	char l [250];
	FileReader *f = new FileReader();
	f->Open("inceku.conf");
	while (!f->EndOfFile()) {
		f->ReadLine(l,250);
		line++;
		if (strncmp(l,"#",1) != 0) {
		    char * tmp;
		    tmp = strtok(l," ");
		    while (tmp != NULL)
		    {
			if(strcmp(tmp,"port") == 0) {
			    	port = atoi(strtok(NULL," "));
				cout << "Setting port to " << port << endl;
			} else if(strcmp(tmp,"docroot") == 0) {
				docroot = strtok(NULL," ");
			} else if(strcmp(tmp,"cgi-bin") == 0) {
				cgibin = strtok(NULL," ");
			} else if(strcmp(tmp,"alogdir") == 0) {
				alogdir = strtok(NULL," ");
			} else if(strcmp(tmp,"elogdir") == 0) {
				elogdir = strtok(NULL," ");
			} else {
			    cout << "Error reading config file on line " << line << endl;
			    return 1;
			}
			tmp = strtok(NULL," ");
		    }
		}
	}
	return 0;
}

Config::~Config()
{
	// nothing to see here
}
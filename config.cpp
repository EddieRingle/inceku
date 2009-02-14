/*
 *   Inceku
 *   A portable HTTP server.
 *
 *   (c) 2008 Eddie Ringle.
 *   Licensed under the New BSD License.
 */

#include "config.h"
#include "header.h"

Config::Config()
{
    docroot = new char [150];
    cgibin = new char [150];
    alogdir = new char [150];
    elogdir = new char [150];
    dindex = new char [150];
}

Config::~Config()
{
    delete [] docroot;
    delete [] cgibin;
    delete [] alogdir;
    delete [] elogdir;
    delete [] dindex;
    docroot = NULL;
    cgibin = NULL;
    alogdir = NULL;
    elogdir = NULL;
    dindex = NULL;
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
				strcpy(docroot, strtok(NULL," "));
				cout << "Docroot: " << docroot << endl;
			} else if(strcmp(tmp,"cgi-bin") == 0) {
				strcpy(cgibin, strtok(NULL," "));
				cout << "Cgi-bin: " << cgibin << endl;
			} else if(strcmp(tmp,"alogdir") == 0) {
				strcpy(alogdir, strtok(NULL," "));
				cout << "access log: " << alogdir << endl;
			} else if(strcmp(tmp,"elogdir") == 0) {
				strcpy(elogdir, strtok(NULL," "));
				cout << "error log: " << elogdir << endl;
			} else if(strcmp(tmp,"dindex") == 0) {
				strcpy(dindex, strtok(NULL," "));
				cout << "Setting directory index to " << dindex << endl;
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

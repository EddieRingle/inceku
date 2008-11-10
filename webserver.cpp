/*
 *   Inceku
 *   A portable HTTP server.
 *
 *   (c) 2008 Eddie Ringle.
 *   Licensed under the GNU GPL v3
 */

#include "header.h"
#include "webserver.h"
#include "config.h"

Console *sconsole = NULL;

// Server Constructor(s)
Server::Server()
{
	sconsole = new Console(stdout, stdin);
	if(LoadConfig() == 0) {
	TCPSocket *s = new TCPSocket();
	s->Listen(port);
	cout << "Listening on port: " << port << endl;
	Accept(s);
	}
}

// If someone wanted to force a port through the command line
Server::Server(unsigned short port)
{
	unsigned short fport = port;
	sconsole = new Console(stdout, stdin);
	if(LoadConfig() == 0) {
	LoadConfig();
	TCPSocket *s = new TCPSocket();
	s->Listen(fport);
	Accept(s);
	}
}

// Accepts incoming connections, and passes requests to the parser
int Server::Accept(TCPSocket *a)
{
	TCPSocket *s = a;
	TCPSocket *tmps = NULL;
	while (1) {
		int ccerr;
		ccerr = s->Accept(&tmps);
		if (ccerr == 0) {
		    while(ReadSocket(tmps) != 0);
		    Respond(tmps);
		}
		if (tmps != NULL)
		{
			tmps->Close();
		}
		ThreadSleep(50);
	}
	return 0;
}

// Reads from the socket, currently just prints out what's received
int Server::ReadSocket(TCPSocket *a)
{
	TCPSocket *s = a;
	char *in = new char [250];
	unsigned int len = 250;
	if (s->Read(in,&len) == 0) {
	    Parse(in);
	    return 0;
	} else {
	    return 1;
	}
}

// Respond to the HTTP request, currently hard-coded
int Server::Respond(TCPSocket *a)
{
	TCPSocket *s = a;
	FileReader *f = new FileReader();
	if (reqdir[strlen(reqdir) - 1] == '/')
	{
	    cout << "wewt!" << endl;
	}
	f->Open(strcat(docroot,reqdir));
//	s->Send(r);
	return 0;
}

int Server::Parse(char *str)
{
    char *line;
    line = strtok(str,"\n");
    while(line != NULL) {
	int meth = RequestCheck(line);
	switch(meth)
	{
	    case OPTIONS:
		// not implemented yet
		break;
	    case GET:
		ProcGET(line);
		break;
	    case HEAD:
		// not implemented yet
		break;
	    case POST:
		// not implemented yet
		break;
	    case PUT:
		// not implemented yet
		break;
	    case TRACE:
		// not implemented yet
		break;
	    case CONNECT:
		// not implemented yet
		break;
	    case -1:
		break;
	    default:
		break;
	}
	line = strtok(NULL,"\n");
    }
    return 0;
}

int Server::RequestCheck(char *str)
{
    if(strncmp(str,"OPTIONS",6) == 0) {
	return OPTIONS;
    } else if(strncmp(str,"GET",3) == 0) {
	return GET;
    } else if(strncmp(str,"HEAD",4) == 0) {
	return HEAD;
    } else if(strncmp(str,"POST",4) == 0) {
	return POST;
    } else if(strncmp(str,"PUT",3) == 0) {
	return PUT;
    } else if(strncmp(str,"TRACE",5) == 0) {
	return TRACE;
    } else if(strncmp(str,"CONNECT",7) == 0) {
	return CONNECT;
    } else {
    return -1; // Not a request line
    }
}

int Server::ProcGET(char *str)
{
    char *word;
    char *reqdir = new char [500];
    word = strtok(str," ");
    while (word != NULL) {
	cout << word << endl;
	if(strcmp(word,"GET")) {
	    // do nothing, we know it's a GET request
	} else if(strncmp(word,"/",1) == 0) {
	    reqdir[0] = 0;
	    strcpy(reqdir,word);
	    cout << "Requested directory: " << reqdir << endl;
	} else if(strncmp(word,"HTTP",4) == 0) {
	    if(strncmp(word,"HTTP/1.0",8) == 0) {
		httpver = 1.0;
	    } else if(strncmp(word,"HTTP/1.1",8) == 0) {
		httpver = 1.1;
	    } else {
		httpver = 1.0; // fallback to 1.0
	    }
	} else {
	    // oh well...
	}
	word = strtok(NULL," ");
    }
    return 0;
}

// Load the config file and set variables
int Server::LoadConfig()
{
	Config *c = new Config();
	if(c->LoadnParse() != 0) {
		return 1;
	} else {
		port = c->port;
		docroot = c->docroot;
		cgibin = c->cgibin;
		alogdir = c->alogdir;
		elogdir = c->elogdir;
		return 0;
	}
}
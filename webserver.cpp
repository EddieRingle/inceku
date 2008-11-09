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
	sconsole = new Console(stdout, stdin);
	if(LoadConfig() == 0) {
	LoadConfig();
	TCPSocket *s = new TCPSocket();
	s->Listen(port);
	Accept(s);
	}
}

// Accepts incoming connections, and passes requests to the parser
int Server::Accept(TCPSocket * a)
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
	char *in;
	if (s->Read(in,100) == 0) {
	    sconsole->WriteLine(in);
	    return 0;
	} else {
	    return 1;
	}
}

// Respond to the HTTP request, currently hard-coded
int Server::Respond(TCPSocket * a)
{
	TCPSocket *s = a;
	std::string r = "HTTP/1.1 200 OK\r\nServer: Inceku/0alpha\r\n\r\n"
			"<h1>It Works! \\o/</h1>\r\n";
	sconsole->WriteLine(r);
	s->Send(r);
	sconsole->WriteLine("Done. :)");
	return 0;
}

int Server::Parse(std::string str)
{
    
    return 0;
}

int Server::RequestCheck(std::string str)
{
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
		std::string docroot = c->docroot;
		std::string cgibin = c->cgibin;
		std::string alogdir = c->alogdir;
		std::string elogdir = c->elogdir;
		return 0;
	}
}
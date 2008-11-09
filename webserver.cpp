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
		    // Parse(in) will go here when we're ready to parse stuff.
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
	string in;
	if (s->Read(in) == 0) {
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
    /* <todo> Write Parser function.
    All we care about is the first line the client sends in,
    it contains the command we must process */
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
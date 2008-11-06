#include "header.h"
#include "webserver.h"

Console *sconsole = NULL;

// Server Constructor(s)
Server::Server()
{
	sconsole = new Console(stdout, stdin);
	ReadConfig();
	TCPSocket *s = new TCPSocket();
	s->Listen(port);
	sconsole->WriteLine("Listening on port" + port + ".");
	Accept(s);
}
Server::Server(unsigned short port)
{
	sconsole = new Console(stdout, stdin);
	ReadConfig();
	TCPSocket *s = new TCPSocket();
	s->Listen(port);
	sconsole->WriteLine("Listening on port" + port + ".");
	Accept(s);
}

// Accepts incoming connections, and passes requests to the parser
int Server::Accept(TCPSocket * a)
{
	TCPSocket *s = a;
	TCPSocket *tmps = NULL;
	while (1) {
		int ccerr;
		ccerr = s->Accept(&tmps);
		if (ccerr == CC_ERR_WOULD_BLOCK)
			sconsole->WriteLine("Non-blocking Sockets are enabled...");
		if (ccerr == 0) {
		    while(ReadSocket(tmps) != 0);
		    // Parse(in) will go here when we're ready to parse stuff.
		    Respond(tmps);
		} else {
		tmps->Close();
		}
		ThreadSleep(50);
	}
	return 0;
}

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

int Server::Respond(TCPSocket * a)
{
	TCPSocket *s = a;
	sconsole->WriteLine("Sending Response...");
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

int Server::ReadConfig()
{
	std::string l;
	FileReader *f = new FileReader();
	f->Open("inceku.conf");
	sconsole->WriteLine("Opening inceku.conf...");
	bool IsOpen = f->IsOpen();
	cout << IsOpen << endl;
	if (IsOpen) {
		sconsole->WriteLine("Opened inceku.conf.");
		while (!f->EndOfFile()) {
			f->ReadLine(l);
			if (l.compare(0,1,"#") != 0) {
			sconsole->WriteLine(l);
			}
		}
	} else {
	    sconsole->WriteLine("Error reading file?");
	}
	delete f;
	return 0;
}
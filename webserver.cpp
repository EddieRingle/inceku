#include "header.h"
#include "webserver.h"

Server::Server(unsigned short port) {
		TCPSocket * s = new TCPSocket();
		s->Listen(port);
		cout << "Listening on port " << port << endl;
		Accept(s);
}

int Server::Accept(TCPSocket * a) {
	TCPSocket * s = a;
	TCPSocket * nulls = NULL;
	while(1)
	{
		string in;
                int ccerr;
                ccerr = s->Accept(&nulls);
                if (ccerr == CC_ERR_WOULD_BLOCK)
                    cout << "Non-blocking Sockets are enabled...";
		if(ccerr == 0) { // If Accept(&nulls) responded with CC_ERR_NONE
			cout << "Reading from socket..." << endl;
			if(nulls->Read(in) == 0)
			{
				cout << in << endl;
				cout << "Gotta respond now..." << endl;
				Respond(nulls);
			} else {
				cout << "Error with Reading?" << endl;
			}
		}
                nulls->Close();
                ThreadSleep(50);
	}

	return 0;
}

int Server::Respond(TCPSocket * a) {
	TCPSocket *s = a;
	cout << "Sending response..." << endl;
	std::string r = "HTTP/1.1 200 OK\r\nServer: Inceku/0alpha (Win)\r\n\r\n<h1>It Works! \\o/</h1>\r\n";
	cout << r;
	s->Send(r);
	cout << "Sent." << endl;
	return 0;
}

int Server::Parse(std::string str) {
	/* <todo> Write Parser function.
	All we care about is the first line the client sends in,
	it contains the command we must process */
	return 0;
}

int Server::ReadConfig() {
	/* <todo> Write Config file Reader.
	syntax would be something like:
	[item]: definition
	something like that, I'll work on it ;) */
	return 0;
}

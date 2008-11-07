#include "header.h"

#ifndef WEBSERVER_H
#define WEBSERVER_H

enum HTTPMethod {
	OPT = 0, //OPTIONS = 0
	GET, //GET = 1
	HEA, //HEAD = 2
	POS, //POST = 3
	PUT, //PUT = 4
	TRA, //TRACE = 5
	CON //CONNECT = 6
};

class Server {
public:
	unsigned short port;
	Server(); // The default constructor
	Server(unsigned short port); // If someone decides to force a port
	~Server(); // The deconstructor
	int Accept(TCPSocket *a);
	int ReadSocket(TCPSocket *a);
	int Respond(TCPSocket *a);
	int Parse(std::string str);
	int ReadConfig();
};
#endif

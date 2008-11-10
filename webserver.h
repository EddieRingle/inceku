/*
 *   Inceku
 *   A portable HTTP server.
 *
 *   (c) 2008 Eddie Ringle.
 *   Licensed under the GNU GPL v3
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "header.h"
#include "config.h"

enum HTTPMethod {
	OPTIONS = 0, //OPTIONS = 0
	GET, //GET = 1
	HEAD, //HEAD = 2
	POST, //POST = 3
	PUT, //PUT = 4
	TRACE, //TRACE = 5
	CONNECT //CONNECT = 6
};

class Server {
public:
	char reqdir;
	float httpver;
	Server();
	Server(unsigned short port);
	~Server(); 
	int Accept(TCPSocket *a);
	int ReadSocket(TCPSocket *a);
	int Respond(TCPSocket *a);
	int Parse(char *str);
	int RequestCheck(char *str);
	int LoadConfig();
	
	int ProcGET(char *str);
};
#endif

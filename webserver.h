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
        unsigned int port; // default 8080
	char *docroot; // default <inceku dir>/docroot
	char *cgibin; // default <inceku dir>/cgi-bin
	char *alogdir; // default <inceku dir>/access.log
	char *elogdir; // default <inceku dir>/error.log
	char *dindex; // default index.html
	char *reqdir;
	float httpver;
	Server();
	~Server();
	int Start();
	int Start(unsigned short fport);
	int Accept(TCPSocket *a);
	int ReadSocket(TCPSocket *a);
	int Respond(TCPSocket *a);
	int Parse(char *str);
	int RequestCheck(char *str);
	int LoadConfig();
	
	int ProcGET(char *str);
};
#endif

/*
 *   Inceku
 *   A portable HTTP server.
 *
 *   (c) 2008 Eddie Ringle.
 *   Licensed under the New BSD License.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "header.h"
#include "webserver.h"

class Config {
public:
    unsigned int port; // default 8080
    char *docroot; // default <inceku dir>/docroot
    char *cgibin; // default <inceku dir>/cgi-bin
    char *alogdir; // default <inceku dir>/access.log
    char *elogdir; // default <inceku dir>/error.log
    char *dindex; // default index.html
    Config(); // Default constructor
    int LoadnParse();
    ~Config();
};

#endif

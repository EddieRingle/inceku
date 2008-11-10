/*
 *   Inceku
 *   A portable HTTP server.
 *
 *   (c) 2008 Eddie Ringle.
 *   Licensed under the GNU GPL v3
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "header.h"

class Config {
public:
    unsigned int port; // default 8080
    std::string docroot; // default <inceku dir>/docroot
    std::string cgibin; // default <inceku dir>/cgi-bin
    std::string alogdir; // default <inceku dir>/access.log
    std::string elogdir; // default <inceku dir>/error.log
    Config(); // Default constructor
    int LoadnParse();
    ~Config();
};

#endif
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
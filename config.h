#ifndef CONFIG_H
#define CONFIG_H

#include "header.h"
#include "StringTokenizer.h"

class Config {
public:
    unsigned int port; // default 8080
    std::string docroot; // default <inceku dir>/docroot
    std::string cgibin; // default <inceku dir>/cgi-bin
    std::string alogdir; // default <inceku dir>/access.log
    std::string elogdir; // default <inceku dir>/error.log
    Config(); // Default constructor
    ~Config();
};

#endif
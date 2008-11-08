#ifndef CONFIG_H
#define CONFIG_H

#include "header.h"

class Config {
public:
    unsigned int port;
    std::string docroot;
    std::string cgibin;
    std::string alogdir;
    std::string elogdir;
    Config(); // An empty constructor
    Config(std::string l); // Default Config reader/parser constructor
    ~Config();
};

#endif
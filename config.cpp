#include "config.h"
#include "header.h"

Config::Config(std::string l)
{
    char *cstr, *p;
    cstr = new char [l.size()+1];
    strcpy(cstr, l.c_str());
    
    p = strtok(cstr," ");
    while (p != NULL)
    {
	cout << p << endl;
    }
}

Config::~Config()
{
	// nothing to see here
}
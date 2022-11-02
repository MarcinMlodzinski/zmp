#pragma once

#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>

#define LINE_SIZE 500

class Reader
{
private:
    std::string cmdFileName;

public:
    Reader(){};
    bool init(std::string cmdFile);
    bool execPreprocesor(std::istringstream &IStrm4Cmds);
};
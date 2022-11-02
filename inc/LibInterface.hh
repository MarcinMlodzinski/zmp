#pragma once

#include <iostream>
#include <string>
#include <dlfcn.h>
#include "Interp4Command.hh"

class LibInterface
{
private:
    void *_LibHandler;
    std::string _CmdName;
    Interp4Command *(*_pCreateCmd)(void);

public:
    ~LibInterface();
    bool init(std::string libraryName);
    Interp4Command *CreateCmd();
};
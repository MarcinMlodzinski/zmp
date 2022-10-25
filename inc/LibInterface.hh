#pragma once

#include <string>
#include "Interp4Command.hh"

class LibInterface
{
private:
    void *_LibHandler;
    std::string _CmdName;
    Interp4Command *_pCreateCmd;

public:
    ~LibInterface();
};
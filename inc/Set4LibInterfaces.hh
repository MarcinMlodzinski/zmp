#pragma once

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <memory>
#include "LibInterface.hh"
#include "Interp4Command.hh"

class Set4LibInterfaces
{
private:
    std::map<std::string, std::shared_ptr<LibInterface>> libraries;

public:
    bool init();
    bool execute(std::istringstream &stream);
};
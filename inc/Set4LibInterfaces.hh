#pragma once

#include <string>
#include <vector>
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
    bool init(std::vector<std::string> libraries_vector);
    bool execute(std::istringstream &stream);
};
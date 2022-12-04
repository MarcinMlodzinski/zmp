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
    bool parallel = false;

public:
    bool init(std::vector<std::string> libraries_vector);
    Interp4Command *execute(std::string key);
    bool isParallel() { return parallel; }
};
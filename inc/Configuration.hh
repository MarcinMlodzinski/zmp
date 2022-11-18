#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <vector>
#include <string>

class Configuration
{
private:
  std::vector<std::string> libraries_vector;

public:
  void addLibrary(std::string name) { libraries_vector.push_back(name); };
  std::vector<std::string> getLibraries() { return libraries_vector; };
};

#endif

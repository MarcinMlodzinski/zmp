#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Reader.hh"
#include "Set4LibInterfaces.hh"

int main()
{
  Configuration Config;
  Reader reader;
  Set4LibInterfaces handler;
  std::istringstream stream;
  reader.init("opis_dzialan.cmd");
  reader.execPreprocesor(stream);

  if (!reader.ReadFile("config/config.xml", Config))
  {
    return 1;
  }

  handler.init(Config.getLibraries());
  handler.execute(stream);

  return 0;
}

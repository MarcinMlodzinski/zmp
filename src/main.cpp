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
  Configuration   Config;
  Reader preprocRead;
  Set4LibInterfaces handler;
  std::istringstream stream;
  preprocRead.init("opis_dzialan.cmd");
  preprocRead.execPreprocesor(stream);

  handler.init();
  handler.execute(stream);

  if (!preprocRead.ReadFile("config/config.xml",Config)){
    return 1;
  }

  return 0;
}

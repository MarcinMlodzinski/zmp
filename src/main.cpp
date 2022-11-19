#include <iostream>
#include <thread>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Reader.hh"
#include "Set4LibInterfaces.hh"
#include "Scene.hh"
#include "Sender.hh"

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

  Scene scene(Config);
  Sender sender(&scene);
  if (!sender.OpenConnection())
    return 1;

  std::thread Thread4Sending(&Sender::Watching_and_Sending, &sender);

  handler.init(Config.getLibraries());
  handler.execute(stream);

  const char *sConfigCmds =
      "Clear\n"
      "AddObj Name=Podstawa1 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
      "AddObj Name=Podstawa1.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
      "AddObj Name=Podstawa1.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n"
      "AddObj Name=Podstawa2 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(-1,-3,0)\n"
      "AddObj Name=Podstawa2.Ramie1 RGB=(200,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
      "AddObj Name=Podstawa2.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n";

  sender.Send(sConfigCmds);

  sender.Send("Close\n");
  sender.CancelCountinueLooping();
  Thread4Sending.join();

  return 0;
}

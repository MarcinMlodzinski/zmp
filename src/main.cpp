#include "Interp4Command.hh"
#include "LibInterface.hh"
#include "MobileObj.hh"
#include "Reader.hh"
#include "Scene.hh"
#include "Sender.hh"
#include "Set4LibInterfaces.hh"
#include <cassert>
#include <dlfcn.h>
#include <iostream>
#include <thread>

int main()
{
  Configuration Config;
  Reader reader;
  Set4LibInterfaces handler;
  Interp4Command *command;
  std::istringstream stream;
  std::vector<std::thread> threads;
  reader.init("opis_dzialan.cmd");

  if (!reader.ReadFile("config/config.xml", Config))
  {
    return 1;
  }

  Scene scene(Config);
  Sender sender(&scene);
  if (!sender.OpenConnection())
    return 1;

  handler.init(Config.libraries_vector);
  std::thread Thread4Sending(&Sender::Watching_and_Sending, &sender);
  std::string key;
  reader.execPreprocesor(stream);
  while (stream >> key)
  {
    command = handler.execute(key);
    // if (command != nullptr)
    // {
    //   command->ReadParams(stream);
    // }

    if (handler.isParallel() && command != nullptr)
    {
      command->ReadParams(stream);
      threads.push_back(std::thread(&Interp4Command::ExecCmd, command, &scene));
      // command->ExecCmd(&scene);
    }
    else if (!handler.isParallel())
    {
      for (int i = 0; i < threads.size(); ++i)
      {
        if (threads[i].joinable())
          threads[i].join();
      }
      threads.clear();
    }
  }

  // const char *sConfigCmds =
  //     "Clear\n"
  //     "AddObj Name=Podstawa1 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) "
  //     "RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
  //     "AddObj Name=Podstawa1.Ramie1 RGB=(200,0,0) Scale=(3,3,1) "
  //     "Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
  //     "AddObj Name=Podstawa1.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) "
  //     "Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n"
  //     "AddObj Name=Podstawa2 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) "
  //     "RotXYZ_deg=(0,-45,0) Trans_m=(-1,-3,0)\n"
  //     "AddObj Name=Podstawa2.Ramie1 RGB=(200,0,0) Scale=(3,3,1) "
  //     "Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
  //     "AddObj Name=Podstawa2.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) "
  //     "Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n";

  // sender.Send(sConfigCmds);

  sender.Send("Close\n");
  sender.CancelCountinueLooping();
  for (int i = 0; i < threads.size(); ++i)
  {
    // std::cout << "ccc\n";
    if (threads[i].joinable())
      threads[i].join();
  }
  Thread4Sending.join();

  return 0;
}

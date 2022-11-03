#include "Set4LibInterfaces.hh"

bool Set4LibInterfaces::init()
{
    LibInterface *move = new LibInterface();
    LibInterface *set = new LibInterface();
    LibInterface *pause = new LibInterface();
    LibInterface *rotate = new LibInterface();

    move->init("libs/libInterp4Move.so");
    set->init("libs/libInterp4Set.so");
    pause->init("libs/libInterp4Pause.so");
    rotate->init("libs/libInterp4Rotate.so");

    libraries.insert(std::make_pair("Move", move));
    libraries.insert(std::make_pair("Set", set));
    libraries.insert(std::make_pair("Pause", pause));
    libraries.insert(std::make_pair("Rotate", rotate));

    return 0;
}

bool Set4LibInterfaces::execute(std::istringstream &stream)
{
    std::string key;
    LibInterface *handle;
    Interp4Command *command;

    while (stream >> key)
    {
        std::map<std::string, LibInterface *>::iterator iterator = libraries.find(key);
        if (iterator == libraries.end())
        {
            std::cout << "Nie znaleziono wtyczki dla polecenia: " << key << std::endl;
            return 1;
        }

        handle = iterator->second;
        command = handle->CreateCmd();
        command->ReadParams(stream);
        std::cout << "Polecenie:" << std::endl;
        command->PrintCmd();
        delete command;
    }

    return 0;
}
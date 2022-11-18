#include "Set4LibInterfaces.hh"

bool Set4LibInterfaces::init(std::vector<std::string> libraries_vector)
{
    for (int i = 0; i < libraries_vector.size(); i++)
    {
        std::shared_ptr<LibInterface> tmp_library = std::make_shared<LibInterface>();
        tmp_library->init("libs/" + libraries_vector[i]);
        std::string command_name = libraries_vector[i].substr(10, libraries_vector[i].length() - 13);
        std::cout << command_name << std::endl;

        libraries.insert(std::make_pair(command_name, tmp_library));
    }

    // std::shared_ptr<LibInterface> move = std::make_shared<LibInterface>();
    // std::shared_ptr<LibInterface> set = std::make_shared<LibInterface>();
    // std::shared_ptr<LibInterface> pause = std::make_shared<LibInterface>();
    // std::shared_ptr<LibInterface> rotate = std::make_shared<LibInterface>();

    // move->init("libs/libInterp4Move.so");
    // set->init("libs/libInterp4Set.so");
    // pause->init("libs/libInterp4Pause.so");
    // rotate->init("libs/libInterp4Rotate.so");

    // libraries.insert(std::make_pair("Move", move));
    // libraries.insert(std::make_pair("Set", set));
    // libraries.insert(std::make_pair("Pause", pause));
    // libraries.insert(std::make_pair("Rotate", rotate));

    return 0;
}

bool Set4LibInterfaces::execute(std::istringstream &stream)
{
    std::string key;
    std::shared_ptr<LibInterface> handle;
    Interp4Command *command;

    while (stream >> key)
    {
        std::map<std::string, std::shared_ptr<LibInterface>>::iterator iterator = libraries.find(key);
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
#pragma once

#include <map>
#include <string>
#include "MobileObj.hh"
#include "AccessControl.hh"
#include "Configuration.hh"

class Scene : public AccessControl
{
private:
    /*!
     * \brief Prosta kolekcja obiektów sceny
     */
    std::map<std::string, MobileObj> _Container4Objects;

public:
    Scene(Configuration &config);
    MobileObj *FindMobileObj(const char *sName)
    {
        MobileObj *pointer_to_object = NULL;
        std::map<std::string, MobileObj>::iterator iterator =
            _Container4Objects.find(sName);
        if (iterator == _Container4Objects.end())
        {
            std::cout << "Nie znaleziono wtyczki dla polecenia: " << sName << std::endl;
        }
        pointer_to_object = &(iterator->second);
        return pointer_to_object;
    }
    void AddMobileObj(MobileObj *pMobObj);
    std::map<std::string, MobileObj> getMobileObjects() { return _Container4Objects; }
};

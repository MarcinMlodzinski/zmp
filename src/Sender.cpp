#include "Sender.hh"

Sender::~Sender()
{
    close(_Socket);
}

int Sender::Send(const char *sMesg)
{
    ssize_t IlWyslanych;
    ssize_t IlDoWyslania = (ssize_t)strlen(sMesg);

    while ((IlWyslanych = write(_Socket, sMesg, IlDoWyslania)) > 0)
    {
        IlDoWyslania -= IlWyslanych;
        sMesg += IlWyslanych;
    }
    if (IlWyslanych < 0)
    {
        std::cerr << "*** Blad przeslania napisu." << std::endl;
    }
    return 0;
}

void Sender::Watching_and_Sending()
{
    Send("Clear\n");
    _pScn->LockAccess();
    for (auto &iterator : _pScn->getMobileObjects())
    {
        // std::cout << iterator.first << std::endl;
        Send(getAddInstruction(&(iterator.second)).c_str());
        // Ta instrukcja to tylko uproszczony przykład
        // std::cout << rObj.GetStateDesc();
        // Send(rObj.GetStateDesc()); // Tu musi zostać wywołanie odpowiedniej
        // metody/funkcji gerującej polecenia dla serwera.
    }
    _pScn->UnlockAccess();
    while (ShouldCountinueLooping())
    {
        if (!_pScn->IsChanged())
        {
            usleep(10000);
            continue;
        }
        std::cout << "send\n";
        _pScn->LockAccess();

        //------- Przeglądanie tej kolekcji to uproszczony przykład

        for (auto &iterator : _pScn->getMobileObjects())
        {
            // std::cout << iterator.first << std::endl;
            Send(getUpdateInstruction(&(iterator.second)).c_str());
            // Ta instrukcja to tylko uproszczony przykład
            // std::cout << rObj.GetStateDesc();
            // Send(rObj.GetStateDesc()); // Tu musi zostać wywołanie odpowiedniej
            // metody/funkcji gerującej polecenia dla serwera.
        }

        _pScn->CancelChange();
        _pScn->UnlockAccess();
    }
}

bool Sender::OpenConnection()
{
    struct sockaddr_in DaneAdSerw;

    bzero((char *)&DaneAdSerw, sizeof(DaneAdSerw));

    DaneAdSerw.sin_family = AF_INET;
    DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
    DaneAdSerw.sin_port = htons(PORT);

    _Socket = socket(AF_INET, SOCK_STREAM, 0);

    if (_Socket < 0)
    {
        std::cerr << "*** Blad otwarcia gniazda." << std::endl;
        return false;
    }

    if (connect(_Socket, (struct sockaddr *)&DaneAdSerw, sizeof(DaneAdSerw)) < 0)
    {
        std::cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << std::endl;
        return false;
    }
    return true;
}

std::string Sender::getUpdateInstruction(MobileObj *object) const
{
    std::string tmp = "UpdateObj";
    Vector3D pos = object->GetPositoin_m();
    Vector3D sca = object->getScale();
    Vector3D tra = object->getTranslation();
    Vector3D rgb = object->getRgb();
    tmp += " Name=" + object->GetName();
    tmp += " Shift=(" + std::to_string(pos[0]) + ", " + std::to_string(pos[1]) + ", " + std::to_string(pos[2]) + ")";
    tmp += " Scale=(" + std::to_string(sca[0]) + ", " + std::to_string(sca[1]) + ", " + std::to_string(sca[2]) + ")";
    tmp += " Trans_m=(" + std::to_string(tra[0]) + ", " + std::to_string(tra[1]) + ", " + std::to_string(tra[2]) + ")";
    tmp += " RGB=(" + std::to_string((int)rgb[0]) + ", " + std::to_string((int)rgb[1]) + ", " + std::to_string((int)rgb[2]) + ")";
    tmp += " RotXYZ_deg=(" + std::to_string(object->GetAng_Roll_deg()) + ", " + std::to_string(object->GetAng_Pitch_deg()) + ", " + std::to_string(object->GetAng_Yaw_deg()) + ")\n";

    return tmp;
}

std::string Sender::getAddInstruction(MobileObj *object) const
{
    std::string tmp = "AddObj";
    Vector3D pos = object->GetPositoin_m();
    Vector3D sca = object->getScale();
    Vector3D tra = object->getTranslation();
    Vector3D rgb = object->getRgb();
    tmp += " Name=" + object->GetName();
    tmp += " Shift=(" + std::to_string(pos[0]) + ", " + std::to_string(pos[1]) + ", " + std::to_string(pos[2]) + ")";
    tmp += " Scale=(" + std::to_string(sca[0]) + ", " + std::to_string(sca[1]) + ", " + std::to_string(sca[2]) + ")";
    tmp += " Trans_m=(" + std::to_string(tra[0]) + ", " + std::to_string(tra[1]) + ", " + std::to_string(tra[2]) + ")";
    tmp += " RGB=(" + std::to_string((int)rgb[0]) + ", " + std::to_string((int)rgb[1]) + ", " + std::to_string((int)rgb[2]) + ")";
    tmp += " RotXYZ_deg=(" + std::to_string(object->GetAng_Roll_deg()) + ", " + std::to_string(object->GetAng_Pitch_deg()) + ", " + std::to_string(object->GetAng_Yaw_deg()) + ")\n";
    std::cout << tmp;
    return tmp;
}
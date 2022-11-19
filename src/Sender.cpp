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
    while (ShouldCountinueLooping())
    {
        if (!_pScn->IsChanged())
        {
            usleep(10000);
            continue;
        }
        _pScn->LockAccess();

        //------- Przeglądanie tej kolekcji to uproszczony przykład

        for (auto const &iterator : _pScn->getMobileObjects())
        {
            std::cout << iterator.first << std::endl;
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
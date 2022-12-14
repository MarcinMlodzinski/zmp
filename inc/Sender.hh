#pragma once

#include <unistd.h>
#include <cstring>
#include <ostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Scene.hh"
#include "Port.hh"

/*!
 * \brief Modeluje nadajnik poleceń odzwierciedlających aktualny stan sceny.
 *
 * Modeluje nadajnik poleceń odzwierciedlających aktualny stan sceny.
 * W tym celu monitoruje zmiany na scenie, a gdy je wykryje przesyła
 * informacje o aktualnej pozycji wszystkich obiektów.
 */
class Sender
{
    /*!
     * \brief Wartość tego pola decyduje o kontynuacji wykonywania wątku.
     *
     * Wartość tego pola decyduje o kontynuacji wykonywania wątku.
     * W przypadku wartości \p true, pętla wątku będzie wykonywana.
     * Natomiast wartość \p false powoduje przerwanie pętli.
     */
    volatile bool _ContinueLooping = true;
    /*!
     * \brief Deskryptor gniazda sieciowego, poprzez które wysyłane są polecenia.
     */
    int _Socket = 0;
    /*!
     * \brief Wskaźnik na scenę, które stan jest przesyłany w postaci
     *        poleceń do serwera graficzneg.
     */
    Scene *_pScn = nullptr;

public:
    /*!
     * \brief Inicjalizuje obiekt deskryptorem gniazda i wskaźnikiem
     *        na scenę, na zmianę stanu które będzie ten obiekt reagował.
     */
    Sender(Scene *pScn) : _pScn(pScn) {}

    ~Sender();

    /*!
     * Otwiera połączenie sieciowe
     * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
     *                        realizowana komunikacja sieciowa.
     */
    bool OpenConnection();

    /*!
     * \brief Wysyła napis do poprzez gniazdo sieciowe.
     *
     * Wysyła napis do poprzez gniazdo sieciowe.
     * \param[in] Sk2Server - deskryptor gniazda sieciowego, poprzez które
     *                        ma zostać wysłany napis w sensie języka C.
     * \param[in] sMesg - zawiera napis, który ma zostać wysłany poprzez
     *                    gniazdo sieciowe.
     */
    int Send(const char *sMesg);

    /*!
     * \brief Sprawdza, czy pętla wątku może być wykonywana.
     *
     * Sprawdza, czy pętla wątku może być wykonywana.
     * \retval true - pętla wątku może być nadal wykonywana.
     * \retval false - w przypadku przeciwnym.
     */
    bool ShouldCountinueLooping() const { return _ContinueLooping; }
    /*!
     * \brief Powoduje przerwanie działania pętli wątku.
     *
     * Powoduje przerwanie działania pętli wątku.
     * \warning Reakcja na tę operację nie będize natychmiastowa.
     */
    void CancelCountinueLooping() { _ContinueLooping = false; }

    /*!
     * \brief Ta metoda jest de facto treścią wątku komunikacyjnego
     *
     * Przegląda scenę i tworzy odpowiednie polecenia, a następnie
     * wysyła je do serwera.
     * \param[in] Socket - deskryptor gniazda sieciowego, poprzez które
     *                     wysyłane są polecenia.
     */
    void Watching_and_Sending();
    std::string getUpdateInstruction(MobileObj *object) const;
    std::string getAddInstruction(MobileObj *object) const;
};
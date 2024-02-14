/**
 * @file kategori.cpp
 * @brief Alle funksjoner fra Kategori-klassen
 */

#include <iostream>
#include "kategorier.h"
#include "bruktTing.h"
#include "LesData3.h"
#include <string>
#include <list>

extern Kategorier gKategoribase; ///< Globalt container-objekt med alle kategoriene.

/**
 * Funksjon som leser inn data fra fil.
 *
 * @param   innfil - Filen dataen leses inn fra.
 * @see     Kategori::settSisteNr(...)
 * @see     NyTing::hentTingId()
 * @see     BruktTing::hentTingId()
 */
void Kategori::lesFraFil(std::ifstream & innfil) {
    NyTing* temp = nullptr;
    int antallTing;
    
    // Variabel for å lagre hva slags type ting det er (Ny/Brukt)
    char type;
    innfil >> antallTing;
    innfil.ignore();

    sistNr = antallTing;

    for (int i = 0; i < antallTing; i++) {
        innfil >> type;
        innfil.ignore();
        switch(type) {
            case 'N': tingbase.push_back(temp = new NyTing(innfil));        break;
            case 'B': tingbase.push_back(temp = new BruktTing(innfil));     break;
        }
        // Oppdaterer siste nr så det blir korrekt ved opprettelse av nye
        Kategori::settSisteNr(temp->hentTingId());
    }
}

/**
 * Funksjon som skriver Kategori til fil.
 *
 * @see     NyTing::skrivTilFil(...)
 * @see     BruktTing::skrivTilFil(...)
 */
void Kategori::skrivTilFil(std::ofstream & ut) {
    ut << tingbase.size() << "\n";
    for (const auto & ting : tingbase) {
        ting->skrivTilFil(ut);
    }
}

/**
 * Funksjon som skriver data for en gitt kategori
 *
 * @see     Kategori::skrivAntall()
 * @see     NyTing::skrivData()
 * @see     BruktTing::skrivData()
 * @see     NyTing::skrivTilstand()
 * @see     BruktTing::skrivTilstand()
 */
void Kategori::skrivData() {
    Kategori::skrivAntall();
    for (auto it = tingbase.begin(); it != tingbase.end(); ++it) {
        (*it)->skrivData();
        (*it)->skrivTilstand();
    }
}


/**
 * @brief Skriver ut antall ting til salgs fra hver kategori.
 */
void Kategori::skrivAntall() {
    std::cout << "\tAntall ting til salgs: " << Kategori::tingbase.size() << std::endl;
}


/**
 * @brief Oppretter en ny ting, leser inn all data og legger bakerst i listen.
 * 
 * @param   selgersNr - nummeret til selgeren som skal selge tingen
 * @see     NyTing::lesData(...)
 * @see     Nyting::lesTilstand()
 * @see     BruktTing::lesTilstand()
 */
void Kategori::nyTing(int selgersNr) {
    char tilstand;
    NyTing* temp = nullptr;
    do{
        tilstand = lesChar("\tTilstand, (N)y eller (B)rukt");
    } while (tilstand != 'N' && tilstand != 'B');

    switch (tilstand) {
        case 'B':
            temp = new BruktTing;
            temp->lesData(sistNr+1, selgersNr);
            temp->lesTilstand();
            break;
        default:
            temp = new NyTing;
            temp->lesData(sistNr+1, selgersNr);
            break;
    }

    tingbase.push_back(temp);
    std::cout << "\tTing lagt til\n";
    Kategori::sistNr ++;
}


/**
 * @brief Endre datamedlemmer fra en ting
 * 
 * @see Kategori::skrivData()
 * @see NyTing::hentTingId()
 * @see NyTing::endre()
 */
void Kategori::endreTing() {
    Kategori::skrivData();
    bool finnes = false;
    int valg;
    
    int lavestTingId = 0; // Default verdi som vi overrider etterpå
    int hoyestTingId = 0; // Default verdi som vi overrider etterpå
    
    for (const auto & ting : tingbase) {
        if (lavestTingId == 0 && hoyestTingId == 0) {
            lavestTingId = ting->hentTingId();
            hoyestTingId = ting->hentTingId();
        }
        if (ting->hentTingId() < lavestTingId) {
            lavestTingId = ting->hentTingId();
        }
        if (ting->hentTingId() > hoyestTingId) {
            hoyestTingId = ting->hentTingId();
        }
    }
    
    if (tingbase.size() > 0) {
        valg = lesInt("\tSkriv ID-nummeret for tingen du ønsker å endre", lavestTingId, hoyestTingId);
        for (const auto & val : tingbase) {
            if (valg == val->hentTingId()) {
                val->endre();
                finnes = true;
            }
        }
        if (!finnes) {
            std::cout << "\tFinner ikke ting med ID " << valg << std::endl;
        }
    } else {
        std::cout << "\tFinnes ingen ting i denne kategorien.\n";
    }
}


/**
 * @brief Finner en ting i kategorien
 * 
 * @param   tingId - Id på tingen som skal finnes
 * @return  NyTing - peker til gitt ting om den finnes. Om ikke returneres nullptr  og en feilmelding
 * @see     NyTing::hentTingId()
 */
NyTing *Kategori::finnTing(int tingId)
{
    NyTing *ting = nullptr;
    for (auto it = tingbase.begin(); it != tingbase.end(); ++it)
    {
        if ((*it)->hentTingId() == tingId)
        {
            ting = *it;
        }
    }

    if (ting == nullptr)
    {
        std::cout << "\tFant ikke tingen\n";
    }
    return ting;
}


/**
 * @brief Fjerner en ting fra kategorien
 * 
 * @param   tingId - Id til tingen som skal fjernes.
 * @see     NyTing::hentTingId()
 */
void Kategori::fjernTing(int tingId)
{
    if (Kategori::tingbase.size() == 0) {
        std::cout << "\tFinnes ingen ting i denne kategorien.\n";
    } else {
        for (auto it = tingbase.begin(); it != tingbase.end(); ++it)
        {
            if ((*it)->hentTingId() == tingId)
            {
                delete *it;
                tingbase.erase(it);
                break;
            }
        }
    }
}

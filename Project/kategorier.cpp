/**
 * @file kategorier.cpp
 * @brief Funksjoner for Kategorier-klassen
 */

#include <iostream>
#include "kategorier.h"
#include <string>
#include "fstream"
#include "LesData3.h"
#include <cctype>
#include "kunder.h"
#include "kunde.h"
using namespace std;


extern Kategorier gKategoribase; ///< Globalt container-objekt med alle kategoriene.
extern Kunder gKundebase; ///< Globalt container-objekt med alle kundene.


/**
 * Funksjon som leser fra fil for klassen Kategorier.
 *
 * @see     Kategori::lesFraFil(...)
 */
void Kategorier::lesFraFil()
{
    ifstream innfil("KATEGORIER.DTA");
    int kategoriNr;
    Kategori* temp = nullptr;
    string navn;
    this->sisteNr = 3;
    
    if (innfil) {
        std::cout << "Leser fra 'KATEGORIER.DTA\n";
        while (innfil >> kategoriNr) {
            innfil.ignore();
            getline(innfil, navn);
            temp = new Kategori;
            
            temp->lesFraFil(innfil);
            kategoribase[navn] = temp;
            sisteNr = kategoriNr;
        }
        innfil.close();
    } else {
        cout << "Kan ikke åpne 'KATEGORIER.DTA'\n";
    }
}


/**
 * Funksjon som skriver Kategorier til fil.
 *
 * @see     Kategori::skrivTilFil(...)
 */
void Kategorier::skrivTilFil()
{
    // Variabel for å legge til nr. før Kategori i filen.
    int i = 1;
    
    ofstream utfil("KATEGORIER.DTA");
    cout << "Skriver til 'KATEGORIER.DTA\n";
    for (const auto & val : kategoribase) {
        utfil << i << " " << val.first << "\n";
        val.second->skrivTilFil(utfil);
        i++;
    }
}


/**
 * Funksjon som skriver meny for Kategorier.
 */
void Kategorier::skrivKategorierMeny() {
    cout << "Kategori-meny\n"
         << "N - Ny kategori\n"
         << "A - Skriv alle kategorier\n"
         << "S - Skriv en kategori\n"
         << "Q - tilbake\n";
}


/**
 * @brief skriver meny for ting sin handlingsmeny.
 */
void Kategorier::skrivTingMeny() {
    cout << "Kategori-meny\n"
         << "N - Ny ting\n"
         << "E - Endre en ting\n"    
         << "Q - Tilbake\n";
}


/**
 * Funksjon som hånfyrtrt menyvalg for Kategorier.
 *
 * @see     Kategorier::ny()
 * @see     Kategorier::skrivAlle()
 * @see     Kategorier::skrivEn()
 * @see     Kategorier::skrivKategorierMeny()
 */
void Kategorier::handling()
{
    char valg;
    
    do {
        Kategorier::skrivKategorierMeny();
        valg = lesChar("\n Kommando");
        
        switch (valg) {
            case 'N': Kategorier::ny();                     break;
            case 'A': Kategorier::skrivAlle();              break;
            case 'S': Kategorier::skrivEn();                break;
            default:  Kategorier::skrivKategorierMeny();    break;
        }
    } while (valg != 'Q');
}


/**
 * @brief Handlingsmeny for ting
 * 
 * @see Kategorier::nyTing()
 * @see Kategorier::endreTing()
 * @see Kategorier::skrivTingMeny()
 */
void Kategorier::tingHandling() {
    char valg;
    
    do {
        Kategorier::skrivTingMeny();
        valg = lesChar("\n Kommando");
        
        switch (valg) {
            case 'N': Kategorier::nyTing();                 break;
            case 'E': Kategorier::endreTing();              break;
            default:  Kategorier::skrivTingMeny();          break;
        }
    } while (valg != 'Q');
}


/**
 * @brief Funksjon for at en kjøper skal få kjøpt en ting.
 * 
 * @see Kunder::hentSistNr()
 * @see Kunder::hentKundebase()
 * @see Kunder::hentKundeNummer()
 * @see Kateogrier::hentKategori(...)
 * @see Kategori::skrivData()
 * @see Kategori::hentSistNr()
 * @see Kategori::finnTing(...)
 * @see Kunder::hentSelgerNr()
 * @see NyTing::kjop()
 * @see Kategori::fjernTing()
 */
void Kategorier::kjopEnTing() {
    int tingNr;
    int kjoperKundeNr = lesInt("\tKjoperens nummer", 1, gKundebase.hentSistNr());
    Kategori *kategori = nullptr;
    std::string kat_navn;
    Kunde *kjoper = nullptr;
    Kunde *selger = nullptr;
    NyTing *ting = nullptr;
    bool erTingTom = false;
    int lavestTingId = 0; // Default verdi som vi overrider etterpå
    int hoyestTingId = 0; // Default verdi som vi overrider etterpå

    // Henter kjoper
    for (auto const &kunde : gKundebase.hentKundebase())
    {
        if (kunde->hentKundeNummer() == kjoperKundeNr) {
            kjoper = kunde;
        }
    }
    // Sjekker om vi fant kjoper
    if (kjoper == nullptr) {
        std::cout << "Fant ingen kunde med kundenummeret: " << kjoperKundeNr << "\n";
    } else {
        std::string navn;
        std::cout << "\tKategoriens navn\n";
        std::getline(std::cin, navn);
        kategori = gKategoribase.hentKategori(navn, kat_navn);

        // Passser på at vi fant kategori
        if (kategori != nullptr) {
            kategori->skrivData();
            
            // Henter laveste og høyeste kategori
            for (const auto & ting : kategori->hentTingbase()) {
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

            tingNr = lesInt("\tVelg varenummer", lavestTingId, hoyestTingId);
            ting = kategori->finnTing(tingNr);
            
            // Passer på at vi finner ting
            if (ting != nullptr) {
                // Henter selger
                for (auto const &kunde : gKundebase.hentKundebase())
                {
                    if (kunde->hentKundeNummer() == ting->hentSelgerNr()) {
                        selger = kunde;
                    }
                }
                
                // Sjekker om selger og kjoper er samme
                if (kjoperKundeNr == ting->hentSelgerNr()) {
                    cout << "Kjøper kan ikke være samme som selger!\n";
                } else {
                    // Registrerer kjop
                    erTingTom = ting->kjop(kjoper, selger);
                    std::cout << "\tKjøp vellykket!\n";
                        
                    if (erTingTom) {
                        // Sletter tingen om det ikke finnes flere ting
                        std::cout << "\tTingen er tom, sletter annonsen\n";
                        kategori->fjernTing(tingNr);
                    }
                }
            }
        }
    }
}


/**
 * Oppretter en ny kategori og legger den til i datastrukturen. Tilatter ikke duplikate navn.
 */
void Kategorier::ny()
{
    bool navnEksisterer = false;
    
    cout << "Oppretter ny kategori.\n";
    Kategori* temp = new Kategori;
    string navn;
    cout << "Navn på ny kategori: ";
    getline(cin, navn);
    
    // Sjekker om navn allerede eksisterer
    for (const auto & val : kategoribase) {
        if (val.first == navn) {
            navnEksisterer = true;
            cout << "Denne kategorien finnes allerede!\n";
            break;
        }
    }
    
    // Legger til ny kategori i datastrukturen om navnet ikke finnes
    if (!(navnEksisterer)) {
        cout << "Oppretter kategorien \"" << navn << "\".\n";
        kategoribase[navn] = temp;
        sisteNr++;
    }
}


/**
 * Funksjon som skriver ut alle kategorier som er lagret i datastrukturen.
 *
 * @see Kategori::skrivAntall()
 */
void Kategorier::skrivAlle()
{
    int i = 0;
    cout << "\tAlle kategorier: \n";
    
    for (const auto & val : kategoribase) {
        cout << i+1 << ". " << val.first << " - ";
        val.second->skrivAntall();
        cout << "\n";
        i++;
    }
}


/**
 * @brief Funksjon som skriver ut alle gjenstander i en gitt kategori.
 *
 * @see Kategorier::hentKategorier(...)
 * @see Kategori::skrivData()
 */
void Kategorier::skrivEn()
{
    if (gKategoribase.kategoribase.size() == 0) {
        std::cout << "\tIngen kategorier i databasen.\n";
    } else {
        string input, navn;
        cout << "\tSkriv navn på kategori: ";
        getline(cin, input);
        
        Kategori* kat = Kategorier::hentKategori(input, navn);

        if (kat != nullptr) {
            std::cout << "\tSkriver info for " << navn << std::endl;
            kat->skrivData();
        }
    }
}


/**
 * @brief Funksjon som finner en entydig kategori
 * 
 * @param input - brukerens input
 * @param navn - navnet på kateogrien som referanseoverføres
 * @return Kategori* - peker til elementet om entydig eller nullptr
 */
Kategori* Kategorier::hentKategori(std::string input, std::string & navn)
{
    for (char &val : input) {
        val = toupper(val);
    }
    int count = 0;
    Kategori *kat = nullptr;
    for (auto it = kategoribase.begin(); it != kategoribase.end(); ++it) {
        string temp = (*it).first;
        for (char &val : temp) {
            val = toupper(val);
        }
        if (temp.find(input) == 0) {
            ++count;
            navn = (*it).first;
            kat = (*it).second;
        }
    }
    if (count == 1) {
        return kat;
    }
    else if (count > 1) {
        cout << "\tFlere kategorier matcher søket. Vennligst skriv inn et mer spesifikt søk.\n";
    }
    else {
        cout << "\tFant ingen kategorier som matcher søket.\n";
    }

    return nullptr;
}


/**
 * @brief Oppretter en ny ting  og leser inn all data, avhenging om den er 
 * brukt eller ny
 * 
 * @see Kategorier::hentKategori(...)
 * @see Kunder::hentKundebase()
 * @see Kunder::hentSistNr()
 * @see Kunde::hentKundeNummer()
 * @see Kategori::nyTing(...)
 */
void Kategorier::nyTing() {
    if (Kategorier::kategoribase.size() == 0) {
        std::cout << "Finnes ingen kategorier.\n";
    } else {
        string input, navn;
        cout << "Skriv navn på kategori: ";
        getline(cin, input);
        
        Kategori* kat = Kategorier::hentKategori(input, navn);

        if (kat != nullptr) {
            int selgers_nummer;
            Kunde* selger = nullptr;
            auto kundebase = gKundebase.hentKundebase();
            selgers_nummer = lesInt("Skriv inn selgers nummer", 1, gKundebase.hentSistNr());

            for (auto it = kundebase.begin(); it != kundebase.end(); ++it) {
                if (selgers_nummer == (*it)->hentKundeNummer()) {
                    selger = (*it);
                }
            }

            if (selger != nullptr) {
                std::cout << "\tOppretter ny ting i " << navn << std::endl;
                kat->nyTing(selgers_nummer);
            } else {
                std::cout << "\tFinner ikke selger\n";
            }
        }
    }
}


/**
 * Funksjon som skriver ut alle kategorier, og lar bruker velge en kategori hvor
 * den vil endre en av tingenes datamedlemmer.
 *
 * @see     Kategorier::hentKategori()
 * @see     Kategori::endreTing()
 */
void Kategorier::endreTing() {
    if (Kategorier::kategoribase.size() == 0) {
        std::cout << "Finnes ingen kategorier.\n";
    } else {
        Kategorier::skrivAlle();
        string input, navn;
        cout << "\nSkriv kategori du ønsker å endre ting i:\n";
        getline(cin, input);
        Kategori* kat = Kategorier::hentKategori(input, navn);
        
        if (kat != nullptr) {
            cout << "Skriver tingene i \"" << navn << "\"\n";
            kat->endreTing();
        } else {
            cout << "Finner ingen kategori med dette navnet.\n";
        }
    }
}


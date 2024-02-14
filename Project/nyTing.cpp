/**
 * @file nyTing.cpp
 * @brief Funskjoner for Kunder-klassen
 */

#include "nyTing.h"
#include "kunder.h"
#include "kunde.h"
#include "LesData3.h"
#include "kategorier.h"
#include "kategori.h"
#include "const.h"

extern Kunder gKundebase;
extern Kategorier gKategoribase;


/**
 * Constructorfunksjon som leser inn datamedlemmene til et objekt fra fil.
 *
 * @param   inn - Filen dataen leses fra.
 */
NyTing::NyTing(std::ifstream & inn) {
    inn >> tingId >> selgerNr >> antall;
    inn.ignore();
    
    getline(inn, navn);
    inn >> pris;    inn.ignore();
    getline(inn, beskrivelse);
}


/**
 * Funksjon som skriver til datamedlemmene til NyTing til fil.
 */
void NyTing::skrivTilFil(std::ofstream & ut) {
    ut << "N " << tingId << " " << selgerNr << " " << antall << "\n"
    << navn << "\n" << pris << "\n" << beskrivelse << "\n";
}


/**
 * Funksjon som skriver baseklassens datamedlemmer til fil.
 * Brukes for at BruktTing skal få riktig type skrevet til filen (B).
 */
void NyTing::skrivBruktTilFil(std::ofstream & ut) {
    ut << tingId << " " << selgerNr << " " << antall << "\n"
    << navn << "\n" << pris << "\n" << beskrivelse << "\n";
}


/**
 * @brief leser inn data for en ting.
 * 
 * @param id - tingens nye ID
 * @param selgerNr - selgers id-nummer
 */
void NyTing::lesData(int id, int selgerNr)
{
    NyTing::tingId = id;
    NyTing::selgerNr = selgerNr;

    do {
        std::cout << "\tNavn: ";
        std::getline(std::cin, NyTing::navn);
    } while (NyTing::navn == "");

    do {
        std::cout << "\tKort beskrivelse: ";
        std::getline(std::cin, NyTing::beskrivelse);
    } while (NyTing::beskrivelse == "");

    NyTing::pris = lesInt("\tPris", MINPRISTING, MAKSPRISTING);
    NyTing::antall = lesInt("\tAntall", 1, MAKSANTALL);
}


/**
 * Funksjon som spør om hva brukeren ønsker å endre ved en ting.
 *
 * @see     NyTing::skrivData()
 * @see     NyTing::endreHandler(...)
 */
void NyTing::endre()
{
    NyTing::skrivData();

    std::cout << "\t1. Navn\n";
    std::cout << "\t2. Beskrivelse\n";
    std::cout << "\t3. Pris\n";
    std::cout << "\t4. Antall\n";
    std::cout << "\t5. Avbryt\n";

    int valg = lesInt("\tValg", 1, 5);

    NyTing::endreHandler(valg);
}


/**
 * Funksjon som håndterer hva som endres i en NyTing.
 */
void NyTing::endreHandler(int valg) {
    switch (valg)
    {
    case 1:
        do
        {
            std::cout << "\tNavn: ";
            std::getline(std::cin, NyTing::navn);
        } while (NyTing::navn == "");
        break;
    case 2:
        do
        {
            std::cout << "\tKort beskrivelse: ";
            std::getline(std::cin, NyTing::beskrivelse);
        } while (NyTing::beskrivelse == "");
        break;
    case 3:
        NyTing::pris = lesInt("\tPris", MINPRISTING, MAKSPRISTING);
        break;
    case 4:
        NyTing::antall = lesInt("\tAntall", 1, MAKSANTALL);
        break;
    default:
        break;
    }
}


/**
 * Funksjon som håndterer kjøp av ting. Håndterer registrering av kjøp på kjøper og salg på selger.
 *
 * @return  antall <=0 - True/False om det er igjen noen eksemplarer av tingen.
 * @see     Kunde::registrerKjop()
 * @see     Kunde::registrerSalg()
 */
bool NyTing::kjop(Kunde *kjoper, Kunde *selger)
{
    antall -= 1;
    kjoper->registrerKjop();
    selger->registrerSalg();
    
    return antall <= 0;
}


/**
 * @brief Skriver ut all data for en ting
 */
void NyTing::skrivData()
{
  std::cout << "\tId: " << NyTing::tingId << ":\n";
  std::cout << "\t\tNavn: " << NyTing::navn << std::endl;
  std::cout << "\t\tBeskrivelse: " << NyTing::beskrivelse << std::endl;
  std::cout << "\t\tPris: " << NyTing::pris << std::endl;
  std::cout << "\t\tAntall ting til salgs: " << NyTing::antall << std::endl;
}


/**
 * @brief Skriver tilstand til produktet om det er en NyTing
 */
void NyTing::skrivTilstand() {
    std::cout << "\t\tTilstand: NY" << std::endl;
}

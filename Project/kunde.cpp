/**
 * @file kunde.cpp
 * @brief Inneholder alle funksjoner til Kunde-klassen
 */

#include "kunde.h"
#include "LesData3.h"
#include <iostream>

/**
 * @brief Leser inn alle data for en kunde
 *
 * @param kundeNummer - kundenummeret til den nye kunden
 */
void Kunde :: lesData(int kundeNummer)
{
  Kunde::kundeNr = kundeNummer;

  do {
    std::cout << "\tNavn: ";
    std::getline(std::cin, Kunde::navn);
  } while (Kunde::navn == "");

  do {
    std::cout << "\tAddresse: ";
    std::getline(std::cin, Kunde::adresse);
  } while (Kunde::adresse == "");

  do {
    std::cout << "\tE-post: ";
    std::getline(std::cin, Kunde::epost);
  } while (Kunde::epost == "");

  Kunde::tlf = lesInt("\tTlf-nummer", 10000000, 99999999);

  Kunde::tilSalgs = 0; Kunde::kjopt = 0; Kunde::solgt = 0;
}

/**
 * @brief returnerer kundenummeret til en kunde.
 * 
 * @return int - kundenummeret.
 */
int Kunde :: hentKundeNummer() {
  return Kunde::kundeNr;
}

/**
 * @brief Skriver ut knudeNr, navn og telefonnummer for en kunde.
 */
void Kunde::skrivEnkelData() {
    std::cout << "Kundenummer: " << kundeNr
        << " Navn: " << navn
        << " Telefonnummer: " << tlf << "\n";
}

/**
 * @brief Skriver alle data for en gitt kunde.
 */
void Kunde :: skrivAllData() {
    std::cout << "Kundenummer: " << kundeNr << "\n"
        << "\tNavn: " << navn << "\n"
        << "\tTelefonnummer: " << tlf << "\n"
        << "\tEpost: " << epost << "\n"
        << "\tAdresse: " << adresse << "\n"
        << "\tTilsalgs: " << tilSalgs << " Kjopt: " << kjopt << " Solgt: " << solgt << "\n";
}

/**
 * @brief Leser all info om en kunde fra fil.
 * 
 * @param innFil - filen som skal leses fra
 */
void Kunde::lesFraFil(std::ifstream &innFil) {
    getline(innFil, navn);
    getline(innFil, adresse);
    getline(innFil, epost);
    innFil >> tlf; innFil.ignore();
    innFil >> tilSalgs >> kjopt >> solgt;
}

/**
 * @brief Skriver all info om en kunde til fil
 * 
 * @param utFil - filen som skal skrives til
 */
void Kunde::skrivTilFil(std::ofstream &utFil) {
    utFil << kundeNr << "\n"
        << navn << "\n"
        << adresse << "\n"
        << epost << "\n"
        << tlf << "\n"
        << tilSalgs << " " << kjopt << " " << solgt << "\n";
}

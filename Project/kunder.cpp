/**
 * @file kunder.cpp
 * @brief Inneholder alle funksjoner til Kunder-klassen 
 */

#include "kunder.h"
#include "kunde.h"
#include "LesData3.h"
#include "const.h"
#include <iostream>
#include <list>
#include <fstream>

extern Kunder gKundebase; ///< Globalt container-objekt med alle Kundene.


/**
 * @brief Leser inne alle kunder fra KUNDER.DTA
 */
void Kunder::lesFraFil()
{
  int kundeNummer;
  Kunde* temp;
  std::ifstream innFil("KUNDER.DTA");

  // Sjekker om den klarte å åpne filen;
  if (innFil.is_open() == false) {
    std::cout << "\tKan ikke åpne KUNDER.DTA\n";
  } else {
    // Looper over hele filen og setter kundeNummer
    while (innFil >> kundeNummer) {
      innFil.ignore();
      temp = new Kunde(kundeNummer);

      // Leser data fra filen og pusher det inn i kundebasen
      temp->lesFraFil(innFil);
      Kunder::kundebase.push_back(temp);
      Kunder::sistNr = kundeNummer;
    }
  }

  // Lukker filen når vi er ferdige med den
  innFil.close();
}


/**
 * @brief Lagrer all kundedata i KUNDER.DTA
 *
 * @see   Kunde::skrivTilFil(...)
 */
void Kunder::skrivTilFil()
{
  // Åpner KUNDER.DTA i skrivemodus
  std::ofstream utFil("KUNDER.DTA");

  if (utFil.is_open() == false) {
    std::cout << "\tKan ikke åpne KUNDER.DTA\n";
  } else {
    for (auto const& kunde : kundebase) {
      // Skriver hver enkelt kunde inn i filen
      kunde->skrivTilFil(utFil);
    }
  }

  // Lukker filen når vi er ferdige med den
  utFil.close();
}


/**
 * @brief Skriver ut handlingsmenyen på skjermen
 */
void Kunder::skrivKunderMeny() {
  std::cout << "Kunde-meny\n";
	std::cout << "\t(N) Ny\n";
	std::cout << "\t(A) skriv Alle\n";
	std::cout << "\t(S) skriv en gitt kunde\n";
	std::cout << "\t(F) Fjern/slett en gitt kunde\n";
  std::cout << "\t(Q) Tilbake\n";
}


/**
 * @brief En handlingsmeny for alle Kunder sine handliger
 * 
 * @see Kunder::skrivKunderMeny()
 * @see Kunder::ny()
 * @see Kunder::skrivAlle()
 * @see Kunder::skrivEn(...)
 * @see Kunder::fjern(...)
 */
void Kunder::handling()
{
  char valg;

  do {
  Kunder::skrivKunderMeny();
  valg = lesChar("\n Kommando");
  
  switch (valg) {
    case 'N': Kunder::ny(); break;
    case 'A': Kunder::skrivAlle(); break;
    case 'S': {int kundeNrS = lesInt("\tKundenummer", 1, Kunder::sistNr); Kunder::skrivEn(kundeNrS); break;}
    case 'F': {int kundeNrF = lesInt("\tKundenummer", 1, Kunder::sistNr); Kunder::fjern(kundeNrF); break;}
    default: Kunder::skrivKunderMeny(); break;
  }
  } while (valg != 'Q');
}


/**
 * @brief Oppretter en ny kunde og legger bakerst i listen
 * 
 * @see Kunde::lesData(...)
 */
void Kunder::ny()
{
  if (Kunder::kundebase.size() < MAXKUNDER) {
    std::cout << "\tOppretter ny kunde\n";
    Kunde *temp = new Kunde;
    temp->lesData(Kunder::sistNr + 1);
    Kunder::kundebase.push_back(temp);
    Kunder::sistNr ++;
  } else {
    std::cout << "\tKundebase full.\n";
  }
}


/**
 * @brief Skriver ut alle kunder paginert på ANTALLKUNDERPERSIDE personer
 *
 * @see kunde::skrivEnkelData()
 */
void Kunder::skrivAlle()
{
  // Sjekker om det fins kunder
  if (kundebase.size() <= 0) {
    std::cout << "Ingen kunder registrert\n";
  } else {
    
    std::cout << "Siste kundenummer hittil i bruk: " << sistNr << "\n";
    std::cout << "Antall kunder i systemet: " << kundebase.size() << "\n";

    int i = 0;
    for (auto const& kunde : kundebase) {
      // Skriver dataen til kunden
      kunde->skrivEnkelData();
      
      // Sjekker om den skal vente på et tastetrykk
      if (i != 0
          && (i + 1) != kundebase.size()
          && (i + 1) % ANTALLKUNDERPERSIDE == 0) {
        lesChar("Trykk på en tast for å fortsette\n");
      }
      i++;
    }
  }
}


/**
 * @brief Skriv ut all data om en spesifikk kunde
 *
 * @param kundeNummer - Nummeret til kunden som skal skrives ut
 * @see   Kunde::hentKundeNummer(...)
 * @see   Kunde::skrivAllData(...)
 */
void Kunder::skrivEn(int kundeNummer)
{
  Kunde* funnetKunde = nullptr;
  
  for (auto const& kunde : kundebase) {
    if (kunde->hentKundeNummer() == kundeNummer) {
      funnetKunde = kunde;
    }
  }
  
  if (funnetKunde == nullptr) {
    std::cout << "Fant ingen kunde med kundenummeret: " << kundeNummer << "\n";
  } else {
    funnetKunde->skrivAllData();
  }
}


/**
 * @brief fjerner en kunde fra databasen og firgjør pekeren.
 * 
 * @param kundeNummer - nummeret til kunden som skal fjernes
 * @see   Kunde::hentKundeNummer(...)
 * @see   Kunde::skrivAllData()
 */
void Kunder::fjern(int kundeNummer)
{
  char valg;
  if (kundebase.size() > 0) {
    // lage en iterator som går gjennom til den finner brukeren og sletter alle data og deleter pekeren.
    bool check = false;
    auto it = kundebase.begin();
    for (; it != kundebase.end(); ++it) {
      if ((*it)->hentKundeNummer() == kundeNummer) {
        check = true;
        (*it)->skrivAllData();
        
        do{
          valg = lesChar("\tØnsker du å slette brukeren? (J)a eller (N)ei");
        } while (valg != 'J' && valg != 'N');
        if (valg == 'J') {
          delete *it;
          kundebase.erase(it);
          std::cout << "\tKunde nummer " << kundeNummer << " er slettet.\n";
        } else {
          std::cout << "\tKunde nummer " << kundeNummer << " ble ikke slettet.\n";
        }
        break;
      }
    }
    if (!check) {
      std::cout << "\tKundenummer " << kundeNummer << " ikke funnet.\n";
    }
    // endre kundenummer til alle de andre så de ligger i rekkefølge hele tiden?
  } else {
    std::cout << "\tIngen kunder registrert.\n";
  }
}

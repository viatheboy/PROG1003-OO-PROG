/**
 * @file kunder.h
 * @brief Header for Kunde-klassen
 */

#ifndef __KUNDER_H
#define __KUNDER_H

#include <list>
#include "kunde.h"

class Kunder {
  private:
    int sistNr;
    std::list<Kunde*> kundebase;
  public:
    void ny();
    void lesFraFil();
    void skrivTilFil();
    void handling();
    void skrivAlle();
    void skrivEn(int kundeNummer);
    void fjern(int kundeNummer);
    void skrivKunderMeny();
    int hentSistNr() { return sistNr; }
    std::list<Kunde *> hentKundebase() { return kundebase; }
};

#endif

/**
 * @file kunde.h
 * @brief Header for Kunde-klassen
 */

#ifndef __KUNDE_H
#define __KUNDE_H

#include <string>
#include <iostream>
#include <fstream>

class Kunde {
	private:
        int kundeNr;
        std::string navn;
        std::string adresse;
        std::string epost;
        int tlf;
        int tilSalgs, kjopt, solgt;
	public:
    Kunde() {}
        Kunde(int kundeNummer) { kundeNr = kundeNummer; }
        void lesFraFil(std::ifstream &innFil);
        void skrivTilFil(std::ofstream &utFil);
        void lesData(int kundeNummer);
        int hentKundeNummer();
        void skrivEnkelData();
        void skrivAllData();
        void registrerKjop() { kjopt += 1; }
        void registrerSalg() { solgt += 1; }

};

#endif

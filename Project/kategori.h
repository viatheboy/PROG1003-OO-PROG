/**
 * @file kategori.h
 * @brief Kategori-klassen
 */

#ifndef __KATEGORI_H
#define __KATEGORI_H
#include "nyTing.h"
#include <string>
#include <list>

class Kategori
{
private:
    int sistNr;
    std::list <NyTing*> tingbase;
public:
    void lesFraFil(std::ifstream & innfil);
    void skrivTilFil(std::ofstream & ut);
    void skrivData();
    void skrivAntall();
    void endreTing();
    void settSisteNr(int tingId) { sistNr = tingId; }
    void handling(char valg);
    void nyTing(int selgersNr);
    int hentSistNr() { return sistNr; }
    NyTing* finnTing(int tingId);
    std::list <NyTing*> hentTingbase() { return tingbase; }
    void fjernTing(int tingId);
};

#endif

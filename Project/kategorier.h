/**
 * @file kategorier.h
 * @brief Header fil for Kategorier-klassen
 */

#ifndef __KATEGORIER_H
#define __KATEGORIER_H
#include "kategori.h"
#include <map>

class Kategorier {
private:
    int sisteNr;
    std::map<std::string, Kategori*> kategoribase;
public:
    void lesFraFil();
    void skrivTilFil();
    void skrivKategorierMeny();
    void handling();
    void skrivTingMeny();
    void tingHandling();
    void ny();
    void skrivAlle();
    void skrivEn();
    int  finnSisteNr() { return sisteNr; };
    Kategori *hentKategori(std::string input, std::string & navn);
    void kjopEnTing();
    void nyTing();
    void endreTing();
};

#endif

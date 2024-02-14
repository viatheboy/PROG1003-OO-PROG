/**
 * @file nyTing.h
 * @brief Header for NyTing-klassen
 */

#ifndef __NYTING_H
#define __NYTING_H
#include <iostream>
#include <fstream>
#include <string>
#include "kunde.h"

class NyTing
{
private:
    int tingId, selgerNr, pris, antall;
    std::string navn, beskrivelse;
public:
    NyTing() { }
    NyTing(std::ifstream & inn);
    virtual void lesData(int id, int selgerNr);
	virtual void endre();
	virtual bool kjop(Kunde *kjoper, Kunde *selger);
	void skrivData();
	virtual void skrivTilstand();
    virtual void skrivTilFil(std::ofstream & ut);
    void skrivBruktTilFil(std::ofstream & ut);
    void virtual lesTilstand() {}
    int hentTingId() { return tingId; }
    int hentSelgerNr() { return selgerNr; }
    void endreHandler(int valg);
};

#endif

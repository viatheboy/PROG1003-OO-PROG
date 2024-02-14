/**
 * @file bruktTing.h
 * @brief Klassen BruktTing
 */

#ifndef __BRUKTTING_H
#define __BRUKTTING_H

#include "nyTing.h"
#include "enum.h"

class BruktTing : public NyTing
{
private:
  int alder;
  kvalitet kval;
public:
    BruktTing() { }
    BruktTing(std::ifstream & inn);
    virtual void skrivTilFil(std::ofstream & ut);
    virtual void lesTilstand();
    virtual void endre();
    void skrivTilstand();
};

#endif

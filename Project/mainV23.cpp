/**
 *   Hovedprogrammet for OOP-prosjektet V23 med et Miniatyr-Finn<dot>no
 *      med salg av "Leker og Spill".
 *
 *   @file     MAINV23.CPP
 *   @author   Frode Haug, NTNU
 */


#include <iostream>
#include "funksjoner.h"
#include "kunder.h"
#include "kunde.h"
#include "kategorier.h"
#include "LesData3.h"
using namespace std;


Kunder     gKundebase;    ///<  Globalt container-objekt med ALLE kundene.
Kategorier gKategoribase; ///<  Globalt container-objekt med ALLE kategoriene.


/**
 *  Hovedprogram.
 */
int main()  {
  char valg;

  gKundebase.lesFraFil();
  gKategoribase.lesFraFil();

  skrivMeny();
  valg = lesChar("\nKommando");

  while (valg != 'Q')  {
    switch(valg)  {
        case 'U': gKundebase.handling();            break;
        case 'A': gKategoribase.handling();         break;
        case 'K': gKategoribase.kjopEnTing();       break;
        case 'T': gKategoribase.tingHandling();     break;
        default:  skrivMeny();                      break;
    }
    skrivMeny();
    valg = lesChar("\nKommando");
  }

  gKundebase.skrivTilFil();
  gKategoribase.skrivTilFil();

  cout << "\n\n";
  return 0;
}

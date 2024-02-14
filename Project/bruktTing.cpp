/**
 * @file bruktTing.cpp
 * @brief Alle funksjoner for BruktTing
 */

#include "bruktTing.h"
#include "LesData3.h"
#include "const.h"
#include "enum.h"
#include <iostream>


/**
 * Constructorfunksjon som leser inn datamedlemmene til et objekt fra fil.
 *
 * @param   inn - Filen dataen leses fra.
 */
BruktTing::BruktTing(std::ifstream & inn) : NyTing(inn) {
    int k;
    inn >> alder >> k;
    inn.ignore();
    
    // Caster om til riktig tilstand.
    BruktTing::kval = static_cast<kvalitet>(k);
}


/**
 * Funksjon som skriver en BruktTings datamedlememr til fil.
 *
 * @see     NyTing::skrivBruktTilFil(...)
 */
void BruktTing::skrivTilFil(std::ofstream & ut) {
    ut << "B ";
    NyTing::skrivBruktTilFil(ut);
    ut << alder << " " << static_cast<int>(kval) << "\n";
}


/**
 * @brief Leser inn tilstanden til en brukt ting
 */
void BruktTing::lesTilstand() {
  BruktTing::alder = lesInt("\tAlder", 1, MAKSALDER);
  std::cout << "\tKvalitet:\n\t\t1. Som ny\n\t\t2. Pent Brukt\n\t\t3. Brukt\n\t\t4. Godt brukt\n\t\t5. Sliten\n";
  BruktTing::kval = static_cast<kvalitet>(lesInt("Tall", 1,5) - 1);
}


/**
 * Funksjon som spør om hva brukeren ønsker å endre ved en brukt ting.
 *
 * @see NyTing::endreHandler(...)
 */
void BruktTing::endre() {
  std::cout << "\t1. Navn\n";
  std::cout << "\t2. Beskrivelse\n";
  std::cout << "\t3. Pris\n";
  std::cout << "\t4. Antall\n";
  std::cout << "\t5. Alder\n";
  std::cout << "\t6. Tilstand\n";
  std::cout << "\t7. Avbryt\n";
  int valg = lesInt("Hva vil du endre?\n", 1, 7);

  switch (valg) {
    case 1:
    case 2:
    case 3:
    case 4:
      NyTing::endreHandler(valg);
      break;
    case 5:
      BruktTing::alder = lesInt("\tAlder", 1, MAKSALDER);
      break;
    case 6:
      std::cout << "\tKvalitet:\n\t\t1. Som ny\n\t\t2. Pent Brukt\n\t\t3. Brukt\n\t\t4. Godt brukt\n\t\t5. Sliten\n";
      BruktTing::kval = static_cast<kvalitet>(lesInt("Tall", 1, 5) - 1);
      break;
    default:
      break;
  }
}


/**
 * @brief Skriver tilstanden om tingen er en BruktTing
 */
void BruktTing::skrivTilstand() {
    std::cout << "\t\tTilstand: BRUKT" << std::endl;
    std::cout << "\t\tAlder: " << BruktTing::alder << std::endl;
    switch(kval) {
      case SomNy:
        std::cout << "\t\tKvalitet: Som ny" << std::endl;
        break;
      case PentBrukt:
        std::cout << "\t\tKvalitet: Pent brukt" << std::endl;
        break;
      case Brukt:
        std::cout << "\t\tKvalitet: Brukt" << std::endl;
        break;
      case GodtBrukt:
        std::cout << "\t\tKvalitet: Godt brukt" << std::endl;
        break;
      default:
        std::cout << "\t\tKvalitet: Sliten" << std::endl;
        break;
    }
}

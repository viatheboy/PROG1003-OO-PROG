/**
 * @file oppg9.cpp
 * 
 * Program som tar inn dato, enten som parameter eller som bruker input.
 * Sjekker så om hvilken dato som kommer først, eller om datoene er identiske. 
 * 
 */

#include <iostream>
#include <string>
#include <iomanip>
#include "LesData2.h"
using namespace std;

class Dato {
    private:
        int dag, maaned, aar;
    public:
        // Initialiserer uten gitte parametere
        Dato() {
            dag = 1;
            maaned = 1;
            aar = 2000;
        }

        // Initialiserer gitt parametere
        Dato(int d, int m, int a) {
            dag = d;
            maaned = m;
            aar = a;
        }

        // Leser inn data fra brukeren
        void lesData() {
            dag =       lesInt("Dag", 1, 30);
            maaned =    lesInt("Måned", 1, 12);
            aar =       lesInt("År", 1923, 2023);
        }

        // Skriver ut datoen
        void skrivData() {
            cout   << setw(2) << setfill('0') << dag 
            << "/" << setw(2) << setfill('0') << maaned 
            << "-" << aar;
        }

        // Returnerer om det er samme år
        bool sammeAar(const Dato dato) {
            if (aar == dato.aar) {
                return true;
            } else {
                return false;
            }
        }

        // Returnerer om det er samme dag
        bool sammeAarsdag(const Dato dato) {
            if (maaned == dato.maaned && dag == dato.dag) {
                return true;
            } else {
                return false;
            }
        }

        // Returnerer om datoen kommer før annen dato
        bool tidligereEnn(const Dato dato) {
            if (aar < dato.aar) {
                return true;
            } else if (aar > dato.aar) {
                return false;
            } else {
                if (maaned < dato.maaned) {
                    return true;
                } else if (maaned > dato.maaned) {
                    return false;
                } else {
                    if (dag < dato.dag) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        }


};

/**
 * Hovedprogram 
 */
int main() {
    Dato dato1(12, 2, 1995),
        dato2;

    dato2.lesData();

    dato1.skrivData(); cout << "\n";
    dato2.skrivData(); cout << "\n";
    cout << "Samme år: ";
    cout << ((dato1.sammeAar(dato2)) ? "True" : "False") << "\n";
    cout << "Samme årsdag: ";
    cout << ((dato1.sammeAarsdag(dato2)) ? "True" : "False") << "\n";
    
    if (dato1.sammeAarsdag(dato2) && dato1.sammeAar(dato2)) {
        cout << "Datoene er identiske!\n";
    } else if (dato1.tidligereEnn(dato2))
    {
        dato1.skrivData();
        cout << " er tidligere enn "; 
        dato2.skrivData();
        cout << "\n";
    } else {
        dato2.skrivData(); 
        cout << " er tidligere enn ";
        dato1.skrivData(); 
        cout << "\n"; 
    }

    return 0;

}
/**
 * @file oppg11.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <string>
#include <iomanip>
#include "LesData2.h"
using namespace std;

class Posisjon {
    private:
        int grad, minutt, sekund;
        char retning;
    public:
        Posisjon() {
            grad = 0;
            minutt = 0;
            sekund = 0;
        }

        void lesData(int gr, char r1, char r2) {
            char buffer;
            grad = lesInt("Grad", 0, gr);
            minutt = lesInt("Minutt", 0, 59);
            sekund = lesInt("Sekund", 0, 59);

            do {            
                cout << "Retning (" << r1 << ',' << r2 << "):  ";
                retning = lesChar("");
            } while (retning != r1  &&  retning != r2);
            
        }

        void skrivData() {
            cout << grad << "°" << minutt << "'" << sekund << '"' << retning << "\n";
        }
};

class Skip {
    private: 
        int nr;
        string navn;
        Posisjon breddegrad;
        Posisjon lengdegrad;
    public:
        Skip(int n, string na) {
            nr = n;
            navn = na;
        }

        void lesData() {
            breddegrad.lesData(90, 'N', 'S');
            lengdegrad.lesData(180, 'E', 'W');
        }

        void skrivData() {
            cout << "Nr: " << nr << "\nNavn: " << navn << "\nBreddegrad: ";
            breddegrad.skrivData();
            cout << "\nLengdegrad: ";
            lengdegrad.skrivData();
            cout << "\n";
        }
};

/**
 * Hovedprogram 
 */
int main() {

    Skip skip1(1, "Brennevin"), skip2(2, "Hedvig"), skip3(3, "Skiblander");

    skip1.lesData();
    skip2.lesData();
    skip3.lesData();

    skip1.skrivData();
    skip2.skrivData();
    skip3.skrivData();


    return 0;
}

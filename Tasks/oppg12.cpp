/**
 * @file oppg12.cpp
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
#include <vector>
#include "LesData2.h"
using namespace std;

class Kunde {
    private:
        string navn;
        vector <float>* kontoer;    // peker til kontoer og deres beløp
    public:
        Kunde(const int n) {
            kontoer = new vector <float>(n);
            for (int i = 1; i < n; i++)
                (*kontoer)[i] = 0.0F;
        }

        ~Kunde() {
            delete kontoer;
        }

        void lesData() {
            cout << "Kundens navn: ";
            getline(cin, navn);

            for (int i = 0; i < kontoer->size(); i++) {
                cout << "Beløp på konto nr. " << i+1 << "\n";
                (*kontoer)[i] = lesFloat("", 0, 1000000);
            }
        }

        void skrivData() {
            cout << "Kundens navn: " << navn << "\n";
            for (int i = 0; i < kontoer->size(); i++) {
                cout << "Beløp på konto nr." << i+1 << ": ";
                cout << (*kontoer)[i] << "\n";
            }
        }
};

vector <Kunde*> gKundene;

int main() {

    char valg;
    int antall;
    Kunde* nyKunde;

    do {
        cout << "Kunde nr. " << gKundene.size()+1 << "\n";
        antall = lesInt("Antall kontoer for denne kunden", 1, 20);

        nyKunde = new Kunde(antall);
        nyKunde->lesData();
        gKundene.push_back(nyKunde);

        valg = lesChar("Registrere ny kunde? (J/N)");
    } while (valg != 'N');

    for (int i = 0; i < gKundene.size(); i++) {
        cout << "\nKunde nr. " << i+1 << "\n";
        gKundene[i]->skrivData();
        delete gKundene[i];
    }
    gKundene.clear();

    cout << "\n\n";

    return 0;

}
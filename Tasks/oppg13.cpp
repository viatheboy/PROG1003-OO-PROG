/**
 * @file oppg13.cpp
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

class Publikasjon {
    private:
        string navn;
        int aar;
    public:
        void lesData() {
            cout << "Navn på publikasjon: ";
            getline(cin, navn);
            aar = lesInt("År", 1500, 2023);
        }

        void skrivData() {
            cout << "Navn: " << navn << "\nUtgivelsesår: " << aar << "\n";
        }
};

class Bok : public Publikasjon {
    private:
        string forfatter, ISBN;
        float pris;
    public:
        void lesData() {
            cout << "Leser boks data:\n";
            //Publikasjon::lesData();
            cout << "Forfatter: ";
            getline(cin, forfatter);

            cout << "ISBN: ";
            getline(cin, ISBN);

            pris = lesFloat("Pris", 20, 1000);
        }

        void skrivData() {
           // Publikasjon::skrivData();
            cout << "Forfatter: " << forfatter 
            << "\nISBN: " << ISBN << "\nPris: " << pris << "\n";
        }
};

class Blad : public Publikasjon {
    private:
        int nummer, ukeNr, aarsAbonnement;
    public:
        void lesData() {
            cout << "Leser boks data:\n";
            cin.ignore();
           // Publikasjon::lesData();
            nummer = lesInt("Nummer", 1, 1000);
            ukeNr = lesInt("Ukenummer", 1, 52);
            aarsAbonnement = lesInt("Årsabonnement", 1, 100);
        }

        void skrivData() {
           // Publikasjon::skrivData();
            cout << "Nummer: " << nummer 
            << "\nUkenummer: " << ukeNr 
            << "\nÅrsabonnement" << aarsAbonnement << "\n";
        }
};

int main() {    

    Publikasjon publik1;
    Bok bok1;
    Blad blad1;

    cin.ignore();
    publik1.lesData();
    bok1.lesData();
    blad1.lesData();

    publik1.skrivData();

    cout << "*************************************";
    cout << "\nNB NB NB NB NB NB NB NB NB NB NB NB";
    cout << "\nLinjeskift tabulator tabulator char\narray tabulator linjeskift oblig";
    cout << "\n************************************";

    bok1.skrivData();

    cout <<"\n\nBle for mye å skrive tabulator oblig\n\n";

    blad1.skrivData();

    return 0;
}
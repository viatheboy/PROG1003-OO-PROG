#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "LesData2.h"
using namespace std;

struct Kamp {
    string  hjemmeNavn, 
            borteNavn;
    int     hjemmeMål, 
            borteMål;
};

void skrivMeny();
void kampLesData(Kamp & kamp);
void kampSkrivData(const Kamp* kamp);

vector <Kamp*> gKampene;

int main() {

    char valg;
    int antallKamper = 0;
    Kamp* nyKamp;

    do {
        cout << "Legg til kamp nr. " << antallKamper+1 << "\n";
        nyKamp = new Kamp;
        kampLesData(*nyKamp);
        antallKamper++;
        gKampene.push_back(nyKamp);

        cout << "Legge til kamp? (Y/N)\n";
        cin >> valg;
        cin.ignore();
    } while (toupper(valg) != 'N');

    for (int i = 0; i < gKampene.size(); i++) {
        cout << "\nKamp nr: " << i+1 << "\n";
        kampSkrivData(gKampene[i]);
    }

    // Sletter alle kampene
    for (int i = 0; i < gKampene.size(); i++) {
        delete gKampene[i];
    }
    gKampene.clear();

    return 0;
}

void kampLesData(Kamp & kamp) {
    cout << "Hjemmelag: ";
    getline(cin, kamp.hjemmeNavn);
    cout << "Hjemmelag antall mål: ";
    cin >> kamp.hjemmeMål;  cin.ignore();

    cout << "Bortelag: ";
    getline(cin, kamp.borteNavn);
    cout << "Bortelag antall mål: ";
    cin >> kamp.borteMål; cin.ignore();
    
}

void kampSkrivData(const Kamp* kamp) {
    cout << "Hjemmelag: " << kamp->hjemmeNavn;
    cout << "\nBortelag: " << kamp->borteNavn;
    cout << "\nStilling: " << kamp->hjemmeMål 
         << " - " << kamp->borteMål << "\n";
}

#include <iostream>
#include <string>
#include <vector>
#include "LesData2.h"
using namespace std;

char lesValg() {
    char valg;
    do {
        cout << "Legge til et nytt kjøretøy?\n(J)a\n(N)ei" << endl;
        cin >> valg;
        cin.ignore(MAXCHAR, '\n');
        valg = toupper(valg);
    } while (valg != 'J' && valg != 'N'); 
    return valg;   
}

class Kjøretøy {
    private:
        string registreringsNr;  
    public: 
        virtual void lesData() {
            cout << "Registreringsnr: ";
            getline(cin, registreringsNr);
        }
        virtual void skrivData() { 
            cout << "Registreringsnr: " << registreringsNr << endl; }
        virtual bool tomt() = 0;
};


class Bil : public Kjøretøy {
    private:
        int antPassasjerer;
    public: 
        virtual void lesData() {
            Kjøretøy::lesData();
            antPassasjerer = lesInt("Antall passasjerer", 0, 8);
        }
        virtual void skrivData() {
            Kjøretøy::skrivData();
            cout << "Antall passasjerer: " << antPassasjerer << endl;
        }
        virtual bool tomt() {
            return (antPassasjerer);
        }
};


class Vogntog : public Kjøretøy {
    private:
        float tonnLast;
    public:
        virtual void lesData() {
            Kjøretøy::lesData();
            tonnLast = lesFloat("Antall tonn", 0, 60);
        }
        virtual void skrivData() {
            Kjøretøy::skrivData();
            cout << "Antall tonn: " << tonnLast << endl;
        }
        virtual bool tomt() {
            return (tonnLast);
        }
};

int main() {

    vector <Kjøretøy*> gKjøretøyene;
    char valg;

    valg = lesValg();

    while (valg == 'J') {
        Kjøretøy* kjøretøyPeker;
        do {
            cout << "(B)il eller (V)ogntog? ";
            cin >> valg;    cin.ignore(MAXCHAR, '\n');
            valg = toupper(valg);
            if (valg == 'B') {
                kjøretøyPeker = new Bil;
                kjøretøyPeker->lesData();
                gKjøretøyene.push_back(kjøretøyPeker);
            } else if (valg == 'V') {
                kjøretøyPeker = new Vogntog;
                kjøretøyPeker->lesData();
                gKjøretøyene.push_back(kjøretøyPeker);
            } else {
                cout << "Ugyldig tegn.\n";
            }
        } while (valg != 'B' && valg != 'V');

        valg = lesValg(); 
    }

    cout << "Antall registrerte kjøretøy: " << gKjøretøyene.size() << "\n\n";
    cout << "Alle registrerte kjøretøy: \n";
    for (int i = 0; i < gKjøretøyene.size(); i++) {
        gKjøretøyene[i]->skrivData();
        cout << endl;
    }

    cout << "Indeks til alle tomme kjøretøy: \n";
    for (int i = 0; i < gKjøretøyene.size(); i++) {
        if (!gKjøretøyene[i]->tomt()) {
            cout << i << endl;
        }
    }

    for (int i = 0; i < gKjøretøyene.size(); i++) {
        delete gKjøretøyene[i];
    }
    gKjøretøyene.clear();

    return 0;
}
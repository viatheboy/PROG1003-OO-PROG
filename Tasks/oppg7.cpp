#include <iostream>
#include <string>
#include <iomanip>
#include "LesData2.h"
using namespace std;

struct Klokkeslett {
    int time, 
    minutt, 
    sekund;
};

void les(string & s);
void les(Klokkeslett & klokkeslett);
void skriv(const Klokkeslett klokkeslett);

int main() {

    string strenger[3];
    Klokkeslett klokker[3];

    // Leser inne tre strenger
    for (int i = 0; i < 3; i++) {
        cout << "Tekst nr. " << i+1 << "\n";
        les(strenger[i]);
    }

    // Leser inn tre tidspuntker
    for (int i = 0; i < 3; i++) {
        cout << "Tid nr. " << i+1 << "\n";
        les(klokker[i]);
    }

    // Skriver ut de tre strengene
    for (int i = 0; i < 3; i++) {
        cout << strenger[i] << "\n";
    }

    // Skriver ut de tre tidspunktene
    for (int i = 0; i < 3; i ++) {
        skriv(klokker[i]);
    }

    return 0;
}

void les(string & s) {
    do {
        cout << "Less in en hel tekst: ";
        getline(cin, s);
    } while (s.length() == 0);
}

void les(Klokkeslett & klokkeslett) {
    klokkeslett.time    = lesInt("Time", 0, 24);
    klokkeslett.minutt  = lesInt("Minutt", 0, 60);
    klokkeslett.sekund  = lesInt("Sekund", 0, 60);
}

void skriv(const Klokkeslett klokkeslett) {
    cout << "Tiden er: " << klokkeslett.time << ":" << klokkeslett.minutt << ":" << klokkeslett.sekund << "\n";
}
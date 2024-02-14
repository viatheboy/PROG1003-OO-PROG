/**
 * @file oblig1.cpp
 * @author Steffen S. Martinsen  (steffema@stud.ntnu.no) 
 * @version 0.1
 * @date 2023-02-01
 * 
 * Program som holder orden på en students faste gjøremål hver uke. 
 * Programmet kan lese inn et gjøremål, skrive ut opplysninger om et gjøremål,
 * og slette gjøremålene etter bruk.
 * 
 * 
 * NB: Ikke komplett program, se PDF fil for fullstendig oppgave. 
 */
#include <iostream>
#include <string>
#include <vector>
#include "LesData2.h"
using namespace std;

const vector <string> UKEDAG{"Man", "Tirs", "Ons", "Tors", "Fre", "Lor", "Son"};

struct Gjøremål {
    string  beskrivelse,    // Beskrivelse av gjøremålet.
            ukedag;         // Ukedagen det skjer. 
    float   tid;            // Tiden det tar (ikke klokkeslett).
};

vector <Gjøremål*> gGjøremålene;    ///< Oversikt over alle gjøremålene.

void fjernAlleGjøremål();
void fjernEttGjøremål();
void gjøremålLesData(Gjøremål & gjøremål);
void gjøremålSkrivData(const Gjøremål* gjøremål);
void nyttGjøremål();
void skrivAlleGjøremål(const string dag = "Alle");
void skrivEnDagsGjøremål();
void skrivMeny();

int main() {
    char kommando;

    skrivMeny();
    kommando = lesChar("\nKommando");

    while (kommando != 'Q') {
        switch (kommando) {
            case 'N': nyttGjøremål();           break;
            //case 'A': skrivAlleGjøremål();      break;
            case 'D': skrivEnDagsGjøremål();    break;
            case 'F': fjernEttGjøremål();       break;
            default:  skrivMeny();              break;
        }
        kommando = lesChar("\nKommando");
    }

    fjernAlleGjøremål();

    return 0;
}

/**
 * Fjerner alle gjøremålene.
 */
void fjernAlleGjøremål() {

}

/**
 * Fjernet ett enkelt gjøremål.
 */
void fjernEttGjøremål() {

}

/**
 * Leser inn data for et gjøremål.
 * 
 * @param gjøremål - gjøremålet det leses inn data for.
*/
void gjøremålLesData(Gjøremål & gjøremål) {
    int ukedag;
    cout << "Beskriv gjøremålet:\n";
    getline(cin, gjøremål.beskrivelse);

    ukedag = lesInt("Ukedag", 1, 7);
    gjøremål.ukedag = UKEDAG[ukedag-1];

    // 0 til 60 mimnutter. 
    gjøremål.tid = lesFloat("Tid gjøremålet vil ta", 0, 60);
}

/**
 * Skriver ut data for et gjøremål.
 * 
 * @param gjøremål - gjøremålet det skrives ut data for.
 */
void gjøremålSkrivData(const Gjøremål* gjøremål) {

}

/**
 * 
 */
void nyttGjøremål() {
    Gjøremål* nyttGjøremål = new Gjøremål;     
    cout << "Nytt gjøremål:\n";
    gjøremålLesData(*nyttGjøremål);
    gGjøremålene.push_back(nyttGjøremål);     
}

/**
 * 
 
void skrivAlleGjøremål(const string dag = "Alle") {

}
*/

/**
 * 
 */
void skrivEnDagsGjøremål() {

}

/**
 * Menyen brukt i main.
 */
void skrivMeny() {
    cout << "\nVennligst velg en kommando:\n\n"
         << "N = Nytt gjøremål\n"
         << "A = Skriv ut alle gjøremål\n"
         << "D = Skriv ut gjøremål for en dag\n"
         << "F = Fjern ett gjøremål\n";
}
#include <iostream>
#include <string>
#include "LesData2.h"
#include 
using namespace std;

class Publikasjon {
    private:
        string tittel;
        float pris;
};

class Bok : public Publikasjon {
    private: 
        string forfatter;
        int antallSider;
    public: 
        Publikasjon()
};

class Magasin : public Publikasjon {
    private:
        int aar, volum;
};

int main() {


    return 0;
}
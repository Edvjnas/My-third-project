#include "mylib.h"
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main() {
    //Studentas studentas;
    //Zmogus zmogus;
        int s;
        cout << "Pasirinkite konteinerio tipa (1 - vector, 2 - list): ";
    int containerType;
    cin >> containerType;
        cout << "Ar norite nuskaityti is failo ir skaiciuoti laika?(Rasykite 2, jei taip, ir 1, jei ne)"<< endl;
        cin >> s;
    if (s == 1 && containerType == 1){
        vector<Studentas> studentai;
        IvestiDuomenis(studentai);
    }
    if (s == 2 && containerType == 1) {
        vector<Studentas> studentai;
        Testavimas(studentai);
    }
    if (s == 1 && containerType == 2){
        list<Studentas> studentai;
        IvestiDuomenis(studentai);
    }
    if (s == 2 && containerType == 2) {
        list<Studentas> studentai;
        Testavimas(studentai);
    }

    return 0;
}



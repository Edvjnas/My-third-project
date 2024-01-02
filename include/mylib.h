#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
/*
struct Studentas {
    string vardas;
    string pavarde;
    vector<int> namuDarbai;
    int egzaminas;
    double galutinisBalas, galutinisBalasM;
};*/

class Zmogus {
public:
    virtual ~Zmogus() {}

    virtual const std::string& GetVardas() const = 0;
    virtual const std::string& GetPavarde() const = 0;
};

class Studentas : public Zmogus {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> namuDarbai;
    int egzaminas;
    double galutinisBalas, galutinisBalasM;

    friend std::ostream& Failas(std::ostream& out, const Studentas& studentas);
    friend std::ostream& Ekranas(std::ostream& out, const Studentas& studentas);
    friend std::istream& Rankinis(std::istream& in, Studentas& studentas);


public:
    Studentas() : egzaminas(0), galutinisBalas(0.0), galutinisBalasM(0.0) {}
    Studentas(const std::string& vardas, const std::string& pavarde, const std::vector<int>& namuDarbai, int egzaminas)
        : vardas(vardas), pavarde(pavarde), namuDarbai(namuDarbai), egzaminas(egzaminas),
          galutinisBalas(0.0), galutinisBalasM(0.0) {}

    const std::string& GetVardas() const override {
        return vardas;
    }

    const std::string& GetPavarde() const override {
        return pavarde;
    }
    void SetVardas(const std::string& newVardas) {
        vardas = newVardas;
    }

    void SetPavarde(const std::string& newPavarde) {
        pavarde = newPavarde;
    }

    const std::vector<int>& GetNamuDarbai() const {
        return namuDarbai;
    }

    void AddNamuDarbas(int pazymys) {
        namuDarbai.push_back(pazymys);
    }

    void ClearNamuDarbai() {
        namuDarbai.clear();
    }

    void SetNamuDarbai(const std::vector<int>& newNamuDarbai) {
        namuDarbai = newNamuDarbai;
    }

    int GetEgzaminas() const {
        return egzaminas;
    }

    void SetEgzaminas(int newEgzaminas) {
        egzaminas = newEgzaminas;
    }

    double GetGalutinisBalas() const {
        return galutinisBalas;
    }

    void SetGalutinisBalas(double newGalutinisBalas) {
        galutinisBalas = newGalutinisBalas;
    }

    double GetGalutinisBalasM() const {
        return galutinisBalasM;
    }

    void SetGalutinisBalasM(double newGalutinisBalasM) {
        galutinisBalasM = newGalutinisBalasM;
    }

    Studentas(const Studentas& kitas)
        : vardas(kitas.vardas), pavarde(kitas.pavarde), namuDarbai(kitas.namuDarbai),
          egzaminas(kitas.egzaminas), galutinisBalas(kitas.galutinisBalas),
          galutinisBalasM(kitas.galutinisBalasM) {}

    Studentas& operator=(const Studentas& kitas) {
        if (this != &kitas) {
            vardas = kitas.vardas;
            pavarde = kitas.pavarde;
            namuDarbai = kitas.namuDarbai;
            egzaminas = kitas.egzaminas;
            galutinisBalas = kitas.galutinisBalas;
            galutinisBalasM = kitas.galutinisBalasM;
        }
        return *this;
    }

    ~Studentas() {}
};

template <typename T>
double SkaiciuotiGalutiniBalaM(const T& studentas);

template <typename T>
double SkaiciuotiGalutiniBala(const T& studentas);

template <typename T>
bool SortVardas(const T& a, const T& b);

template <typename T>
int NamuDarbuSk(const string& pav);


void klaida(int &a);

void klaida1(int &a);

void klaida2(int &a);


void klaida3(int &a);

template <typename T>
void klaida4(T &a);

template <typename T>
void klaida5(T &a);

template <typename T>
void IvestiDuomenis(T& studentai);

template <typename T>
void SpausdintiRezultatus(const T& studentai);

template <typename T>
void SpausdintiStudentus(const T& studentai, const string& failoPavadinimas);

template <typename T>
pair<T, T> RikiuotiStudentus(const T& studentai);

vector<Studentas> GeneruotiStudentus(int studentuSkaicius, const string& failoPavadinimas, int namuDarbuSkaicius);

template <typename T>
string GeneruotiVarda(int a);

template <typename T>
string GeneruotiPavarde(int a);

template <typename T>
void FailoNuskaitymas(const string& failoPavadinimas, T& studentai, int namuDarbuSkaicius);

template <typename T>
bool sortDidejant(const T& a, const T& b);

template <typename T>
bool sortMazejant(const T& a, const T& b);

template <typename T>
void Testavimas (T& studentai);

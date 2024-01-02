#include "mylib.h"
using namespace std;
std::ostream& Failas(ostream& out, const Studentas& studentas) {
    out << "Vardas: " << studentas.vardas << ", Pavarde: " << studentas.pavarde << endl;
    out << "Namu darbai: ";
    for (int nd : studentas.namuDarbai) {
        out << nd << " ";
    }
    out << endl;
    out << "Egzaminas: " << studentas.egzaminas << endl;
    out << "Galutinis balas: " << studentas.galutinisBalas << endl;
    out << "Galutinis balas (Mediana): " << studentas.galutinisBalasM << endl;
    return out;
}

std::ostream& Ekranas(ostream& cout, const Studentas& studentas) {
    cout << "Vardas: " << studentas.vardas << ", Pavarde: " << studentas.pavarde << endl;
    cout << "Namu darbai: ";
    for (int nd : studentas.namuDarbai) {
        cout << nd << " ";
    }
    cout << endl;
    cout << "Egzaminas: " << studentas.egzaminas << endl;
    cout << "Galutinis balas: " << studentas.galutinisBalas << endl;
    cout << "Galutinis balas (Mediana): " << studentas.galutinisBalasM << endl;
    return cout;
}

std::istream& Rankinis(std::istream& in, std::vector<Studentas>& studentai) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(1, 10);

    Studentas naujasStudentas;
    std::string vardas, pavarde;
    std::cout << "Iveskite studento varda: ";
    in >> vardas;
    naujasStudentas.SetVardas(vardas);

    std::cout << "Iveskite studento pavarde: ";
    in >> pavarde;
    naujasStudentas.SetPavarde(pavarde);

    naujasStudentas.ClearNamuDarbai();

    int nd;
    std::cout << "Iveskite namu darbu tarpinius rezultatus (-1, jei baigete ir -2, jei norite, kad namu darbu balai butu sugeneruoti atsitiktinai): ";
    while (true) {
        in >> nd;
        klaida(nd);
        if (nd == -1) {
            break;
        }
        if (nd == -2){
            int n=0;
            std::cout << "Iveskite kiek namu darbu balu dar sugeneruoti: " << std::endl;
            in >> n;
            klaida3(n);
            for (int i = 1; i <= n; i++){
                nd = distribution(mt);
                naujasStudentas.AddNamuDarbas(nd);
                std::cout << "(" << nd << ")" << std::endl;
            }
            break;
        }
        naujasStudentas.AddNamuDarbas(nd);
    }

    int egzaminas;
    std::cout << "Iveskite egzamino rezultata (-2, jei norite, kad ji sugeneruotu atsitiktinai): ";
    in >> egzaminas;
    naujasStudentas.SetEgzaminas(egzaminas);
    if(naujasStudentas.GetEgzaminas() == -2){
        naujasStudentas.SetEgzaminas(distribution(mt));
        std::cout << "(" << naujasStudentas.GetEgzaminas() << ")" << std::endl;
    }

    naujasStudentas.SetGalutinisBalas(SkaiciuotiGalutiniBala(naujasStudentas));
    naujasStudentas.SetGalutinisBalasM(SkaiciuotiGalutiniBalaM(naujasStudentas));

    studentai.push_back(naujasStudentas);

    return in;
}


template <typename T>
    bool sortDidejant(const T& a, const T& b) {
    return a.GetGalutinisBalas() < b.GetGalutinisBalas();
}
    template <typename T>
    bool sortMazejant(const T& a, const T& b) {
        return a.GetGalutinisBalas() > b.GetGalutinisBalas();
}
template <typename T>
double SkaiciuotiGalutiniBalaM(const T& studentas) {
    if (studentas.GetNamuDarbai().empty()) {
        return studentas.GetEgzaminas() * 0.6;
    }
    vector<int> namuDarbaiSorted = studentas.GetNamuDarbai();
    sort(namuDarbaiSorted.begin(), namuDarbaiSorted.end());
    double namuDarbuMediana = 0.0;
    int n = namuDarbaiSorted.size();
    if (n % 2 == 0){
        int mid1 = namuDarbaiSorted[n/2];
        int mid2 = namuDarbaiSorted[(n/2)-1];
        namuDarbuMediana = (mid1 + mid2) / 2;
    }
    else {
        namuDarbuMediana = namuDarbaiSorted[n/2];
    }

    return 0.4 * namuDarbuMediana + 0.6 * studentas.GetEgzaminas();
}
template <typename T>
double SkaiciuotiGalutiniBala(const T& studentas) {
    if (studentas.GetNamuDarbai().empty()) {
        return studentas.GetEgzaminas() * 0.6;
    }
    double namuDarbuVidurkis = 0.0;
    for (int nd : studentas.GetNamuDarbai()) {
        namuDarbuVidurkis =namuDarbuVidurkis + nd;
    }
    namuDarbuVidurkis = namuDarbuVidurkis / studentas.GetNamuDarbai().size();

    return 0.4 * namuDarbuVidurkis + 0.6 * studentas.GetEgzaminas();
}
template <typename T>
bool SortVardas(const T& a, const T& b) {
    return a.GetVardas() < b.GetVardas();
}

int NamuDarbuSk(const string& pav){
    //std::istringstream InputStringStream(pav);
    std::stringstream ss(pav);
            std::vector<string> zodziai;
            std::string zodis;
            while (ss >> zodis) {
                zodziai.push_back(zodis);
                }
            int ndsk= zodziai.size()-3;
    return ndsk;
}

void klaida(int &a){
    do{
        try{
                    if (cin.fail()) {
                            throw runtime_error("Ivedete ne sveikaji skaiciu. ");
                    }
                    if (a < -2 || a > 10) {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
        }
        catch (const runtime_error& e){
                    cout << e.what();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Veskite duomenis dar karta: ";
                    cin >> a;
                }
        }
        while (cin.fail() == true || a < -2 || a > 10);
    }

    int klaida1(int a) {
    do {
        try {
            if (cin.fail()) {
                throw runtime_error("Ivedete ne sveikaji skaiciu. ");
            }
            if (a < -2 || a > 10 || a == -1) {
                throw runtime_error("Ivedete netinkamus duomenis. ");
            }
        } catch (const runtime_error& e) {
            cout << e.what();
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Veskite duomenis dar karta: ";
            cin >> a;
        }
    } while (cin.fail() == true || a == -1 || a > 10 || a < -2);

    return a;
}

    void klaida2(int &a){
    do{
        try{
                    if (cin.fail()) {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
                    if (a < 1 || a > 2) {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
        }
        catch (const runtime_error& e){
                    cout << e.what();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Veskite duomenis dar karta (1 arba 2): ";
                    cin >> a;
                }
        }
        while (cin.fail() == true || a < 1 || a > 2);
    }

     void klaida3(int &a){
    do{
        try{
                    if (cin.fail() || a < 0) {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
        }
        catch (const runtime_error& e){
                    cout << e.what();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Veskite duomenis dar karta: ";
                    cin >> a;
                }
        }
        while (cin.fail() == true || a < 0);
    }

    void klaida4(string &a){
    do{
        try{
                    if (a != "taip" && a != "ne" && a != "Taip" && a != "Ne" && a != "TAIP" && a != "NE") {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
        }
        catch (const runtime_error& e){
                    cout << e.what();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Veskite duomenis dar karta: ";
                    cin >> a;
                }
        }
        while (a != "taip" && a != "ne" && a != "Taip" && a != "Ne" && a != "TAIP" && a != "NE");
    }

    void klaida5(string &a){
    do{
        try{
                    if (a != "Vidurkis" && a != "VIDURKIS" && a != "vidurkis" && a != "Mediana" && a != "mediana" && a != "MEDIANA") {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
        }
        catch (const runtime_error& e){
                    cout << e.what();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Veskite duomenis dar karta: ";
                    cin >> a;
                }
        }
        while (a != "Vidurkis" && a != "VIDURKIS" && a != "vidurkis" && a != "Mediana" && a != "mediana" && a != "MEDIANA");
    }
template <typename T>
void IvestiDuomenis(T& studentai) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(1, 10);
     int s;
        cout << "Norite pazymius suvesti ar nuskaityti juos is failo?(Rasykite 1, jei norite pazymius suvesti, ir 2, jei norite juos nuskaityti is failo)"<< endl;
        cin >> s;
        klaida2(s);
        cout << "Pagal koki parametra norite rusiuoti? |1.Didejant | 2.Mazejant | 3.Vardas | (Rasykite tik skaiciuka)" << endl;
    int c;
    cin >> c;

    auto sortingFunction = sortDidejant<Studentas>;
    if (c == 1) {
        sortingFunction = sortDidejant;
    } else if (c == 2) {
        sortingFunction = sortMazejant;
    } else if (c == 3) {
        sortingFunction = SortVardas;
    }

        if (s==2){
            ifstream input("2.txt");
            if (!input.is_open()) {
                cout << "Nepavyko atidaryti failo..." << endl;
            }
            else {
                std::string pav;
                    getline(input, pav);
                    int ndsk = NamuDarbuSk(pav);

    while (!input.eof()) {
        Studentas naujasStudentas;
        string vardas, pavarde;
        input >> vardas >> pavarde;
        naujasStudentas.SetVardas(vardas);
        naujasStudentas.SetPavarde(pavarde);
        for(int i = 1; i <= ndsk; i++){
            int nd;
            input >> nd;
            naujasStudentas.AddNamuDarbas(nd);
        }
        int egzaminas;
        input >> egzaminas;
        naujasStudentas.SetEgzaminas(egzaminas);


        naujasStudentas.SetGalutinisBalas(SkaiciuotiGalutiniBala(naujasStudentas));
        naujasStudentas.SetGalutinisBalasM(SkaiciuotiGalutiniBalaM(naujasStudentas));
        studentai.push_back(naujasStudentas);

            }

            input.close();
           if constexpr (std::is_same<T, std::vector<Studentas>>::value) {
    cout << "Objekto adresas su vector: " << &studentai.back() << endl;
    std::sort(studentai.begin(), studentai.end(), sortingFunction);
} else if constexpr (std::is_same<T, std::list<Studentas>>::value) {
    cout << "Objekto adresas su list: " << &studentai.back() << endl;
    studentai.sort(sortingFunction);
}


ofstream output("4rez.txt");
output << "\nGalutiniai rezultatai:\n";
output << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis balas(vid.)" << setw(20) << "Galutinis balas(med.)" << endl;
output << "----------------------------------------------------------------------------" << endl;
for (const Studentas& studentas : studentai) {
    output << setw(15) << studentas.GetVardas() << setw(15) << studentas.GetPavarde() << fixed << setprecision(2) << setw(25) <<
        studentas.GetGalutinisBalas() << setprecision(2) << setw(20) << studentas.GetGalutinisBalasM() << endl;
}
output.close();
            }
        }

    if (s==1){
    while (true) {
        Studentas naujasStudentas;
        string vardas, pavarde;
        cout << "Iveskite studento varda: ";
        cin >> vardas;
        naujasStudentas.SetVardas(vardas);

        cout << "Iveskite studento pavarde: ";
        cin >> pavarde;
        naujasStudentas.SetPavarde(pavarde);

        naujasStudentas.ClearNamuDarbai();

        int nd;
        cout << "Iveskite namu darbu tarpinius rezultatus (-1, jei baigete ir -2, jei norite, kad namu darbu balai butu sugeneruoti atsitiktinai): ";
        while (true) {
            cin >> nd;
            klaida(nd);
            if (nd == -1) {
                break;
            }
            if (nd == -2){
                int n=0;
                cout << "Iveskite kiek namu darbu balu dar sugeneruoti: " << endl;
                cin >> n;
                klaida3(n);
                for (int i = 1; i <= n; i++){
                   nd = distribution(mt);
                   naujasStudentas.AddNamuDarbas(nd);
                   cout << "(" << nd << ")" << endl;
                }
                break;
                }
            naujasStudentas.AddNamuDarbas(nd);
        }
        int egzaminas;
        cout << "Iveskite egzamino rezultata (-2, jei norite, kad ji sugeneruotu atsitiktinai): ";
        cin >> egzaminas;
        naujasStudentas.SetEgzaminas(egzaminas);
        klaida1(naujasStudentas.GetEgzaminas());
        if(naujasStudentas.GetEgzaminas() == -2){
            naujasStudentas.SetEgzaminas(distribution(mt));
            cout << "(" << naujasStudentas.GetEgzaminas() << ")" << endl;
        }

        naujasStudentas.SetGalutinisBalas(SkaiciuotiGalutiniBala(naujasStudentas));
        naujasStudentas.SetGalutinisBalasM(SkaiciuotiGalutiniBalaM(naujasStudentas));

        studentai.push_back(naujasStudentas);

        cout << "Ar norite ivesti dar vieno studento duomenis? (Taip/Ne): ";
        string pasirinkimas;
        cin >> pasirinkimas;
        klaida4(pasirinkimas);
        if (pasirinkimas != "Taip" && pasirinkimas != "taip" && pasirinkimas != "TAIP") {
            break;
        }
    }
    if constexpr (std::is_same<T, std::vector<Studentas>>::value) {
    cout << "Objekto adresas su vector: " << &studentai.back() << endl;
    std::sort(studentai.begin(), studentai.end(), sortingFunction);
} else if constexpr (std::is_same<T, std::list<Studentas>>::value) {
    cout << "Objekto adresas su list: " << &studentai.back() << endl;
    studentai.sort(sortingFunction);
        }
    SpausdintiRezultatus(studentai);
    }
}

template <typename T>
void SpausdintiRezultatus(const T& studentai) {
    cout << "Norite kad isspausdintu studentu vidurkius ar medianas? (Vidurkis/Mediana): ";
    string pasirinkimas2;
    cin >> pasirinkimas2;
    klaida5(pasirinkimas2);
    cout << "\nGalutiniai rezultatai:\n";
    if (pasirinkimas2 != "Vidurkis" && pasirinkimas2 != "vidurkis"){
        cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis balas(med)" << endl;
        cout << "--------------------------------------------" << endl;
        for (const Studentas& studentas : studentai) {
            cout << setw(15) << studentas.GetVardas() << setw(15) << studentas.GetPavarde() << fixed << setprecision(2) << setw(15) << studentas.GetGalutinisBalasM() << endl;
        }
    }
    else {
        cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis balas(vid)" << endl;
        cout << "--------------------------------------------" << endl;
        for (const Studentas& studentas : studentai) {
        cout << setw(15) << studentas.GetVardas() << setw(15) << studentas.GetPavarde() << fixed << setprecision(2) << setw(15) << studentas.GetGalutinisBalas() << endl;
        }
    }
}
/*template <typename T>
pair<T, T> RikiuotiStudentus1(const T& studentai) {
    T genijai;
    T vargsiukai;

    for (const Studentas& studentas : studentai) {
        if (studentas.GetGalutinisBalas() >= 5.0) {
            genijai.push_back(studentas);
        } else {
            vargsiukai.push_back(studentas);
        }
    }
    return make_pair(genijai, vargsiukai);
}
template <typename T>
std::pair<T, T> RikiuotiStudentus2(T& studentai) {
    T vargsiukai;
    auto it = studentai.begin();

    while (it != studentai.end()) {
        if (it->galutinisBalas < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }

    return std::make_pair(studentai, vargsiukai);
}*/
template <typename T>
pair<T, T> RikiuotiStudentus3(T& studentai) {
    auto partitionIter = partition(studentai.begin(), studentai.end(),
        [](const auto& studentas) { return studentas.GetGalutinisBalas() >= 5.0; });

    T genijai(studentai.begin(), partitionIter);
    T vargsiukai(partitionIter, studentai.end());

    return make_pair(genijai, vargsiukai);
}
    template <typename T>
   void SpausdintiStudentus(const T& studentai, const string& failoPavadinimas) {
    ofstream output(failoPavadinimas);
     output << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis balas(vid)" << endl;

    for (const Studentas& studentas : studentai) {
        output << left << setw(15) << studentas.GetVardas() << setw(15) << studentas.GetPavarde() << setw(15) << studentas.GetGalutinisBalas() << endl;
    }

    output.close();
}

    string GeneruotiVarda(int a) {
        return "Vardas" + to_string(a);
}
    string GeneruotiPavarde(int a) {
        return " Pavarde" + to_string(a);
}

   vector<Studentas> GeneruotiStudentus(int studentuSkaicius, const string& failoPavadinimas, int namuDarbuSkaicius) {
        vector<Studentas> studentai;
        ofstream output(failoPavadinimas);
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> distribution(1, 10);

        output << left << setw(20) << " Vardas" << setw(20) << "  Pavarde";
        for (int p = 1; p <= namuDarbuSkaicius; p++){
            output << setw(10) << "ND" + to_string(p);
        }
        output << setw(10) << "Egz" << endl;
        for (int i = 0; i < studentuSkaicius; ++i) {
        Studentas naujasStudentas;
        naujasStudentas.SetVardas(GeneruotiVarda(i));
        naujasStudentas.SetPavarde(GeneruotiPavarde(i));
        naujasStudentas.SetNamuDarbai(std::vector<int>(namuDarbuSkaicius));
        for (int j = 1; j <= namuDarbuSkaicius; j++) {
            naujasStudentas.AddNamuDarbas(distribution(mt));
        }
        naujasStudentas.SetEgzaminas(distribution(mt));
        studentai.push_back(naujasStudentas);

        output << left << setw(20) << naujasStudentas.GetVardas() << setw(20) << naujasStudentas.GetPavarde();
        for (const int& pazymys : naujasStudentas.GetNamuDarbai()) {
            output << setw(10) << pazymys;
        }
        output << setw(10) << naujasStudentas.GetEgzaminas() << endl;
    }
    output.close();
    return studentai;
    }
    template <typename T>
    void FailoNuskaitymas(const string& failoPavadinimas, T& studentai, int namuDarbuSkaicius){
        ifstream input(failoPavadinimas);
            if (!input.is_open()) {
                cout << "Nepavyko atidaryti failo..." << endl;
            }
            string pav;
            getline(input, pav);
        while (!input.eof()) {
            Studentas naujasStudentas;
           string vardas, pavarde;
    input >> vardas >> pavarde;
    naujasStudentas.SetVardas(vardas);
    naujasStudentas.SetPavarde(pavarde);

    for (int i = 1; i <= namuDarbuSkaicius; i++) {
        int nd;
        input >> nd;
        naujasStudentas.AddNamuDarbas(nd);
    }

    int egzaminas;
    input >> egzaminas;
    naujasStudentas.SetEgzaminas(egzaminas);

    naujasStudentas.SetGalutinisBalas(SkaiciuotiGalutiniBala(naujasStudentas));
            studentai.push_back(naujasStudentas);
        }
        input.close();
    }
template <typename T>
void Testavimas(T& studentai) {
    int n = 10;
    int b;
    cout << "Jei norite is naujo generuoti failus, rasykite 1" << endl;
    cin >> b;
    if (b == 1) {
        GeneruotiStudentus(1000, "1000.txt", n);
        GeneruotiStudentus(10000, "10000.txt", n);
        GeneruotiStudentus(100000, "100000.txt", n);
        GeneruotiStudentus(1000000, "1000000.txt", n);
        GeneruotiStudentus(10000000, "10000000.txt", n);
    }
    cout << "Pagal koki parametra norite rusiuoti? |1.Didejant | 2.Mazejant | 3.Vardas | (Rasykite tik skaiciuka)" << endl;
    int c;
    cin >> c;

    auto sortingFunction = sortDidejant<Studentas>;
    if (c == 1) {
        sortingFunction = sortDidejant;
    } else if (c == 2) {
        sortingFunction = sortMazejant;
    } else if (c == 3) {
        sortingFunction = SortVardas;
    }

    for (int i = 10000; i <= 10000; i = i * 10) {
        T studentaiContainer;
        chrono::duration<double> suma = chrono::duration<double>::zero();
        auto start = std::chrono::high_resolution_clock::now();
        FailoNuskaitymas(to_string(i) + ".txt", studentaiContainer, n);
        auto end = std::chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        suma += diff;
        cout << i << " studentu nuskaitymas is failo: " << diff.count() << endl;

        if constexpr (std::is_same<T, std::vector<Studentas>>::value) {
            std::sort(studentaiContainer.begin(), studentaiContainer.end(), sortingFunction);
        } else if constexpr (std::is_same<T, std::list<Studentas>>::value) {
            studentaiContainer.sort(sortingFunction);
        }

        start = std::chrono::high_resolution_clock::now();
        pair<T, T> sortedStudents = RikiuotiStudentus3(studentaiContainer);
        T genijai = sortedStudents.first;
        T vargsiukai = sortedStudents.second;
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        suma = suma + diff;
        cout << i << " studentu rusiavimas i dvi grupes: " << diff.count() << endl;

        start = std::chrono::high_resolution_clock::now();
        SpausdintiStudentus(genijai, "genijai.txt");
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        suma = suma + diff;
        cout << i << " geniju spausdinimas i faila: " << diff.count() << endl;

        start = std::chrono::high_resolution_clock::now();
        SpausdintiStudentus(vargsiukai, "vargsiukai.txt");
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        suma = suma + diff;
        cout << i << " vargsiuku spausdinimas i faila: " << diff.count() << endl;
        cout << endl;

        cout << i << " irasu testo laikas: " << suma.count() << endl;
        cout << endl;
    }
}

template void Testavimas(std::vector<Studentas>&);

template void Testavimas(std::list<Studentas>&);

template void IvestiDuomenis(std::vector<Studentas>&);

template void IvestiDuomenis(std::list<Studentas>&);

/*
template <typename T>
    bool sortDidejant(const T& a, const T& b) {
    return a.galutinisBalas < b.galutinisBalas;
}
    template <typename T>
    bool sortMazejant(const T& a, const T& b) {
        return a.galutinisBalas > b.galutinisBalas;
}
template <typename T>
double SkaiciuotiGalutiniBalaM(const T& studentas) {
    if (studentas.namuDarbai.empty()) {
        return studentas.egzaminas * 0.6;
    }
    vector<int> namuDarbaiSorted = studentas.namuDarbai;
    sort(namuDarbaiSorted.begin(), namuDarbaiSorted.end());
    double namuDarbuMediana = 0.0;
    int n = namuDarbaiSorted.size();
    if (n % 2 == 0){
        int mid1 = namuDarbaiSorted[n/2];
        int mid2 = namuDarbaiSorted[(n/2)-1];
        namuDarbuMediana = (mid1 + mid2) / 2;
    }
    else {
        namuDarbuMediana = namuDarbaiSorted[n/2];
    }

    return 0.4 * namuDarbuMediana + 0.6 * studentas.egzaminas;
}
template <typename T>
double SkaiciuotiGalutiniBala(const T& studentas) {
    if (studentas.namuDarbai.empty()) {
        return studentas.egzaminas * 0.6;
    }
    double namuDarbuVidurkis = 0.0;
    for (int nd : studentas.namuDarbai) {
        namuDarbuVidurkis =namuDarbuVidurkis + nd;
    }
    namuDarbuVidurkis = namuDarbuVidurkis / studentas.namuDarbai.size();

    return 0.4 * namuDarbuVidurkis + 0.6 * studentas.egzaminas;
}
template <typename T>
bool SortVardas(const T& a, const T& b) {
    return a.vardas < b.vardas;
}

int NamuDarbuSk(const string& pav){
    std::istringstream ss(pav);
            vector<string> zodziai;
            string zodis;
            while (ss >> zodis) {
                zodziai.push_back(zodis);
                }
            int ndsk= zodziai.size()-3;
    return ndsk;
}

void klaida(int &a){
    do{
        try{
                    if (cin.fail()) {
                            throw runtime_error("Ivedete ne sveikaji skaiciu. ");
                    }
                    if (a < -2 || a > 10) {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
        }
        catch (const runtime_error& e){
                    cout << e.what();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Veskite duomenis dar karta: ";
                    cin >> a;
                }
        }
        while (cin.fail() == true || a < -2 || a > 10);
    }

    void klaida1(int &a){
    do{
        try{
                    if (cin.fail()) {
                            throw runtime_error("Ivedete ne sveikaji skaiciu. ");
                    }
                    if (a < -2 || a > 10 || a == -1) {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
        }
        catch (const runtime_error& e){
                    cout << e.what();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Veskite duomenis dar karta: ";
                    cin >> a;
                }
        }
        while (cin.fail() == true || a == -1 || a > 10 || a < -2);
    }

    void klaida2(int &a){
    do{
        try{
                    if (cin.fail()) {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
                    if (a < 1 || a > 2) {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
        }
        catch (const runtime_error& e){
                    cout << e.what();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Veskite duomenis dar karta (1 arba 2): ";
                    cin >> a;
                }
        }
        while (cin.fail() == true || a < 1 || a > 2);
    }

     void klaida3(int &a){
    do{
        try{
                    if (cin.fail() || a < 0) {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
        }
        catch (const runtime_error& e){
                    cout << e.what();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Veskite duomenis dar karta: ";
                    cin >> a;
                }
        }
        while (cin.fail() == true || a < 0);
    }

    void klaida4(string &a){
    do{
        try{
                    if (a != "taip" && a != "ne" && a != "Taip" && a != "Ne" && a != "TAIP" && a != "NE") {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
        }
        catch (const runtime_error& e){
                    cout << e.what();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Veskite duomenis dar karta: ";
                    cin >> a;
                }
        }
        while (a != "taip" && a != "ne" && a != "Taip" && a != "Ne" && a != "TAIP" && a != "NE");
    }

    void klaida5(string &a){
    do{
        try{
                    if (a != "Vidurkis" && a != "VIDURKIS" && a != "vidurkis" && a != "Mediana" && a != "mediana" && a != "MEDIANA") {
                            throw runtime_error("Ivedete netinkamus duomenis. ");
                    }
        }
        catch (const runtime_error& e){
                    cout << e.what();
                    cin.clear();
                    cin.ignore(256, '\n');
                    cout << "Veskite duomenis dar karta: ";
                    cin >> a;
                }
        }
        while (a != "Vidurkis" && a != "VIDURKIS" && a != "vidurkis" && a != "Mediana" && a != "mediana" && a != "MEDIANA");
    }
    template <typename T>
    void IvestiDuomenis(T& studentai) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(1, 10);
     int s;
        cout << "Norite pazymius suvesti ar nuskaityti juos is failo?(Rasykite 1, jei norite pazymius suvesti, ir 2, jei norite juos nuskaityti is failo)"<< endl;
        cin >> s;
        klaida2(s);
        cout << "Pagal koki parametra norite rusiuoti? |1.Didejant | 2.Mazejant | 3.Vardas | (Rasykite tik skaiciuka)" << endl;
    int c;
    cin >> c;

    auto sortingFunction = sortDidejant<Studentas>;
    if (c == 1) {
        sortingFunction = sortDidejant;
    } else if (c == 2) {
        sortingFunction = sortMazejant;
    } else if (c == 3) {
        sortingFunction = SortVardas;
    }

        if (s==2){
            ifstream input("studentai.txt");
            if (!input.is_open()) {
                cout << "Nepavyko atidaryti failo..." << endl;
            }
            else {
                string pav;
                    getline(input, pav);
                    int ndsk = NamuDarbuSk(pav);

    while (!input.eof()) {
        Studentas naujasStudentas;
        input >> naujasStudentas.vardas >> naujasStudentas.pavarde;
        for(int i = 1; i <= ndsk; i++){
            int nd;
            input >> nd;
            naujasStudentas.namuDarbai.push_back(nd);
        }
        input >> naujasStudentas.egzaminas;

        naujasStudentas.galutinisBalas = SkaiciuotiGalutiniBala(naujasStudentas);
        naujasStudentas.galutinisBalasM = SkaiciuotiGalutiniBalaM(naujasStudentas);
        studentai.push_back(naujasStudentas);

            }

            input.close();
           if constexpr (std::is_same<T, std::vector<Studentas>>::value) {
    cout << "Objekto adresas su vector: " << &studentai.back() << endl;
    std::sort(studentai.begin(), studentai.end(), sortingFunction);
} else if constexpr (std::is_same<T, std::list<Studentas>>::value) {
    cout << "Objekto adresas su list: " << &studentai.back() << endl;
    studentai.sort(sortingFunction);
}


ofstream output("4rez.txt");
output << "\nGalutiniai rezultatai:\n";
output << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis balas(vid.)" << setw(20) << "Galutinis balas(med.)" << endl;
output << "----------------------------------------------------------------------------" << endl;
for (const Studentas& studentas : studentai) {
    output << setw(15) << studentas.vardas << setw(15) << studentas.pavarde << fixed << setprecision(2) << setw(25) <<
        studentas.galutinisBalas << setprecision(2) << setw(20) << studentas.galutinisBalasM << endl;
}
output.close();
            }
        }

    if (s==1){
    while (true) {
        Studentas naujasStudentas;

        cout << "Iveskite studento varda: ";
        cin >> naujasStudentas.vardas;

        cout << "Iveskite studento pavarde: ";
        cin >> naujasStudentas.pavarde;

        naujasStudentas.namuDarbai.clear();

        int nd;
        cout << "Iveskite namu darbu tarpinius rezultatus (-1, jei baigete ir -2, jei norite, kad namu darbu balai butu sugeneruoti atsitiktinai): ";
        while (true) {
            cin >> nd;
            klaida(nd);
            if (nd == -1) {
                break;
            }
            if (nd == -2){
                int n=0;
                cout << "Iveskite kiek namu darbu balu dar sugeneruoti: " << endl;
                cin >> n;
                klaida3(n);
                for (int i = 1; i <= n; i++){
                   nd = distribution(mt);
                   naujasStudentas.namuDarbai.push_back(nd);
                   cout << "(" << nd << ")" << endl;
                }
                break;
                }
            naujasStudentas.namuDarbai.push_back(nd);
        }
        cout << "Iveskite egzamino rezultata (-2, jei norite, kad ji sugeneruotu atsitiktinai): ";
        cin >> naujasStudentas.egzaminas;
        klaida1(naujasStudentas.egzaminas);
        if(naujasStudentas.egzaminas == -2){
            naujasStudentas.egzaminas = distribution(mt);
            cout << "(" << naujasStudentas.egzaminas << ")" << endl;
        }

        naujasStudentas.galutinisBalas = SkaiciuotiGalutiniBala(naujasStudentas);
        naujasStudentas.galutinisBalasM = SkaiciuotiGalutiniBalaM(naujasStudentas);

        studentai.push_back(naujasStudentas);

        cout << "Ar norite ivesti dar vieno studento duomenis? (Taip/Ne): ";
        string pasirinkimas;
        cin >> pasirinkimas;
        klaida4(pasirinkimas);
        if (pasirinkimas != "Taip" && pasirinkimas != "taip" && pasirinkimas != "TAIP") {
            break;
        }
    }
    if constexpr (std::is_same<T, std::vector<Studentas>>::value) {
    cout << "Objekto adresas su vector: " << &studentai.back() << endl;
    std::sort(studentai.begin(), studentai.end(), sortingFunction);
} else if constexpr (std::is_same<T, std::list<Studentas>>::value) {
    cout << "Objekto adresas su list: " << &studentai.back() << endl;
    studentai.sort(sortingFunction);
        }
    SpausdintiRezultatus(studentai);
    }
    }

template <typename T>
void SpausdintiRezultatus(const T& studentai) {
    cout << "Norite kad isspausdintu studentu vidurkius ar medianas? (Vidurkis/Mediana): ";
    string pasirinkimas2;
    cin >> pasirinkimas2;
    klaida5(pasirinkimas2);
    cout << "\nGalutiniai rezultatai:\n";
    if (pasirinkimas2 != "Vidurkis" && pasirinkimas2 != "vidurkis"){
        cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis balas(med)" << endl;
        cout << "--------------------------------------------" << endl;
        for (const Studentas& studentas : studentai) {
            cout << setw(15) << studentas.vardas << setw(15) << studentas.pavarde << fixed << setprecision(2) << setw(15) << studentas.galutinisBalasM << endl;
        }
    }
    else {
        cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis balas(vid)" << endl;
        cout << "--------------------------------------------" << endl;
        for (const Studentas& studentas : studentai) {
        cout << setw(15) << studentas.vardas << setw(15) << studentas.pavarde << fixed << setprecision(2) << setw(15) << studentas.galutinisBalas << endl;
        }
    }
}
template <typename T>
pair<T, T> RikiuotiStudentus1(const T& studentai) {
    T genijai;
    T vargsiukai;

    for (const Studentas& studentas : studentai) {
        if (studentas.galutinisBalas >= 5.0) {
            genijai.push_back(studentas);
        } else {
            vargsiukai.push_back(studentas);
        }
    }
    return make_pair(genijai, vargsiukai);
}
template <typename T>
std::pair<T, T> RikiuotiStudentus2(T& studentai) {
    T vargsiukai;
    auto it = studentai.begin();

    while (it != studentai.end()) {
        if (it->galutinisBalas < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }

    return std::make_pair(studentai, vargsiukai);
}
template <typename T>
pair<T, T> RikiuotiStudentus3(T& studentai) {
    auto partitionIter = partition(studentai.begin(), studentai.end(),
        [](const auto& studentas) { return studentas.galutinisBalas >= 5.0; });

    T genijai(studentai.begin(), partitionIter);
    T vargsiukai(partitionIter, studentai.end());

    return make_pair(genijai, vargsiukai);
}
    template <typename T>
   void SpausdintiStudentus(const T& studentai, const string& failoPavadinimas) {
    ofstream output(failoPavadinimas);
     output << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis balas(vid)" << endl;

    for (const Studentas& studentas : studentai) {
        output << left << setw(15) << studentas.vardas << setw(15) << studentas.pavarde << setw(15) << studentas.galutinisBalas << endl;
    }

    output.close();
}

    string GeneruotiVarda(int a) {
        return "Vardas" + to_string(a);
}
    string GeneruotiPavarde(int a) {
        return " Pavarde" + to_string(a);
}

    vector<Studentas> GeneruotiStudentus(int studentuSkaicius, const string& failoPavadinimas, int namuDarbuSkaicius) {
        vector<Studentas> studentai;
        ofstream output(failoPavadinimas);
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> distribution(1, 10);

        output << left << setw(20) << " Vardas" << setw(20) << "  Pavarde";
        for (int p = 1; p <= namuDarbuSkaicius; p++){
            output << setw(10) << "ND" + to_string(p);
        }
        output << setw(10) << "Egz" << endl;
        for (int i = 1; i <= studentuSkaicius; i++) {
            Studentas naujasStudentas;
            naujasStudentas.vardas = GeneruotiVarda(i);
            naujasStudentas.pavarde = GeneruotiPavarde(i);
            naujasStudentas.namuDarbai.reserve(namuDarbuSkaicius);
            for (int j = 1; j <= namuDarbuSkaicius; j++) {
                naujasStudentas.namuDarbai.push_back(distribution(mt));
            }
            naujasStudentas.egzaminas = distribution(mt);
            studentai.push_back(naujasStudentas);
            output << left << setw(20) << naujasStudentas.vardas << setw(20) << naujasStudentas.pavarde;
            for (const int& pazymys : naujasStudentas.namuDarbai) {
                output << setw(10) << pazymys;
            }
            output << setw(10) << naujasStudentas.egzaminas << endl;
        }
        output.close();
    return studentai;
    }
    template <typename T>
    void FailoNuskaitymas(const string& failoPavadinimas, T& studentai, int namuDarbuSkaicius){
        ifstream input(failoPavadinimas);
            if (!input.is_open()) {
                cout << "Nepavyko atidaryti failo..." << endl;
            }
            string pav;
            getline(input, pav);
        while (!input.eof()) {
            Studentas naujasStudentas;
            input >> naujasStudentas.vardas >> naujasStudentas.pavarde;
            for(int i = 1; i <= namuDarbuSkaicius; i++){
                int nd;
                input >> nd;
                naujasStudentas.namuDarbai.push_back(nd);
            }
            input >> naujasStudentas.egzaminas;
            naujasStudentas.galutinisBalas = SkaiciuotiGalutiniBala(naujasStudentas);
            studentai.push_back(naujasStudentas);
        }
        input.close();
    }
template <typename T>
void Testavimas(T& studentai) {
    int n = 10;
    int b;
    cout << "Jei norite is naujo generuoti failus, rasykite 1" << endl;
    cin >> b;
    if (b == 1) {
        GeneruotiStudentus(1000, "1000.txt", n);
        GeneruotiStudentus(10000, "10000.txt", n);
        GeneruotiStudentus(100000, "100000.txt", n);
        GeneruotiStudentus(1000000, "1000000.txt", n);
        GeneruotiStudentus(10000000, "10000000.txt", n);
    }
    cout << "Pagal koki parametra norite rusiuoti? |1.Didejant | 2.Mazejant | 3.Vardas | (Rasykite tik skaiciuka)" << endl;
    int c;
    cin >> c;

    auto sortingFunction = sortDidejant<Studentas>;
    if (c == 1) {
        sortingFunction = sortDidejant;
    } else if (c == 2) {
        sortingFunction = sortMazejant;
    } else if (c == 3) {
        sortingFunction = SortVardas;
    }

    for (int i = 10000; i <= 10000; i = i * 10) {
        T studentaiContainer;
        chrono::duration<double> suma = chrono::duration<double>::zero();
        auto start = std::chrono::high_resolution_clock::now();
        FailoNuskaitymas(to_string(i) + ".txt", studentaiContainer, n);
        auto end = std::chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        suma += diff;
        cout << i << " studentu nuskaitymas is failo: " << diff.count() << endl;

        if constexpr (std::is_same<T, std::vector<Studentas>>::value) {
            std::sort(studentaiContainer.begin(), studentaiContainer.end(), sortingFunction);
        } else if constexpr (std::is_same<T, std::list<Studentas>>::value) {
            studentaiContainer.sort(sortingFunction);
        }

        start = std::chrono::high_resolution_clock::now();
        pair<T, T> sortedStudents = RikiuotiStudentus3(studentaiContainer);
        T genijai = sortedStudents.first;
        T vargsiukai = sortedStudents.second;
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        suma = suma + diff;
        cout << i << " studentu rusiavimas i dvi grupes: " << diff.count() << endl;

        start = std::chrono::high_resolution_clock::now();
        SpausdintiStudentus(genijai, "genijai.txt");
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        suma = suma + diff;
        cout << i << " geniju spausdinimas i faila: " << diff.count() << endl;

        start = std::chrono::high_resolution_clock::now();
        SpausdintiStudentus(vargsiukai, "vargsiukai.txt");
        end = std::chrono::high_resolution_clock::now();
        diff = end - start;
        suma = suma + diff;
        cout << i << " vargsiuku spausdinimas i faila: " << diff.count() << endl;
        cout << endl;

        cout << i << " irasu testo laikas: " << suma.count() << endl;
        cout << endl;
    }
}

template void Testavimas(std::vector<Studentas>&);

template void Testavimas(std::list<Studentas>&);

template void IvestiDuomenis(std::vector<Studentas>&);

template void IvestiDuomenis(std::list<Studentas>&);

*/

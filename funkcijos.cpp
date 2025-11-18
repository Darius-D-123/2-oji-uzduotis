#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <chrono>
#include <list>
#include <type_traits>
#include <iterator>
#include "studentas.h"
#include "funkcijos.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;
using std::sort;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::getline;
using std::to_string;
using std::list;
using std::back_inserter;
using namespace std::chrono;

Studentas ivesk(bool randomMode) {
    Studentas Laik;
    cout << "Iveskite varda: "; getline(cin, Laik.vard);
    cout << "Iveskite pavarde: "; getline(cin, Laik.pav);

    if (randomMode) {
        int n = rand() % 8 + 3;
        for (int i = 0; i < n; i++) {
            Laik.paz.push_back(rand() % 10 + 1);
        }
        Laik.egzas = rand() % 10 + 1;
        cout << "Sugeneruoti " << n << " pazymiai ir egzaminas.\n";
    } else {
        cout << "Iveskite pazymius (baigti su 'q' arba ne skaiciumi):\n";
        string input;
        int pazymiuKiekis = 0;
        while (true) {
            cout << "Pazymys " << (pazymiuKiekis + 1) << ": ";
            getline(cin, input);
            if (input == "q" || input == "Q") {
                if (pazymiuKiekis == 0) {
                    cout << "Privalote ivesti bent viena pazymi! Bandykite dar karta.\n";
                    continue;
                }
                break;
            }
            if (arSkaicius(input)) {
                try {
                    int pazymys = std::stoi(input);
                    if (pazymys >= 1 && pazymys <= 10) {
                        Laik.paz.push_back(pazymys);
                        pazymiuKiekis++;
                    } else {
                        cout << "Klaida: pazymys turi buti nuo 1 iki 10!\n";
                    }
                } catch (const std::exception& e) {
                    cout << "Klaida: netinkamas pazymys! Bandykite dar karta.\n";
                }
            } else {
                cout << "Klaida: iveskite skaiciu nuo 1 iki 10 arba 'q' baigti! Bandykite dar karta.\n";
            }
        }

        while (true) {
            string egzInput;
            cout << "Iveskite egzamino rezultata (1-10): ";
            getline(cin, egzInput);
            if (arSkaicius(egzInput)) {
                try {
                    Laik.egzas = std::stoi(egzInput);
                    if (Laik.egzas >= 1 && Laik.egzas <= 10) {
                        break;
                    } else {
                        cout << "Klaida: egzamino rezultatas turi buti nuo 1 iki 10!\n";
                    }
                } catch (const std::exception& e) {
                    cout << "Klaida: netinkamas egzamino rezultatas! Bandykite dar karta.\n";
                }
            } else {
                cout << "Klaida: iveskite skaiciu nuo 1 iki 10! Bandykite dar karta.\n";
            }
        }
    }

    Laik.rez_vid = apskaiciuotiGalutiniVid(Laik);
    Laik.rez_med = apskaiciuotiGalutiniMed(Laik);
    return Laik;
}

void parodykFailuSarasa() {
    cout << "\nGalimi failai:\n";
    cout << "1. studentai1000.txt (1,000 studentu)\n";
    cout << "2. studentai10000.txt (10,000 studentu)\n";
    cout << "3. studentai100000.txt (100,000 studentu)\n";
    cout << "4. studentai1000000.txt (1,000,000 studentu)\n";
    cout << "5. studentai10000000.txt (10,000,000 studentu)\n";
    cout << "6. kursiokai.txt \n";
}

template<typename Container>
void issaugokIFaila(const Container &Grupe, const string &failoVardas) {
    ofstream out(failoVardas);
    if (!out) {
        cout << "Klaida: nepavyko sukurti failo " << failoVardas << endl;
        return;
    }
    out << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    out << string(70, '-') << endl;
    out << fixed << setprecision(2);
    for (auto &s : Grupe) {
        out << setw(15) << s.pav << setw(15) << s.vard << setw(20) << s.rez_vid << setw(20) << s.rez_med << endl;
    }
    out.close();
    cout << "Rezultatai issaugoti faile " << failoVardas << endl;
}

template<typename Container>
void issaugokPadalintusStudentus(const Container &Vargsai, const Container &Kietiakiai) {
    ofstream outVargsai("vargsai.txt");
    if (!outVargsai) {
        cout << "Klaida: nepavyko sukurti failo vargsai.txt" << endl;
        return;
    }
    outVargsai << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    outVargsai << string(70, '-') << endl;
    outVargsai << fixed << setprecision(2);
    for (auto &s : Vargsai) {
        outVargsai << setw(20) << s.pav << setw(20) << s.vard << setw(20) << s.rez_vid << setw(20) << s.rez_med << endl;
    }
    outVargsai.close();
    cout << "Vargsai issaugoti faile vargsai.txt (" << Vargsai.size() << " studentai)" << endl;

    ofstream outKietiakiai("kietiakiai.txt");
    if (!outKietiakiai) {
        cout << "Klaida: nepavyko sukurti failo kietiakiai.txt" << endl;
        return;
    }
    outKietiakiai << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    outKietiakiai << string(70, '-') << endl;
    outKietiakiai << fixed << setprecision(2);
    for (auto &s : Kietiakiai) {
        outKietiakiai << setw(20) << s.pav << setw(20) << s.vard << setw(20) << s.rez_vid << setw(20) << s.rez_med << endl;
    }
    outKietiakiai.close();
    cout << "Kietiakiai issaugoti faile kietiakiai.txt (" << Kietiakiai.size() << " studentai)" << endl;
}

template<typename Container>
Container nuskaitykIsFailo(const string &failoVardas) {
    Container Grupe;
    ifstream in(failoVardas);
    if (!in) {
        cout << "Klaida: nepavyko atidaryti failo " << failoVardas << endl;
        return Grupe;
    }

    string line;
    int studentuSkaicius = -1;
    while (getline(in, line)) {
        studentuSkaicius++;
    }

    if (studentuSkaicius <= 0) {
        cout << "Failas tuscias arba neturi duomenu!\n";
        in.close();
        return Grupe;
    }

    in.clear();
    in.seekg(0);
    string headerLine;
    getline(in, headerLine);

    int nuskaityta = 0;
    cout << "Skaitomas failas...\n";

    while (getline(in, line)) {
        istringstream iss(line);
        Studentas s;
        if (iss >> s.vard >> s.pav) {
            s.paz.clear();
            string token;
            vector<int> visiPazymiai;
            bool klaidaEiluteje = false;

            while (iss >> token) {
                if (arSkaicius(token)) {
                    try {
                        int skaicius = std::stoi(token);
                        if (skaicius >= 1 && skaicius <= 10) {
                            visiPazymiai.push_back(skaicius);
                        } else {
                            klaidaEiluteje = true;
                        }
                    } catch (const std::exception& e) {
                        klaidaEiluteje = true;
                    }
                } else {
                    klaidaEiluteje = true;
                }
            }

            if (!klaidaEiluteje && !visiPazymiai.empty()) {
                s.egzas = visiPazymiai.back();
                visiPazymiai.pop_back();
                s.paz = visiPazymiai;
                s.rez_vid = apskaiciuotiGalutiniVid(s);
                s.rez_med = apskaiciuotiGalutiniMed(s);
                Grupe.push_back(s);
                nuskaityta++;

                if (studentuSkaicius >= 10000 && nuskaityta % 10000 == 0) {
                    cout << "Nuskaityta: " << nuskaityta << " is " << studentuSkaicius
                         << " (" << (nuskaityta * 100 / studentuSkaicius) << "%)" << endl;
                }
            }
        }
    }
    in.close();
    return Grupe;
}

void generuotiStudentuFailus() {
    vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
    for (int dydis : dydziai) {
        string failoVardas = "studentai" + std::to_string(dydis) + ".txt";
        cout << "Kuriamas failas: " << failoVardas << "..." << endl;

        ofstream out(failoVardas);
        if (!out) {
            cout << "Klaida: nepavyko sukurti failo " << failoVardas << endl;
            continue;
        }

        out << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
        for (int i = 1; i <= 10; i++) {
            out << setw(10) << "ND" + std::to_string(i);
        }
        out << setw(10) << "Egz." << endl;

        for (int i = 1; i <= dydis; i++) {
            out << setw(20) << "Vardas" + std::to_string(i)
                << setw(20) << "Pavarde" + std::to_string(i);
            for (int j = 0; j < 10; j++) {
                out << setw(10) << (rand() % 10 + 1);
            }
            out << setw(10) << (rand() % 10 + 1) << endl;

            if (dydis >= 100000 && i % (dydis / 10) == 0) {
                cout << "Sugeneruota: " << (i * 100 / dydis) << "%" << endl;
            }
        }
        out.close();
        cout << "Failas " << failoVardas << " sekmingai sukurtas (" << dydis << " irasu)" << endl;
    }
}

double testuotiFailuKurima() {
    vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
    double bendrasLaikas = 0.0;
    for (int dydis : dydziai) {
        string failoVardas = "studentai" + to_string(dydis) + ".txt";
        cout << "Kuriamas failas: " << failoVardas << endl;
        auto start = high_resolution_clock::now();
        ofstream out(failoVardas);
        if (!out) {
            cout << "KLAIDA: nepavyko sukurti failo " << failoVardas << endl;
            continue;
        }
        out << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
        for (int i = 1; i <= 10; i++) {
            out << setw(10) << "ND" + to_string(i);
        }
        out << setw(10) << "Egz." << endl;
        for (int i = 1; i <= dydis; i++) {
            out << setw(20) << "Vardas" + std::to_string(i)
                << setw(20) << "Pavarde" + std::to_string(i);
            for (int j = 0; j < 10; j++) {
                out << setw(10) << (rand() % 10 + 1);
            }
            out << setw(10) << (rand() % 10 + 1) << endl;
        }
        out.close();
        auto end = high_resolution_clock::now();
        duration<double> diff = end - start;
        cout << fixed << setprecision(6);
        cout << "[" << dydis << "] irasu failo kurimo laikas: " << diff.count() << "s" << endl;
        cout << "Failas " << failoVardas << " sekmingai sukurtas\n\n";
    }
    cout << "Visi failai sugeneruoti sekmingai!\n";
    return 0.0;
}

double median(vector<int> v) {
    if (v.empty()) return 0.0;
    sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 0) {
        return (v[n/2 - 1] + v[n/2]) / 2.0;
    } else {
        return v[n/2];
    }
}

double apskaiciuotiGalutiniVid(const Studentas &s) {
    if (s.paz.empty()) {
        return 0.6 * s.egzas;
    }
    double sum = 0.0;
    for (int x : s.paz) sum += x;
    double vid = sum / s.paz.size();
    return 0.6 * s.egzas + 0.4 * vid;
}

double apskaiciuotiGalutiniMed(const Studentas &s) {
    if (s.paz.empty()) {
        return 0.6 * s.egzas;
    }
    return 0.6 * s.egzas + 0.4 * median(s.paz);
}

template<typename Container>
void rusiuokStudentus(Container &Grupe) {
    Grupe.sort(palyginkStudentusPagalSkaitineReiksme);
}

template<>
void rusiuokStudentus<std::vector<Studentas>>(std::vector<Studentas> &Grupe) {
    sort(Grupe.begin(), Grupe.end(), palyginkStudentusPagalSkaitineReiksme);
}

template<typename Container>
void padalinkStudentus1(const Container &Grupe, Container &Vargsai, Container &Kietiakiai) {
    for (const auto &studentas : Grupe) {
        if (studentas.rez_vid < 5.0) {
            Vargsai.push_back(studentas);
        } else {
            Kietiakiai.push_back(studentas);
        }
    }
    rusiuokStudentus(Vargsai);
    rusiuokStudentus(Kietiakiai);
}

template<typename Container>
void padalinkStudentus2(Container &Grupe, Container &Vargsai) {
    auto it = std::remove_if(Grupe.begin(), Grupe.end(), [&Vargsai](const Studentas& s) {
        if (s.rez_vid < 5.0) {
            Vargsai.push_back(s);
            return true;
        }
        return false;
    });
    Grupe.erase(it, Grupe.end());
    rusiuokStudentus(Vargsai);
    rusiuokStudentus(Grupe);
}

template<typename Container>
void padalinkStudentus3(Container &Grupe, Container &Vargsai) {
    auto partition_point = std::stable_partition(Grupe.begin(), Grupe.end(), 
        [](const Studentas& s) { return s.rez_vid >= 5.0; });
    
    Vargsai.assign(partition_point, Grupe.end());
    Grupe.erase(partition_point, Grupe.end());
    
    rusiuokStudentus(Vargsai);
    rusiuokStudentus(Grupe);
}

bool palyginkStudentusPagalSkaitineReiksme(const Studentas &a, const Studentas &b) {
    int skaiciusA = gautiSkaitineReiksmeIsPavardes(a.pav);
    int skaiciusB = gautiSkaitineReiksmeIsPavardes(b.pav);
    if (skaiciusA != skaiciusB) {
        return skaiciusA < skaiciusB;
    }
    if (a.pav != b.pav) {
        return a.pav < b.pav;
    }
    return a.vard < b.vard;
}

bool arSkaicius(const string &str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c) && c != '-' && c != '+') {
            return false;
        }
    }
    return true;
}

int gautiSkaiciu(const string &pranesimas) {
    string input;
    int skaicius;

    while (true) {
        cout << pranesimas;
        getline(cin, input);

        if (arSkaicius(input)) {
            try {
                skaicius = std::stoi(input);
                if (skaicius > 0) {
                    return skaicius;
                } else {
                    cout << "Klaida: skaicius turi buti teigiamas!\n";
                }
            } catch (const std::exception& e) {
                cout << "Klaida: netinkamas skaicius! Bandykite dar karta.\n";
            }
        } else {
            cout << "Klaida: iveskite skaiciu! Bandykite dar karta.\n";
        }
    }
}

int gautiSkaitineReiksmeIsPavardes(const string& pavarde) {
    string skaitmuoStr = "";
    for (int i = pavarde.length() - 1; i >= 0; i--) {
        if (isdigit(pavarde[i])) {
            skaitmuoStr = pavarde[i] + skaitmuoStr;
        } else if (!skaitmuoStr.empty()) {
            break;
        }
    }
    if (!skaitmuoStr.empty()) {
        try {
            return std::stoi(skaitmuoStr);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

void testuotiProgramosSparta() {

    cout << "Pasirinkite testavimo varianta:\n";
    cout << "1 - Failu kurimo testavimas\n";
    cout << "2 - Programos veikimo testavimas (nuskaitymas/rusiavimas/isvedimas)\n";
    cout << "Jusu pasirinkimas (1 arba 2): ";
    string pasirinkimas;
    getline(cin, pasirinkimas);
    if (pasirinkimas == "1") {
        cout << "         FAILU KURIMO TESTAVIMAS \n";
        testuotiFailuKurima();
    } else if (pasirinkimas == "2") {
         cout << "\nPasirinkite failo dydi:\n";
        cout << "1 - 1000 irasu\n";
        cout << "2 - 10000 irasu\n";
        cout << "3 - 100000 irasu\n";
        cout << "4 - 1000000 irasu\n";
        cout << "5 - 10000000 irasu\n";
        cout << "Jusu pasirinkimas (1-5): ";
        string dydzioPasirinkimas;
        getline(cin, dydzioPasirinkimas);
        int dydis = 0;
        if (dydzioPasirinkimas == "1") dydis = 1000;
        else if (dydzioPasirinkimas == "2") dydis = 10000;
        else if (dydzioPasirinkimas == "3") dydis = 100000;
        else if (dydzioPasirinkimas == "4") dydis = 1000000;
        else if (dydzioPasirinkimas == "5") dydis = 10000000;
        else {
            cout << "Netinkamas pasirinkimas! Naudojamas 1000 irasu.\n";
            dydis = 1000;
        }
        cout << "        FAILO SPARTOS ANALIZE\n";
        testuotiPasirinktaFaila<std::vector<Studentas>>(dydis);
    } else {
        cout << "Netinkamas pasirinkimas!\n";
    }
    cout << "        TESTAVIMAS BAIGTAS\n";
}

template<typename Container>
void testuotiPasirinktaFaila(int dydis) {
    string failoVardas = "studentai" + std::to_string(dydis) + ".txt";
    ifstream testas(failoVardas);
    if (!testas) {
        cout << "KLAIDA: Failas " << failoVardas << " nerastas!\n";
        cout << "Pirmiausia sugeneruokite failus pasirinkdami 1 varianta.\n";
        return;
    }
    testas.close();
    cout << "\n=== TESTAS SU " << dydis << " IRASU ===";
    if (std::is_same<Container, std::vector<Studentas>>::value) {
        cout << " (std::vector) ===";
    } else {
        cout << " (std::list) ===";
    }
    cout << "\n";
    cout << fixed << setprecision(6);
    cout << "Nuskaitomas failas... ";
    auto nuskaitymoStart = high_resolution_clock::now();
    Container Grupe = nuskaitykIsFailo<Container>(failoVardas);
    auto nuskaitymoEnd = high_resolution_clock::now();
    duration<double> nuskaitymoLaikas = nuskaitymoEnd - nuskaitymoStart;
    cout << "nuskaitymo laikas: " << nuskaitymoLaikas.count() << "s\n";
    if (std::is_same<Container, std::vector<Studentas>>::value) {
        cout << "Rusiavimas su pradiniu vektoriumi: ";
    } else {
        cout << "Rusiavimas: ";
    }
    auto rusStart1 = high_resolution_clock::now();
    Container GrupeRusiavimui = Grupe;
    rusiuokStudentus(GrupeRusiavimui);
    auto rusEnd1 = high_resolution_clock::now();
    duration<double> rusLaikas1 = rusEnd1 - rusStart1;
    cout << rusLaikas1.count() << "s\n";
    cout << "Studentu dalijimas i dvi grupes: ";
    auto gruStart = high_resolution_clock::now();
    Container Vargsai, Kietiakiai;
    for (const auto &studentas : Grupe) {
        if (studentas.rez_vid < 5.0) {
            Vargsai.push_back(studentas);
        } else {
            Kietiakiai.push_back(studentas);
        }
    }
    rusiuokStudentus(Vargsai);
    rusiuokStudentus(Kietiakiai);
    auto gruEnd = high_resolution_clock::now();
    duration<double> gruLaikas = gruEnd - gruStart;
    cout << gruLaikas.count() << "s\n";
    cout << "Vargsu irasymo i faila laikas: ";
    auto vargsaiStart = high_resolution_clock::now();
    ofstream vargsaiOut("vargsai.txt");
    vargsaiOut << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    vargsaiOut << string(70, '-') << endl;
    vargsaiOut << fixed << setprecision(2);
    for (auto &s : Vargsai) {
        vargsaiOut << setw(20) << s.pav << setw(20) << s.vard << setw(20) << s.rez_vid << setw(20) << s.rez_med << endl;
    }
    vargsaiOut.close();
    auto vargsaiEnd = high_resolution_clock::now();
    duration<double> vargsaiLaikas = vargsaiEnd - vargsaiStart;
    cout << vargsaiLaikas.count() << "s\n";
    cout << "Kietiakiai irasymo i faila laikas: ";
    auto kietStart = high_resolution_clock::now();
    ofstream kietiakiaiOut("kietiakiai.txt");
    kietiakiaiOut << left << setw(20) << "Pavarde" << setw(20) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    kietiakiaiOut << string(70, '-') << endl;
    kietiakiaiOut << fixed << setprecision(2);
    for (auto &s : Kietiakiai) {
        kietiakiaiOut << setw(20) << s.pav << setw(20) << s.vard << setw(20) << s.rez_vid << setw(20) << s.rez_med << endl;
    }
    kietiakiaiOut.close();
    auto kietEnd = high_resolution_clock::now();
    duration<double> kietLaikas = kietEnd - kietStart;
    cout << kietLaikas.count() << "s\n";
}

template void issaugokIFaila<std::vector<Studentas>>(const std::vector<Studentas> &Grupe, const string &failoVardas);
template void issaugokIFaila<std::list<Studentas>>(const std::list<Studentas> &Grupe, const string &failoVardas);
template void issaugokPadalintusStudentus<std::vector<Studentas>>(const std::vector<Studentas> &Vargsai, const std::vector<Studentas> &Kietiakiai);
template void issaugokPadalintusStudentus<std::list<Studentas>>(const std::list<Studentas> &Vargsai, const std::list<Studentas> &Kietiakiai);
template std::vector<Studentas> nuskaitykIsFailo<std::vector<Studentas>>(const string &failoVardas);
template std::list<Studentas> nuskaitykIsFailo<std::list<Studentas>>(const string &failoVardas);
template void rusiuokStudentus<std::vector<Studentas>>(std::vector<Studentas> &Grupe);
template void rusiuokStudentus<std::list<Studentas>>(std::list<Studentas> &Grupe);
template void padalinkStudentus<std::vector<Studentas>>(const std::vector<Studentas> &Grupe, std::vector<Studentas> &Vargsai, std::vector<Studentas> &Kietiakiai);
template void padalinkStudentus<std::list<Studentas>>(const std::list<Studentas> &Grupe, std::list<Studentas> &Vargsai, std::list<Studentas> &Kietiakiai);
template void testuotiPasirinktaFaila<std::vector<Studentas>>(int dydis);
template void testuotiPasirinktaFaila<std::list<Studentas>>(int dydis);









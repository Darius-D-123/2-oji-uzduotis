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

Studentas ivestiStudenta(bool randomMode) {
    Studentas studentas;
    studentas.readStudent(cin, randomMode);
    return studentas;
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
        out << setw(15) << s.pavarde() << setw(15) << s.vardas() << setw(20) << s.rezultatasVidurkis() << setw(20) << s.rezultatasMediana() << endl;
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
        outVargsai << setw(20) << s.pavarde() << setw(20) << s.vardas() << setw(20) << s.rezultatasVidurkis() << setw(20) << s.rezultatasMediana() << endl;
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
        outKietiakiai << setw(20) << s.pavarde() << setw(20) << s.vardas() << setw(20) << s.rezultatasVidurkis() << setw(20) << s.rezultatasMediana() << endl;
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
        string vardas, pavarde;
        
        if (iss >> vardas >> pavarde) {
            s.setVardas(vardas);
            s.setPavarde(pavarde);
            
            vector<int> visiPazymiai;
            string token;
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
                int egzaminas = visiPazymiai.back();
                visiPazymiai.pop_back();
                
                s.setEgzaminas(egzaminas);
                s.setPazymiai(visiPazymiai);
                
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

template<typename Container>
void rusiuokStudentus(Container &Grupe) {
    Grupe.sort(palyginkPagalPavarde);
}

template<>
void rusiuokStudentus<std::vector<Studentas>>(std::vector<Studentas> &Grupe) {
    sort(Grupe.begin(), Grupe.end(), palyginkPagalPavarde);
}

template<typename Container>
void padalinkStudentus1(const Container &Grupe, Container &Vargsai, Container &Kietiakiai) {
    for (const auto &studentas : Grupe) {
        if (studentas.rezultatasVidurkis() < 5.0) {
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
        if (s.rezultatasVidurkis() < 5.0) {
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
        [](const Studentas& s) { return s.rezultatasVidurkis() >= 5.0; });
    
    Vargsai.assign(partition_point, Grupe.end());
    Grupe.erase(partition_point, Grupe.end());
    
    rusiuokStudentus(Vargsai);
    rusiuokStudentus(Grupe);
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
    for (size_t i = pavarde.length() - 1; i != static_cast<size_t>(-1); i--) {
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
    cout << "3 - Strategiju palyginimo testavimas\n";
    cout << "Jusu pasirinkimas (1, 2 arba 3): ";
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
    } else if (pasirinkimas == "3") {
        cout << "\nPasirinkite failo dydi:\n";
        cout << "1 - 1000 irasu\n";
        cout << "2 - 10000 irasu\n";
        cout << "3 - 100000 irasu\n";
        cout << "4 - 1000000 irasu\n";
        cout << "Jusu pasirinkimas (1-4): ";
        string dydzioPasirinkimas;
        getline(cin, dydzioPasirinkimas);
        int dydis = 0;
        if (dydzioPasirinkimas == "1") dydis = 1000;
        else if (dydzioPasirinkimas == "2") dydis = 10000;
        else if (dydzioPasirinkimas == "3") dydis = 100000;
        else if (dydzioPasirinkimas == "4") dydis = 1000000;
        else {
            cout << "Netinkamas pasirinkimas! Naudojamas 1000 irasu.\n";
            dydis = 1000;
        }
        cout << "\nPasirinkite konteineri:\n";
        cout << "1 - std::vector\n";
        cout << "2 - std::list\n";
        cout << "Jusu pasirinkimas (1 arba 2): ";
        string konteinerioPasirinkimas;
        getline(cin, konteinerioPasirinkimas);
        
        if (konteinerioPasirinkimas == "1") {
            testuotiVisasStrategijas<std::vector<Studentas>>(dydis);
        } else if (konteinerioPasirinkimas == "2") {
            testuotiVisasStrategijas<std::list<Studentas>>(dydis);
        } else {
            cout << "Netinkamas pasirinkimas! Naudojamas std::vector.\n";
            testuotiVisasStrategijas<std::vector<Studentas>>(dydis);
        }
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
    cout << "Studentu rusiavimas: ";
    auto rusStart = high_resolution_clock::now();
    rusiuokStudentus(Grupe);
    auto rusEnd = high_resolution_clock::now();
    duration<double> rusLaikas = rusEnd - rusStart;
    cout << rusLaikas.count() << "s\n";
    cout << "Studentu dalijimas i dvi grupes: ";
    auto gruStart = high_resolution_clock::now();
    Container Vargsai, Kietiakiai = Grupe;
    padalinkStudentus2(Kietiakiai, Vargsai);
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
        vargsaiOut << setw(20) << s.pavarde() << setw(20) << s.vardas() << setw(20) << s.rezultatasVidurkis() << setw(20) << s.rezultatasMediana() << endl;
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
        kietiakiaiOut << setw(20) << s.pavarde() << setw(20) << s.vardas() << setw(20) << s.rezultatasVidurkis() << setw(20) << s.rezultatasMediana() << endl;
    }
    kietiakiaiOut.close();
    auto kietEnd = high_resolution_clock::now();
    duration<double> kietLaikas = kietEnd - kietStart;
    cout << kietLaikas.count() << "s\n";
}

template<typename Container>
void testuotiVisasStrategijas(int dydis) {
    string failoVardas = "studentai" + std::to_string(dydis) + ".txt";
    ifstream testas(failoVardas);
    if (!testas) {
        cout << "KLAIDA: Failas " << failoVardas << " nerastas!\n";
        cout << "Pirmiausia sugeneruokite failus pasirinkdami 1 varianta.\n";
        return;
    }
    testas.close();
    cout << "\n=== STRATEGIJU PALYGINIMAS SU " << dydis << " IRASU ===";
    if (std::is_same<Container, std::vector<Studentas>>::value) {
        cout << " (std::vector) ===\n";
    } else {
        cout << " (std::list) ===\n";
    }
    cout << "Nuskaitomas failas... ";
    auto nuskaitymoStart = high_resolution_clock::now();
    Container Grupe = nuskaitykIsFailo<Container>(failoVardas);
    auto nuskaitymoEnd = high_resolution_clock::now();
    duration<double> nuskaitymoLaikas = nuskaitymoEnd - nuskaitymoStart;
    cout << "nuskaitymo laikas: " << nuskaitymoLaikas.count() << "s\n";
    cout << "nuskaityta " << Grupe.size() << " studentu\n\n";
    cout << fixed << setprecision(6);
    cout << "1 STRATEGIJA (dvi kopijos):\n";
    Container Grupe1 = Grupe;
    Container Vargsai1, Kietiakiai1;
    auto start1 = high_resolution_clock::now();
    padalinkStudentus1(Grupe1, Vargsai1, Kietiakiai1);
    auto end1 = high_resolution_clock::now();
    duration<double> laikas1 = end1 - start1;
    cout << "Laikas: " << laikas1.count() << "s\n";
    cout << "2 STRATEGIJA (remove_if):\n";
    Container Grupe2 = Grupe;
    Container Vargsai2;
    auto start2 = high_resolution_clock::now();
    padalinkStudentus2(Grupe2, Vargsai2);
    auto end2 = high_resolution_clock::now();
    duration<double> laikas2 = end2 - start2;
    cout << "Laikas: " << laikas2.count() << "s\n";
    cout << "3 STRATEGIJA (stable_partition):\n";
    Container Grupe3 = Grupe;
    Container Vargsai3;
    auto start3 = high_resolution_clock::now();
    padalinkStudentus3(Grupe3, Vargsai3);
    auto end3 = high_resolution_clock::now();
    duration<double> laikas3 = end3 - start3;
    cout << "Laikas: " << laikas3.count() << "s\n";
}

template void issaugokIFaila<std::vector<Studentas>>(const std::vector<Studentas> &Grupe, const string &failoVardas);
template void issaugokIFaila<std::list<Studentas>>(const std::list<Studentas> &Grupe, const string &failoVardas);
template void issaugokPadalintusStudentus<std::vector<Studentas>>(const std::vector<Studentas> &Vargsai, const std::vector<Studentas> &Kietiakiai);
template void issaugokPadalintusStudentus<std::list<Studentas>>(const std::list<Studentas> &Vargsai, const std::list<Studentas> &Kietiakiai);
template std::vector<Studentas> nuskaitykIsFailo<std::vector<Studentas>>(const string &failoVardas);
template std::list<Studentas> nuskaitykIsFailo<std::list<Studentas>>(const string &failoVardas);
template void rusiuokStudentus<std::vector<Studentas>>(std::vector<Studentas> &Grupe);
template void rusiuokStudentus<std::list<Studentas>>(std::list<Studentas> &Grupe);
template void padalinkStudentus1<std::vector<Studentas>>(const std::vector<Studentas> &Grupe, std::vector<Studentas> &Vargsai, std::vector<Studentas> &Kietiakiai);
template void padalinkStudentus1<std::list<Studentas>>(const std::list<Studentas> &Grupe, std::list<Studentas> &Vargsai, std::list<Studentas> &Kietiakiai);
template void padalinkStudentus2<std::vector<Studentas>>(std::vector<Studentas> &Grupe, std::vector<Studentas> &Vargsai);
template void padalinkStudentus2<std::list<Studentas>>(std::list<Studentas> &Grupe, std::list<Studentas> &Vargsai);
template void padalinkStudentus3<std::vector<Studentas>>(std::vector<Studentas> &Grupe, std::vector<Studentas> &Vargsai);
template void padalinkStudentus3<std::list<Studentas>>(std::list<Studentas> &Grupe, std::list<Studentas> &Vargsai);
template void testuotiPasirinktaFaila<std::vector<Studentas>>(int dydis);
template void testuotiPasirinktaFaila<std::list<Studentas>>(int dydis);
template void testuotiVisasStrategijas<std::vector<Studentas>>(int dydis);
template void testuotiVisasStrategijas<std::list<Studentas>>(int dydis);


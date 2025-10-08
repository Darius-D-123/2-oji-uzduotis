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

struct Studentas {
    string vard;
    string pav;
    int egzas;
    double rez_vid;
    double rez_med;
    vector<int> paz;
};

Studentas ivesk(bool randomMode);
double median(vector<int> v);
vector<Studentas> nuskaitykIsFailo(const string &failoVardas);
void issaugokIFaila(const vector<Studentas> &Grupe, const string &failoVardas);
void parodykFailuSarasa();
void rusiuokStudentus(vector<Studentas> &Grupe);
bool arSkaicius(const string &str);
int gautiSkaiciu(const string &pranesimas);
double apskaiciuotiGalutiniVid(const Studentas &s);
double apskaiciuotiGalutiniMed(const Studentas &s);
int gautiSkaitineReiksmeIsPavardes(const string& pavarde);
bool palyginkStudentusPagalSkaitineReiksme(const Studentas &a, const Studentas &b);
void generuotiStudentuFailus();

int main() {
    srand(time(nullptr));
    vector<Studentas> Grupe;
    int kiek;
    char pasirinkimas;
    cout << "Ar norite generuoti studentu failus? (t/n): ";
    char generuotiFailus;
    cin >> generuotiFailus;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (generuotiFailus == 't' || generuotiFailus == 'T') {
        generuotiStudentuFailus();
        cout << "Studentu failai sugeneruoti sekmingai!\n\n";
    }
    do {
    cout << "Pasirinkite veiksma:\n";
    cout << "  t - generuoti atsitiktinai\n";
    cout << "  n - ivesti ranka\n";
    cout << "  f - nuskaityti is failo\n";
    cin >> pasirinkimas;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       } while (pasirinkimas != 't' && pasirinkimas != 'T' &&
             pasirinkimas != 'n' && pasirinkimas != 'N' &&
             pasirinkimas != 'f' && pasirinkimas != 'F');
    if (pasirinkimas == 'f' || pasirinkimas == 'F') {
        parodykFailuSarasa();
        int failoPasirinkimas = gautiSkaiciu("Pasirinkite faila (iveskite skaiciu 1-6): ");
        string failoVardas;
        switch (failoPasirinkimas) {
            case 1: failoVardas = "studentai1000.txt"; break;
            case 2: failoVardas = "studentai10000.txt"; break;
            case 3: failoVardas = "studentai100000.txt"; break;
            case 4: failoVardas = "studentai1000000.txt"; break;
            case 5: failoVardas = "studentai10000000.txt"; break;
            case 6: failoVardas = "kursiokai.txt"; break;
            default:
                cout << "Netinkamas pasirinkimas! Naudojamas studentai10000.txt\n";
                failoVardas = "studentai10000.txt";
                break;
        }
        cout << "Skaitomas failas: " << failoVardas << endl;
        Grupe = nuskaitykIsFailo(failoVardas);
        if (Grupe.empty()) {
            cout << "Nepavyko nuskaityti studentu duomenu. Programa baigia darba.\n";
            return 1;
        }
    } else {
        int kiek = gautiSkaiciu("Kiek studentu norite ivesti? ");
        bool randomMode = (pasirinkimas == 't' || pasirinkimas == 'T');
        for (int j = 0; j < kiek; j++) {
            cout << "\n--- Studentas " << j + 1 << " ---\n";
            Grupe.push_back(ivesk(randomMode));
        }
    }
    if (!Grupe.empty()) {
        rusiuokStudentus(Grupe);
        issaugokIFaila(Grupe, "rez.txt");
    }
    return 0;
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
        int m;
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

vector<Studentas> nuskaitykIsFailo(const string &failoVardas) {
    vector<Studentas> Grupe;
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
    Grupe.reserve(studentuSkaicius);
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

void issaugokIFaila(const vector<Studentas> &Grupe, const string &failoVardas) {
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

void parodykFailuSarasa() {
    cout << "\nGalimi failai:\n";
    cout << "1. studentai1000.txt (1,000 studentu)\n";
    cout << "2. studentai10000.txt (10,000 studentu)\n";
    cout << "3. studentai100000.txt (100,000 studentu)\n";
    cout << "4. studentai1000000.txt (1,000,000 studentu)\n";
    cout << "5. studentai10000000.txt (10,000,000 studentu)\n";
    cout << "6. kursiokai.txt \n";
}


void rusiuokStudentus(vector<Studentas> &Grupe) {
    sort(Grupe.begin(), Grupe.end(), palyginkStudentusPagalSkaitineReiksme);
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

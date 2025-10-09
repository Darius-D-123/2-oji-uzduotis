#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "studentas.h"
#include "funkcijos.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int main() {
     cout << "Ar norite atlikti greicio testavima? (t/n): ";
    char testavimoPasirinkimas;
    cin >> testavimoPasirinkimas;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (testavimoPasirinkimas == 't' || testavimoPasirinkimas == 'T') {
        testuotiProgramosSparta();
    } else {
    srand(time(nullptr));
    vector<Studentas> Grupe;
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
        vector<Studentas> Vargsai, Kietiakiai;
        padalinkStudentus(Grupe, Vargsai, Kietiakiai);
        issaugokPadalintusStudentus(Vargsai, Kietiakiai);
    }
    return 0;
    }
}

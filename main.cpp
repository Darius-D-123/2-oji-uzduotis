#include <iostream>
#include <vector>
#include <list>
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
using std::list;

int main() {
    cout << "Ar norite atlikti greicio testavima? (t/n): ";
    char testavimoPasirinkimas;
    cin >> testavimoPasirinkimas;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (testavimoPasirinkimas == 't' || testavimoPasirinkimas == 'T') {
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
            cout << "\nPasirinkite konteineri:\n";
            cout << "1 - std::vector\n";
            cout << "2 - std::list\n";
            cout << "Jusu pasirinkimas (1 arba 2): ";
            char konteinerioPasirinkimas;
            cin >> konteinerioPasirinkimas;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
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
            
            if (konteinerioPasirinkimas == '1') {
                testuotiPasirinktaFaila<vector<Studentas>>(dydis);
            } else if (konteinerioPasirinkimas == '2') {
                testuotiPasirinktaFaila<list<Studentas>>(dydis);
            } else {
                cout << "Netinkamas pasirinkimas! Naudojamas std::vector.\n";
                testuotiPasirinktaFaila<vector<Studentas>>(dydis);
            }
        } else if (pasirinkimas == "3") {
            cout << "\nPasirinkite konteineri:\n";
            cout << "1 - std::vector\n";
            cout << "2 - std::list\n";
            cout << "Jusu pasirinkimas (1 arba 2): ";
            char konteinerioPasirinkimas;
            cin >> konteinerioPasirinkimas;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
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
            
            if (konteinerioPasirinkimas == '1') {
                testuotiVisasStrategijas<vector<Studentas>>(dydis);
            } else if (konteinerioPasirinkimas == '2') {
                testuotiVisasStrategijas<list<Studentas>>(dydis);
            } else {
                cout << "Netinkamas pasirinkimas! Naudojamas std::vector.\n";
                testuotiVisasStrategijas<vector<Studentas>>(dydis);
            }
        } else {
            cout << "Netinkamas pasirinkimas!\n";
        }
        cout << "        TESTAVIMAS BAIGTAS\n";
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
            Grupe = nuskaitykIsFailo<vector<Studentas>>(failoVardas);

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
    }

    return 0;
}


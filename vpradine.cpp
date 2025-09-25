#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>

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

struct Studentas {
    string vard;
    string pav;
    vector<int> paz;
    int egzas;
    double rez_vid;
    double rez_med;
};

Studentas ivesk(bool randomMode);
double median(vector<int> v);
vector<Studentas> nuskaitykIsFailo(const string &failoVardas);
void issaugokIFaila(const vector<Studentas> &Grupe, const string &failoVardas);

int main() {
    srand(time(nullptr));
    vector<Studentas> Grupe;
    int kiek;
    char pasirinkimas;
    do {
    cout << "Pasirinkite veiksma:\n";
    cout << "  t - generuoti atsitiktinai\n";
    cout << "  n - ivesti ranka\n";
    cout << "  f - nuskaityti is failo\n";
    cin >> pasirinkimas;
       } while (pasirinkimas != 't' && pasirinkimas != 'T' &&
             pasirinkimas != 'n' && pasirinkimas != 'N' &&
             pasirinkimas != 'f' && pasirinkimas != 'F');
    if (pasirinkimas == 'f' || pasirinkimas == 'F') {
        Grupe = nuskaitykIsFailo("studentai10000.txt");
    } else {
        int kiek;
        cout << "Kiek studentu norite ivesti? ";
        cin >> kiek;
        bool randomMode = (pasirinkimas == 't' || pasirinkimas == 'T');
        for (int j = 0; j < kiek; j++) {
            cout << "\n--- Studentas " << j + 1 << " ---\n";
            Grupe.push_back(ivesk(randomMode));
        }
    }
    if (!Grupe.empty()) {
        cout << "\nRezultatai:\n";
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
        cout << "---------------------------------------------------------------\n";
        cout << fixed << setprecision(2);
        for (auto &s : Grupe) {
            cout << setw(15) << s.pav << setw(15) << s.vard << setw(20) << s.rez_vid << setw(20) << s.rez_med << endl;
        }
    }
}

Studentas ivesk(bool randomMode) {
    Studentas Laik;
    cout << "Iveskite varda: "; cin >> Laik.vard;
    cout << "Iveskite pavarde: "; cin >> Laik.pav;
    if (randomMode) {
        int n = rand() % 8 + 3;
        for (int i = 0; i < n; i++) {
            Laik.paz.push_back(rand() % 10 + 1);
        }
        Laik.egzas = rand() % 10 + 1;
        cout << "Sugeneruoti " << n << " pazymiai ir egzaminas.\n";
    } else {
        int m;
        cout << "Iveskite pazymius (baigti su ne skaiciumi, pvz. ENTER):\n";
        while (true) {
            if (!(cin >> m)) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            Laik.paz.push_back(m);
        }
        cout << "Iveskite egzamino rezultata: ";
        cin >> Laik.egzas;
    }
    double sum = 0.0;
    for (int x : Laik.paz) sum += x;
    double vid = Laik.paz.empty() ? 0 : sum / Laik.paz.size();
    Laik.rez_vid = 0.6 * Laik.egzas + 0.4 * vid;
    Laik.rez_med = 0.6 * Laik.egzas + 0.4 * median(Laik.paz);
    return Laik;
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
    string headerLine;
    getline(in, headerLine);
    string pav, vard;
    int nd1, nd2, nd3, nd4, nd5, egz;
    while (in >> pav >> vard >> nd1 >> nd2 >> nd3 >> nd4 >> nd5 >> egz) {
        Studentas s;
        s.pav = pav;
        s.vard = vard;
        s.paz = {nd1, nd2, nd3, nd4, nd5};
        s.egzas = egz;
        double vid = (nd1 + nd2 + nd3 + nd4 + nd5) / 5.0;
        s.rez_vid = 0.6 * egz + 0.4 * vid;
        s.rez_med = 0.6 * egz + 0.4 * median(s.paz);
        Grupe.push_back(s);
    }
    return Grupe;
}

void issaugokIFaila(const vector<Studentas> &Grupe, const string &failoVardas) {
    ofstream out(failoVardas);
    if (!out) {
        cout << "Klaida: nepavyko sukurti failo " << failoVardas << endl;
        return;
    }
    out << left << setw(15) << "Pavarde"
        << setw(15) << "Vardas"
        << setw(20) << "Galutinis (Vid.)"
        << setw(20) << "Galutinis (Med.)" << endl;
    out << "---------------------------------------------------------------\n";
    out << fixed << setprecision(2);
    for (auto &s : Grupe) {
        out << setw(15) << s.pav
            << setw(15) << s.vard
            << setw(20) << s.rez_vid
            << setw(20) << s.rez_med << endl;
    }
    cout << "Rezultatai issaugoti faile " << failoVardas << endl;
}

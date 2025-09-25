#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::fixed;
using std::setprecision;

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

int main() {
    srand(time(nullptr));
    vector<Studentas> Grupe;
    int kiek;
    char pasirinkimas;
    cout << "Kiek studentu norite ivesti? ";
    cin >> kiek;
    cout << "Ar generuoti pazymius atsitiktinai? (t/n): ";
    cin >> pasirinkimas;
    bool randomMode = (pasirinkimas == 't' || pasirinkimas == 'T');
    for (int j = 0; j < kiek; j++) {
        cout << "\n--- Studentas " << j + 1 << " ---\n";
        Grupe.push_back(ivesk(randomMode));
    }
    cout << "\nRezultatai:\n";
    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << "--------------------------------------------------------------\n";
    cout << fixed << setprecision(2);
    for (auto &s : Grupe) {
        cout << setw(15) << s.vard << setw(15) << s.pav << setw(20) << s.rez_vid << setw(20) << s.rez_med << endl;
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
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 0) {
        return (v[n/2 - 1] + v[n/2]) / 2.0;
    } else {
        return v[n/2];
    }
}

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

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

Studentas ivesk();
double median(vector<int> v);

int main() {
    vector<Studentas> Grupe;
    int kiek;
    cout << "Kiek studentu norite ivesti? ";
    cin >> kiek;
    for (int j = 0; j < kiek; j++) {
        cout << "\nIveskite " << j + 1 << " studenta:\n";
        Grupe.push_back(ivesk());
    }
    cout << "\nRezultatai:\n";
    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << "--------------------------------------------------------------\n";
    cout << fixed << setprecision(2);
    for (auto temp : Grupe) {
        cout << setw(15) << temp.vard << setw(15) << temp.pav << setw(20) << temp.rez_vid << setw(20) << temp.rez_med << endl;
    }
}

Studentas ivesk() {
    Studentas Laik;
    int m;
    cout << "Iveskite varda: "; cin >> Laik.vard;
    cout << "Iveskite pavarde: "; cin >> Laik.pav;
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

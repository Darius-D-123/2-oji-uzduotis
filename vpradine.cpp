#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;

struct Studentas{
    string vard;
    string pav;
    vector<int> paz;
    int egzas;
    float rez;
};
Studentas ivesk();

int main(){
    vector<Studentas> Grupe;
    for (int j=0; j<3; j++){
        cout << "Iveskite " << j+1 << " studentas:\n";
        Grupe.push_back(ivesk());
    }
    cout << "\nRezultatai:\n";
    cout << left << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(10) << "Galutinis" << endl;
    cout << "------------------------------------------\n";

    cout << fixed << setprecision(2);
    for (auto temp : Grupe) {
        cout << setw(15) << temp.vard << setw(15) << temp.pav << setw(10) << temp.rez << endl;
    }
}

Studentas ivesk(){
    Studentas Laik;
    int sum=0, n, m;
    cout << "Iveskite varda: "; cin >> Laik.vard;
    cout << "Iveskite pavarde: "; cin >> Laik.pav;
    cout << "Kiek pazymiu turi studentas: "; cin >> n;
    for (int i=0; i<n; i++) {
        cout << "Iveskite " << i+1 << " paz. is " << n << " : "; cin >> m;
        Laik.paz.push_back(m);
        sum+=m;
        }
    cout << "Iveskite egzamina: "; cin >> Laik.egzas;
    Laik.rez=Laik.egzas*0.6 + double(sum)/double(Laik.paz.size())*0.4;
    return Laik;
}


#include "studentas.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>
#include <stdexcept>
#include <iomanip>

using std::left;
using std::setw;
using std::fixed;
using std::setprecision;

double median(std::vector<int> v) {
    if (v.empty()) return 0.0;
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 0) {
        return (v[n/2 - 1] + v[n/2]) / 2.0;
    } else {
        return v[n/2];
    }
}

Studentas::Studentas() 
    : vardas_(""), pavarde_(""), egzaminas_(0), 
      rezultatas_vidurkis_(0.0), rezultatas_mediana_(0.0) {
}

Studentas::Studentas(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde), egzaminas_(0),
      rezultatas_vidurkis_(0.0), rezultatas_mediana_(0.0) {
}

Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_),
      egzaminas_(other.egzaminas_), pazymiai_(other.pazymiai_),
      rezultatas_vidurkis_(other.rezultatas_vidurkis_),
      rezultatas_mediana_(other.rezultatas_mediana_) {
}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        egzaminas_ = other.egzaminas_;
        pazymiai_ = other.pazymiai_;
        rezultatas_vidurkis_ = other.rezultatas_vidurkis_;
        rezultatas_mediana_ = other.rezultatas_mediana_;
    }
    return *this;
}

Studentas::Studentas(Studentas&& other) noexcept
    : vardas_(std::move(other.vardas_)),
      pavarde_(std::move(other.pavarde_)),
      egzaminas_(other.egzaminas_),
      pazymiai_(std::move(other.pazymiai_)),
      rezultatas_vidurkis_(other.rezultatas_vidurkis_),
      rezultatas_mediana_(other.rezultatas_mediana_) {
    other.vardas_.clear();
    other.pavarde_.clear();
    other.egzaminas_ = 0;
    other.pazymiai_.clear();
    other.rezultatas_vidurkis_ = 0.0;
    other.rezultatas_mediana_ = 0.0;
}

Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
        egzaminas_ = other.egzaminas_;
        pazymiai_ = std::move(other.pazymiai_);
        rezultatas_vidurkis_ = other.rezultatas_vidurkis_;
        rezultatas_mediana_ = other.rezultatas_mediana_;
        other.vardas_.clear();
        other.pavarde_.clear();
        other.egzaminas_ = 0;
        other.pazymiai_.clear();
        other.rezultatas_vidurkis_ = 0.0;
        other.rezultatas_mediana_ = 0.0;
    }
    return *this;
}

Studentas::~Studentas() {
    clearData();
}

void Studentas::clearData() {
    vardas_.clear();
    pavarde_.clear();
    egzaminas_ = 0;
    pazymiai_.clear();
    pazymiai_.shrink_to_fit();
    rezultatas_vidurkis_ = 0.0;
    rezultatas_mediana_ = 0.0;
}

bool Studentas::isEmpty() const {
    return vardas_.empty() && pavarde_.empty() && 
           pazymiai_.empty() && egzaminas_ == 0 &&
           rezultatas_vidurkis_ == 0.0 && rezultatas_mediana_ == 0.0;
}

void Studentas::skaiciuotiRezultatus() {
    if (pazymiai_.empty()) {
        rezultatas_vidurkis_ = 0.6 * egzaminas_;
        rezultatas_mediana_ = 0.6 * egzaminas_;
        return;
    }
    double suma = std::accumulate(pazymiai_.begin(), pazymiai_.end(), 0.0);
    double vidurkis = suma / pazymiai_.size();
    rezultatas_vidurkis_ = 0.6 * egzaminas_ + 0.4 * vidurkis;
    rezultatas_mediana_ = 0.6 * egzaminas_ + 0.4 * median(pazymiai_);
}

void Studentas::setVardas(const std::string& vardas) {
    if (vardas.empty()) {
        throw std::invalid_argument("Vardas negali buti tuscias");
    }
    vardas_ = vardas;
}

void Studentas::setPavarde(const std::string& pavarde) {
    if (pavarde.empty()) {
        throw std::invalid_argument("Pavarde negali buti tuscia");
    }
    pavarde_ = pavarde;
}

void Studentas::setEgzaminas(int egzaminas) {
    if (egzaminas < 1 || egzaminas > 10) {
        throw std::out_of_range("Egzamino pazymys turi buti nuo 1 iki 10");
    }
    egzaminas_ = egzaminas;
    skaiciuotiRezultatus();
}

void Studentas::setPazymiai(const std::vector<int>& pazymiai) {
    for (int pazymys : pazymiai) {
        if (pazymys < 1 || pazymys > 10) {
            throw std::out_of_range("Pazymys turi buti nuo 1 iki 10");
        }
    }
    pazymiai_ = pazymiai;
    skaiciuotiRezultatus();
}

void Studentas::addPazymys(int pazymys) {
    if (pazymys < 1 || pazymys > 10) {
        throw std::out_of_range("Pazymys turi buti nuo 1 iki 10");
    }
    pazymiai_.push_back(pazymys);
    skaiciuotiRezultatus();
}

std::istream& Studentas::readStudent(std::istream& is, bool randomMode) {
    if (!is) return is;

    std::cout << "Iveskite varda: ";
    std::getline(is, vardas_);
    
    std::cout << "Iveskite pavarde: ";
    std::getline(is, pavarde_);

    if (randomMode) {
        pazymiai_.clear();
        int n = rand() % 8 + 3;
        for (int i = 0; i < n; i++) {
            pazymiai_.push_back(rand() % 10 + 1);
        }
        egzaminas_ = rand() % 10 + 1;
        std::cout << "Sugeneruoti " << n << " pazymiai ir egzaminas.\n";
    } else {
        pazymiai_.clear();
        std::cout << "Iveskite pazymius (baigti su 'q'):\n";
        std::string input;
        int pazymiuKiekis = 0;
        
        while (true) {
            std::cout << "Pazymys " << (pazymiuKiekis + 1) << ": ";
            std::getline(is, input);
            if (input == "q" || input == "Q") {
                if (pazymiuKiekis == 0) {
                    std::cout << "Privalote ivesti bent viena pazymi!\n";
                    continue;
                }
                break;
            }
            try {
                int pazymys = std::stoi(input);
                if (pazymys >= 1 && pazymys <= 10) {
                    pazymiai_.push_back(pazymys);
                    pazymiuKiekis++;
                } else {
                    std::cout << "Pazymys turi buti nuo 1 iki 10!\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Netinkamas pazymys! Bandykite dar karta.\n";
            }
        }
        while (true) {
            std::string egzInput;
            std::cout << "Iveskite egzamino rezultata (1-10): ";
            std::getline(is, egzInput);
            try {
                egzaminas_ = std::stoi(egzInput);
                if (egzaminas_ >= 1 && egzaminas_ <= 10) {
                    break;
                } else {
                    std::cout << "Egzamino rezultatas turi buti nuo 1 iki 10!\n";
                }
            } catch (const std::exception& e) {
                std::cout << "Netinkamas egzamino rezultatas! Bandykite dar karta.\n";
            }
        }
    }

    skaiciuotiRezultatus();
    return is;
}

void Studentas::display(std::ostream& os) const {
    os << left << setw(20) << pavarde_ << setw(20) << vardas_
       << fixed << setprecision(2)
       << setw(20) << rezultatas_vidurkis_ 
       << setw(20) << rezultatas_mediana_;
}

bool Studentas::operator<(const Studentas& other) const {
    return pavarde_ < other.pavarde_ || 
          (pavarde_ == other.pavarde_ && vardas_ < other.vardas_);
}

bool Studentas::operator>(const Studentas& other) const {
    return other < *this;
}

bool Studentas::operator==(const Studentas& other) const {
    return vardas_ == other.vardas_ && 
           pavarde_ == other.pavarde_ &&
           egzaminas_ == other.egzaminas_ &&
           pazymiai_ == other.pazymiai_;
}

bool Studentas::operator!=(const Studentas& other) const {
    return !(*this == other);
}

bool Studentas::operator<=(const Studentas& other) const {
    return !(*this > other);
}

bool Studentas::operator>=(const Studentas& other) const {
    return !(*this < other);
}

bool palyginkPagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool palyginkPagalVarda(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool palyginkPagalGalutini(const Studentas& a, const Studentas& b) {
    return a.rezultatasVidurkis() < b.rezultatasVidurkis();
}

std::istream& operator>>(std::istream& is, Studentas& studentas) {
    return studentas.readStudent(is);
}

std::ostream& operator<<(std::ostream& os, const Studentas& studentas) {
    studentas.display(os);
    return os;
}

#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#include "zmogus.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class Studentas : public Zmogus {
private:
    int egzaminas_;
    std::vector<int> pazymiai_;
    double rezultatas_vidurkis_;
    double rezultatas_mediana_;

    void skaiciuotiRezultatus();

public:
    Studentas();
    Studentas(const std::string& vardas, const std::string& pavarde);
    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);
    Studentas(Studentas&& other) noexcept;
    Studentas& operator=(Studentas&& other) noexcept;
    ~Studentas();

    inline int egzaminas() const { return egzaminas_; }
    inline const std::vector<int>& pazymiai() const { return pazymiai_; }
    inline double rezultatasVidurkis() const { return rezultatas_vidurkis_; }
    inline double rezultatasMediana() const { return rezultatas_mediana_; }
    double galutinisBalas() const { return rezultatas_vidurkis_; }

    void setVardas(const std::string& vardas) override;
    void setPavarde(const std::string& pavarde) override;
    void setEgzaminas(int egzaminas);
    void setPazymiai(const std::vector<int>& pazymiai);
    void addPazymys(int pazymys);

    void display(std::ostream& os) const override;
    std::istream& read(std::istream& is) override;

    std::istream& readStudent(std::istream& is, bool randomMode = false);
    void clearData();
    bool isEmpty() const;
    size_t pazymiuSkaicius() const { return pazymiai_.size(); }

    bool operator<(const Studentas& other) const;
    bool operator>(const Studentas& other) const;
    bool operator==(const Studentas& other) const;
    bool operator!=(const Studentas& other) const;
    bool operator<=(const Studentas& other) const;
    bool operator>=(const Studentas& other) const;
};

bool palyginkPagalPavarde(const Studentas& a, const Studentas& b);
bool palyginkPagalVarda(const Studentas& a, const Studentas& b);
bool palyginkPagalGalutini(const Studentas& a, const Studentas& b);

std::istream& operator>>(std::istream& is, Studentas& studentas);
std::ostream& operator<<(std::ostream& os, const Studentas& studentas);

#endif

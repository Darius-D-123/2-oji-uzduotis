#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    int egzaminas_;
    std::vector<int> pazymiai_;
    double rezultatas_vidurkis_;
    double rezultatas_mediana_;
    void skaiciuotiRezultatus();

public:
    Studentas();
    Studentas(const std::string& vardas, const std::string& pavarde);
    Studentas(std::istream& is);
    Studentas(const Studentas& other); 
    Studentas& operator=(const Studentas& other); 
    ~Studentas(); 
    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }
    inline int egzaminas() const { return egzaminas_; }
    inline const std::vector<int>& pazymiai() const { return pazymiai_; }
    inline double rezultatasVidurkis() const { return rezultatas_vidurkis_; }
    inline double rezultatasMediana() const { return rezultatas_mediana_; }
    double galutinisBalas() const { return rezultatas_vidurkis_; }
    void setVardas(const std::string& vardas);
    void setPavarde(const std::string& pavarde);
    void setEgzaminas(int egzaminas);
    void setPazymiai(const std::vector<int>& pazymiai);
    void addPazymys(int pazymys);
    std::istream& readStudent(std::istream& is, bool randomMode = false);
    void display(std::ostream& os) const;
    bool operator<(const Studentas& other) const;
    bool operator>(const Studentas& other) const;
};


#endif


#ifndef ZMOGUS_H_INCLUDED
#define ZMOGUS_H_INCLUDED

#include <string>
#include <iostream>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus() : vardas_(""), pavarde_("") {}
    Zmogus(const std::string& vardas, const std::string& pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}

    virtual ~Zmogus() {}

    virtual void display(std::ostream& os) const = 0;
    virtual std::istream& read(std::istream& is) = 0;

    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }

    virtual void setVardas(const std::string& vardas) { vardas_ = vardas; }
    virtual void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
};

#endif
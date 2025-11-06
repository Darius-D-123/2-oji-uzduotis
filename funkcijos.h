#ifndef FUNKCIJOS_H_INCLUDED
#define FUNKCIJOS_H_INCLUDED

#include <string>
#include <vector>
#include <list>
#include "studentas.h"

using std::string;
using std::vector;
using std::list;

Studentas ivesk(bool randomMode);
void parodykFailuSarasa();
template<typename Container>
void issaugokIFaila(const Container &Grupe, const string &failoVardas);
template<typename Container>
void issaugokPadalintusStudentus(const Container &Vargsai, const Container &Kietiakiai);

template<typename Container>
Container nuskaitykIsFailo(const string &failoVardas);
void generuotiStudentuFailus();
double testuotiFailuKurima();

double median(vector<int> v);
double apskaiciuotiGalutiniVid(const Studentas &s);
double apskaiciuotiGalutiniMed(const Studentas &s);

template<typename Container>
void rusiuokStudentus(Container &Grupe);
template<typename Container>
void padalinkStudentus(const Container &Grupe, Container &Vargsai, Container &Kietiakiai);
bool palyginkStudentusPagalSkaitineReiksme(const Studentas &a, const Studentas &b);

bool arSkaicius(const string &str);
int gautiSkaiciu(const string &pranesimas);
int gautiSkaitineReiksmeIsPavardes(const string& pavarde);

void testuotiProgramosSparta();
template<typename Container>
void testuotiPasirinktaFaila(int dydis);


#endif

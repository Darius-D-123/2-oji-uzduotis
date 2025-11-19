#ifndef FUNKCIJOS_H_INCLUDED
#define FUNKCIJOS_H_INCLUDED

#include <string>
#include <vector>
#include <list>
#include "studentas.h"

using std::string;
using std::vector;
using std::list;

Studentas ivestiStudenta(bool randomMode = false);
void parodykFailuSarasa();
template<typename Container>
void issaugokIFaila(const Container &Grupe, const string &failoVardas);
template<typename Container>
void issaugokPadalintusStudentus(const Container &Vargsai, const Container &Kietiakiai);

template<typename Container>
Container nuskaitykIsFailo(const string &failoVardas);
void generuotiStudentuFailus();
double testuotiFailuKurima();

template<typename Container>
void rusiuokStudentus(Container &Grupe);
template<typename Container>
void padalinkStudentus1(const Container &Grupe, Container &Vargsai, Container &Kietiakiai);
template<typename Container>
void padalinkStudentus2(Container &Grupe, Container &Vargsai);
template<typename Container>
void padalinkStudentus3(Container &Grupe, Container &Vargsai);

bool arSkaicius(const string &str);
int gautiSkaiciu(const string &pranesimas);
int gautiSkaitineReiksmeIsPavardes(const string& pavarde);

void testuotiProgramosSparta();
template<typename Container>
void testuotiPasirinktaFaila(int dydis);
template<typename Container>
void testuotiVisasStrategijas(int dydis);


#endif

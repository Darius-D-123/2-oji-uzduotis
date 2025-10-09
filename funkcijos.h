#ifndef FUNKCIJOS_H_INCLUDED
#define FUNKCIJOS_H_INCLUDED

#include <string>
#include <vector>
#include "studentas.h"

using std::string;
using std::vector;

Studentas ivesk(bool randomMode);
void parodykFailuSarasa();
void issaugokIFaila(const vector<Studentas> &Grupe, const string &failoVardas);
void issaugokPadalintusStudentus(const vector<Studentas> &Vargsai, const vector<Studentas> &Kietiakiai);

vector<Studentas> nuskaitykIsFailo(const string &failoVardas);
void generuotiStudentuFailus();
double testuotiFailuKurima();

double median(vector<int> v);
double apskaiciuotiGalutiniVid(const Studentas &s);
double apskaiciuotiGalutiniMed(const Studentas &s);

void rusiuokStudentus(vector<Studentas> &Grupe);
void padalinkStudentus(const vector<Studentas> &Grupe, vector<Studentas> &Vargsai, vector<Studentas> &Kietiakiai);
bool palyginkStudentusPagalSkaitineReiksme(const Studentas &a, const Studentas &b);

bool arSkaicius(const string &str);
int gautiSkaiciu(const string &pranesimas);
int gautiSkaitineReiksmeIsPavardes(const string& pavarde);

void testuotiProgramosSparta();
void testuotiPasirinktaFaila(int dydis);

#endif

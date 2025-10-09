#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Studentas {
    string vard;
    string pav;
    int egzas;
    double rez_vid;
    double rez_med;
    vector<int> paz;
};

#endif

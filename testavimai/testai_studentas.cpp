#include "studentas.h"
#include "funkcijos.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <vector>
#include <string>
#include <sstream>
#include <utility>

TEST_CASE("Default constructor sukuria tuscia studenta", "[ctor][default]") {
    Studentas s;

    REQUIRE(s.vardas() == "");
    REQUIRE(s.pavarde() == "");
    REQUIRE(s.egzaminas() == 0);
    REQUIRE(s.pazymiai().empty());
    REQUIRE(s.rezultatasVidurkis() == Catch::Approx(0.0));
    REQUIRE(s.rezultatasMediana() == Catch::Approx(0.0));
    REQUIRE(s.isEmpty() == true);
}

TEST_CASE("Parametrized constructor nustato varda ir pavarde", "[ctor][param]") {
    Studentas s("Vardenis", "Pavardenis");

    REQUIRE(s.vardas() == "Vardenis");
    REQUIRE(s.pavarde() == "Pavardenis");
}

TEST_CASE("Copy constructor nukopijuoja duomenis", "[copy][ctor]") {
    Studentas a("Vardenis", "Pavardenis");
    a.setPazymiai({5, 8, 7});
    a.setEgzaminas(5);

    Studentas b(a);
    REQUIRE(b == a);
}

TEST_CASE("Copy assignment operator nukopijuoja duomenis", "[copy][assign]") {
    Studentas a("Vardenis", "Pavardenis");
    a.setPazymiai({5, 8, 7});
    a.setEgzaminas(5);

    Studentas b;
    b = a;

    REQUIRE(b == a);
}

TEST_CASE("Move constructor perkelia duomenis", "[move][ctor]") {
    Studentas a("Vardenis", "Pavardenis");
    a.setPazymiai({5, 8, 7});
    a.setEgzaminas(5);

    Studentas b(std::move(a));

    REQUIRE(b.vardas() == "Vardenis");
    REQUIRE(b.pavarde() == "Pavardenis");
    REQUIRE(b.egzaminas() == 5);
    REQUIRE(b.pazymiai() == std::vector<int>({5, 8, 7}));

    REQUIRE(a.egzaminas() == 0);
    REQUIRE(a.rezultatasVidurkis() == Catch::Approx(0.0));
    REQUIRE(a.rezultatasMediana() == Catch::Approx(0.0));
}

TEST_CASE("Move assignment operator perkelia duomenis", "[move][assign]") {
    Studentas a("Vardenis", "Pavardenis");
    a.setPazymiai({5, 8, 7});
    a.setEgzaminas(5);

    Studentas b("X", "Y");
    b = std::move(a);

    REQUIRE(b.vardas() == "Vardenis");
    REQUIRE(b.pavarde() == "Pavardenis");
    REQUIRE(b.egzaminas() == 5);
    REQUIRE(b.pazymiai() == std::vector<int>({5, 8, 7}));

    REQUIRE(a.egzaminas() == 0);
    REQUIRE(a.rezultatasVidurkis() == Catch::Approx(0.0));
    REQUIRE(a.rezultatasMediana() == Catch::Approx(0.0));
}

TEST_CASE("Getteriai grazina teisingas reiksmes", "[getters]") {
    Studentas s("Vardenis", "Pavardenis");
    s.setPazymiai({5, 8, 7});
    s.setEgzaminas(5);

    REQUIRE(s.vardas() == "Vardenis");
    REQUIRE(s.pavarde() == "Pavardenis");
    REQUIRE(s.egzaminas() == 5);
    REQUIRE(s.pazymiai().size() == 3);
}

TEST_CASE("operator<< isveda varda ir pavarde", "[io]") {
    Studentas s("Vardenis", "Pavardenis");
    std::ostringstream oss;
    oss << s;

    REQUIRE(oss.str().find("Vardenis") != std::string::npos);
    REQUIRE(oss.str().find("Pavardenis") != std::string::npos);
}

# 1-oji užduotis

## Aprašymas
Programa skirta studentų duomenų apdorojimui ir rūšiavimui į dvi kategorijas.

## Releasai

### v0.1
Sukurtas kodas, kuriame galima:
- Įvesti studentų duomenis rankiniu būdu.
- Generuoti studentų duomenis atsitiktinai.
- Nuskaityti studentų duomenis iš failo.
- Apskaičiuoti galutinį balą naudojant vidurkį.
- Apskaičiuoti galutinį balą naudojant medianą.
- Naudoti patogų programos meniu su pasirinkimais.


### v0.2
Pridėta studentų duomenų generavimas kur sukuriami 5 skirtingų dydžių failai: 1,000; 10,000; 100,000; 1,000,000; 10,000,000 įrašų. <br />
Pridėtas studentų kategorizavimas - skirstymas į dvi grupes: <br />
**Vargsai** - galutinis balas < 5.0 <br /> 
**Kietiakiai** - galutinis balas >= 5.0 <br />
Pridėtas spartos testavimas ir projekto struktūra. <br />
Atlikti testavimai su 1 tūkstančių, 10 tūkstančių, 100 tūkstančių, 1 milijonų, 10 milijonų studentų įrašų buvo kartojami 

#### Testavimai
| Įrašų skaičius | Nuskaitymas | Rūšiavimas | Dalijimas | Vargšų įrašymas | Kietiakų įrašymas |
| :--- | :---: | :---: | :---: | :---: | :---: |
| 1 k | 7.11 ms | 4.39 ms | 4.26 ms | 2.36 ms | 2.85 ms |
| 10 k | 38.30 ms | 84.97 ms | 75.17 ms | 17.13 ms | 23.62 ms |
| 100 k | 0.39 s | 1.24 s | 1.14 s | 0.16 s | 0. 23 s |
| 1 mil | 3.80 s | 16.44 s | 15.44 s | 1.49 s | 2.22 s |
| 10 mil | 38.34 s | 227.34 s | 213.82 s | 14.66 s | 20.99 s |

#### Išvados
Didėjant duomenims, rūšiavimas užima daugiausiai laiko, o įrašymas yra greičiausias, ypač vargšams.

### v0.3
Atlikti testavimai su 1 tūkstančių, 10 tūkstančių, 100 tūkstančių, 1 milijonų, 10 milijonų studentų įrašų, kur buvo skaičiuojami šie veiksmų laikai: failo nuskaitymo į konteinerį, studentų rūšiavimo konteinerio viduje, studentų dalijimo į dvi grupes, vargšų įrašymo į failą ir kietiakų įrašymo į failą, palyginant `std::vector` ir `std::list`konteinerių našumą. <br />

#### Sistemos parametrai
CPU - Intel i5-12400f, 2500 Mhz, 6 Core(s), 12 Logical Processor(s) <br />
GPU - AMD Radeon RX 6700 XT, 12 GB VRAM <br /> 
RAM - 16 GB  3200 MHz<br />
SSD - Crucial P3 M.2 500GB <br />

#### Testavimai
|  Konteinerio tipas | Įrašų skaičius | Nuskaitymas | Rūšiavimas | Dalijimas | Vargšų įrašymas | Kietiakų įrašymas |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: |
| std::vector | 1 k | 4.02 ms | 4.29 ms | 4.14 ms | 2.23 ms | 2.96 ms |
| std::list | 1 k | 3.71 ms | 2.22 ms | 2.28 ms | 2.22 ms | 3.05 ms |
| std::vector | 10 k | 36.32 ms | 76.03 ms | 67.52 ms | 17.99 ms | 24.47 ms |
| std::list | 10 k | 34.78 ms | 36.17 ms | 34.23 ms | 18.76 ms | 24.70 ms |
| std::vector | 100 k | 0.36 s | 1.10 s | 1.04 s | 0.18 s | 0. 23 s |
| std::list | 100 k | 0.35 s | 0.50 s | 0.46 s | 0.17 s | 0.25 s |
| std::vector | 1 mil | 3.47 s | 14.68 s | 13.88 s | 1.65 s | 2.33 s |
| std::list | 1 mil| 3.52 s | 6.19 s | 6.19 s | 1.63 s | 2.47 s |
| std::vector | 10 mil | 37.91 s | 206.66 s | 194.08 s | 13.42 s | 13.42 s |
| std::list | 10 mil| 39.58 s | 85.55 s | 85.47 s | 13.53 s | 19.24 s |

#### Išvados
`std::list` dažniausiai efektyvesnis rūšiavimo ir dalijimo operacijose, o `std::vector` – įrašant į vargšus didelėje apimtyje.


<img width="348" height="307" alt="image" src="https://github.com/user-attachments/assets/b68e1cd0-01b5-432e-9de5-179f28757904" />


<img width="340" height="317" alt="image" src="https://github.com/user-attachments/assets/c76cc278-a9f1-49c4-ba06-f921b2c03046" />


### V1.0

Pridėtos trys strategijos ir jos testuojamos tarpusavyje su 1 tūkstančių, 10 tūkstančių, 100 tūkstančių, 1 milijonų, 10 milijonų studentų įrašų, kur buvo skaičiuojamas studentų dalijimo į dvi grupes greitis. Testavimo lentelėje duomenys yra 5 bandymų vidurkiai.

#### Testavimai

|  Konteinerio tipas | Strategija | 1 k | 10 k | 100 k | 1 mil | 10 mil |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: |
| std::vector | 1 | 5.58 ms | 71.66 ms | 1.08 s | 14.85 s | 216.96 s |
| std::vector | 2 | 4.25 ms | 69.69 ms | 1.07 s | 14.81 s | 218.15 s |
| std::vector | 3 | 4.26 ms | 70.68 ms | 1.08 s | 15.86 s | 216.66 s |
| std::list | 1 | 2.37 ms | 35.81 ms | 0.48 s | 6.71 s | 92.50 s |
| std::list | 2 | 2.35 ms | 34.43 ms | 0.47 s | 6.63 s | 90.28 s |
| std::list | 3 | 2.38 ms | 36.18 ms | 0.49 s | 6.69 s | 92.26 s |

#### Išvados

Remiantis testavimais, matome, kad 2 strategija yra šiek tiek greitesnė už kitas strategijas, o tarp 1 ir 3 strategijų skirtumas labai minimalus, bet vis tiek vėlesnės už 2 strategiją.

<img width="394" height="192" alt="image" src="https://github.com/user-attachments/assets/5b9b39c0-b09a-4daa-9afc-644c587b242e" />

<img width="383" height="198" alt="image" src="https://github.com/user-attachments/assets/3f366e84-e752-4881-85bd-26d925c10e3c" />


### Įdiegimo instrukcija

1. Atsisiųsti programą <br />
`git clone https://github.com/Darius-D-123/1-uzduotis.git` <br />
`cd 1-uzduotis` <br />
2. Kompiliuoti programą <br />
`g++ -std=c++11 -O2 -o studentu_rusiavimas.exe src\main.cpp src\funkcijos.cpp -Isrc` <br />
3. Paleisti programą <br />
`.\studentu_rusiavimas.exe` <br />

### Naudojimosi instrukcija

1. **Paleiskite programą:** `.\studentu_rusiavimas.exe`

2. **Pasirinkite:**
   - `t` - testuoti greitį
   - `n` - netestuoti greičio

3. **Jei pasirinkote `t`, tada atsiras parinktys:**
   - **Testavimo tipas:** `1` (failai), `2` (veikimas), `3` (strategijos)

4. **Jei pasirinkote 2 arba 3, tada atsiras parinktys:**
   - **Konteineris:** `1` (vector) arba `2` (list)
   - **Failo dydis:** `1` (1,000), `2` (10,000), `3` (100,000), `4` (1,000,000), `5` (10,000,000)

5. **Jei pasirinkote `n` (2 punkte), tada parinkite:**
   - `t` - generuoti studentų failus
   - `n` - negeneruoti studentų failų

6. **Jei pasirinkote `n` (5 punkte), tada parinkite:**
   - `t` - generuoti atsitiktinai
   - `n` - įvesti ranka
   - `f` - nuskaityti iš failo


# 2-oji užduotis

## Releasai

### v1.1

Šioje versijoje `struct Studentas` pakeistas į `class Studentas` ir realizuoti konstruktoriai ir destruktoriai.

#### Testavimai

Testavimas atliktas buvo 5 kartus visais atvejais su 100 tūkstančių, 1 milijonų studentų įrašų ir išvesti jų vidurkiai.

|  Studentas tipas |  Konteinerio tipas | Įrašų skaičius | Nuskaitymas | Rūšiavimas | Dalijimas | Vargšų įrašymas | Kietiakų įrašymas |
| :--- | :--- | :--- | :---: | :---: | :---: | :---: | :---: |
| struct | std::list | 100 k | 1.18 s | 2.08 s | 2.07 s | 0.30 s | 0.45 s |
| class | std::list | 100 k | 0.22 s | 0.02 s | 0.04 s | 0.15 s | 0.22 s |
| struct | std::list | 1 mil | 12.66 s | 29.28 s | 28.93 s | 3.09 s | 4.77 s |
| class | std::list | 1 mil | 2.28 s | 0.23 s | 0.45 s | 1.46 s | 2.13 s |

#### Išvados

Remiantis testavimais, matome, kad konvertavimas iš struct į class suteikė nuo 10 iki 12 kartų greičio padidinimą, ypač pastebimą su dideliais duomenų kiekiais.

#### Testavimai

Testavimas atliktas buvo 5 kartus visais atvejais su 1 milijonų, 10 milijonų studentų įrašų ir išvesti jų vidurkiai.

|  Optimizavimas |  EXE Dydis | Įrašų skaičius | Nuskaitymas | Rūšiavimas | Dalijimas | Vargšų įrašymas | Kietiakų įrašymas |
| :--- | :--- | :--- | :---: | :---: | :---: | :---: | :---: |
| O1 | 273.32 KB | 1 mil | 2.30 s | 0.24 s | 0.45 s | 1.34 s | 2.04 s |
| O2 | 270.82 KB | 1 mil | 2.26 s | 0.24 s | 0.45 s | 1.34 s | 2.02 s |
| O3 | 267.23 KB | 1 mil | 2.24 s | 0.22 s | 0.43 s | 1.33 s | 1.99 s |
| O1 | 273.32 KB | 10 mil | 22.85 s | 2.96 s | 4.92 s | 13.59 s | 19.58 s |
| O2 | 270.82 KB | 10 mil | 22.41 s | 2.99 s | 4.94 s | 13.44 s | 19.40 s |
| O3 | 267.23 KB | 10 mil | 22.20 s | 2.74 s | 4.69 s | 13.43 s | 19.36 s |

#### Išvados

Remiantis testavimais, matome, kad optimizavimo lygiai O1, O2 ir O3 suteikė nuo 2% iki 7% papildomą greičio padidinimą, o didžiausias efektas pasiektas su O3 optimizavimu ir dideliais duomenų kiekiais.

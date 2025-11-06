# 1-uzduotis

# v0.2
Pridėta studentų duomenų generavimas kur sukuriami 5 skirtingų dydžių failai: 1,000; 10,000; 100,000; 1,000,000; 10,000,000 įrašų.
Pridėtas studentų kategorizavimas - skirstymas į dvi grupes:
Vargsai - galutinis balas < 5.0
Kietiakiai - galutinis balas >= 5.0
Pridėtas spartos testavimas ir projekto struktūra.

# v0.3
Atliktas testavimas su 100 tūkstančių studentų įrašų, kur buvo skaičiuojami šie veiksmų laikai: failo nuskaitymo į konteinerį, studentų rūšiavimo konteinerio viduje, studentų dalijimo į dvi grupes, vargšų įrašymo į failą ir kietiakų įrašymo į failą, palyginant `std::vector` ir `std::list`konteinerių našumą. <br />
## Sistemos parametrai
CPU - Intel i5-12400f, 2500 Mhz, 6 Core(s), 12 Logical Processor(s) <br />
GPU - AMD Radeon RX 6700 XT, 12 GB VRAM <br /> 
RAM - 16 GB <br />
SSD - Samsung SSD 860 EVO 250 GB <br />

## Rezultatai
Buvo atlikti 5 testavimai su kiekvienu konteineriu.


### std::vector vidurkiai:
Nuskaitymas: 1.086 s <br />
Rūšiavimas: 4.509 s  <br />
Dalijimas: 4.219 s <br />
Vargšų įrašymas: 0.267 s <br />
Kietiakų įrašymas: 0.383 s <br />

### std::list vidurkiai:
Nuskaitymas: 1.089 s <br />
Rūšiavimas: 1.932 s <br />
Dalijimas: 1.786 s <br />
Vargšų įrašymas: 0.267 s <br />
Kietiakų įrašymas: 0.391 s <br />



<img width="404" height="303" alt="image" src="https://github.com/user-attachments/assets/f3858852-1d39-4027-8f32-fcdf6792b69e" />

<img width="410" height="296" alt="image" src="https://github.com/user-attachments/assets/cfa956aa-2a70-4954-ba31-d9fd5f299dfa" />



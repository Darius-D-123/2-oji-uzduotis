# 1-uzduotis

# v0.2
Pridėta studentų duomenų generavimas kur sukuriami 5 skirtingų dydžių failai: 1,000; 10,000; 100,000; 1,000,000; 10,000,000 įrašų.
Pridėtas studentų kategorizavimas - skirstymas į dvi grupes:
Vargsai - galutinis balas < 5.0
Kietiakiai - galutinis balas >= 5.0
Pridėtas spartos testavimas ir projekto struktūra.

# v0.3
Atlikti testavimai su 1 tūkstančių, 10 tūkstančių, 100 tūkstančių, 1 milijonų, 10 milijonų studentų įrašų, kur buvo skaičiuojami šie veiksmų laikai: failo nuskaitymo į konteinerį, studentų rūšiavimo konteinerio viduje, studentų dalijimo į dvi grupes, vargšų įrašymo į failą ir kietiakų įrašymo į failą, palyginant `std::vector` ir `std::list`konteinerių našumą. <br />
## Sistemos parametrai
CPU - Intel i5-12400f, 2500 Mhz, 6 Core(s), 12 Logical Processor(s) <br />
GPU - AMD Radeon RX 6700 XT, 12 GB VRAM <br /> 
RAM - 16 GB  3200 MHz<br />
SSD - Crucial P3 M.2 500GB <br />

## Testavimai
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



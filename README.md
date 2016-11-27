# Program magazynowy Wicher
Program powstał jako zadanie na stopień ćwika. Pozwala on na zautomatyzowanie działań związanych z magazynem harcerskim, automatyczne podliczanie stanu magazynu, szeroko rozwinięty system komentarzy do przedmiotów oraz tworzenie dokumentów wydań oraz przyjęć sprzętu.
Strona domowa: https://majudev.net/wicher
  
## Zależności
Gtkmm 3.20 lub wyższe  
jansson 2.7 lub wyższe  
g++ 5.1 lub wyższe  
  
## Instalacja zależności
### Windows 32 bity (MSYS2)
### Windows 64 bity (MSYS2)
### Debian
Instalujemy kompilator 32 i 64 bitowy, a następnie biblioteki:
```
sudo apt-get install libjansson-dev gtkmm-3.0-dev
```
## Kompilacja
Pobieramy repozytorium:
```
git clone --recursive https://github.com/majudev/wicher.git
```
Wchodzimy do katalogu i kompilujemy program:
```
cd wicher  
./bootstrap  
./configure  
make
```
## Instalacja
### Windows 64 bity (MSYS2)
### Windows 32 bity (MSYS2)
### Debian
Instalujemy:
```
sudo make install
```
## Licencja
Licencja znajduje się w pliku LICENSE.

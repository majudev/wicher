# Program magazynowy Wicher
To jest repozytorium zawierające zestaw narzędzi ułatwiających kompilację programu Wicher.  
Aby skompilować projekt, należy zainstalować podążać za instrukcjami w pliku INSTALL.  
  
## Zależności
Gtkmm 3.20 lub wyższe  
jansson 2.7 lub wyższe  
g++ 5.1 lub wyższe  
  
## Kompilacja - Windows 32 bity:
## Kompilacja - Windows 64 bity:
## Kompilacja - Debian
Instalujemy kompilator 32 i 64 bitowy, a następnie biblioteki:
```
sudo apt-get install libjansson-dev gtkmm-3.0-dev
```
Pobieramy repozytorium:
```
git clone --recursive https://github.com/majudev/wicher.git
```
Wchodzimy do katalogu i kompilujemy program:
```
cd wicher  
./make.sh
```
Tworzymy paczki deb:
```
./gen.sh
```
## Licencja
Licencja znajduje się w pliku LICENSE.

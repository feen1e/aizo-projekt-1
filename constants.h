#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string>

inline const std::string MENU = R"MENU(
-------------------Menu-------------------
1 - Zmień typ elementów tablicy
2 - Zmień liczbę elementów w tablicy
3 - Wygeneruj nową losową tablicę
4 - Załaduj tablicę z pliku
5 - Wyświetl tablicę
6 - Zmień algorytm sortowania
7 - Posortuj tablicę
8 - Porównanie czasu sortowań
0 - Zakończ działanie programu
------------------------------------------
)MENU";

inline const std::string COMPARE_SORTS = R"CS(
--------Porównanie czasu sortowań---------
Funkcja ta spowoduje utworzenie pliku results.txt
zawierającego czasy sortowania każdego z algorytmów
dla dwóch typów danych o różnych długościach tablic.
Wykonanie może zająć dużo czasu.
Czy chcesz kontynuować? (T/N) )CS";

inline const std::string CHANGE_SORTING_ALGORITHM = R"CSA(
--------Wybór algorytmu sortowania--------
1 - Sortowanie przez wstawianie
2 - Sortowanie przez kopcowanie
3 - Sortowanie Shella - wzór Shella
4 - Sortowanie Shella - wzór Tokudy
5 - Sortowanie szybkie - skrajny lewy
6 - Sortowanie szybkie - skrajny prawy
7 - Sortowanie szybkie - mediana z trzech
8 - Sortowanie szybkie - losowy
------------------------------------------
Wprowadź numer wybranej opcji: )CSA";

inline const std::string CHANGE_TYPE = R"CT(
----------Zmiana typu elementów-----------
1 - Liczby całkowite - int
2 - Liczby zmiennoprzecinkowe - float
------------------------------------------
Wprowadź numer wybranej opcji: )CT";

inline const std::string CHANGE_SIZE = R"CS(
---------Zmiana liczby elementów----------
Wprowadź liczbę elementów: )CS";

inline const std::string WRITE_NUMBER = R"WN(
Wprowadź numer wybranej opcji: )WN";

inline const std::string PRINT_ARRAY = R"PA(
------------Zawartość tablicy-------------
)PA";

inline const std::string LOAD_FILE = R"LF(
------------Wczytywanie pliku-------------
Wprowadź ścieżkę do pliku: )LF";

#endif //CONSTANTS_H

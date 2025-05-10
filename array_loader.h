#ifndef ARRAY_LOADER_H
#define ARRAY_LOADER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


// ładowanie tablicy z pliku
class ArrayLoader {
public:
    template <typename T>
    static int loadArrayFromFile(const std::string& fileName, std::vector<T>& array) {
        std::ifstream file(fileName);

        if (!file.is_open()) {
            std::cerr << "Nie można otworzyć pliku" << std::endl;
        }

        int n; // pierwsza liczba to długość tablicy
        file >> n;
        array = std::vector<T>(n);

        for (int i = 0; i < n; i++) {
            double value;
            file >> value;  // Obsługa różnych typów
            array[i] = static_cast<T>(value);
        }

        file.close();
        return n;
    }
};



#endif //ARRAY_LOADER_H

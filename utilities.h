#ifndef UTILITIES_H
#define UTILITIES_H
#include <chrono>
#include <iostream>
#include <vector>

// Funkcje pomocnicze

class Utilities {
public:
    // wypisanie czasu
    static void print_time(const std::chrono::steady_clock::time_point start, const std::chrono::steady_clock::time_point end) {
        std::cout << "------------------------------------------\n";
        std::cout << "Czas sortowania: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
        << " (" << (end - start) << ")." << std::endl;
        std::cout << "------------------------------------------\n";
    }
    // wypisanie tablicy
    template<typename T>
    static void print_array(std::vector<T> array) {
        std::cout << "\n-----------Posortowana tablica------------\n";
        const int n = array.size();
        if (typeid(T) == typeid(int)) {
            for (int i = 0; i < n; i++) {
                printf("%4d", array[i]);
                if (i != n - 1) {
                    std::cout << ", ";
                }
                if ((i + 1) % 10 == 0) {
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
        } else if (typeid(T) == typeid(float)) {
            for (int i = 0; i < n; i++) {
                printf("%11.6f", array[i]);
                if (i != n - 1) {
                    std::cout << ", ";
                }
                if ((i + 1) % 10 == 0) {
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;
        }
    }
};



#endif //UTILITIES_H

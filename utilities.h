#ifndef UTILITIES_H
#define UTILITIES_H
#include <iostream>
#include <vector>

// Funkcje pomocnicze

template<typename T>
class Utilities {
public:
    void printArray(std::vector<T> &array) {
        std::cout << "Array of type " << typeid(T).name() << std::endl;
        for (T i: array) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};



#endif //UTILITIES_H

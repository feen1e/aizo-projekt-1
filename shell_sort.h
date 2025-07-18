﻿#ifndef SHELL_SORT_H
#define SHELL_SORT_H
#include <vector>
#include <cmath>
#include <algorithm>


// Sortowanie Shella
class ShellSort {
private:
    bool tokudasFormula = false; // false - wzór Shella, true - Tokudy

    static std::vector<int> generateTokudaGaps(const int n) {
        std::vector<int> gaps;
        int k = 0;
        while (true) {
            int gap = std::ceil((9 * (std::pow(9.0 / 4.0, k-1)) - 4) / 5);
            if (gap >= n) {
                break;
            }
            gaps.push_back(gap);
            k++;
        }
        std::ranges::reverse(gaps); // Reverse, żeby kroki były od największego
        return gaps;
    }

public:
    void setTokudaFormula(bool f) {
        tokudasFormula = f;
    }
    template<typename T>
    void sort(std::vector<T> &array) {
        const int n = array.size();
        if (!tokudasFormula) { // sekwencja shella
            for (int gap = n / 2; gap > 0; gap /= 2) {
                for (int i = gap; i < n; i++) {
                    T temp = array[i];

                    int j;
                    for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                        array[j] = array[j - gap];
                    }

                    array[j] = temp;
                }
            }
        } else { // sekwencja tokudy
            const std::vector<int> gaps = generateTokudaGaps(n);

            for (const int gap: gaps) {
                for (int i = gap; i < n; i++) {
                    T temp = array[i];
                    int j = i;
                    while (j >= gap && array[j - gap] > temp) {
                        array[j] = array[j - gap];
                        j -= gap;
                    }
                    array[j] = temp;
                }
            }
        }
    }
};


#endif //SHELL_SORT_H

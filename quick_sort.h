#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include <fstream>
#include <vector>



class QuickSort {
private:
    int partition_method = 0; // 0 - skrajny lewy, 1 - skrajny prawy, 2 - środkowy, 3 - losowy

    template<typename T>
    void quickSort(std::vector<T> &array, const int left, const int right) {
        if (left >= right) {
            return;
        }

        int border = partition(array, left, right);

        // najpierw posortuj krótszą część
        if (border - left < right - border) {
            quickSort(array, left, border - 1);
            quickSort(array, border + 1, right);
        } else {
            quickSort(array, border + 1, right);
            quickSort(array, left, border - 1);
        }
    }

    template<typename T>
    int partition(std::vector<T> &array, const int left, const int right) {
        choosePivot(array, left, right);
        T pivot = array[right]; // pivot jest zawsze po prawej
        int border = left - 1;

        for (int i = left; i < right; i++) {
            if (array[i] < pivot) {
                border++;
                std::swap(array[i], array[border]);
            }
        }

        border++;
        std::swap(array[right], array[border]);
        return border;
    }

    template<typename T>
    void choosePivot(std::vector<T> &array, const int left, const int right) {
        switch (partition_method) {
            case 0: { // skrajny lewy
                std::swap(array[left], array[right]);
                break;
            }
            case 1: { // skrajny prawy
                break;
            }
            case 2: { // środkowy
                int mid = left + (right - left) / 2;
                std::swap(array[mid], array[right]);
                break;
            }
            case 3: { // losowy
                int r = left + rand() % (right - left + 1);
                std::swap(array[r], array[right]);
                break;
            }
            default: {
                throw std::invalid_argument("Błąd. Dana metoda wybrania pivota nie istnieje.");
                break;
            }
        }
    }

public:
    void setPartitionMethod(const int method) {
        partition_method = method;
    }

    template<typename T>
    void sort(std::vector<T> &array) {
        if (!array.empty()) {
            if (partition_method == 3) {
                srand(time(nullptr));
            }
            quickSort(array, 0, array.size() - 1);
        }

    }
};


#endif //QUICK_SORT_H

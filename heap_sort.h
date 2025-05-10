#ifndef HEAP_SORT_H
#define HEAP_SORT_H
#include <vector>


// Sortowanie przez kopcowanie
class HeapSort {
private:
    template <typename T>
    void heapify(std::vector<T>& array, const int n, const int i) {
        // znajdowanie najwiekszej wartosci sposrod rodzica i dzieci
        int largest = i;
        const int left = 2 * i + 1;
        const int right = 2 * i + 2;

        if (left < n && array[left] > array[largest])
            largest = left;

        if (right < n && array[right] > array[largest])
            largest = right;

        // zamiana i dalsze kopcowanie jesli korzen nie jest najwiekszy
        if (largest != i) {
            std::swap(array[i], array[largest]);
            heapify(array, n, largest);
        }
    }

public:
    template <typename T>
    void sort(std::vector<T>& array) {
        const int n = array.size();
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(array, n, i);
        }
        for (int i = n - 1; i > 0; i--) {
            std::swap(array[0], array[i]);
            heapify(array, i, 0);
        }
    }
};



#endif //HEAP_SORT_H

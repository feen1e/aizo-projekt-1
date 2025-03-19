#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include <fstream>
#include <vector>


template<typename T>
class QuickSort {
private:
    //int partition_method;

    void quickSort(std::vector<T> &array, int left, int right) {
        if (left >= right) {
            return;
        }

        int border = partition(array, left, right);

        if (border - left < right - border) {
            quickSort(array, left, border - 1);
            quickSort(array, border + 1, right);
        } else {
            quickSort(array, border + 1, right);
            quickSort(array, left, border - 1);
        }
    }

    int partition(std::vector<T> &array, int left, int right) {
        choosePivot(array, left, right);
        T pivot = array[right]; // pivot is always on the right side
        int border = left - 1;

        for (int i = left; i < right; i++) {
            if (array[i] < pivot) {
                border++;
                std::swap(array[i], array[border]);
            }
        }

        border++;
        //if (border != right) {
        std::swap(array[right], array[border]);
        //}
        return border;
    }

    void choosePivot(std::vector<T> &array, int left, int right) {

        int mid = left + (right - left) / 2;

        // sort array[left], array[mid], array[right] to find the median
        if (array[mid] < array[left]) {
            std::swap(array[mid], array[left]);
        }
        if (array[right] < array[left]) {
            std::swap(array[right], array[left]);
        }
        if (array[right] < array[mid]) {
            std::swap(array[right], array[mid]);
        }

        // move median to the end
        std::swap(array[mid], array[right]);
    }

public:
    void sort(std::vector<T> &array) {
        if (!array.empty()) {
            quickSort(array, 0, array.size() - 1);
        }
    }
};


#endif //QUICK_SORT_H

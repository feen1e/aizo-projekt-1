#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H
#include <vector>



class InsertionSort {
public:
    template <typename T>
     void sort(std::vector<T> &array) {
        for (size_t i = 1; i < array.size(); i++) {
            T current = array[i];
            size_t index = i;
            while (index > 0 && array[index - 1] > current) {
                array[index] = array[index - 1];
                index--;
            }
            array[index] = current;
        }
    }
};



#endif //INSERTION_SORT_H

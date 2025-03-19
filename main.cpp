#include "utilities.h"
#include "insertion_sort.h"
#include "quick_sort.h"

int main() {
    Utilities<int> intHelper;
    Utilities<float> floatHelper;

    std::vector<int> array = {7, 5, 4, 3, 2, 1};
    std::vector<float> array2 = {12.42, 12.11, 56.23, 1.23, 6.32};

    InsertionSort<int> intInsertion;
    //intInsertion.sort(array);

    InsertionSort<float> floatInsertion;
    //floatInsertion.sort(array2);

    QuickSort<int> intQuick;
    intQuick.sort(array);

    QuickSort<float> floatQuick;
    floatQuick.sort(array2);

    intHelper.printArray(array);
    floatHelper.printArray(array2);
    return 0;
}



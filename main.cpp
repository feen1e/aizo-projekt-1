#include "main.h"

#include <chrono>
#include <windows.h>
#include "constants.h"
#include "utilities.h"
#include "insertion_sort.h"
#include "heap_sort.h"
#include "shell_sort.h"
#include "quick_sort.h"
#include "hundred_results.h"

void menu();

int main() {
    SetConsoleOutputCP(65001);

    menu();
    return 0;

    Utilities<int> intHelper;
    Utilities<float> floatHelper;
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    std::vector<int> array = {7, 5, 4, 3, 2, 1};
    std::vector<float> array2 = {12.42, 12.11, 56.23, 1.23, 6.32};

    InsertionSort<int> intInsertion;
    //intInsertion.sort(array);

    InsertionSort<float> floatInsertion;
    //floatInsertion.sort(array2);

    QuickSort<int> intQuick;
    start = std::chrono::steady_clock::now();
    intQuick.sort(array);
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

    QuickSort<float> floatQuick;
    start = std::chrono::steady_clock::now();
    floatQuick.sort(array2);
    end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

    intHelper.printArray(array);
    floatHelper.printArray(array2);
}

void menu() {
    Main app;

    int option;
    do {
        std::cout << MENU;
        app.print_current_parameters();
        std::cout << WRITE_NUMBER;
        std::cin >> option;
        switch (option) {
            case 1: {
                app.change_type();
                break;
            }
            case 2: {
                app.change_size();
                break;
            }
            case 3: {
                app.generate_array();
                break;
            }
            case 4: {
                app.load_array_from_file();
                break;
            }
            case 5: {
                app.print_array();
                break;
            }
            case 6: {
                app.change_sorting_algorithm();
                break;
            }
            case 7: {
                app.sort_array();
                break;
            }
            case 8: {
                HundredResults results;
                results.get_results();
                break;
            }
            default: break;
        }
    }
    while (option != 0);
}

void Main::print_current_parameters() const {
    std::string t;
    std::string algorithm;

    if (Main::current_type == 1) {
        t = "int";
    } else if (Main::current_type == 2) {
        t = "float";
    }

    switch (Main::sorting_algorithm) {
        case 1: {
            algorithm = "przez wstawianie";
            break;
        }
        case 2: {
            algorithm = "przez kopcowanie";
            break;
        }
        case 3: {
            algorithm = "Shella - algorytm 1";
            break;
        }
        case 4: {
            algorithm = "Shella - algorytm 2";
            break;
        }
        case 5: {
            algorithm = "szybkie - pivot skrajny lewy";
            break;
        }
        case 6: {
            algorithm = "szybkie - pivot skrajny prawy";
            break;
        }
        case 7: {
            algorithm = "szybkie - pivot mediany z trzech";
            break;
        }
        case 8: {
            algorithm = "szybkie - pivot losowy";
            break;
        }
        default: break;
    }

    std::cout << "Typ: " << t << std::endl;
    std::cout << "Rozmiar: " << Main::array_size << std::endl;
    std::cout << "Sortowanie " << algorithm << std::endl;
}

void Main::change_type() {
    int t;
    do {
        std::cout << CHANGE_TYPE;
        std::cin >> t;
    } while (t != 1 && t != 2);
    Main::current_type = t;
}

void Main::change_size() {
    size_t size;
    do {
        std::cout << CHANGE_SIZE;
        std::cin >> size;
    } while (size < 1);
    Main::array_size = size;
}

void Main::generate_array() {

}

void Main::load_array_from_file() {

}

void Main::print_array() {

}

void Main::change_sorting_algorithm() {

}

void Main::sort_array() {

}

#include "main.h"

#include <chrono>
#include <random>
#include <windows.h>

#include "array_loader.h"
#include "comparison_generator.h"
#include "constants.h"
#include "heap_sort.h"
#include "insertion_sort.h"
#include "quick_sort.h"
#include "shell_sort.h"
#include "utilities.h"

void menu();

int main() {
    SetConsoleOutputCP(65001); // Włączenie UTF-8 w konsoli, żeby poprawnie wyświetlać polskie znaki

    menu();

    return 0;
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
                ComparisonGenerator results;
                results.get_results();
                // TODO
                break;
            }
            default: break;
        }
    } while (option != 0);
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
            algorithm = "Shella (wzór Shella)";
            break;
        }
        case 4: {
            algorithm = "Shella (wzór Tokudy)";
            break;
        }
        case 5: {
            algorithm = "szybkie (pivot skrajny lewy)";
            break;
        }
        case 6: {
            algorithm = "szybkie (pivot skrajny prawy)";
            break;
        }
        case 7: {
            algorithm = "szybkie (pivot mediany z trzech)";
            break;
        }
        case 8: {
            algorithm = "szybkie (pivot losowy)";
            break;
        }
        default: break;
    }

    std::cout << "Typ: " << t << std::endl;
    std::cout << "Rozmiar: " << Main::array_size << std::endl;
    std::cout << "Sortowanie " << algorithm << std::endl;
}

void Main::change_type() {
    int_array.clear();
    float_array.clear();
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
    if (Main::current_type == 1) {
        int_array = std::vector<int>(Main::array_size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(-100, 100);

        for (int i = 0; i < Main::array_size; i++) {
            int_array[i] = dis(gen);
        }
    } else if (Main::current_type == 2) {
        float_array = std::vector<float>(Main::array_size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-100.0, 100.0);

        for (int i = 0; i < Main::array_size; i++) {
            float_array[i] = dis(gen);
        }
    } else {
        throw std::invalid_argument("Błąd. Taki typ nie istnieje.");
    }
}

void Main::load_array_from_file() {
    std::string filename;
    std::cout << LOAD_FILE;
    std::cin >> filename;
    if (Main::current_type == 1) {
        Main::array_size = ArrayLoader::loadArrayFromFile(filename, int_array);
    } else {
        Main::array_size = ArrayLoader::loadArrayFromFile(filename, float_array);
    }
}

void Main::change_sorting_algorithm() {
    int s;
    do {
        std::cout << CHANGE_SORTING_ALGORITHM;
        std::cin >> s;
    } while (s < 1 || s > 8);
    Main::sorting_algorithm = s;
}

template<typename T, typename Sorter>
void sort_and_print(std::vector<T> &array, Sorter sorter) {
    const auto start = std::chrono::steady_clock::now();
    sorter.sort(array);
    const auto end = std::chrono::steady_clock::now();
    Utilities::print_array(array);
    Utilities::print_time(start, end);
}

void Main::sort_array() const {
    Main::print_array();
    if (Main::int_array.empty() && Main::float_array.empty()) {
        return;
    }

    // Wybór typu danych
    bool is_int = (Main::current_type == 1);

    // Przygotowanie tablicy do sortowania
    std::vector<int> int_array_copy;
    std::vector<float> float_array_copy;

    if (is_int) {
        int_array_copy = Main::int_array;
    } else {
        float_array_copy = Main::float_array;
    }

    // Sortowanie według wybranego algorytmu
    switch (Main::sorting_algorithm) {
        case 1: {
            // Insertion Sort
            if (is_int)
                sort_and_print(int_array_copy, InsertionSort());
            else
                sort_and_print(float_array_copy, InsertionSort());
            break;
        }
        case 2: {
            // Heap Sort
            if (is_int)
                sort_and_print(int_array_copy, HeapSort());
            else
                sort_and_print(float_array_copy, HeapSort());
            break;
        }
        case 3:
        case 4: {
            // Shell Sort; jeśli wybrano 4, to używamy wzoru Tokudy; w przeciwnym wypadku Shella
            const bool use_tokuda = (Main::sorting_algorithm == 4);
            ShellSort shell_sort;
            shell_sort.setTokudaFormula(use_tokuda);
            if (is_int) {
                sort_and_print(int_array_copy, shell_sort);
            } else {
                sort_and_print(float_array_copy, shell_sort);
            }
            break;
        }
        case 5:
        case 6:
        case 7:
        case 8: {
            // Quick Sort; algorytmy wybierania pivota to wartości od 0 do 3 więc odejmujemy 5 od wybranej opcji
            const int partition_method = Main::sorting_algorithm - 5;
            QuickSort quick_sort;
            quick_sort.setPartitionMethod(partition_method);
            if (is_int) {
                sort_and_print(int_array_copy, quick_sort);
            } else {
                quick_sort.setPartitionMethod(partition_method);
                sort_and_print(float_array_copy, quick_sort);
            }
            break;
        }
        default:
            break;
    }
}

void Main::print_array() const {
    if (!Main::int_array.empty()) {
        std::cout << PRINT_ARRAY;
        for (int i = 0; i < Main::array_size; i++) {
            std::cout << int_array[i];
            if (i != Main::array_size - 1) {
                std::cout << ", ";
            }
            if (i % 10 == 0 && i != 0) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    } else if (!Main::float_array.empty()) {
        std::cout << PRINT_ARRAY;
        for (int i = 0; i < Main::array_size; i++) {
            std::cout << float_array[i];
            if (i != Main::array_size - 1) {
                std::cout << ", ";
            }
            if (i % 10 == 0 && i != 0) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "Nie wygenerowano ani nie wczytano jeszcze żadnej tablicy." << std::endl;
    }
}

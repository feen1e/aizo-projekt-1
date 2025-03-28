#include "comparison_generator.h"

#include <chrono>
#include <fstream>
#include <future>
#include <random>

#include "heap_sort.h"
#include "insertion_sort.h"
#include "main.h"
#include "quick_sort.h"
#include "shell_sort.h"


class Sorting {
public:
    int current_type = 1;
    size_t array_size = 50;
    int sorting_algorithm = 1;
    std::vector<int> int_array;
    std::vector<float> float_array;
    int sort_duration = 0;

    void generate_array();

    void sort_array();

    void sort_100_times_10_increments(std::string &results);
};


void ComparisonGenerator::get_results() {
    std::ofstream file("results.csv");

    file << "typ;liczba elementów;algorytm sortowania;czas sortowania\n";

    // kolejne sortowania
    std::vector<std::tuple<int, int>> sorting_configs = {
        {1, 1}, // int - Insertion sort
        {1, 2}, // Heap sort
        {1, 3}, // Shell sort S
        {1, 4}, // Shell sort T
        {1, 5}, // Quick sort (l)
        {1, 6}, // Quick sort (r)
        {1, 7}, // Quick sort (m)
        {1, 8}, // Quick sort (rand)
        {2, 1}, // analogicznie ale float
        {2, 2},
        {2, 3},
        {2, 4},
        {2, 5},
        {2, 6},
        {2, 7},
        {2, 8}
    };

    std::vector<std::string> results;
    int index = 0;
    for (const auto& [type, algorithm] : sorting_configs) {
        std::string result;
        Sorting sorting_instance;
        sorting_instance.current_type = type;
        sorting_instance.sorting_algorithm = algorithm;

        std::cout << index << "/" << sorting_configs.size() << std::endl;
        sorting_instance.sort_100_times_10_increments(result);

        results.push_back(result);
    }

    for (const auto& result : results) {
        file << result;
    }

    file.close();
}

template<typename T, typename Sorter>
int sort_and_get_ms(std::vector<T> &array, Sorter sorter) {
    const auto start = std::chrono::steady_clock::now();
    sorter.sort(array);
    const auto end = std::chrono::steady_clock::now();
    return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

void Sorting::generate_array() {
    if (current_type == 1) {
        int_array = std::vector<int>(array_size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(-10000, 10000);

        for (int i = 0; i < array_size; i++) {
            int_array[i] = dis(gen);
        }
    } else if (current_type == 2) {
        float_array = std::vector<float>(array_size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-10000.0, 10000.0);

        for (int i = 0; i < array_size; i++) {
            float_array[i] = dis(gen);
        }
    }
}

void Sorting::sort_array() {
    const bool is_int = (current_type == 1);
    std::vector<int> int_array_copy;
    std::vector<float> float_array_copy;

    if (is_int) {
        int_array_copy = int_array;
    } else {
        float_array_copy = float_array;
    }

    switch (sorting_algorithm) {
        case 1: {
            if (is_int)
                sort_duration = sort_and_get_ms(int_array_copy, InsertionSort());
            else
                sort_duration = sort_and_get_ms(float_array_copy, InsertionSort());
            break;
        }
        case 2: {
            if (is_int)
                sort_duration = sort_and_get_ms(int_array_copy, HeapSort());
            else
                sort_duration = sort_and_get_ms(float_array_copy, HeapSort());
            break;
        }
        case 3:
        case 4: {
            const bool use_tokuda = (sorting_algorithm == 4);
            ShellSort shell_sort;
            shell_sort.setTokudaFormula(use_tokuda);
            if (is_int) {
                sort_duration = sort_and_get_ms(int_array_copy, shell_sort);
            } else {
                sort_duration = sort_and_get_ms(float_array_copy, shell_sort);
            }
            break;
        }
        case 5:
        case 6:
        case 7:
        case 8: {
            const int partition_method = sorting_algorithm - 5;
            QuickSort quick_sort;
            quick_sort.setPartitionMethod(partition_method);
            if (is_int) {
                sort_duration = sort_and_get_ms(int_array_copy, quick_sort);
            } else {
                sort_duration = sort_and_get_ms(float_array_copy, quick_sort);
            }
            break;
        }
        default:
            break;
    }
}

void Sorting::sort_100_times_10_increments(std::string &results) {
    std::cout << "start!" << std::endl;
    for (int n = 1; n <= 10; n++) {
        if (sorting_algorithm == 1) {
            array_size = 1000 * n;
        } else {
            array_size = 10000 * n;
        }
        for (int i = 0; i < 100; i++) {
            generate_array();
            sort_array();

            std::string data_type;
            if (current_type == 1) {
                data_type = "int";
            } else {
                data_type = "float";
            }

            std::string algorithm;
            switch (sorting_algorithm) {
                case 1: {
                    algorithm = "Przez wstawianie";
                    break;
                }
                case 2: {
                    algorithm = "Przez kopcowanie";
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
                    algorithm = "Szybkie (pivot skrajny lewy)";
                    break;
                }
                case 6: {
                    algorithm = "Szybkie (pivot skrajny prawy)";
                    break;
                }
                case 7: {
                    algorithm = "Szybkie (pivot mediany z trzech)";
                    break;
                }
                case 8: {
                    algorithm = "Szybkie (pivot losowy)";
                    break;
                }
                default: break;
            }
            std::cout << "|";
            results += data_type + ";" + std::to_string(array_size) + ";" + algorithm + ";" + std::to_string(
                sort_duration) + "\n";
        }
        std::cout << std::endl;
    }
}

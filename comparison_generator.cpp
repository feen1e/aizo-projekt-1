#include "comparison_generator.h"

#include <chrono>
#include <fstream>
#include <random>
#include <vector>
#include <filesystem>

#include "heap_sort.h"
#include "insertion_sort.h"
#include "main.h"
#include "quick_sort.h"
#include "shell_sort.h"

// zmienne globalne do zarzadzania generowaniem
static int array_generation_method = 0;
static int index = 1;
static int file_index = 1;
static size_t base_size = 10000;

// klasa odpowiedzialna za generowanie porownania
class Sorting {
public:
    int current_type = 1; // typ elementow tablicy
    size_t array_size = 50; // rozmiar tablicy
    int sorting_algorithm = 1; // aktualny algorytm sortowania
    std::vector<int> int_array; // tablica intow
    std::vector<float> float_array; // tablica floatow
    int sort_duration = 0; // mierzenie czasu
    std::mt19937 gen = std::mt19937(std::random_device()()); // generowanie liczb pseudolosowych

    void generate_array();

    void generate_random();

    void generate_sorted();

    void generate_reversed();

    void generate_one_third();

    void generate_two_thirds();

    static void generate_results(std::ofstream &result_file, const std::vector<std::tuple<int, int> > &sorting_configs);

    void sort_array();

    void sort_100_times_10_increments(std::ofstream &result_file);
};

// generowanie porownania: 5 plikow po 160 linii -> (8 sposobow sortowania * 2 typy danych * 10 roznych rozmiarow) -> sredni czas z kazdego
void ComparisonGenerator::get_results() {
    std::filesystem::create_directories("results"); // tworzymy katalog results jesli nie istnieje
    // tworzymy pliki na wyniki
    std::ofstream random_results_file("results/1_random_results.csv");
    std::ofstream sorted_results_file("results/2_sorted_results.csv");
    std::ofstream reversed_results_file("results/3_reversed_results.csv");
    std::ofstream one_third_results_file("results/4_one_third_results.csv");
    std::ofstream two_thirds_results_file("results/5_two_thirds_results.csv");

    // umieszczamy je w wektorze
    std::vector<std::ofstream> results_files;
    results_files.push_back(std::move(random_results_file));
    results_files.push_back(std::move(sorted_results_file));
    results_files.push_back(std::move(reversed_results_file));
    results_files.push_back(std::move(one_third_results_file));
    results_files.push_back(std::move(two_thirds_results_file));

    // konfiguracje sortowania
    std::vector<std::tuple<int, int> > sorting_configs = {
        {1, 1}, // int - Insertion sort
        {1, 2}, // Heap sort
        {1, 3}, // Shell sort Shell
        {1, 4}, // Shell sort Tokuda
        {1, 5}, // Quick sort (lewy)
        {1, 6}, // Quick sort (prawy)
        {1, 7}, // Quick sort (sredni)
        {1, 8}, // Quick sort (losowy)
        {2, 1}, // analogicznie ale float
        {2, 2},
        {2, 3},
        {2, 4},
        {2, 5},
        {2, 6},
        {2, 7},
        {2, 8}
    };

    index = 1;
    file_index = 1;
    array_generation_method = 0;

    std::string header = "typ,liczba elementów,średni czas sortowania,algorytm sortowania\n"; // naglowek
    for (auto &result_file: results_files) {
        // przechodzenie po kazdym z plikow
        result_file << header; // zapisujemy naglowek do pliku
        Sorting::generate_results(result_file, sorting_configs);
        result_file.close();
        array_generation_method++; // kolejna metoda generowania: losowe -> posortowane -> odwrotnie -> w 1/3 -> w 2/3
        if (array_generation_method > 4) {
            break;
        }
    }
}

// generuje wyniki dla wszystkich konfiguracji sortowania z sorting_configs
void Sorting::generate_results(std::ofstream &result_file, const std::vector<std::tuple<int, int> > &sorting_configs) {
    for (const auto &[type, algorithm]: sorting_configs) {
        Sorting sorting_instance;
        sorting_instance.current_type = type;
        sorting_instance.sorting_algorithm = algorithm;

        std::cout << "\n[" << index++ << "/" << sorting_configs.size() * 5 << "] (" << file_index << "/5 - " << type <<
                "/2 - " << algorithm << "/8)" << std::endl;
        sorting_instance.sort_100_times_10_increments(result_file);
        std::cout << "✓\n";
    }
    file_index++;
}

// sortowanie tablicy i zwracanie czasu w ms
template<typename T, typename Sorter>
int sort_and_get_ms(std::vector<T> &array, Sorter sorter) {
    const auto start = std::chrono::steady_clock::now();
    sorter.sort(array);
    const auto end = std::chrono::steady_clock::now();
    return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

// funkcja generujaca tablice w zaleznosci od aktualnej metody
void Sorting::generate_array() {
    switch (array_generation_method) {
        case 0: {
            Sorting::generate_random();
            break;
        }
        case 1: {
            Sorting::generate_sorted();
            break;
        }
        case 2: {
            Sorting::generate_reversed();
            break;
        }
        case 3: {
            Sorting::generate_one_third();
            break;
        }
        case 4: {
            Sorting::generate_two_thirds();
            break;
        }
        default: {
            break;
        }
    }
}

// generowanie losowych
void Sorting::generate_random() {
    if (current_type == 1) {
        int_array = std::vector<int>(array_size);
        std::uniform_int_distribution<int> dis(-10000, 10000);
        for (size_t i = 0; i < array_size; i++) {
            int_array[i] = dis(gen);
        }
    } else if (current_type == 2) {
        float_array = std::vector<float>(array_size);
        std::uniform_real_distribution<float> dis(-10000.0, 10000.0);
        for (size_t i = 0; i < array_size; i++) {
            float_array[i] = dis(gen);
        }
    }
}

// generowanie posortowanych
void Sorting::generate_sorted() {
    if (current_type == 1) {
        int_array = std::vector<int>(array_size);
        std::uniform_int_distribution<int> dis(-1000, 1000);
        for (size_t i = 0; i < array_size; i++) {
            int_array[i] = dis(gen);
        }
        std::ranges::sort(int_array);
    } else if (current_type == 2) {
        float_array = std::vector<float>(array_size);
        std::uniform_real_distribution<float> dis(-1000.0, 1000.0);
        for (size_t i = 0; i < array_size; i++) {
            float_array[i] = dis(gen);
        }
        std::ranges::sort(float_array);
    }
}

// generowanie posortowanych odwrotnie
void Sorting::generate_reversed() {
    if (current_type == 1) {
        int_array = std::vector<int>(array_size);
        std::uniform_int_distribution<int> dis(-1000, 1000);
        for (size_t i = 0; i < array_size; i++) {
            int_array[i] = dis(gen);
        }
        std::ranges::sort(int_array);
        std::ranges::reverse(int_array);
    } else if (current_type == 2) {
        float_array = std::vector<float>(array_size);
        std::uniform_real_distribution<float> dis(-1000.0, 1000.0);
        for (size_t i = 0; i < array_size; i++) {
            float_array[i] = dis(gen);
        }
        std::ranges::sort(float_array);
        std::ranges::reverse(float_array);
    }
}

// generowanie posortowanych w 1/3
void Sorting::generate_one_third() {
    const size_t third = array_size / 3;
    if (current_type == 1) {
        int_array = std::vector<int>(array_size);
        std::uniform_int_distribution<int> dis(-1000, 1000);
        for (size_t i = 0; i < array_size; i++) {
            int_array[i] = dis(gen);
        }
        std::ranges::sort(int_array);
        std::shuffle(int_array.begin() + third, int_array.end(), gen); // shuffle elementow od 1/3 do konca
    } else if (current_type == 2) {
        float_array = std::vector<float>(array_size);
        std::uniform_real_distribution<float> dis(-1000.0, 1000.0);
        for (size_t i = 0; i < array_size; i++) {
            float_array[i] = dis(gen);
        }
        std::ranges::sort(float_array);
        std::shuffle(float_array.begin() + third, float_array.end(), gen);
    }
}

// generowanie posortowanych w 2/3
void Sorting::generate_two_thirds() {
    const size_t two_thirds = array_size * 2 / 3;
    if (current_type == 1) {
        int_array = std::vector<int>(array_size);
        std::uniform_int_distribution<int> dis(-1000, 1000);
        for (size_t i = 0; i < array_size; i++) {
            int_array[i] = dis(gen);
        }
        std::ranges::sort(int_array);
        std::shuffle(int_array.begin() + two_thirds, int_array.end(), gen); // shuffle elementow od 2/3 do konca
    } else if (current_type == 2) {
        float_array = std::vector<float>(array_size);
        std::uniform_real_distribution<float> dis(-1000.0, 1000.0);
        for (size_t i = 0; i < array_size; i++) {
            float_array[i] = dis(gen);
        }
        std::ranges::sort(float_array);
        std::shuffle(float_array.begin() + two_thirds, float_array.end(), gen);
    }
}

// sortowanie w zaleznosci od aktualnej metody
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

// wykonuje po 100 sortowan dla 10 roznych rozmiarow, oblicza srednia i zapisuje do pliku
void Sorting::sort_100_times_10_increments(std::ofstream &result_file) {
    for (int n = 1; n <= 10; n++) {
        // zmniejszenie rozmiaru tablicy w przypadkach zajmujacych duzo czasu lub dajacych zbyt gleboka rekurencje
        if (sorting_algorithm == 1) {
            array_size = base_size / 10 * n + base_size / 2;
        } else if ((sorting_algorithm == 5 || sorting_algorithm == 6)
                   && (array_generation_method == 1 || array_generation_method == 2 || array_generation_method == 3 ||
                       array_generation_method == 4)) {
            array_size = base_size / 10 * n;
        } else { // w przeciwnym wypadku rozmiar normalny
            array_size = base_size * n;
        }

        double total_sort_duration = 0;
        for (int i = 0; i < 100; i++) {
            generate_array();
            sort_array();
            total_sort_duration += sort_duration;
        }
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
                algorithm = "Szybkie (pivot środkowy)";
                break;
            }
            case 8: {
                algorithm = "Szybkie (pivot losowy)";
                break;
            }
            default: break;
        }
        std::cout << ". avg ";
        total_sort_duration /= 100;
        std::cout << total_sort_duration << " ms" << std::endl;
        result_file << data_type + "," + std::to_string(array_size) + "," + std::to_string(total_sort_duration) + "," +
                algorithm + "\n";
    }
}

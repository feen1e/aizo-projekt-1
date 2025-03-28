#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <vector>



class Main {
private:
    int current_type = 1;
    size_t array_size = 50;
    int sorting_algorithm = 1;
    std::vector<int> int_array;
    std::vector<float> float_array;

public:
    void change_type();
    void change_size();
    void change_sorting_algorithm();
    void print_current_parameters() const;
    void generate_array();
    void load_array_from_file();
    void sort_array() const;
    void print_array() const;
};



#endif //MAIN_H

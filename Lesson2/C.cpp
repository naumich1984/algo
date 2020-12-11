/*
C. Цифровая сортировка
ограничение по времени на тест3 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Дано n строк, выведите их порядок после k фаз цифровой сортировки.

В этой задаче требуется реализовать цифровую сортировку.

Входные данные
В первой строке входного файла содержится число n — количество строк, m — их длина и k – число фаз цифровой сортировки (1≤n≤1000, 1≤k≤m≤1000). В следующих n строках находятся сами строки.

Выходные данные
Выведите строки в порядке в котором они будут после k фаз цифровой сортировки.
*/

// L2, task: C, DS-12 Naumovskiy Alexey
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
 
void print_result(std::vector <std::pair <int, std::string>>& digits_vector) {
    for (int i = 0; i < digits_vector.size(); i++) {
        std::cout << digits_vector[i].second << std::endl;
    }
}
 
void fill_vector(std::vector <std::pair <int, std::string>>& digits_vector, int count_strings) {
    std::string buff = "";
    for (int i = 0; i < count_strings; i++) {
        std::cin >> buff;
        digits_vector[i].first = 0;
        digits_vector[i].second = buff;
    }
}
 
void sort_digital(std::vector <std::pair <int, std::string>>& digits_vector, 
        const int count_strings, const int count_phases, const int len_strings, const int MAX_CHR_VALUE) {
    for (int k = 0; k < count_phases; k++) {
        std::vector <int>  cnt_vector(MAX_CHR_VALUE);
        for (int i = 0; i < count_strings; i++) {
            digits_vector[i].first = (int)digits_vector[i].second[len_strings - 1 - k]; // с младшего до старшего разряда (по числу фаз)
            cnt_vector[digits_vector[i].first]++;
        }
        std::vector <int>  position_vector(MAX_CHR_VALUE);
        position_vector[0] = 0;
        for (int i = 1; i < MAX_CHR_VALUE; i++) {
            position_vector[i] = position_vector[i - 1] + cnt_vector[i - 1];
        }
        std::vector <std::pair <int, std::string>> temp_vector(count_strings);
        for (int i = 0; i < count_strings; i++) {
            temp_vector[position_vector[digits_vector[i].first]++] = digits_vector[i];
        }
        std::swap(temp_vector, digits_vector);
    }
}
 
int main()
{
    int count_strings;
    int len_strings;
    int count_phases;
    const int MAX_CHR_VALUE = 256;
    std::cin >> count_strings >> len_strings >> count_phases;
    std::vector <std::pair <int, std::string>> digits_vector(count_strings);
 
    fill_vector(digits_vector, count_strings);
    sort_digital(digits_vector, count_strings, count_phases, len_strings, MAX_CHR_VALUE);
    print_result(digits_vector);
    return 0;
}

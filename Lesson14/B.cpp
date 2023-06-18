// L14, task: B, DS-12 Naumovskiy Alexey
/*
B. Z-функция
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Постройте Z-функцию для заданной строки s.

Входные данные
Первая строка входного файла содержит s (1 ≤ |s| ≤ 106). Строка состоит из букв латинского алфавита.

Выходные данные
Выведите значения Z-функции строки s для индексов 2, 3, ..., |s|.
*/
#include <iostream>
#include <vector>
#include <string>

class BuildZfunc {
    std::string full_string;
    int size_string;
    std::vector<int> z_func_values;
    void z_function();
 public:
     BuildZfunc();
     ~BuildZfunc() { z_func_values.clear(); };
     void get_z_values();
};

BuildZfunc::BuildZfunc() {
    std::string full_string;
    std::cin >> full_string;
    this->full_string = full_string;
    this->size_string = full_string.length();
    z_func_values = std::vector<int>(size_string);
}

void BuildZfunc::z_function() {
    z_func_values[0] = 0;
    int left = 0;
    int right = 0;
    for (int i = 1; i < size_string; ++i) {
        if (i <= right) {
            z_func_values[i] = std::min(right - i + 1, z_func_values[i - left]);
        }
        while (i + z_func_values[i] < size_string && full_string[z_func_values[i]] == full_string[i + z_func_values[i]]) {
            z_func_values[i]++;
        }
        if (i + z_func_values[i] - 1 > right) {
            left = i;
            right = i + z_func_values[i] - 1;
        }
    }
}

void BuildZfunc::get_z_values() {
    z_function();
    for (int i = 1; i < size_string; ++i) {
        std::cout << z_func_values[i] << " ";
    }
}

int main() {
    BuildZfunc current_z_values;
    current_z_values.get_z_values();
    return 0;
}

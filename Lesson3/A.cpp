/*
A. Приближенный двоичный поиск
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Даны два массива. Первый массив отсортирован по неубыванию, второй массив содержит запросы — целые числа.

Для каждого запроса выведите число из первого массива наиболее близкое (то есть с минимальным модулем разности) к числу в этом запросе . Если таких несколько, выведите меньшее из них.

Входные данные
В первой строке входных данных содержатся числа n и k (0 < n, k ≤ 105). Во второй строке задаются n чисел первого массива, отсортированного по неубыванию, а в третьей строке — k чисел второго массива. Каждое число в обоих массивах по модулю не превосходит 2·109 .

Выходные данные
Для каждого из k чисел выведите в отдельную строку число из первого массива, наиболее близкое к данному. Если таких несколько, выведите меньшее из них.
*/

// L3, task: A, DS-12 Naumovskiy Alexey
#include <iostream>
#include <vector>
 
void fill_vector(std::vector<int>& my_vector) {
    for (std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it) {
        std::cin >> *it;
    }
}
 
void print_vector(std::vector<int>& my_vector) {
    for (std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it) {
        std::cout << *it << " ";
    }
}
 
int bin_search_close(std::vector<int>& my_vector, int idx_left, int idx_right, int search_value) {
    if (idx_left == idx_right - 1) {
        //дошли двоичным поиском до 1го элемента. Выбираем наименьший из ближайших:
        if (abs(my_vector[idx_right] - search_value) < abs(my_vector[idx_left] - search_value))
            return my_vector[idx_right];
        else  return my_vector[idx_left];
    }
    int idx_middle = (idx_left + idx_right) / 2;
    if (search_value == my_vector[idx_middle]) return my_vector[idx_middle];
    if (search_value < my_vector[idx_middle]) {
        return bin_search_close(my_vector, idx_left, idx_middle, search_value);
    }
    else return bin_search_close(my_vector, idx_middle, idx_right, search_value);
}
 
int main() {
    int first_arr_size, second_arr_size;
    std::cin >> first_arr_size >> second_arr_size;
    std::vector <int> first_vector(first_arr_size);
    std::vector <int> second_vector(second_arr_size);
    fill_vector(first_vector);
    fill_vector(second_vector);
 
    for (int i = 0; i < second_arr_size; ++i) {
        // проверяем что элемент принадлежит массиву. Если нет, то он: 
        if (second_vector[i] <= first_vector[0]) { //ближе к первому
            std::cout << first_vector[0]<< std::endl; 
            continue; 
        }
        if (second_vector[i] >= first_vector[first_arr_size - 1]) {//либо, ближе к последнему
            std::cout << first_vector[first_arr_size - 1] << std::endl; 
            continue; 
        }
        std::cout << bin_search_close(first_vector, 0, first_arr_size, second_vector[i]) << std::endl;
    }
}

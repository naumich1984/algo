/*
B. Сортировка подсчетом
ограничение по времени на тест1 секунда
ограничение по памяти на тест64 мегабайта
вводстандартный ввод
выводстандартный вывод
Дан список из N элементов, которые принимают целые значения от 0 до 100. Отсортируйте этот список в порядке неубывания элементов. Выведите полученный список.

Входные данные
На одной строке дан массив из N элементов. (1 ≤ N ≤ 2·105) — количество элементов в массиве. Гарантируется, что все элементы массива принимают целые значения от 0 до 100.

Выходные данные
Выведите отсортированный список элeментов
*/

// L2, task: B, DS-12 Naumovskiy Alexey
#include <iostream>
#include <vector>
 
void fill_vector(std::vector<int>& my_vector) {
    int buff;
    while (std::cin >> buff) {
        my_vector.push_back(buff);
    }
}
 
void fill_count_stats(std::vector<int>& my_vector, std::vector<int>& cnt_vector) {
    for (std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it) {
        cnt_vector[*it]++;
    }
}
 
void print_vector(std::vector<int>& my_vector) {
    for (std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it) {
        std::cout << *it << " ";
    }
}
 
void sort_by_count(std::vector<int>& my_vector, std::vector<int>& cnt_vector,const int MAX_ELEMENT) {
    fill_count_stats(my_vector, cnt_vector);
    int idx_main = 0;
    for (int j = 0; j < MAX_ELEMENT; j++) { 
        while (cnt_vector[j] > 0) { 
            my_vector[idx_main++] = j;
            cnt_vector[j]--;
        }
    }
}
 
int main() {
    std::vector <int> my_vector;
    const int MAX_ELEMENT = 2 * pow(10, 5);
    std::vector <int> cnt_vector(MAX_ELEMENT + 1);
 
    fill_vector(my_vector);
    sort_by_count(my_vector, cnt_vector, MAX_ELEMENT);
    print_vector(my_vector);
    return 0;
}
 

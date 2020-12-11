/*
B. Быстрый поиск в массиве
ограничение по времени на тест1 секунда
ограничение по памяти на тест512 мегабайт
вводстандартный ввод
выводстандартный вывод
Дан массив из n целых чисел. Все числа от −109 до 109.

Нужно уметь отвечать на запросы вида «Cколько чисел имеют значения от l до r»?

Входные данные
Число n (1≤n≤105). Далее n целых чисел.

Затем число запросов k (1≤k≤105).

Далее k пар чисел l,r (−109≤l≤r≤109) — собственно запросы.

Выходные данные
Выведите k чисел — ответы на запросы.
*/

// L3, task: B, DS-12 Naumovskiy Alexey
#include <iostream>
#include <vector>
#include <algorithm>
 
void fill_vector(std::vector<int>& my_vector) {
    for (std::vector<int>::iterator it = my_vector.begin(); it != my_vector.end(); ++it) {
        std::cin >> *it;
    }
}
 
// lower_bound без рекурсии
int lower_bound(std::vector<int>& my_vector, int search_value) {
    int idx_left = -1;                      
    int idx_right = my_vector.size();
    while (idx_left < idx_right - 1) {                
        int idx_middle = (idx_left + idx_right) / 2;            
        if (search_value <= my_vector[idx_middle])
            idx_right = idx_middle;
        else
            idx_left = idx_middle;
    }                 
    return idx_right;
}
 
int main() {
    int arr_size, cnt_requests;
    std::cin >> arr_size;
    std::vector <int> first_vector(arr_size);
    fill_vector(first_vector);
    std::cin >> cnt_requests;
    //упорядочиваем массив
    std::sort(first_vector.begin(), first_vector.end());
    //обрабатываем все запросы:
    for (int i = 0; i < cnt_requests; ++i) {
        int left_value, right_value;
        std::cin >> left_value >> right_value;
        // находим границы и считаем количество элементов в этих границах 
        int idx_left = lower_bound(first_vector,  left_value);
        int idx_right = lower_bound(first_vector,  right_value + 1); //выражаем upper через lower
        std::cout << (idx_right - idx_left) << " " << std::endl;
    }
    return 0;
}
 

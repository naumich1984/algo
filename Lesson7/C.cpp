/*
C. RSQ
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Входные данные
В первой строке находится число n — размер массива. (1 ≤ n ≤ 500 000) Во второй строке находится n чисел ai — элементы массива. Далее содержится описание операций, их количество не превышает 1 000 000. В каждой строке находится одна из следующих операций:

set i x — установить a[i] в x.
sum i j — вывести значение суммы элементов в массиве на отрезке с i по j, гарантируется, что (1 ≤ i ≤ j ≤ n).
Все числа во входном файле и результаты выполнения всех операций не превышают по модулю 1018.
Выходные данные
Выведите последовательно результат выполнения всех операций sum. Следуйте формату выходного файла из примера.
*/

// L7, task: C, DS-12 Naumovskiy Alexey
#include <iostream>
#include <vector>
#include <string>

//функция Фенвика:
long long fenwick_func(long long idx_to_fenwick) {
    return (idx_to_fenwick & (idx_to_fenwick + 1));
}

//добавление элемента в дерево Фенвика:
void add(long long idx_add, long long new_value, std::vector<long long>& fenwick) {
    while (idx_add < fenwick.size()) {
        fenwick[idx_add] += new_value;
        idx_add |= (idx_add + 1);
    }
}

//обновление iго элемента новым new_value значением:
void set(long long idx_update, long long new_value, std::vector<long long>& array_input,
        std::vector<long long>& fenwick) {
    long long d = new_value - array_input[idx_update];
    array_input[idx_update] = new_value;
    add(idx_update, d, fenwick);
}

long long get_one_sum(long long idx_get_sum, std::vector<long long>& fenwick) {
    long long result_sum = 0;
    while (idx_get_sum >= 0) {
        result_sum += fenwick[idx_get_sum];
        idx_get_sum = fenwick_func(idx_get_sum) - 1;
    }
    return result_sum;
}

//получение RSQ:
long long get_rsq(long long l_bound, long long r_bound, std::vector<long long>& fenwick) {
    if (l_bound == 0) return get_one_sum(r_bound - 1, fenwick);
    return get_one_sum(r_bound - 1, fenwick) - get_one_sum(l_bound - 2, fenwick);
}

//создаем дерево Фенвика:
void create_fenwick(std::vector<long long>& array_input, std::vector<long long>& fenwick) {
    for (long long i = 0; i < array_input.size(); i++) { 
        add(i, array_input[i], fenwick); 
    }
}

void fill_array_input(std::vector <long long>& array_input, long long len_array) {
    long long buff;
    for (long long i = 0; i < len_array; i++) {
        std::cin >> buff;
        array_input[i] = buff;
    }
}

//обработка потока команд:
void processing_command(std::vector <long long>& array_input, std::vector <long long>& fenwick) {
    long long l_bound;
    long long r_bound;
    long long i_to_set;
    long long new_value;
    std::string current_command = "";
    while (std::cin >> current_command) {
        if (current_command.compare("sum") == 0) {
            std::cin >> l_bound >> r_bound;
            std::cout << get_rsq(l_bound, r_bound, fenwick) << std::endl;
        } else if (current_command.compare("set") == 0) {
            std::cin >> i_to_set >> new_value;
            set(i_to_set - 1, new_value, array_input, fenwick);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    long long len_array;
    std::cin >> len_array;
    std::vector<long long> array_input(len_array);
    std::vector<long long> fenwick(len_array, 0);
    fill_array_input(array_input, len_array);
    create_fenwick(array_input, fenwick);
    processing_command(array_input, fenwick);
    return 0;
}

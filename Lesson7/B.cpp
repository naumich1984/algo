/*
B. Разреженные таблицы
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Дан массив из n чисел. Требуется написать программу, которая будет отвечать на запросы следующего вида: найти минимум на отрезке между u и v включительно.

Входные данные
В первой строке зданы три натуральных числа n, m (1⩽n⩽105, 1⩽m⩽107) и a1 (0⩽a1<16714589) — количество элементов в массиве, количество запросов и первый элемент массива соответственно. Вторая строка содержит два натуральных числа u1 и v1 (1⩽u1,v1⩽n) — первый запрос.

Для того, размер ввода был небольшой, массив и запросы генерируются.

Элементы a2,a3,…,an задаются следующей формулой:
ai+1=(23⋅ai+21563)mod16714589.
Например, при n=10, a1=12345 получается следующий массив: a = (12345, 305498, 7048017, 11694653, 1565158, 2591019, 9471233, 570265, 13137658, 1325095).

Запросы генерируются следующим образом:

ui+1=((17⋅ui+751+ri+2i)modn)+1, vi+1=((13⋅vi+593+ri+5i)modn)+1,
где ri — ответ на запрос номер i.
Обратите внимание, что ui может быть больше, чем vi.

Выходные данные
В выходной файл выведите um, vm и rm (последний запрос и ответ на него).
*/

// L7, task: B, DS-12 Naumovskiy Alexey
#include <iostream>
#include <vector>
#include <cmath>

//обработка запроса
int query(int l_bound, int r_bound, std::vector<std::vector<int>>& min_vector,
    std::vector<int>& max_pow_vector) {
    l_bound--;
    r_bound--;
    if (l_bound > r_bound) {
        int buff = l_bound;
        l_bound = r_bound;
        r_bound = buff;
    }
    int max_pow = max_pow_vector[r_bound - l_bound + 1];
    return std::min(min_vector[l_bound][max_pow], min_vector[r_bound - (1 << max_pow) + 1][max_pow]);
}

//формирование списка степеней двойки(используем для ответа на запросы):
void fill_max_pow_vector(std::vector<int>& max_pow_vector, int len_array) {
    max_pow_vector[1] = 0;
    for (auto i = 2; i <= len_array; i++)
        max_pow_vector[i] = max_pow_vector[i / 2] + 1;
}

void fill_array_input_vector(std::vector<int>& array_input, int len_array,
    int first_array_element) {
    const int C_16714589 = 16714589;
    const int C_21563 = 21563;
    const int C_23 = 23;
    array_input[0] = first_array_element;
    for (auto i = 1; i < len_array; ++i) {
        array_input[i] = (C_23 * array_input[i - 1] + C_21563) % C_16714589;
    }
}

//Предподсчет за nlogn:
void fill_min_matrix_vector(std::vector<int>& array_input, std::vector<std::vector<int>>& min_vector,
    int len_array, int nlong_len_array) {
    for (auto i = 0; i < len_array; i++)  min_vector[i][0] = array_input[i];
    array_input.clear();
    for (auto j = 1; j <= nlong_len_array; j++)
        for (auto i = 0; (i + (1 << j) - 1) < len_array; i++)
            min_vector[i][j] = std::min(min_vector[i][j - 1], min_vector[i + (1 << (j - 1))][j - 1]);
}

void generate_reuqests_and_get_last(std::vector<std::vector<int>>& min_vector, std::vector<int>& max_pow_vector,
    int first_u_bound, int first_v_bound, int count_requests, int len_array) {
    const int C_751 = 751;
    const int C_593 = 593;
    const int C_17 = 17;
    const int C_13 = 13;
    const int C_2 = 2;
    const int C_5 = 5;
    int prev_u_bound = first_u_bound;
    int prev_v_bound = first_v_bound;
    int prev_request = query(prev_u_bound, prev_v_bound, min_vector, max_pow_vector);
    for (auto i = 1; i < count_requests; ++i) {
        int cur_u_bound = ((C_17 * (prev_u_bound)+C_751 + prev_request + C_2 * i) % len_array) + 1;
        int cur_v_bound = ((C_13 * (prev_v_bound)+C_593 + prev_request + C_5 * i) % len_array) + 1;
        prev_request = query(cur_u_bound, cur_v_bound, min_vector, max_pow_vector);
        prev_u_bound = cur_u_bound;
        prev_v_bound = cur_v_bound;
    }
    std::cout << prev_u_bound << ' ' << prev_v_bound << ' ' << prev_request << std::endl;
}

void clear(std::vector<std::vector<int>>& min_vector, std::vector<int>& max_pow_vector,
    std::vector<int>& array_input) {
    max_pow_vector.clear();
    min_vector.clear();
    array_input.clear();
}

int main() {
    int len_array;
    int count_requests;
    int first_array_element;
    int first_u_bound;
    int first_v_bound;
    std::cin >> len_array >> count_requests >> first_array_element;
    std::cin >> first_u_bound >> first_v_bound;
    int nlong_len_array = (int)floor(log2(len_array));
    std::vector<int> array_input(len_array);
    //матрица для хранения предподсчета(размер N x NlogN)
    std::vector<std::vector<int>> min_vector(len_array, std::vector<int>(nlong_len_array + 1)); 
    std::vector<int> max_pow_vector(len_array + 1);
    fill_max_pow_vector(max_pow_vector, len_array);
    fill_array_input_vector(array_input, len_array, first_array_element);
    fill_min_matrix_vector(array_input, min_vector, len_array, nlong_len_array);
    generate_reuqests_and_get_last(min_vector, max_pow_vector, first_u_bound, first_v_bound, count_requests, len_array);
    clear(min_vector, max_pow_vector, array_input);
    return 0;
}

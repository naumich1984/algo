/*
A. Сумма простая
ограничение по времени на тест1 секунда
ограничение по памяти на тест512 мегабайт
вводстандартный ввод
выводстандартный вывод
Вам нужно научиться отвечать на запрос «сумма чисел на отрезке».

Массив не меняется. Запросов много. Отвечать на каждый запрос следует за .

Входные данные
Размер массива — n и числа x, y, a0, порождающие массив a: 

Далее следует количество запросов m и числа z, t, b0, порождающие массив b: .

Массив c строится следующим образом: .

Запросы: i-й из них — найти сумму на отрезке от min(c2i, c2i + 1) до max(c2i, c2i + 1) в массиве a.

Ограничения: 1 ≤ n ≤ 107, 0 ≤ m ≤ 107. Все числа целые от 0 до 216. t может быть равно  - 1.

Выходные данные
Выведите сумму всех сумм.
*/

// L7, task: A, DS-12 Naumovskiy Alexey
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

class OriginalArray {
    long long array_len;
    long long x_value;
    long long y_value;
    long long first_element;
    long long requests_count;
    long long z_value;
    long long t_value;
    long long b_first_element;
    const long long CONST_SUMS = (long long)pow(2, 16);
    const long long CONST_REQUESTS = (long long)pow(2, 30);
    std::vector<long long> sum_vector;
    std::vector<long long> request_vector;
    void fill_sums_vector();
    void fill_requests_vector();

 public:
    OriginalArray(long long array_len, long long x_value, long long y_value, long long first_element,
                 long long requests_count, long long z_value, long long t_value, long long b_first_element);
    ~OriginalArray();
    long long get_full_sum_requests();
    long long get_rsq(long long l_bound, long long r_bound) {
        if (l_bound == 0) {
            return sum_vector[r_bound];
        }
        return (sum_vector[r_bound] - sum_vector[l_bound - 1]);
    }
};

void OriginalArray::fill_sums_vector() {
    long long prev_element = first_element;
    sum_vector[0] = first_element;
    for (int i = 1; i < array_len; ++i) {
        long long cur_element = (x_value * prev_element + y_value) % CONST_SUMS;
        sum_vector[i] = sum_vector[i - 1] + cur_element;
        prev_element = cur_element;
    }
}

void OriginalArray::fill_requests_vector() {
    if (requests_count > 0) {
        int request_bounds_count = requests_count * 2;
        long long prev_element = b_first_element;
        for (int i = 1; i < request_bounds_count; ++i) {
            long long sum_intermediate = (z_value * prev_element + t_value);
            long long cur_element = (sum_intermediate % CONST_REQUESTS + CONST_REQUESTS) % CONST_REQUESTS;
            request_vector[i - 1] = prev_element % array_len;
            prev_element = cur_element;
        }
        request_vector[request_bounds_count - 1] = prev_element % array_len;
    }
}

long long OriginalArray::get_full_sum_requests() {
    long long result_sum = 0;
    if (requests_count == 0) return 0;
    int request_bounds_count = requests_count * 2;
    for (int i = 0; i < request_bounds_count; i = i + 2) {
        result_sum = result_sum + get_rsq(std::min(request_vector[i + 1], request_vector[i]),
                                         std::max(request_vector[i + 1], request_vector[i]));
    }
    return result_sum;
}

OriginalArray::OriginalArray(long long array_len, long long x_value, long long y_value, long long first_element,
                    long long requests_count, long long z_value, long long t_value, long long b_first_element) {
    this->array_len = array_len;
    this->x_value = x_value;
    this->y_value = y_value;
    this->first_element = first_element;
    this->requests_count = requests_count;
    this->z_value = z_value;
    this->t_value = t_value;
    this->b_first_element = b_first_element;
    sum_vector = std::vector<long long>(array_len);
    request_vector = std::vector<long long>(requests_count * 2);
    fill_sums_vector();
    fill_requests_vector();
}

OriginalArray::~OriginalArray() {
    sum_vector.clear();
    request_vector.clear();
}

int main() {
    long long original_array_len;
    long long x_value;
    long long y_value;
    long long first_element;
    long long requests_count;
    long long z_value;
    long long t_value;
    long long b_first_element;
    std::cin >> original_array_len >> x_value >> y_value >> first_element;
    std::cin >> requests_count >> z_value >> t_value >> b_first_element;
    OriginalArray my_array(original_array_len, x_value, y_value, first_element, requests_count, z_value, t_value, b_first_element);
    std::cout << my_array.get_full_sum_requests();
    return 0;
}



// L14, task: A, DS-12 Naumovskiy Alexey
/*
A. Сравнения подстрок
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Дана строка s. Ответьте на m запросов вида: равны ли подстроки s[a..b] и s[c..d].

Входные данные
В первой строке ввода записана строка s (1 ≤ |s| ≤ 105).

Во второй строке записано целое число m — количество запросов (0 ≤ m ≤ 105).

В следующих m строках четверки чисел a, b, c, d (1 ≤ a ≤ b ≤ |s|, 1 ≤ c ≤ d ≤ |s|).

Выходные данные
Выведите m строк. Выведите Yes, если подстроки совпадают, и No иначе.
*/
#include <iostream>
#include <vector>
#include <string>

class CompareSubs {
    std::string full_string;
    int request_count;
    const long long P_HASH_TUNE = 199999991;
    std::vector<unsigned long long> vector_pow;
    std::vector<unsigned long long> vector_hash;
    unsigned long long get_hash(int idx_left, int idx_right);
    bool compare_subs(int idx_left_first, int idx_right_first, int idx_left_second, int idx_right_second);
    void init();
    void clear();

public:
    CompareSubs();
    ~CompareSubs() { clear(); };
    void compare_by_requests();
};

CompareSubs::CompareSubs() {
    std::string full_string;
    int request_count;
    std::cin >> full_string;
    std::cin >> request_count;
    this->full_string = full_string;
    this->request_count = request_count;
    vector_hash = std::vector<unsigned long long>(full_string.length() + 1);
    vector_pow = std::vector<unsigned long long>(full_string.length() + 1);
}

void CompareSubs::clear() {
    vector_pow.clear();
    vector_hash.clear();
}

unsigned long long CompareSubs::get_hash(int idx_left, int idx_right) {
    return vector_hash[idx_right + 1] - vector_hash[idx_left] * vector_pow[idx_right - idx_left + 1];
}

bool CompareSubs::compare_subs(int idx_left_first, int idx_right_first, int idx_left_second, int idx_right_second) {
    return get_hash(idx_left_first, idx_right_first) == get_hash(idx_left_second, idx_right_second);
}

void CompareSubs::init() {
    vector_hash[0] = 0;
    vector_pow[0] = 1;
    for (int i = 0; i < full_string.length(); ++i) {
        vector_hash[i + 1] = vector_hash[i] * P_HASH_TUNE + full_string[i];
        vector_pow[i + 1] = vector_pow[i] * P_HASH_TUNE;
    }
}

void CompareSubs::compare_by_requests() {
    init();
    for (int i = 0; i < request_count; ++i) {
        int idx_left_first;
        int idx_right_first;
        int idx_left_second;
        int idx_right_second;
        std::cin >> idx_left_first >> idx_right_first >> idx_left_second >> idx_right_second;
        idx_left_first--;
        idx_right_first--;
        idx_left_second--;
        idx_right_second--;
        std::cout << (compare_subs(idx_left_first, idx_right_first, idx_left_second, idx_right_second) ? "Yes\n" : "No\n");
    }
}

int main() {
    CompareSubs current_compare;
    current_compare.compare_by_requests();
    return 0;
}
